#!/bin/bash

error="../error.log"
files=(
  "../input/test.nag"
  "../input/INPUT1_Hello.nag"
  "../input/INPUT2_Voluem.nag"
  "../input/INPUT3_Factorial.nag"
  "../input/INPUT4_Datatypes.nag"
  "../input/INPUT5_General.nag"
  "../input/INPUT6_Big.nag"
)

cd build
if [ -f "$error" ]; then
  rm -rf $error
fi

cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=12 2>>$error
make 2>>$error

cp ./bin/compiler ../
# for f in "${files[@]}"; do
#   if [ -f $f ]; then
#     echo $f
#     ./bin/compiler R $f
#     sleep 2
#   fi
# done
#
./bin/compiler R "${files[1]}"
