#!/bin/sh

cd "$(dirname "$0")"

VERSION=7.19.5
DIR=curl-$VERSION
URL=http://curl.haxx.se/download/$DIR.tar.bz2
FILE=${URL##*/}

die () {
	echo "$*" >&2
	exit 1
}

test -d $DIR || {
	test -f $FILE ||
	curl -O $URL ||
	die "Could not download cURL"

	tar xjvf $FILE && (
		cd $DIR &&
		git init &&
		git add . &&
		git commit -m "Import of $FILE"
	)
} || die "Could not check out cURL"

(cd $DIR &&
./configure --prefix=/mingw --with-ssl=/mingw &&
make &&
index=$(/share/msysGit/pre-install.sh) &&
make install &&
/share/msysGit/post-install.sh $index "Install $FILE"
) || die "Could not install $FILE"
