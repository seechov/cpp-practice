cmake_minimum_required(VERSION 3.5)

project(Decode_Strings LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Decode_Strings
	src/main.cpp
	)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "main")