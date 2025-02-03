#!/bin/bash

error="../error.log"
if [ -f $error ]; then
  rm -rf $error
fi
cd build
cmake .. 2>>$error
make 2>>$error

./compiler
