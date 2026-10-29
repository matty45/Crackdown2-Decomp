"""The built-in benchmark agent: any chat model, through any OpenAI-compatible API, sandboxed by construction.

Used by `cd2.py bench run --agent chat:<model> --model <name>`; it runs in the task's workspace (CD2_WORKSPACE) and
uses only the standard library.

The model never touches the file system or a shell. Each reply either asks for files from the workspace (a line
`READ <path>`; paths outside the workspace are refused) or gives the function's body in a code block. The agent splices
the body into the workspace's file, runs the task's check (CD2_CHECK) and sends the result back. It stops at EXACT,
after --rounds replies, or when a reply has neither. Every model gets the same scaffold, so results compare fairly.

Configuration (environment):
  CD2_LLM_BASE_URL   the API's base URL (default https://api.openai.com/v1). Examples:
                       OpenAI      https://api.openai.com/v1
                       Anthropic   https://api.anthropic.com/v1/
                       Gemini      https://generativelanguage.googleapis.com/v1beta/openai/
                       OpenRouter  https://openrouter.ai/api/v1
                       DeepSeek    https://api.deepseek.com/v1
                       Ollama      http://localhost:11434/v1        (local models; no key)
                       LM Studio   http://localhost:1234/v1         (local models; no key)
  CD2_LLM_API_KEY    the API key (sent as a bearer token; not needed by local servers)
  CD2_LLM_OPTIONS    a JSON object merged into every request, e.g. {"temperature": 0, "max_tokens": 8000}

usage: py -I tools/bench_chat.py <model> [--rounds N]
"""
import json, os, re, subprocess, sys, time, urllib.error, urllib.request

TOOLS = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, TOOLS)
import bench  # noqa: E402
import search  # noqa: E402

SYSTEM = """You are taking part in a matching-decompilation benchmark. Crackdown 2 (Xbox 360, PowerPC) was compiled with \
the Xbox 360 XDK's MSVC compiler (15.00.8153, /Ox /Ob1 /Gy /GF /GR- /GS- /fp:fast). Your task: write the C++ body of \
one function so that it compiles to exactly the game's machine code, which the task shows.

Each of your replies must do exactly one of these:
1. Ask for files: one or more lines `READ <path>`, with paths relative to the task directory (for example \
`READ docs/matching-notes.md` or `READ include/AI/cChaseBehaviour.h`). You get their contents back.
2. Give the function's body: ONLY the code between the function's braces, in one ```cpp code block. It replaces the \
body, is compiled and compared, and you get the result back.

Rules: no inline assembly, no __emit, no #pragma, no #line, no #include, and no pointer arithmetic (a cast to \
char * plus an offset, a pointer turned into an integer, a hard-coded address): the check rejects them. Use the members \
and globals the headers declare, by name. Write code a developer would have written. If you cannot improve further, reply STOP."""

MAX_FILE = 60000  # characters of one file sent back


def api(messages, model):
    base = os.environ.get('CD2_LLM_BASE_URL', 'https://api.openai.com/v1').rstrip('/')
    body = dict(model=model, messages=messages)
    body.update(json.loads(os.environ.get('CD2_LLM_OPTIONS') or '{}'))
    headers = {'Content-Type': 'application/json'}
    if os.environ.get('CD2_LLM_API_KEY'):
        headers['Authorization'] = 'Bearer ' + os.environ['CD2_LLM_API_KEY']
    req = urllib.request.Request(base + '/chat/completions', data=json.dumps(body).encode(), headers=headers)
    for attempt in range(4):
        try:
            with urllib.request.urlopen(req, timeout=600) as r:
                data = json.loads(r.read().decode('utf-8'))
            return data['choices'][0]['message'].get('content') or '', data.get('usage') or {}
        except urllib.error.HTTPError as e:
            if e.code in (429, 500, 502, 503, 529) and attempt < 3:
                time.sleep(10 * (attempt + 1))
                continue
            raise SystemExit('API error %d: %s' % (e.code, e.read().decode('utf-8', 'replace')[:2000]))
        except (urllib.error.URLError, ConnectionError, TimeoutError, OSError) as e:  # refused, reset, timed out
            if attempt < 3:
                time.sleep(2 * (attempt + 1))
                continue
            raise SystemExit('API unreachable: %s' % e)


