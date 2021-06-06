#!/bin/sh
llvm-as ./out.ll
llc ./out.bc
ld ./out.s