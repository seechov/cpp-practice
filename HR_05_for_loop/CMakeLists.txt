cmake_minimum_required(VERSION 3.5)

project(HR_05_for_loop LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(HR_05_for_loop
	src/main.cpp
	)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "main")