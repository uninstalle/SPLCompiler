#!/bin/sh
flex -o "./src/Scanner.cc" "./src/Scanner.l"
bison -o "./src/Parser.cc" -d "./src/Parser.yy" 
g++ "./src/main.cc" "./src/Parser.cc" "./src/Scanner.cc" "./src/log.cc" "./src/ast.cc" "./src/table.cc" `llvm-config --cxxflags --ldflags --system-libs --libs core orcjit native` -frtti -o "./bin/main"
if [ $# -eq 0 ]
then
    ./bin/main
else
    ./bin/main $1
fi