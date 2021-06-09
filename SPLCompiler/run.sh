#!/bin/sh
if [ $# -eq 0 ]
then
    ./bin/main
else if [ $# -eq 1 ]
    then
        ./bin/main $1
    else
        ./bin/main $1 $2
    fi
fi
#llvm-as ./out.ll
#llc ./out.bc
#ld ./out.s
clang ./out.ll
./a.out