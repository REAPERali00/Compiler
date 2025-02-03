#!/bin/bash

error="../error.log"

cd build
if [ -f "$error" ]; then
  rm -rf $error
fi
cmake .. 2>>$error
make 2>>$error

./compiler
