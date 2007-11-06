#!/bin/sh
PATH=/bin:$PATH

cd /perl/perl-5.6.1
test -f ext/DynaLoader/dl_win32.xs || cp win32/dl_win32.xs ext/DynaLoader/
test -f ext/DynaLoader/win32.h || cp win32/win32.h ext/DynaLoader/

./Configure -dE \
	-D cc=gcc \
	-U libc= \
	-U libs= \
	-U libsfiles= \
	-U libsfound= \
	-U libswanted= \
	-D runnm=false \
	-D usenm=false \
	-D so=dll \
	-D firstmakefile=GNUmakefile \
	-D exe_ext=.exe -D _exe=.exe \
	-D archname=msys \
	-D dlsrc=dl_dlopen.xs -D dlext=dll -D usedl=define \
	-D ccccdlflags=-fpic -D cccdlflags=-shared -D lddlflags=-shared \
	-D optimize=-g \
	2>&1 | tee config.log
./Configure -S

LIB= make
