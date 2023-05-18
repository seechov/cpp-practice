cmake_minimum_required(VERSION 2.8.12)
project(mygame)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_STANDARD 17)

set(SOURCES src/mygame.cpp
src/meyers/basictransitionfromc.cpp
)

add_executable(mygame ${SOURCES})

# C:/mingw64/lib/gcc/x86_64-w64-mingw32/8.1.0/include/c++/
# C:/mingw64/lib/gcc/x86_64-w64-mingw32/8.1.0/include/c++/x86_64-w64-mingw32/