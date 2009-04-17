#!/bin/sh

die () {
	echo "$*" >&2
	exit 1
}

test -z "$URL" && die "Need URL"
test -z "$TARGET" && die "Need TARGET"

TAR=${URL##*/}
DIR=${TAR%.tar.bz2}

if ! test -s $TAR
then
	curl $URL > $TAR
fi &&
if ! test -d $DIR
then
	tar xjvf $TAR
fi &&
if ! test -f $DIR/Makefile
then
	(cd $DIR && ./configure --prefix=/mingw)
fi &&
if ! test -x $DIR/$TARGET
then
	(cd $DIR && make)
fi &&
INDEX=$(/share/msysGit/pre-install.sh) &&
(cd $DIR && make install) &&
/share/msysGit/post-install.sh $INDEX Install $DIR ||
die "Failed to install $DIR"
