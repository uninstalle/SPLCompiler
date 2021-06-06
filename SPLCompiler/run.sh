#!/bin/sh
#llvm-as ./out.ll
#llc ./out.bc
#ld ./out.s
clang++ ./out.ll
./a.out