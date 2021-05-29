#!/bin/sh
flex -o "./src/Scanner.cc" "./src/Scanner.l"
bison -o "./src/Parser.cc" -d "./src/Parser.yy" 
g++ "./src/main.cc" "./src/Parser.cc" "./src/Scanner.cc" "./src/log.cc" -o "./bin/main"
./bin/main