#!/bin/bash

error="../error.log"

cd build
if [ -f "$error" ]; then
  rm -rf $error
fi

cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=12 2>>$error
make 2>>$error

./compiler
