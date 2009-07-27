#!/bin/sh

cd "$(dirname "$0")"

VERSION=1.4.17
DIR=msmtp-$VERSION
URL=http://sunet.dl.sourceforge.net/project/msmtp/msmtp/$VERSION/$DIR.tar.bz2
FILE=${URL##*/}

die () {
	echo "$*" >&2
	exit 1
}

test -d $DIR || {
	test -f $FILE ||
	curl -O $URL ||
	die "Could not download $FILE"

	tar xjvf $FILE && (
		cd $DIR &&
		git init &&
		git add . &&
		git commit -m "Import of $FILE"
	)
} || die "Could not check out $FILE"

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
