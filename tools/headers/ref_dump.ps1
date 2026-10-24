# Dump a type from a reference PDB as C++ (reference only; not compilable as-is), via resym.
#   tools/headers/ref_dump.ps1 "RWS::CAttributeHandler"            # RuffKing PDB, type + dependencies
#   tools/headers/ref_dump.ps1 "AI::cMission" -Pdb burn -NoDeps     # Burn PDB, the type only
#   tools/headers/ref_dump.ps1 "cAgency" -List                      # list matching type names
# Output: include/ref/<pdb>/<Type>.h. Offsets in the comments are the reference build's; CD2 may differ.
param(
    [Parameter(Mandatory = $true)][string]$Type,
    [ValidateSet('ruffking', 'burn')][string]$Pdb = 'ruffking',
    [switch]$NoDeps,
    [switch]$List
)
$ErrorActionPreference = "Stop"
$repo = Resolve-Path "$PSScriptRoot\..\.."
$resym = "$repo\build\tools\bin\resymc.exe"  # built from the tools/external/resym submodule by tools/build_tools.ps1
if (-not (Test-Path $resym)) { throw "resymc.exe not built yet: run powershell -File tools\build_tools.ps1 resym" }
# The reference PDBs: CD2_RUFFKING_PDB / CD2_BURN_PDB, else "ruffking_pdb" / "burn_pdb" in local.json (repository root)
$local = if (Test-Path "$repo\local.json") { Get-Content "$repo\local.json" -Raw | ConvertFrom-Json } else { $null }
$pdbs = @{
    'ruffking' = $(if ($env:CD2_RUFFKING_PDB) { $env:CD2_RUFFKING_PDB } elseif ($local) { $local.ruffking_pdb })
    'burn'     = $(if ($env:CD2_BURN_PDB) { $env:CD2_BURN_PDB } elseif ($local) { $local.burn_pdb })
}
if (-not $pdbs[$Pdb]) { throw "No path for the $Pdb PDB: set CD2_$($Pdb.ToUpper())_PDB, or ""$($Pdb)_pdb"" in local.json" }
if ($List) { & $resym list $pdbs[$Pdb] $Type; exit $LASTEXITCODE }
$outDir = "$repo\include\ref\$Pdb"
New-Item -ItemType Directory -Force $outDir | Out-Null
$out = Join-Path $outDir (($Type -replace '::', '_' -replace '[<>,\* ]', '_') + '.h')
$args = @('dump', '-a', '-x')
if (-not $NoDeps) { $args += '-d' }
& $resym @args $pdbs[$Pdb] $Type $out
if ($LASTEXITCODE -eq 0) { Write-Output "wrote $out" }
