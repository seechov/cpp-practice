cmake_minimum_required(VERSION 3.12)

# here we specify that the project is C language only, so the default
# C compiler on the system will be used
project(smartqnt C)

set(SOURCES
    src/main.c
    src/glad.c
    src/linmath.h
)

add_subdirectory(lib/glfw-3.3.8)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/lib/include
        ${PROJECT_SOURCE_DIR}/lib/glfw-3.3.8/include
)
target_link_libraries(${PROJECT_NAME} glfw)