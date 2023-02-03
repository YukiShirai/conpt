# specify minimum version of CMake. 
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

# define project
project(
    CONPT
    VERSION 1.0
    DESCRIPTION "library for solving contact-implicit trajectory optimization with CMake"
    LANGUAGES CXX)

set(PROJECT CONPT)
set(LIBRARY conpt)


# avoid in src of build 
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

add_subdirectory(src)
add_subdirectory(example)
add_subdirectory(python)
