#!/bin/sh

cd "$(dirname "$0")" &&
exe=/mingw/bin/connect.exe
gcc -O2 -o $exe connect.c -lws2_32 &&
git add $exe &&
git commit -s -m "Commit connect, a SOCKS proxy" $exe
