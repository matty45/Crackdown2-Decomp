<#
.SYNOPSIS
  Build the decomp's tools from source into build\tools\bin. The repository stores no tool binaries.

.DESCRIPTION
  Each tool is a git submodule pinned to an exact commit under tools\external\:
    jeff     rjkiv/jeff v0.5.2 (6a023e5) + tools\patches\jeff\*.patch (unpatched jeff crashes on Crackdown 2)
    objdiff  encounter/objdiff v3.8.3 -> objdiff-cli
    resym    ergrelet/resym 5be0938 -> resymc (maintainers only, for tools\headers\ref_dump.ps1; built only when named)
  Sources are exported from the pinned commit with `git archive` into build\src\<tool> and patched there, so the
  submodules themselves stay unmodified. Requires git and Rust (cargo).

  resym is a PDB tool that contributors never need, so `git clone --recurse-submodules` does not check it out
  (`update = none` in .gitmodules); naming it here checks it out first.

.EXAMPLE
  powershell -File tools\build_tools.ps1            # what contributors need: jeff and objdiff-cli
  powershell -File tools\build_tools.ps1 jeff       # one tool
  powershell -File tools\build_tools.ps1 resym      # maintainers: resymc
#>
param([string[]]$Only = @('jeff', 'objdiff'))
$ErrorActionPreference = 'Stop'
$root = Split-Path -Parent (Split-Path -Parent $MyInvocation.MyCommand.Path)
$bin = Join-Path $root 'build\tools\bin'
New-Item -ItemType Directory -Force $bin | Out-Null
git -C $root submodule update --init
if ($LASTEXITCODE) { throw 'git submodule update failed' }
if ($Only -contains 'resym') {
    # its test snapshots have long names: allow paths over 260 characters for this checkout
    git -C $root -c core.longpaths=true submodule update --init --checkout tools/external/resym
    if ($LASTEXITCODE) { throw 'git submodule update failed for resym' }
}

function Export-Source($name) {
    $dst = Join-Path $root "build\src\$name"
    if (Test-Path $dst) { Remove-Item -Recurse -Force $dst }
    New-Item -ItemType Directory -Force $dst | Out-Null
    $tar = Join-Path $root "build\src\$name.tar"
    # exported as stored (LF), whatever the local core.autocrlf, so that the LF patches always apply
    git -C (Join-Path $root "tools\external\$name") -c core.autocrlf=false archive --format=tar -o $tar HEAD
    if ($LASTEXITCODE) { throw "git archive failed for $name" }
    # Windows' own tar: another tar first on PATH (Git's) takes "D:\..." for a remote host
    & (Join-Path $env:SystemRoot 'System32\tar.exe') -xf $tar -C $dst
    if ($LASTEXITCODE) { throw "tar failed for $name" }
    Remove-Item $tar
    foreach ($p in Get-ChildItem (Join-Path $root "tools\patches\$name") -Filter *.patch -ErrorAction SilentlyContinue) {
        git -C $root apply --directory="build/src/$name" --whitespace=nowarn $p.FullName
        if ($LASTEXITCODE) { throw "patch $($p.Name) does not apply to $name" }
        Write-Host "  applied $($p.Name)"
    }
    return $dst
}

function Build-Cargo($name, $package, $exe) {
    Write-Host "== $name"
    $src = Export-Source $name
    $target = Join-Path $root "build\cargo\$name"
    $cargoArgs = @('build', '--release', '--locked', '--manifest-path', (Join-Path $src 'Cargo.toml'), '--target-dir', $target)
    if ($package) { $cargoArgs += @('-p', $package) }
    & cargo @cargoArgs
    if ($LASTEXITCODE) { throw "cargo build failed for $name" }
    Copy-Item (Join-Path $target "release\$exe") $bin -Force
    Write-Host "  built $bin\$exe"
}

if ($Only -contains 'jeff') { Build-Cargo 'jeff' $null 'jeff.exe' }
if ($Only -contains 'objdiff') { Build-Cargo 'objdiff' 'objdiff-cli' 'objdiff-cli.exe' }
if ($Only -contains 'resym') { Build-Cargo 'resym' 'resymc' 'resymc.exe' }
