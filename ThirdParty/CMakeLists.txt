cmake_minimum_required(VERSION 3.4)
Project(ThirdParty LANGUAGES CXX)

include(ExternalProject)

set(SKIP ${CMAKE_COMMAND} -E echo "Skipping step")

ExternalProject_Add(catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v2.9.1
    INSTALL_DIR install
    PREFIX catch2
    CONFIGURE_COMMAND ${SKIP}
    BUILD_COMMAND ${SKIP}
    INSTALL_COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/install/include &&
                    ${CMAKE_COMMAND} -E copy <SOURCE_DIR>/single_include/catch2/catch.hpp ${CMAKE_BINARY_DIR}/install/include/
)
