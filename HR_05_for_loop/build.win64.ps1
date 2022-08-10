# This PowerShell script can be started by NppExec command
# powershell ./build.win64.ps1

$project_directory = Split-Path -Path (Get-Location) -Leaf
$project_build_directory = "$project_directory-build.win64"
$clean = $true

astyle --options=.astylerc --recursive ./src/*.cpp,*.h

if ($clean) {
    Write-Output "Clean build: $project_build_directory will be deleted"
    Remove-Item -LiteralPath ..\$project_build_directory -Force -Recurse
}

cd ..\

 
If(!(test-path $project_build_directory))
{
    New-Item -ItemType Directory -Force -Path $project_build_directory
}

cd $project_build_directory
cmake ..\$project_directory -G "MinGW Makefiles"

# cmake --build . --config Release
cmake --build . --config Debug

Copy-Item "main.exe" -Destination "..\$project_directory"

cd ..\$project_directory

.\main.exe
