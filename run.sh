#!/bin/bash

cd build
cmake ..
make

./build/compiler
# ./compiler R ./input/test.nag
