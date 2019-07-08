#!/bin/bash
set -e

CMAKE_SANITIZE_FLAG=""

while [[ $# -gt 0 ]]
do
    key="$1"

    case $key in
        -m|--memory)
            CMAKE_SANITIZE_FLAG=" -DCMAKE_CXX_FLAGS=\"-fsanitize=memory\""
            shift
            ;;
        -a|--address)
            CMAKE_SANITIZE_FLAG=" -DCMAKE_CXX_FLAGS=\"-fsanitize=address\""
            shift
            ;;
    esac
done

cmake -H. -Bbuild $CMAKE_SANITIZE_FLAG
cmake --build ./build
