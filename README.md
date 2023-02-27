# sha256-bruteforce-cpp
This project is in alpha and for now only works with number passwords (will add the rest soon).

Usage: sha256.o <hash> <threads>

Dynamic g++ compile command example: g++ -Wall -Wextra -o sha256.o main.cpp mingw.thread.h main.h sha256.cpp sha256.h fastcmp.h

For static output add the -static flag somewhere in the command.
