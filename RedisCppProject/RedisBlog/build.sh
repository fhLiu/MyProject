#!/bin/bash

echo "the project contains gtest and hiredis lib.."

if [ -d "build" ];then
    rm -rf "build"
fi

mkdir build
cd build

cmake ..
make -j4

if [ $? -ne 0 ];then
    echo "not to exec app..."
    exit 1
fi

echo "compli successful, will exec app process..."
sleep 3
./RedisApp