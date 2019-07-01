project(MegaInt LANGUAGES CXX)

set(sources
    src/MegaInt.cpp
    src/DequeUtils.cpp
)

add_library(MegaInt ${sources})
target_include_directories(MegaInt PUBLIC include)

add_executable(test_MegaInt
    test/TestMegaInt.cpp
)
target_link_libraries(test_MegaInt MegaInt)
add_test(NAME test_MegaInt
    COMMAND test_MegaInt
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
set_tests_properties(test_MegaInt 
    PROPERTIES TIMEOUT 2000
)
