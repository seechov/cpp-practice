cmake_minimum_required(VERSION 2.8.12)
project(astrology)

set (CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE MinSizeRel CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
endif()

# wxWidgets
set(wxBUILD_SHARED OFF)
add_subdirectory(wxwidgets)
include_directories(wxwidgets/include)

set(SOURCES
    src/main.cpp
)

add_executable(astrology ${SOURCES})
target_link_libraries(astrology wx::net wx::core wx::base)
