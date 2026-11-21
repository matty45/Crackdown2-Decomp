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
                       Kilo        https://api.kilo.ai/api/gateway  (its free models: 200 requests an hour per IP)
  CD2_LLM_API_KEY    the API key (sent as a bearer token; not needed by local servers)
  CD2_LLM_OPTIONS    a JSON object merged into every request, e.g. {"temperature": 0, "max_tokens": 8000}
  CD2_LLM_RATE_PER_HOUR
                     at most this many requests in any 60 minutes, across every agent process: each request is logged
                     in CD2_LLM_RATE_LOG (default <bench dir>/llm_requests.jsonl, under a lock), and a request that
                     would exceed the limit waits until the oldest one leaves the window. Unset: no limit.
  CD2_LLM_MAX_WAIT   seconds a task may wait out rate limits (HTTP 429) before it gives up (default 900). The wait
                     honours Retry-After or X-RateLimit-Reset, else backs off 1, 2, 5, 10, 15, 30, 60 minutes. A task
                     that gives up is marked rate_limited: not scored; `bench run` sets it aside, lets its model cool
                     down and runs it again later (and `--resume` does in a later run).

usage: py -I tools/bench_chat.py <model> [--rounds N] [--tools]
  --tools  the same protocol as native function calls (read_file, grep, submit_body, stop), for models trained to
           act through tools: without it they write tool calls in their own markup, or end their turn with empty
           content when the request defines none
"""
import email.utils, json, os, re, subprocess, sys, time, urllib.error, urllib.request

TOOLS = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, TOOLS)
import bench  # noqa: E402
import search  # noqa: E402

INTRO = """You are taking part in a matching-decompilation benchmark. Crackdown 2 (Xbox 360, PowerPC) was compiled with \
the Xbox 360 XDK's MSVC compiler (15.00.8153, /Ox /Ob1 /Gy /GF /GR- /GS- /fp:fast). Your task: write the C++ body of \
one function so that it compiles to exactly the game's machine code, which the task shows.

"""
RULES = """Rules: no inline assembly, no __emit, no #pragma, no #line, no #include, and no pointer arithmetic (a cast to \
char * plus an offset, a pointer turned into an integer, a hard-coded address), and no fake code (volatile or unused \
locals, empty statements or blocks, do {} while (0), self-assignments, + 0): the check rejects them. Use the members \
and globals the headers declare, by name. Write code a developer would have written. """
SYSTEM = INTRO + """Each of your replies must do exactly one of these:
1. Ask for files: one or more lines `READ <path>`, with paths relative to the task directory (for example \
`READ docs/matching-notes.md` or `READ include/AI/cChaseBehaviour.h`). You get their contents back.
2. Give the function's body: ONLY the code between the function's braces, in one ```cpp code block. It replaces the \
body, is compiled and compared, and you get the result back.

""" + RULES + "If you cannot improve further, reply STOP."
# --tools: the same protocol as native function calls, for models trained to act only through tools (they end their
# turn with empty content when the request defines none)
SYSTEM_TOOLS = INTRO + """Work through the tools: read_file reads a file of the task directory (for example \
docs/matching-notes.md or include/AI/cChaseBehaviour.h); grep searches its files; submit_body replaces the function's \
body with your code (ONLY the code between the function's braces), compiles and compares it, and returns the result. \
There is no shell.

""" + RULES + "If you cannot improve further, call stop."
TOOLS = [
    dict(type='function', function=dict(
        name='read_file', description='Read a file of the task directory.',
        parameters=dict(type='object', properties=dict(path=dict(type='string', description='relative to the task '
                                                                  'directory')), required=['path']))),
    dict(type='function', function=dict(
        name='submit_body', description="Replace the function's body with this code (only the code between the "
                                        "function's braces), compile it and compare it with the game's code.",
        parameters=dict(type='object', properties=dict(code=dict(type='string')), required=['code']))),
    dict(type='function', function=dict(
        name='grep', description='Search the files of the task directory for a regular expression: the matching '
                                 'lines, as path:line: text.',
        parameters=dict(type='object', properties=dict(
            pattern=dict(type='string'),
            path=dict(type='string', description='a file or directory of the task directory (default: all of it)')),
            required=['pattern']))),
    dict(type='function', function=dict(
        name='stop', description='Give up: you cannot improve further.',
        parameters=dict(type='object', properties={}))),
]

MAX_FILE = 60000  # characters of one file sent back
REMINDER = ('Your reply had neither READ lines nor a ```cpp code block, so nothing was done. Reply with one or more '
            'lines `READ <path>` (plain text, one path per line), or with the function\'s body in one ```cpp code '
            'block, or with STOP.')
