#!/bin/sh
if [ $# -eq 0 ]
then
    ./bin/main
else
    ./bin/main $1
fi
#llvm-as ./out.ll
#llc ./out.bc
#ld ./out.s
clang ./out.ll
./a.out