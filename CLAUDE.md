@AGENTS.md

## Claude Code

- The `cd2` MCP server is registered in `.mcp.json` (stdio, `py -I tools/mcp_server.py`). Approve it when asked; its
  tools mirror `tools/cd2.py`.
- Bash and PowerShell both work for the commands. In Git Bash, compiler flags such as `/Fo` get path-mangled; the
  `cd2.py` commands avoid this, so prefer them over calling `cl.exe` yourself.
