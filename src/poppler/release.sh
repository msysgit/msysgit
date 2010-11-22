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
		git commit -m "Import of $FILE"
	)
} || die "Could not check out Poppler"

# test $(cd $DIR && git rev-list HEAD | wc -l) -gt 1 ||
# (cd $DIR && git am ../patches/*) ||
# die "Could not apply patches"

# NOTE -Wl,--exclude-libs,libgcc_eh.a is needed because of bug in shipped gcc:
# http://forums.codeblocks.org/index.php/topic,10508.msg72112.html#msg72112
# http://sourceforge.net/tracker/index.php?func=detail&aid=2813974&group_id=200665&atid=974439
# Bug present in TDM GCC 4.4.0 and fixed in TDB GCC 4.4.1-tdm-1
(cd $DIR &&
LDFLAGS="-Wl,--exclude-libs,libgcc_eh.a"	\
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
