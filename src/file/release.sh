#!/bin/sh

cd "$(dirname "$0")"

URL=ftp://ftp.astron.com/pub/file
TAR=file-5.03.tar.gz
DIR=file-5.03

if test ! -f $TAR
then
	curl $URL/$TAR > $TAR
fi &&
if test ! -d $DIR
then
	tar xzvf $TAR
fi &&
(cd $DIR &&
	git init &&
	git add . &&
	git commit -m initial &&
	git am ../patches/* &&
	CFLAGS="-I/git/compat/regex -DGAWK -DNO_MBSUPPORT" \
		./configure --prefix=/mingw &&
	make &&
	index=$(/share/msysGit/pre-install.sh) &&
	make install &&
	/share/msysGit/post-install.sh $INDEX Install $DIR
)
