#!/bin/sh

cd "$(dirname "$0")"

VERSION=7.28.1
DIR=curl-$VERSION
URL=http://curl.haxx.se/download/$DIR.tar.bz2
FILE=${URL##*/}

die () {
	echo "$*" >&2
	exit 1
}

cleanup_old_curl () {
    for f in \
        /mingw/bin/libcurl-4.dll \
        /mingw/bin/curl-config \
        /mingw/bin/libcurl.la
    do
        [ -f $f ] && rm -f $f
    done
    return 0
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
CFG='-ipv6 -zlib -sspi -spnego -winssl -ldaps' \
ZLIB_PATH=/src/zlib/zlib-1.2.7 \
make mingw32 &&
index=$(/share/msysGit/pre-install.sh) &&
cleanup_old_curl &&
/bin/install -m 0755 src/curl.exe /mingw/bin/curl.exe &&
/bin/install -m 0755 lib/libcurl.dll /mingw/bin/libcurl.dll &&
/bin/install -m 0755 lib/libcurl.a /mingw/lib/libcurl.a &&
/bin/install -m 0755 lib/libcurldll.a /mingw/lib/libcurl.dll.a &&
/bin/install -m 0644 include/curl/*.h /mingw/include/curl/ &&
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
