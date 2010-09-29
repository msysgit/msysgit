#!/bin/sh

cd "$(dirname "$0")"

URL=ftp://ftp.astron.com/pub/file
TAR=file-5.04.tar.gz
DIR=file-5.04
MD5='accade81ff1cc774904b47c72c8aeea0'

if test ! -f $TAR
then
	curl $URL/$TAR > $TAR
fi

echo "$MD5 *$TAR" > $TAR.md5
md5sum -c --status $TAR.md5 || (echo "invalid checksum for $TAR"; exit 1)

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
