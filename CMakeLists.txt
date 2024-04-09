cmake_minimum_required(VERSION 3.15)

project(cpp20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(dependencies)

add_subdirectory(cache)
