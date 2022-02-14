Remove-Item -Recurse -Force './build'
New-Item -Path './build' -ItemType Directory
Set-Location build
cmake ..
cmake --build .
./Debug/hello.exe