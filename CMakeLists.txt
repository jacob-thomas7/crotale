# Version Requirements
cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project Metadata
project(
    CROTALE
    VERSION 0.1.0
    LANGUAGES CXX
)

# Options
set(CROTALE_NAMESPACE_SHORTCUT ON CACHE BOOL "Create certain namespace shortcuts, such as CORE_SOURCE_DIR for CROTALE_CORE_SOURCE_DIR")
set(CROTALE_BUILD_EXAMPLES ON CACHE BOOL "Build executables from the examples directory")

# Packages
add_subdirectory("packages/crotale-core")
add_subdirectory("packages/crotale-utils")
add_subdirectory("packages/crotale-gamedev")

if(CROTALE_BUILD_EXAMPLES)
    add_subdirectory("examples")
endif()