#!/bin/sh

cd "$(dirname "$0")"

VERSION=1.7
DIR=hexdump-$VERSION
URL=http://catb.org/~esr/hexdump/$DIR.tar.gz
FILE=${URL##*/}

die () {
	echo "$*" >&2
	exit 1
}

test -d $DIR || {
	test -f $FILE ||
	curl -O $URL ||
	die "Could not download $DIR"

	tar xzvf $FILE && (
		cd $DIR &&
		git init &&
		git add . &&
		git commit -m "Import of $FILE"
	)
} || die "Could not check out $DIR"

test ! -d patches ||
test $(cd $DIR && git rev-list HEAD | wc -l) -gt 1 ||
(cd $DIR && git am ../patches/*) ||
die "Could not apply patches"

(cd $DIR &&
make &&
index=$(/share/msysGit/pre-install.sh) &&
cp hexdump.exe /mingw/bin/ &&
/share/msysGit/post-install.sh $index "Install $FILE"
) || die "Could not install $FILE"
