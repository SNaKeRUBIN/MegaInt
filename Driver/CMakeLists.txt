project(Driver LANGUAGES CXX)

set(source
    src/Driver.cpp
)

add_executable(Driver ${source})
target_link_libraries(Driver MegaCalc)
