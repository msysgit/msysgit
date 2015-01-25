#!/bin/sh

cd "$(dirname "$0")" &&
exe=/mingw/bin/connect.exe
gcc -O2 -o connect.exe connect.c -lws2_32 &&
cp connect.exe $exe &&
git add $exe &&
git commit -n -s -m "Commit connect, a SOCKS proxy" $exe
