#!/bin/bash

if [ -d "build" ];then
    rm -rf "build"
fi

sleep 2
mkdir build
cd build

cmake ..
make -j4

if [ $? -ne 0 ];then
    echo "compile program failed ..."
    exit 1
fi

./app