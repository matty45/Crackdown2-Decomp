# Compile tests/headers/layout_test.cpp with the Crackdown 2 compiler and flags.
# Passes when every curated header compiles and all layout checks hold, and the self-test proves a bad check fails.
# The XDK location: -XdkDir, else XDK_DIR, else "xdk" in local.json (written by tools/cd2.py config --xdk).
param([string]$XdkDir = "")
$ErrorActionPreference = "Stop"
$repo = Resolve-Path "$PSScriptRoot\..\.."
if (-not $XdkDir) { $XdkDir = $env:XDK_DIR }
if (-not $XdkDir -and (Test-Path "$repo\local.json")) { $XdkDir = (Get-Content "$repo\local.json" -Raw | ConvertFrom-Json).xdk }
if (-not $XdkDir) { throw "XDK location not set: run tools\cd2.py config --xdk <dir>, or set XDK_DIR" }
$bin = "$XdkDir\bin\win32"
$env:PATH = "$bin;$env:PATH"
$env:INCLUDE = "$XdkDir\include\xbox;$repo\include"
$tmp = Join-Path $env:TEMP "cd2_header_check"
New-Item -ItemType Directory -Force $tmp | Out-Null
$flags = @('/nologo', '/c', '/Ox', '/Ob1', '/Gy', '/GF', '/GR-', '/GS-', '/fp:fast', '/D_XBOX', '/DNDEBUG', '/W3')

$out = & "$bin\cl.exe" @flags "$repo\tests\headers\layout_test.cpp" "/Fo$tmp\layout_test.obj" 2>&1
$ok = $LASTEXITCODE -eq 0
Write-Output ("headers + layout checks: " + $(if ($ok) { "PASS" } else { "FAIL" }))
if (-not $ok) { $out | Select-String -Pattern 'error' | ForEach-Object { "  $_" } }

$out2 = & "$bin\cl.exe" @flags /DCD2_SELFTEST_EXPECT_FAILURE "$repo\tests\headers\layout_test.cpp" "/Fo$tmp\selftest.obj" 2>&1
$fired = ($LASTEXITCODE -ne 0) -and (($out2 | Out-String) -match 'C2118')
Write-Output ("self-test (a wrong size must fail with C2118): " + $(if ($fired) { "PASS" } else { "FAIL" }))
if (-not ($ok -and $fired)) { exit 1 }
exit 0

