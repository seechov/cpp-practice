cmake_minimum_required(VERSION 2.8.12)
project(main)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_STANDARD 17)
# set_target_properties(main PROPERTIES LINKER_LANGUAGE CXX)
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lstdc++")

# set(CMAKE_VERBOSE_MAKEFILE TRUE)

set(SOURCES src/main.cpp
src/meyers/extensivememoryuser.cpp
src/meyers/newhandlersupport.cpp
)

add_executable(main ${SOURCES})

target_link_libraries(main stdc++)

# C:/mingw64/lib/gcc/x86_64-w64-mingw32/8.1.0/include/c++/
# C:/mingw64/lib/gcc/x86_64-w64-mingw32/8.1.0/include/c++/x86_64-w64-mingw32/