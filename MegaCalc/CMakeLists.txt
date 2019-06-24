project(MegaCalc)

set(sources
    src/MegaCalc.cpp
)

add_library(MegaCalc SHARED ${sources})
target_include_directories(MegaCalc PUBLIC include)
target_link_libraries(MegaCalc PUBLIC MegaInt)
