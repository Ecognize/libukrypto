#!/bin/sh
mkdir build
cd build
cmake ..
make
make test
