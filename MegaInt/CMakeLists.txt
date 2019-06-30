project(MegaInt LANGUAGES CXX)

set(sources
    src/MegaInt.cpp
)

add_library(MegaInt ${sources})
target_include_directories(MegaInt PUBLIC include)
