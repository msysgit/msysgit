#!/bin/sh

cd "$(dirname "$0")"

VERSION=1.15
DIR=popt-$VERSION
URL=http://rpm5.org/files/popt/$DIR.tar.gz
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
		git commit -m "Import of $FILE" &&
		git am ../patches/*
	)
} || die "Could not check out $FILE"

(cd $DIR &&
CFLAGS="-I/git -I/git/compat/vcbuild/include" LDFLAGS="-L/git -L/git/xdiff" LIBS="-lgit -l:lib.a -lws2_32 -lz -liconv" ./configure --prefix=/mingw &&
make &&
index=$(/share/msysGit/pre-install.sh) &&
make install &&
/share/msysGit/post-install.sh $index "Install $FILE"
) || die "Could not install $FILE"
