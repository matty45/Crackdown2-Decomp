"""MCP server: the contributor tool (tools/cd2.py) as tools for any agent that speaks the Model Context Protocol.

usage: py -I tools/mcp_server.py          (stdio transport; register it in your agent's MCP settings)

Each tool runs `tools/cd2.py <command> --json` and returns its JSON, so the tools behave exactly like the command
line. No dependencies beyond Python. The project's .mcp.json registers it for agents that read that file.
"""
import json, os, subprocess, sys

TOOLS = os.path.dirname(os.path.abspath(__file__))
CD2 = os.path.join(TOOLS, 'cd2.py')
PROTOCOL = '2024-11-05'

S = lambda **props: dict(type='object', properties={k: dict(type=t, description=d) for k, (t, d) in props.items()})
ADDR = ('string', 'function address in CD2, hex (e.g. 0x82676298)')
FILE = ('string', 'source file, repository-relative (e.g. src/AI/cChaseBehaviour.cpp)')

# name: (description, input schema, required, argv builder)
TOOLS_DEF = {
    'cd2_status': ('Per source file: functions, matched, LTCG-only, in progress, claimed, open.', S(), [],
                   lambda a: ['status']),
    'cd2_tasks': ('Open functions of the scaffolded files, easiest first, with difficulty tier and features.',
                  S(file=('string', 'only tasks of files whose path contains this'), tier=('integer', 'only this tier (1-4)')), [],
                  lambda a: ['tasks'] + ([a['file']] if a.get('file') else []) + (['--tier', str(a['tier'])] if a.get('tier') else [])),
    'cd2_show': ('Task brief for one function: file, size, tier, status, neighbours, hints and CD2\'s assembly.',
                 S(address=ADDR), ['address'], lambda a: ['show', a['address']]),
    'cd2_claim': ('Start a task: map the function to the mangled symbol (prefix) you are writing for it.',
                  S(address=ADDR, symbol=('string', 'mangled symbol prefix, e.g. ?Update@cFoo@NS@@')), ['address', 'symbol'],
                  lambda a: ['claim', a['address'], a['symbol']]),
    'cd2_unclaim': ('Drop a claim.', S(address=ADDR), ['address'], lambda a: ['unclaim', a['address']]),
    'cd2_check': ('Compile a source file and compare every mapped function with CD2 (EXACT, a percentage, WRONG TARGET); '
                  'verifies relocation targets and the source policy. explain adds the mismatch findings.',
                  S(file=FILE, ltcg=('boolean', 'also build with link-time code generation'),
                    explain=('boolean', 'add the mismatch classifier\'s findings')), ['file'],
                  lambda a: ['check', a['file']] + (['--ltcg'] if a.get('ltcg') else []) + (['--explain'] if a.get('explain') else [])),
    'cd2_diff': ('Instruction diff of one function against CD2, differing regions only, with findings and hints.',
                 S(file=FILE, address=ADDR), ['file', 'address'], lambda a: ['diff', a['file'], a['address']]),
    'cd2_search': ('Try source transformations (operand order, if/else arms, statement order, ...) on one function and '
                   'keep improvements. apply writes the result to the source file.',
                   S(file=FILE, address=ADDR, apply=('boolean', 'write the best result to the file')), ['file', 'address'],
                   lambda a: ['search', a['file'], a['address']] + (['--apply'] if a.get('apply') else [])),
    'cd2_lint': ('The source policy (no inline assembly, pragmas, ...) on one file or all of src/.',
                 S(file=('string', 'one file; omit for all')), [], lambda a: ['lint'] + ([a['file']] if a.get('file') else [])),
    'cd2_verify': ('Every gate (run it before a pull request).',
                   S(facts=('boolean', 'use the recorded facts instead of the game file'),
                     jobs=('integer', 'parallel files; positive, defaults to up to 8 CPUs; 1 runs serially')), [],
                   lambda a: ['verify'] + (['--facts'] if a.get('facts') else [])
                             + (['--jobs', str(a['jobs'])] if 'jobs' in a else [])),
    'cd2_bench_check': ('Score a benchmark task\'s workspace (the check command in its TASK.md); each call is an attempt.',
                        S(address=ADDR, model=('string', 'the model name the task was prepared for (--model)')),
                        ['address', 'model'], lambda a: ['bench', 'check', a['address'], '--model', a['model']]),
}


def call(name, args):
    desc, schema, required, argv = TOOLS_DEF[name]
    missing = [k for k in required if k not in args]
    if missing:
        return 'missing argument(s): %s' % ', '.join(missing), True
    r = subprocess.run([sys.executable, '-I', CD2, '--json'] + argv(args), capture_output=True, text=True,
                       cwd=os.path.dirname(TOOLS))
    text = r.stdout.strip() or r.stderr.strip()
    try:
        # the command could not run ("error": ...); ok=false alone (not exact yet, a gate failed) is a result
        failed = 'error' in json.loads(text)
    except ValueError:
        failed = r.returncode != 0
    return text, failed


class InvalidParams(Exception):
    pass


def handle(msg):
    method, mid = msg.get('method'), msg.get('id')
    if method == 'initialize':
        version = msg.get('params', {}).get('protocolVersion', PROTOCOL)
        return dict(protocolVersion=version, capabilities=dict(tools={}),
                    serverInfo=dict(name='cd2', version='1.0'),
                    instructions='Crackdown 2 decompilation tools. Start with cd2_tasks or cd2_status; read '
                                 'docs/contributor-harness.md and docs/matching-notes.md.')
    if method == 'tools/list':
        return dict(tools=[dict(name=n, description=d, inputSchema=dict(s, required=req))
                           for n, (d, s, req, _) in TOOLS_DEF.items()])
    if method == 'tools/call':
        p = msg.get('params', {})
        if p.get('name') not in TOOLS_DEF:
            raise InvalidParams('unknown tool %s' % p.get('name'))
        text, err = call(p['name'], p.get('arguments') or {})
        return dict(content=[dict(type='text', text=text)], isError=err)
    if method == 'ping':
        return {}
    if mid is None:
        return None  # a notification (e.g. notifications/initialized): no reply
    raise LookupError(method)


def main():
    for line in sys.stdin:
        line = line.strip()
        if not line:
            continue
        try:
            msg = json.loads(line)
        except ValueError:
            msg = None
        if not isinstance(msg, dict):
            reply = dict(jsonrpc='2.0', id=None, error=dict(code=-32700, message='parse error'))
            sys.stdout.write(json.dumps(reply) + '\n')
            sys.stdout.flush()
            continue
        try:
            result = handle(msg)
            if msg.get('id') is None:
                continue
            reply = dict(jsonrpc='2.0', id=msg['id'], result=result)
        except LookupError as e:
            reply = dict(jsonrpc='2.0', id=msg.get('id'), error=dict(code=-32601, message='method not found: %s' % e))
        except InvalidParams as e:
            reply = dict(jsonrpc='2.0', id=msg.get('id'), error=dict(code=-32602, message=str(e)))
        except Exception as e:  # noqa: BLE001 - every failure goes back to the client
            reply = dict(jsonrpc='2.0', id=msg.get('id'), error=dict(code=-32603, message=str(e)))
        sys.stdout.write(json.dumps(reply) + '\n')
        sys.stdout.flush()


if __name__ == '__main__':
    main()
