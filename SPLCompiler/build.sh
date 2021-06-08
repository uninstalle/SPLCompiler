#!/bin/sh
flex -o "./src/Scanner.cc" "./src/lexer/Scanner.l" &&
bison -o "./src/Parser.cc" -d "./src/parser/Parser.yy" &&
clang++ "./src/main.cc" "./src/Parser.cc" "./src/Scanner.cc" ./src/logger/*.cc ./src/ast/*.cc ./src/irgen/*.cc `llvm-config --cxxflags --ldflags --system-libs --libs core orcjit native` -frtti -o "./bin/main"