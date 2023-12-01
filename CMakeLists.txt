cmake_minimum_required(VERSION 3.27)

project(aoc2023 CXX) 

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -Wextra -Werror)

add_subdirectory(day01)
