#!/bin/sh

cd "$(dirname "$0")"

VERSION=0.18.1.1
DIR=gettext-$VERSION
URL=http://ftp.gnu.org/pub/gnu/gettext/$DIR.tar.gz
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
./configure --prefix=/mingw --enable-threads=win32 --enable-relocatable &&
make &&
index=$(/share/msysGit/pre-install.sh) &&
make install &&
/share/msysGit/post-install.sh $index "Install $FILE"
) || die "Could not install $FILE"
