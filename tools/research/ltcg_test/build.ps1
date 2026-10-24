param([string]$Mode = "gl")   # gl = /GL + /LTCG link, plain = no /GL, normal link
$ErrorActionPreference = "Continue"
$S = Split-Path -Parent $MyInvocation.MyCommand.Path
$XDK = "<XDK>"
$BIN = "$XDK\bin\win32"
$LUA = "$S\..\dl\lua-5.0.2"
$env:PATH = "$BIN;$env:PATH"
$env:INCLUDE = "$XDK\include\xbox"
$env:LIB = "$XDK\lib\xbox"
$out = "$S\out_$Mode"
New-Item -ItemType Directory -Force $out | Out-Null
$srcs = @(Get-ChildItem "$LUA\src\*.c" | Where-Object { $_.Name -ne 'ltests.c' } | ForEach-Object FullName) + @("$LUA\src\lib\lauxlib.c", "$LUA\src\lib\lbaselib.c", "$S\main.c")
$gl = if ($Mode -eq "gl") { "/GL" } else { "" }
& "$BIN\cl.exe" /nologo /c /W0 /Ox /Gy /GF $gl /D_XBOX /DNDEBUG /DLUA_NUMBER=float "/I$LUA\include" "/I$LUA\src" "/Fo$out\\" $srcs 2>&1 | Select-String -Pattern 'error' | Select-Object -First 5
$ltcg = if ($Mode -eq "gl") { "/LTCG" } else { "" }
& "$BIN\link.exe" /nologo $ltcg /OPT:REF /MAP "/MAP:$out\test.map" "/OUT:$out\test.exe" (Get-ChildItem "$out\*.obj" | ForEach-Object FullName) xapilib.lib libcmt.lib xboxkrnl.lib 2>&1 | Select-Object -First 15
"link exit=$LASTEXITCODE"
