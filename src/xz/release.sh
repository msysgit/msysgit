#!/bin/sh

cd "$(dirname "$0")"

VERSION=5.2.0
DIR=xz-$VERSION
URL=http://tukaani.org/xz/$DIR.tar.gz
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
		git commit -n -m "Import of $FILE"
	)
} || die "Could not check out $FILE"

test ! -d patches ||
test $(cd $DIR && git rev-list HEAD | wc -l) -gt 1 ||
(cd $DIR && git am ../patches/*) ||
die "Could not apply patches"

(cd $DIR &&
./configure --prefix=/mingw &&
make &&
index=$(/share/msysGit/pre-install.sh) &&
make install &&
/share/msysGit/post-install.sh $index "Install $FILE"
) || die "Could not install $FILE"
