#!/bin/sh
VERSION=3.1
DIR=mongoose
URL=http://mongoose.googlecode.com/files/$DIR-$VERSION.tgz
FILE=${URL##*/}

die () {
	echo "$*" >&2
	exit 1
}

cd "$(dirname "$0")" || die "Could not cd to source directory"

test -d $DIR || {
	test -f $FILE ||
	curl -O $URL ||
	die "Could not download $FILE"

	tar xzvf $FILE
} || die "Could not check out $FILE"

(cd $DIR &&
index=$(/share/msysGit/pre-install.sh) &&
make mingw &&
strip mongoose.exe &&
cp mongoose.exe /bin &&
/share/msysGit/post-install.sh $index "Install $FILE"
) || die "Could not install $FILE"
