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
# # Meson
# cd $project_directory
# meson setup ..\$project_build_directory
# meson configure --buildtype release ..\$project_build_directory
# cd ..\$project_build_directory
# meson compile
# cd ..\$project_directory

cd $project_build_directory
cmake ..\$project_directory -G "MinGW Makefiles"
# cmake ..\$project_directory
# cmake --build . --config Release

# cmake -B .\ -S ..\$project_directory -DCMAKE_TOOLCHAIN_FILE=C:/Users/a.sychev/vcpkg/scripts/buildsystems/vcpkg.cmake
# cmake --build . --config Release
cmake --build . --config Debug

# $glfwDllDestination = ".\glfw3.dll"
# if(!(Test-Path $glfwDllDestination)) {
#     Move-Item -Path "glfw-3.3.4\src\glfw3.dll" -Destination $glfwDllDestination
#     Move-Item -Path "reactphysics3d\libreactphysics3d.dll" -Destination $glfwDllDestination
# }

# .\Release\main.exe
.\main.exe

cd ..\$project_directory
