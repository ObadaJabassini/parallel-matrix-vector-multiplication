#!/bin/sh
cd build
make
cd ../bin
eval "./$1"