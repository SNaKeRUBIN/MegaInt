#!/bin/bash
set -e

IMAGE=megaint:test

rm -rf build

# docker build \
#     --build-arg TEST_FLAG="-a" \
#     -t $IMAGE \
#     -f Dockerfile.test \
#     --rm \
#     .

# docker run \
#     --cap-add=SYS_PTRACE \
#     $IMAGE

docker build \
    --build-arg TEST_FLAG="-m" \
    -t $IMAGE \
    -f Dockerfile.test \
    --rm \
    .

docker run \
    --cap-add=SYS_PTRACE \
    $IMAGE
