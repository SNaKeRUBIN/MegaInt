#!/bin/bash
set -e

IMAGE=building:latest

rm -rf build

docker build \
    -t $IMAGE \
    -f Dockerfile.build \
    --rm \
    .

CONTAINER_ID=`docker create $IMAGE`

docker cp $CONTAINER_ID:/MegaInt/build/ .
docker rm $CONTAINER_ID
