#!/bin/sh

cd "$(dirname "$0")"

VERSION=0.14.5
DIR=poppler-$VERSION
URL=http://poppler.freedesktop.org/$DIR.tar.gz

FILE=${URL##*/}

die () {
	echo "$*" >&2
	exit 1
}

test -d $DIR || {
	test -f $FILE ||
	curl -O $URL ||
	die "Could not download Poppler"

	tar xzvf $FILE && (
		cd $DIR &&
		git init &&
                git config core.autocrlf false &&
		git add . &&
		git commit -n -m "Import of $FILE"
	)
} || die "Could not check out Poppler"

(cd $DIR &&
./configure --prefix=/mingw	\
	--disable-splash-output	\
	--disable-cairo-output	\
	--disable-poppler-glib	\
	--disable-gdk	\
	--disable-poppler-qt	\
	--disable-poppler-qt4	\
	--disable-poppler-cpp	\
	--disable-gtk-test	\
	--disable-abiword-output	\
	&&
make &&
index=$(/share/msysGit/pre-install.sh) &&
make install &&
/share/msysGit/post-install.sh $index "Install $FILE"
) || die "Could not install $FILE"
