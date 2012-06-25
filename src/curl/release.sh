#!/bin/sh

cd "$(dirname "$0")"

VERSION=7.26.0
DIR=curl-$VERSION
URL=http://curl.haxx.se/download/$DIR.tar.bz2
FILE=${URL##*/}

die () {
	echo "$*" >&2
	exit 1
}

test -d $DIR || {
	test -f $FILE ||
	curl -O $URL ||
	die "Could not download cURL"

	tar xjvf $FILE && (
		cd $DIR &&
		git init &&
                git config core.autocrlf false &&
		git add . &&
		git commit -m "Import of $FILE"
	)
} || die "Could not check out cURL"

test $(cd $DIR && git rev-list HEAD | wc -l) -gt 1 ||
(cd $DIR && git am ../patches/*) ||
die "Could not apply patches"

(cd $DIR &&
./configure --prefix=/mingw --with-ssl=/mingw --enable-sspi --disable-shared &&
make &&
index=$(/share/msysGit/pre-install.sh) &&
make install &&
make ca-bundle &&
ls ../certs/*.pem 2>/dev/null |
while read pem
do
	name=${pem%.pem}
	name=${name##*/}
	(printf "\n%s\n%s\n" "$name" "$(echo "$name" | sed 's/./=/g')"  &&
	 cat $pem) >> lib/ca-bundle.crt || break
done &&
cp lib/ca-bundle.crt /mingw/bin/curl-ca-bundle.crt &&
/share/msysGit/post-install.sh $index "Install $FILE"
) || die "Could not install $FILE"
