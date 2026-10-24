"""Kilo Code's CLI as a benchmark agent, sandboxed by its own permission rules. One preset among others: any agent can
run the benchmark (`--agent "<command>"`), and `--agent chat:<model>` (tools/bench_chat.py) runs any model through any
OpenAI-compatible API.

Used by `cd2.py bench run --agent kilo:<provider/model>` (e.g. kilo:openrouter/deepseek/deepseek-chat), in the task's
workspace. The model and the rules come through KILO_CONFIG_CONTENT, which Kilo loads after the global and project
configuration (only organization and managed configuration come later), so it is not a file the agent could edit:
everything is denied, then reading, searching and editing the workspace are allowed, and of the shell only the task's
check. Paths outside the workspace, the web and subagents stay denied. `kilo run` without --auto refuses whatever it
would have to ask for.

Two safeguards where Kilo's documentation is silent:
- how permission rules from several sources merge is not documented, so this refuses to run when your global Kilo
  configuration sets permissions of its own (remove them while benchmarking), and ignores KILO_CONFIG and
  KILO_CONFIG_DIR;
- the workspace is made a git repository of its own (empty, no history), so that Kilo's project root, and with it
  "outside the workspace", is the workspace.

Set up Kilo's credentials once (`kilo auth`, or its provider environment variables) as its documentation describes.
Kilo was not installed where this was written: run one task first and read the transcript (agent.log in the
workspace) to see that the rules hold.

usage: py -I tools/bench_kilo.py <provider/model>          (kilo on PATH, or CD2_KILO = the path of the kilo executable)
"""
import json, os, re, shutil, subprocess, sys

PROMPT = ('Do the benchmark task described in TASK.md in this directory. Work only with the files here. To test your '
          'work, run the check command from TASK.md exactly as written, as often as you need. Stop when it reports '
          'EXACT or when you run out of ideas.')


def rules(check):
    """Kilo permission rules: the last matching rule wins, so the catch-all deny comes first."""
    return {'*': 'deny',
            'read': 'allow', 'list': 'allow', 'glob': 'allow', 'grep': 'allow',
            'edit': 'allow', 'write': 'allow',
            'todowrite': 'allow', 'todoread': 'allow',
            'bash': {'*': 'deny', check: 'allow'},
            'external_directory': 'deny', 'webfetch': 'deny', 'websearch': 'deny', 'task': 'deny'}


def global_permissions():
    """The global configuration files that set permissions of their own."""
    base = os.environ.get('XDG_CONFIG_HOME') or os.path.join(os.path.expanduser('~'), '.config')
    found = []
    for name in ('kilo.json', 'kilo.jsonc', 'opencode.json', 'opencode.jsonc'):
        p = os.path.join(base, 'kilo', name)
        if os.path.exists(p):
            text = re.sub(r'^\s*//[^\n]*$|/\*.*?\*/', '', open(p, encoding='utf-8', errors='replace').read(), flags=re.S | re.M)
            if re.search(r'"permission"\s*:', text):
                found.append(p)
    return found


def main():
    if len(sys.argv) != 2 or sys.argv[1].startswith('-'):
        print(__doc__)
        return 2
    exe = os.environ.get('CD2_KILO') or shutil.which('kilo')
    if not exe:
        print('kilo not found: install the Kilo CLI, or set CD2_KILO to the path of the kilo executable')
        return 2
    clash = global_permissions()
    if clash:
        print('not running: %s set permissions, which could combine with the benchmark\'s rules; remove them while '
              'benchmarking' % ', '.join(clash))
        return 2
    ws = os.environ['CD2_WORKSPACE']
    if not os.path.isdir(os.path.join(ws, '.git')):
        subprocess.run(['git', 'init', '-q', ws], check=True)
    config = dict(model=sys.argv[1], permission=rules(os.environ['CD2_CHECK']))
    env = dict(os.environ, KILO_CONFIG_CONTENT=json.dumps(config))
    for k in ('KILO_CONFIG', 'KILO_CONFIG_DIR'):  # no other configuration
        env.pop(k, None)
    return subprocess.run([exe, 'run', PROMPT], cwd=ws, env=env, stdin=subprocess.DEVNULL).returncode


if __name__ == '__main__':
    sys.exit(main())
