#!/bin/bash

if [ -d "build" ];
then
	rm -rf "build"
fi

mkdir build
cd build

sleep 2

cmake ..
make -j2

sleep 5

./app