REMINDER_TOOLS = 'Your reply called no tool, so nothing was done. Call read_file, grep, submit_body or stop.'

BACKOFF = (60, 120, 300, 600, 900, 1800, 3600)  # seconds between tries after a 429 that says nothing about when
RATE_LIMITED = 75  # the exit status of a task that gave up waiting out rate limits (EX_TEMPFAIL)


class RateLimited(Exception):
    """The API kept refusing (HTTP 429) for longer than CD2_LLM_MAX_WAIT."""


class FileLock:
    """An exclusive lock on a file, shared by every process that opens the same path."""

    def __init__(self, path):
        self.path = path

    def __enter__(self):
        os.makedirs(os.path.dirname(self.path) or '.', exist_ok=True)
        self.f = open(self.path, 'a+b')
        if os.name == 'nt':
            import msvcrt
            while True:
                try:
                    self.f.seek(0)
                    msvcrt.locking(self.f.fileno(), msvcrt.LK_LOCK, 1)  # retries for 10 s itself, then raises
                    break
                except OSError:
                    time.sleep(0.05)
        else:
            import fcntl
            fcntl.flock(self.f, fcntl.LOCK_EX)
        return self

    def __exit__(self, *exc):
        if os.name == 'nt':
            import msvcrt
            self.f.seek(0)
            msvcrt.locking(self.f.fileno(), msvcrt.LK_UNLCK, 1)
        else:
            import fcntl
            fcntl.flock(self.f, fcntl.LOCK_UN)
        self.f.close()


def rate_log():
    return os.environ.get('CD2_LLM_RATE_LOG') or os.path.join(bench.BENCH, 'llm_requests.jsonl')


def log_event(event, **fields):
    """Append one event to the request log (under its lock)."""
    path = rate_log()
    with FileLock(path + '.lock'):
        with open(path, 'a', encoding='utf-8') as f:
            f.write(json.dumps(dict(t=time.time(), event=event, pid=os.getpid(), **fields)) + '\n')


def reserve(model, limit=None, now=time.time, sleep=time.sleep):
    """Wait until one more request fits under `limit` requests in any 60 minutes (every process's requests, from the
    log), then log it. Returns the seconds waited. limit None or 0: log the request and do not wait."""
    path = rate_log()
    waited = 0.0
    while True:
        with FileLock(path + '.lock'):
            t = now()
            times = []
            if limit and os.path.exists(path):
                with open(path, encoding='utf-8') as f:
                    for line in f:
                        try:
                            e = json.loads(line)
                        except ValueError:
                            continue
                        if e.get('event') == 'request' and t - e['t'] < 3600:
                            times.append(e['t'])
            if not limit or len(times) < limit:
                with open(path, 'a', encoding='utf-8') as f:
                    f.write(json.dumps(dict(t=t, event='request', pid=os.getpid(), model=model)) + '\n')
                return waited
            times.sort()
            delay = max(times[-limit] + 3600 - t, 1.0)  # until enough of the window's oldest requests leave it
        sleep(delay)
        waited += delay


def retry_delay(headers, now=time.time):
    """The seconds a 429 response asks to wait (Retry-After, X-RateLimit-Reset), or None."""
    v = headers.get('Retry-After')
    if v:
        try:
            return max(float(v), 0.0)
        except ValueError:
            try:
                return max(email.utils.parsedate_to_datetime(v).timestamp() - now(), 0.0)
            except (TypeError, ValueError):
                pass
    v = headers.get('X-RateLimit-Reset')  # an email.message.Message: names are not case-sensitive
    if v:
        try:
            x = float(v)
        except ValueError:
            return None
        if x > 1e12:  # an epoch time in milliseconds
            x = x / 1000 - now()
        elif x > 1e9:  # an epoch time in seconds
            x -= now()
        return max(x, 0.0)
    return None