def read_request(ws, reply):
    """The files a reply asks for, as one message; paths outside the workspace are refused."""
    out = []
    for path in re.findall(r'^\s*READ\s+(\S+)\s*$', reply, re.M)[:8]:
        full = os.path.normcase(os.path.abspath(os.path.join(ws, path)))
        try:
            inside = os.path.commonpath([full, os.path.normcase(ws)]) == os.path.normcase(ws)
        except ValueError:  # another drive
            inside = False
        if not inside:
            out.append('%s: refused (outside the task directory)' % path)
        elif not os.path.isfile(full):
            out.append('%s: no such file' % path)
        else:
            text = open(full, encoding='utf-8', errors='replace').read()
            out.append('=== %s ===\n%s%s' % (path, text[:MAX_FILE], '\n[... cut]' if len(text) > MAX_FILE else ''))
    return '\n\n'.join(out)


def body_of(reply, name):
    """The code block of a reply as a body; a whole function definition is reduced to its body."""
    m = re.search(r'```[a-zA-Z+]*\n(.*?)```', reply, re.S)
    if not m:
        return None
    code = m.group(1).strip()
    head = code.split('{', 1)[0]
    # a function header names the function and has no statement (no ';') and no control keyword before its brace
    if (re.search(r'\b%s\s*\(' % re.escape(name), head) and ';' not in head and code.endswith('}')
            and not re.match(r'\s*(if|for|while|switch|do|else|return)\b', head)):
        code = code[code.index('{') + 1:-1]
    return '\n' + '\n'.join('        ' + line if line.strip() else '' for line in code.strip('\n').split('\n')) + '\n    '


def listing(ws):
    files = []
    for dp, _, fs in os.walk(ws):
        for f in fs:
            p = os.path.relpath(os.path.join(dp, f), ws).replace('\\', '/')
            files.append('%s (%d bytes)' % (p, os.path.getsize(os.path.join(dp, f))))
    return '\n'.join(sorted(files))


def main():
    if len(sys.argv) < 2 or sys.argv[1].startswith('-'):
        print(__doc__)
        return 2
    model = sys.argv[1]
    rounds = int(sys.argv[sys.argv.index('--rounds') + 1]) if '--rounds' in sys.argv else 12
    ws = os.path.abspath(os.environ['CD2_WORKSPACE'])
    path, file, symbol = bench._task_file(ws)
    name, _ = search.demangle_name(symbol)
    task = open(os.path.join(ws, 'TASK.md'), encoding='utf-8').read()
    task = re.sub(r'Check your work with this command.*?\n\n    .*?\n\n', '', task, flags=re.S)  # we run the check
    messages = [dict(role='system', content=SYSTEM),
                dict(role='user', content='%s\n\n=== %s (the body to write is marked TODO) ===\n%s\n\nFiles in the '
                     'task directory:\n%s' % (task, file, open(path, encoding='utf-8').read(), listing(ws)))]
    usage = dict(prompt_tokens=0, completion_tokens=0, requests=0)
    for r in range(rounds):
        reply, u = api(messages, model)
        usage['requests'] += 1
        for k in ('prompt_tokens', 'completion_tokens'):
            usage[k] += u.get(k) or 0
        print('--- reply %d ---\n%s\n' % (r + 1, reply), flush=True)
        messages.append(dict(role='assistant', content=reply))
        body = body_of(reply, name)
        if body is None:
            files = read_request(ws, reply)
            if not files:
                break  # STOP, or nothing usable
            messages.append(dict(role='user', content=files))
            continue
        text = open(path, encoding='utf-8', newline='').read()
        s, e = search.find_body(text, symbol)
        open(path, 'w', encoding='utf-8', newline='').write(text[:s] + body + text[e:])
        out = subprocess.run(os.environ['CD2_CHECK'] + ' --json', shell=True, cwd=ws, capture_output=True, text=True)
        try:
            res = json.loads(out.stdout)
        except ValueError:
            res = dict(status='check failed', detail=(out.stdout + out.stderr)[-2000:])
        status = res.get('status') or res.get('error') or '?'
        print('--- check %d: %s ---' % (r + 1, status), flush=True)
        if res.get('exact'):
            break
        messages.append(dict(role='user', content='Check: %s (%s of %s instruction words match).\n%s' % (
            status, res.get('words', 0), res.get('of', '?'), (res.get('detail') or '')[:3000])))
    rp = bench.result_path(int(os.path.basename(ws), 16), os.path.basename(os.path.dirname(ws)))
    rec = json.load(open(rp))
    rec['usage'] = usage
    json.dump(rec, open(rp, 'w'), indent=1)
    print('usage: %s' % usage)
    return 0


if __name__ == '__main__':
    sys.exit(main())
