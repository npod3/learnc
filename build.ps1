# PowerShell build script for Windows
param(
    [string]$Compiler = "gcc"
)

$srcBase = Get-ChildItem -Path src -Filter *.c | ForEach-Object { $_.FullName }
$srcEx   = Get-ChildItem -Path src\examples -Filter *.c | ForEach-Object { $_.FullName }
$files = $srcBase + $srcEx

$include = "-Iinclude"
$common = "-std=c17 -Wall -Wextra -Wpedantic -O2"
if ($Compiler -ieq "cl") {
    $cmd = "cl /std:c17 /W4 /EHsc /Fe:bin\learnc.exe /I include " + ($files -join ' ') + " ws2_32.lib"
} else {
    $cmd = "$Compiler $common $include $files -o bin/learnc.exe -lws2_32"
}
Write-Host "Building with: $cmd"
Invoke-Expression $cmd