def api(messages, model, sleep=time.sleep, tools=None):
    """One chat completion: (text, usage, seconds waited for rate limits, the message). tools: function definitions
    sent with the request. Paced by CD2_LLM_RATE_PER_HOUR; a 429 is waited out (RateLimited after CD2_LLM_MAX_WAIT
    seconds); other server errors and network failures are retried 3 times."""
    base = os.environ.get('CD2_LLM_BASE_URL', 'https://api.openai.com/v1').rstrip('/')
    body = dict(model=model, messages=messages)
    if tools:
        body.update(tools=tools, tool_choice='auto')
    body.update(json.loads(os.environ.get('CD2_LLM_OPTIONS') or '{}'))
    headers = {'Content-Type': 'application/json'}
    if os.environ.get('CD2_LLM_API_KEY'):
        headers['Authorization'] = 'Bearer ' + os.environ['CD2_LLM_API_KEY']
    req = urllib.request.Request(base + '/chat/completions', data=json.dumps(body).encode(), headers=headers)
    limit = int(os.environ.get('CD2_LLM_RATE_PER_HOUR') or 0)
    max_wait = float(os.environ.get('CD2_LLM_MAX_WAIT') or 900)
    waited, refused, failures = 0.0, 0, 0
    while True:
        waited += reserve(model, limit, sleep=sleep)
        try:
            with urllib.request.urlopen(req, timeout=600) as r:
                data = json.loads(r.read().decode('utf-8'))
            if not data.get('choices'):  # an error passed on in a 200 response
                if failures < 3:
                    failures += 1
                    print('--- no completion in the response, retrying: %s ---' % json.dumps(data)[:500], flush=True)
                    sleep(10 * failures)
                    continue
                raise SystemExit('API returned no completion: %s' % json.dumps(data)[:2000])
            message = data['choices'][0]['message']
            return reply_text(message), data.get('usage') or {}, waited, message
        except urllib.error.HTTPError as e:
            if e.code == 429:
                e.close()  # its connection: a long wait must not hold it open
                asked = retry_delay(e.headers)
                delay = asked if asked is not None else BACKOFF[min(refused, len(BACKOFF) - 1)]
                refused += 1
                said = {k: v for k, v in e.headers.items() if k.lower() == 'retry-after' or 'ratelimit' in k.lower()}
                log_event('429', model=model, delay=delay, headers=said)
                if waited + delay > max_wait:
                    raise RateLimited('rate limited (HTTP 429) %d times; waited %d s, the next wait (%d s) would pass '
                                      'CD2_LLM_MAX_WAIT' % (refused, waited, delay))
                print('--- rate limited (HTTP 429): waiting %d s ---' % delay, flush=True)
                sleep(delay)
                waited += delay
                continue
            if e.code in (500, 502, 503, 504, 520, 521, 522, 523, 524, 529) and failures < 3:
                failures += 1
                sleep(10 * failures)
                continue
            raise SystemExit('API error %d: %s' % (e.code, e.read().decode('utf-8', 'replace')[:2000]))
        except (urllib.error.URLError, ConnectionError, TimeoutError, OSError) as e:  # refused, reset, timed out
            if failures < 3:
                failures += 1
                sleep(2 * failures)
                continue
            raise SystemExit('API unreachable: %s' % e)


PATH_LIKE = re.compile(r'^[\w.\-/\\]*(/|\.\w+$)[\w.\-/\\]*$')  # has a directory or an extension


def reply_text(message):
    """A reply's text. Some models answer in structured tool calls although the request defines no tools: a call
    that reads (its name says read, open, view or file) becomes `READ <path>` lines for each path among its arguments,
    and any other call is kept as text. A reply with no content at all is shown with its message's fields, for the
    log."""
    text = message.get('content') or ''
    for call in message.get('tool_calls') or []:
        fn = call.get('function') or {}
        name, args = fn.get('name') or '', fn.get('arguments') or ''
        try:
            parsed = json.loads(args) if args.strip().startswith('{') else {'': args}
            values = [v for v in parsed.values() if isinstance(v, str)]
        except ValueError:
            values = [args]
        paths = [v.strip() for v in values if PATH_LIKE.match(v.strip())]
        if paths and re.search(r'read|open|view|file|cat', name, re.I):
            text += ''.join('\nREAD %s' % v for v in paths)
        else:
            text += '\n%s %s' % (name, args)
    if not text.strip():
        print('--- empty reply; message fields: %s ---' % json.dumps(
            {k: (v[:300] if isinstance(v, str) else v) for k, v in message.items()})[:2000], flush=True)
    return text


