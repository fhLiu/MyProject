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

if [ $? -ne 0 ];
then
	echo "fail"
	exit(-1)
else
	echo "success"
fi

sleep 5

./app
