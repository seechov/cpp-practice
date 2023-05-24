cmake_minimum_required(VERSION 3.5)

project(remove_k_from_list LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
	src/main.cpp
	)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "main")