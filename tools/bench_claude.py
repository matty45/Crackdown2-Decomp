"""Claude Code as a benchmark agent, sandboxed by its own permission system. One preset among others: any agent can
run the benchmark (`--agent "<command>"`), and `--agent chat:<model>` (tools/bench_chat.py) runs any model through any
OpenAI-compatible API.

Used by `cd2.py bench run --agent claude:<model>`, in the task's workspace. The agent may read and edit the files of
the workspace and run exactly one command, the task's check (CD2_CHECK). Everything else is refused without asking:
other commands, files outside the workspace, the web, MCP servers. Your own settings, CLAUDE.md files, memory, hooks
and plugins are not loaded. If the installed Claude Code lacks a flag this needs, it refuses to run rather than run
unsandboxed.

usage: py -I tools/bench_claude.py <model>          (claude on PATH, or CD2_CLAUDE = the path of claude.exe)
"""
import os, shutil, subprocess, sys

PROMPT = ('Do the benchmark task described in TASK.md in this directory. Work only with the files here. To test your '
          'work, run the check command from TASK.md exactly as written, as often as you need. Stop when it reports '
          'EXACT or when you run out of ideas.')
REQUIRED = ['--print', '--model', '--tools', '--allowedTools', '--permission-mode', '--permission-prompts',
            '--restricted', '--safe-mode', '--strict-mcp-config', '--no-session-persistence']


def main():
    if len(sys.argv) != 2 or sys.argv[1].startswith('-'):
        print(__doc__)
        return 2
    exe = os.environ.get('CD2_CLAUDE') or shutil.which('claude')
    if not exe:
        print('claude not found: install Claude Code, or set CD2_CLAUDE to the path of claude.exe')
        return 2
    helptext = subprocess.run([exe, '--help'], capture_output=True, text=True).stdout
    missing = [f for f in REQUIRED if f not in helptext]
    if missing:
        print('this Claude Code lacks %s, which the sandbox needs: not running' % ', '.join(missing))
        return 2
    check = os.environ['CD2_CHECK']
    args = [exe, '--print', PROMPT, '--model', sys.argv[1],
            '--restricted',  # settings files ignored, file tools confined to the workspace, no bypassPermissions
            '--safe-mode',  # no CLAUDE.md, memory, skills, plugins or hooks
            '--strict-mcp-config',  # no MCP servers
            '--tools', 'Bash,PowerShell,Read,Edit,Write,Glob,Grep',  # no web tools
            '--allowedTools', 'Bash(%s)' % check, 'PowerShell(%s)' % check,  # the one command
            '--permission-mode', 'acceptEdits',  # edits inside the workspace
            '--permission-prompts', 'none',  # anything else that would ask is refused
            '--no-session-persistence']
    return subprocess.run(args, cwd=os.environ['CD2_WORKSPACE'], stdin=subprocess.DEVNULL).returncode


if __name__ == '__main__':
    sys.exit(main())
