cmake_minimum_required(VERSION 3.5)

project(HR_04_conditional_if_else LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(HR_04_conditional_if_else
	src/stdc++.h
	src/main.cpp
	)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "main")
