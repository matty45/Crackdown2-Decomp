"""Kilo Code's CLI as a benchmark agent, sandboxed by its own permission rules. One preset among others: any agent can
run the benchmark (`--agent "<command>"`), and `--agent chat:<model>` (tools/bench_chat.py) runs any model through any
OpenAI-compatible API.

Used by `cd2.py bench run --agent kilo:<provider/model>` (e.g. kilo:openrouter/deepseek/deepseek-chat), in the task's
workspace. The model and the rules come through KILO_CONFIG_CONTENT, which Kilo loads after the global and project
configuration (only organization and managed configuration come later), so it is not a file the agent could edit:
everything is denied, then reading, searching and editing the workspace are allowed, and of the shell only the task's
check. Paths outside the workspace, the web and subagents stay denied. `kilo run` without --auto refuses whatever it
would have to ask for.

Safeguards where Kilo's documentation is silent:
- your global Kilo configuration is not loaded at all: XDG_CONFIG_HOME points to an empty directory beside the
  workspaces, so its MCP servers (an IDA or a DeepWiki server could reach CD2's database or the public repository),
  agents and permissions stay out; KILO_CONFIG and KILO_CONFIG_DIR are ignored. Credentials live in Kilo's data
  directory, which is not affected;
- before the task, `kilo debug config` must show, with the task's own environment and directory, no enabled MCP
  server, exactly the rules below and the requested model; otherwise nothing runs;
- the workspace is made a git repository of its own (empty, no history), so that Kilo's project root, and with it
  "outside the workspace", is the workspace.

Set up Kilo's credentials once (`kilo auth`, or its provider environment variables) as its documentation describes.
Run one task first and read the transcript (agent.log in the workspace) to see that the rules hold.

usage: py -I tools/bench_kilo.py <provider/model>          (kilo on PATH, or CD2_KILO = the path of the kilo executable)
"""
import json, os, shutil, subprocess, sys

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


def resolved_config(cmd, env, cwd):
    """The configuration Kilo resolves for a run with this environment and directory (`kilo debug config`), or None."""
    r = subprocess.run(cmd + ['debug', 'config'], cwd=cwd, env=env, stdin=subprocess.DEVNULL, capture_output=True,
                       text=True, encoding='utf-8', errors='replace')
    try:
        return json.loads(r.stdout)
    except ValueError:
        return None


def config_problems(config, check, model):
    """Why the resolved configuration is not the sandbox: enabled MCP servers, other rules, another model."""
    if not isinstance(config, dict):
        return ['`kilo debug config` printed no configuration']
    out = ['MCP server %s is enabled' % name for name, server in sorted((config.get('mcp') or {}).items())
           if not isinstance(server, dict) or server.get('enabled', True) is not False]
    if config.get('permission') != rules(check):
        out.append('the permission rules differ from the benchmark rules: %s'
                   % json.dumps(config.get('permission'))[:500])
    if config.get('model') != model:
        out.append('the model is %s, not %s' % (config.get('model'), model))
    return out


def sandbox_env(ws, model):
    """The environment kilo runs in: the rules and the model as KILO_CONFIG_CONTENT, no other configuration."""
    config = dict(model=model, permission=rules(os.environ['CD2_CHECK']))
    env = dict(os.environ, KILO_CONFIG_CONTENT=json.dumps(config))
    for k in ('KILO_CONFIG', 'KILO_CONFIG_DIR'):  # no other configuration
        env.pop(k, None)
    home = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(ws))), '.kilo-config-home')  # <bench dir>
    os.makedirs(home, exist_ok=True)
    env['XDG_CONFIG_HOME'] = home
    return env


def main():
    if len(sys.argv) != 2 or sys.argv[1].startswith('-'):
        print(__doc__)
        return 2
    exe = os.environ.get('CD2_KILO') or shutil.which('kilo')
    if not exe:
        print('kilo not found: install the Kilo CLI, or set CD2_KILO to the path of the kilo executable')
        return 2
    ws = os.environ['CD2_WORKSPACE']
    if not os.path.isdir(os.path.join(ws, '.git')):
        subprocess.run(['git', 'init', '-q', ws], check=True)
    env = sandbox_env(ws, sys.argv[1])
    problems = config_problems(resolved_config([exe], env, ws), os.environ['CD2_CHECK'], sys.argv[1])
    if problems:
        print('not running: Kilo would not run in the sandbox: %s' % '; '.join(problems))
        return 2
    return subprocess.run([exe, 'run', PROMPT], cwd=ws, env=env, stdin=subprocess.DEVNULL).returncode


if __name__ == '__main__':
    sys.exit(main())
