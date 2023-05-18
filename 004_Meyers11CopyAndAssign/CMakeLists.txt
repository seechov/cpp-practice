cmake_minimum_required(VERSION 2.8.12)
project(main)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_STANDARD 17)

# set(CMAKE_VERBOSE_MAKEFILE TRUE)

set(SOURCES src/main.cpp
src/meyers/generalclass.cpp
)

add_executable(main ${SOURCES})

# C:/mingw64/lib/gcc/x86_64-w64-mingw32/8.1.0/include/c++/
# C:/mingw64/lib/gcc/x86_64-w64-mingw32/8.1.0/include/c++/x86_64-w64-mingw32/