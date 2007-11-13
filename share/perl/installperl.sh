#!/bin/sh

url=ftp://ftp.funet.fi/pub/CPAN/src/
version=5.6.1

p=perl-$version
tar=$p.tar.gz
for ext in "" .md5
do
	f=$tar$ext
	test -f $f && continue
	echo "Downloading $f ..." 
	curl $url/$f -o $f || exit
done

echo "Verifying md5 sum ..." 
md5sum -c --status $tar.md5 || exit

test -d $p || {
	echo "Unpacking $tar ..."
	tar -xzf $tar || exit
}

cd $p || {
	echo "Could not cd to $p"
	exit 1
}

test -d .git || {
	git init &&
	git add . &&
	git commit -m "Perl $version from $tar" > /dev/null ||
	exit
}

git rev-parse --verify HEAD^ 2>/dev/null ||
	git am ../patches/* ||
	exit

MSYSTEM=MSYS

test -f config.sh || ./Configure -de || exit

LIB= make || exit

echo "Done"