READ_WORDS = {'read', 'read_file', 'readfile', 'view', 'view_file', 'open', 'open_file', 'cat'}


def requested_paths(reply):
    """The paths a reply asks for: `READ <path>`, and the tool-call markup models wrap a read in, whatever its dialect
    (`<invoke name="read"><parameter name="path">p</parameter>`, `<Read"><parameter name="file_path">p`,
    `<arg key=READ path=p>`, `<function=READ p </parameter>`, `<tool_call>READ<arg_key>path</arg_key><arg_value>p`):
    the reply is cut into words at spaces, quotes, brackets and equals signs, and after each read word the path is the
    first path-like word of the next six (never one starting with /: a closing tag, or outside the task directory)."""
    words = [w for w in re.split(r'[\s<>="\'`,;()\[\]{}]+', reply) if w]
    out = []
    for i, w in enumerate(words):
        if w.lower() in READ_WORDS:
            path = next((x for x in words[i + 1:i + 7] if PATH_LIKE.match(x) and not x.startswith('/')), None)
            if path and path not in out:
                out.append(path)
    return out


def inside(full, ws):
    """Whether a path lies in the task directory."""
    try:
        return os.path.commonpath([os.path.normcase(full), os.path.normcase(ws)]) == os.path.normcase(ws)
    except ValueError:  # another drive
        return False


def grep(ws, pattern, sub=''):
    """The lines of the task directory's files (under sub) that match a regular expression, or the text if it is not
    one: `path:line: text`, at most 200. A path outside the task directory is refused."""
    root = os.path.abspath(os.path.join(ws, sub or '.'))
    if not inside(root, ws):
        return '%s: refused (outside the task directory)' % sub
    try:
        rx = re.compile(pattern)
    except re.error:
        rx = re.compile(re.escape(pattern))
    files = [root] if os.path.isfile(root) else sorted(os.path.join(dp, f) for dp, _, fs in os.walk(root) for f in fs)
    out = []
    for f in files:
        rel = os.path.relpath(f, ws).replace('\\', '/')
        with open(f, encoding='utf-8', errors='replace') as fh:
            for n, line in enumerate(fh, 1):
                if rx.search(line):
                    out.append('%s:%d: %s' % (rel, n, line.rstrip()[:200]))
                    if len(out) >= 200:
                        return '\n'.join(out) + '\n[... more matches]'
    return '\n'.join(out) or 'no match'


def read_request(ws, reply):
    """The files a reply asks for, as one message; paths outside the workspace are refused."""
    out = []
    for path in requested_paths(reply)[:8]:
        full = os.path.abspath(os.path.join(ws, path))
        if not inside(full, ws):
            out.append('%s: refused (outside the task directory)' % path)
        elif not os.path.isfile(full):
            out.append('%s: no such file' % path)
        else:
            text = open(full, encoding='utf-8', errors='replace').read()
            out.append('=== %s ===\n%s%s' % (path, text[:MAX_FILE], '\n[... cut]' if len(text) > MAX_FILE else ''))
    return '\n\n'.join(out)


def body_of(reply, name):
    """The reply's C++ code block as a body (a whole function definition is reduced to its body). A block in another
    language (```markdown), or one that holds only READ lines, is not code: some models put their READ lines in one."""
    for m in re.finditer(r'```([a-zA-Z+]*)\n(.*?)```', reply, re.S):
        lines = [x for x in m.group(2).split('\n') if x.strip()]
        if m.group(1).lower() in ('', 'c', 'cpp', 'c++', 'cxx', 'h', 'hpp') and lines and not all(
                x.strip().startswith('READ ') for x in lines):
            return as_body(m.group(2), name)
    return None


