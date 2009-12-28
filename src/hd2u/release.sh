#!/bin/sh

cd "$(dirname "$0")"

URL=http://hany.sk/~hany/_data/hd2u
TAR=hd2u-1.0.3.tgz
DIR=hd2u-1.0.3

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
	./configure --prefix=/mingw &&
	make &&
	index=$(/share/msysGit/pre-install.sh) &&
	make install &&
	/share/msysGit/post-install.sh $INDEX Install $DIR
)
