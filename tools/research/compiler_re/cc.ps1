param([string]$Src, [string]$Out, [string[]]$Extra)
$env:INCLUDE = '<XDK>\include\xbox;<repo>\include'
$env:PATH = '<XDK>\bin\win32;' + $env:PATH
& '<XDK>\bin\win32\cl.exe' /nologo /c /Ox /Ob1 /Gy /GF /GR- /GS- /fp:fast /D_XBOX /DNDEBUG /W3 "/Fo$Out.obj" @Extra $Src