def as_body(code, name):
    """Code as the function's body, indented; a whole function definition is reduced to its body."""
    m = re.search(r'```[a-zA-Z+]*\n(.*?)```', code, re.S)  # a code block passed to submit_body
    code = (m.group(1) if m else code).strip()
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
    sys.stdout.reconfigure(encoding='utf-8', errors='replace')  # stdout is agent.log, a file in the ANSI code page
    model = sys.argv[1]
    rounds = int(sys.argv[sys.argv.index('--rounds') + 1]) if '--rounds' in sys.argv else 12
    tools = TOOLS if '--tools' in sys.argv else None
    ws = os.path.abspath(os.environ['CD2_WORKSPACE'])
    path, file, symbol = bench._task_file(ws)
    name, _ = search.demangle_name(symbol)
    task = open(os.path.join(ws, 'TASK.md'), encoding='utf-8').read()
    task = re.sub(r'Check your work with this command.*?\n\n    .*?\n\n', '', task, flags=re.S)  # we run the check
    messages = [dict(role='system', content=SYSTEM_TOOLS if tools else SYSTEM),
                dict(role='user', content='%s\n\n=== %s (the body to write is marked TODO) ===\n%s\n\nFiles in the '
                     'task directory:\n%s' % (task, file, open(path, encoding='utf-8').read(), listing(ws)))]
    usage = dict(prompt_tokens=0, completion_tokens=0, requests=0, waited_seconds=0.0)
    rate_limited, reminders = None, 0

    def submit(body, r):
        """Splice the body in and check it: (the check's result, the feedback for the model)."""
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
        return res, 'Check: %s (%s of %s instruction words match).\n%s' % (
            status, res.get('words', 0), res.get('of', '?'), (res.get('detail') or '')[:3000])

    for r in range(rounds):
        try:
            reply, u, waited, message = api(messages, model, tools=tools)
        except RateLimited as e:
            rate_limited = str(e)
            print('--- %s ---' % rate_limited, flush=True)
            break
        usage['requests'] += 1
        usage['waited_seconds'] = round(usage['waited_seconds'] + waited, 1)
        for k in ('prompt_tokens', 'completion_tokens'):
            usage[k] += u.get(k) or 0
        if 'cost' in u:  # what the API says it charged (OpenRouter-style gateways report it)
            usage['cost'] = usage.get('cost', 0) + (u['cost'] or 0)
        print('--- reply %d ---\n%s\n' % (r + 1, reply), flush=True)
        calls = (message.get('tool_calls') or []) if tools else []
        if calls:  # each call answered in a tool message, as the protocol requires
            messages.append(dict(role='assistant', content=message.get('content') or '', tool_calls=calls))
            done = False
            for call in calls:
                if done:  # exact, or stopped: a later call in the same reply must not overwrite the exact body
                    break
                fn = call.get('function') or {}
                try:
                    args = json.loads(fn.get('arguments') or '{}')
                except ValueError:
                    args = {}
                args = args if isinstance(args, dict) else {}
                if fn.get('name') == 'read_file' and isinstance(args.get('path'), str):
                    result = read_request(ws, 'READ %s' % args['path'].strip()) or '%s: no such file' % args['path']
                elif fn.get('name') == 'submit_body' and isinstance(args.get('code'), str):
                    res, result = submit(as_body(args['code'], name), r)
                    done = done or bool(res.get('exact'))
                elif fn.get('name') == 'grep' and isinstance(args.get('pattern'), str):
                    result = grep(ws, args['pattern'], args.get('path') if isinstance(args.get('path'), str) else '')
                elif fn.get('name') == 'stop':
                    result, done = 'stopped', True
                else:
                    result = ('there is no tool %s with these arguments (%s): the only tools are read_file(path), '
                              'grep(pattern, path), submit_body(code) and stop()' % (
                                  fn.get('name'), (fn.get('arguments') or '')[:200]))
                messages.append(dict(role='tool', tool_call_id=call.get('id'), content=result))
            if done:
                break
            continue
        messages.append(dict(role='assistant', content=reply))
        body = body_of(reply, name)
        if body is None:
            files = read_request(ws, reply)
            if not files:
                if re.search(r'^\s*STOP\s*$', reply, re.M) or reminders >= 2:
                    break  # the model gave up, or still does not follow the protocol
                reminders += 1
                messages.append(dict(role='user', content=REMINDER_TOOLS if tools else REMINDER))
                continue
            messages.append(dict(role='user', content=files))
            continue
        res, feedback = submit(body, r)
        if res.get('exact'):
            break
        messages.append(dict(role='user', content=feedback))
    rp = bench.result_path(int(os.path.basename(ws), 16), os.path.basename(os.path.dirname(ws)))
    rec = json.load(open(rp))
    rec['usage'] = usage
    if rate_limited:  # the API's limit, not the model, ended the task: not a result (bench.needs_run runs it again)
        rec['rate_limited'] = rate_limited
    json.dump(rec, open(rp, 'w'), indent=1)
    print('usage: %s' % usage)
    return RATE_LIMITED if rate_limited else 0


if __name__ == '__main__':
    sys.exit(main())
