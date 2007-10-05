#!/bin/sh
PATH=/bin:$PATH
./Configure -dE -D cc=gcc -U libc= -U libs= -U libsfiles= -U libsfound= -U libswanted= -D runnm=false -D usenm=false -D so=dll -D usedl=false -D firstmakefile=GNUmakefile -D exe_ext=.exe -D _exe=.exe -D archname=msys
./Configure -S
LIB= make
echo > ext.libs
LIB= make
