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

if [ $? -ne 0 ];then
	echo "compile failed..."
	exit 1
fi

sleep 5

valgrind --tool=memcheck --leak-check=full ./app
