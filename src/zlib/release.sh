#!/bin/sh

cd "$(dirname "$0")"

VERSION=1.2.7
DIR=zlib-$VERSION
URL=http://zlib.net/$DIR.tar.gz
FILE=${URL##*/}

die () {
	echo "$*" >&2
	exit 1
}

test -d $DIR || {
	test -f $FILE ||
	curl -O $URL ||
	die "Could not download $FILE"

	tar xzvf $FILE && (
		cd $DIR &&
		git init &&
		git add . &&
		git commit -m "Import of $FILE"
	)
} || die "Could not check out $FILE"

(cd $DIR &&
 make -f win32/Makefile.gcc clean &&
 make -f win32/Makefile.gcc &&
 index=$(/share/msysGit/pre-install.sh) &&
 make -f win32/Makefile.gcc INCLUDE_PATH=/mingw/include \
   LIBRARY_PATH=/mingw/lib BINARY_PATH=/mingw/bin install &&
 /share/msysGit/post-install.sh $index "Install $FILE"
) || die "Could not install $FILE"
