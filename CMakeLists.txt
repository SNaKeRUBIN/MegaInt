cmake_minimum_required(VERSION 3.4)
project(MegaIntCalc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

include(CTest)
enable_testing()

add_compile_options(-g -Wall -Wextra -Wpedantic)
add_compile_options(-fPIC)

set(THIRD_PARTY_DIR ${CMAKE_SOURCE_DIR}/ThirdParty)
set(EXTERNAL_BUILD_DIR ${THIRD_PARTY_DIR}/build CACHE PATH "Where to find the ThirdParty dir")
set(EXTERNAL_INSTALL_DIR ${EXTERNAL_BUILD_DIR}/install)

include_directories(${EXTERNAL_INSTALL_DIR}/include)

add_subdirectory(MegaInt)
add_subdirectory(MegaCalc)
add_subdirectory(Driver)
