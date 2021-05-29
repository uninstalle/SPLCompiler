#!/bin/sh
flex -o Scanner.c "./Scanner/Scanner.l"
bison -o Parser.c -d "./Parser/Parser.y" 
gcc -c Parser.c Scanner.c
g++ main.cpp Scanner.o Parser.o -o main
./main