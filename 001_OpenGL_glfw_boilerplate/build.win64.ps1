$myproject_directory = Split-Path -Path (Get-Location) -Leaf
$project_build_directory = "$myproject_directory-build.win64"
$clean = $false

astyle --options=.astylerc --recursive ./src/*.c,*.h

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
cmake ..\$myproject_directory -G "MinGW Makefiles"
cmake --build .

.\main.exe

cd ..\$myproject_directory
