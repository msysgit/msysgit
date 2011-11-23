#!/bin/sh

cd "$(dirname "$0")"

VERSION=1.14
DIR=libiconv-$VERSION
URL=http://ftp.gnu.org/pub/gnu/libiconv/$DIR.tar.gz
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
export am_cv_proto_iconv_arg1= &&
export am_cv_proto_iconv="extern size_t iconv (iconv_t cd, char * *inbuf, size_t *inbytesleft, char * *outbuf, size_t *outbytesleft);" &&
./configure --prefix=/mingw &&
make &&
index=$(/share/msysGit/pre-install.sh) &&
make install &&
/share/msysGit/post-install.sh $index "Install $FILE"
) || die "Could not install $FILE"
