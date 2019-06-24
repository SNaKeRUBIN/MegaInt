cmake_minimum_required(VERSION 3.4)
project(MegaIntCalc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-g -Wall -Wextra -Wpedantic)
add_compile_options(-fPIC)

add_subdirectory(MegaInt)
add_subdirectory(MegaCalc)
add_subdirectory(Driver)
