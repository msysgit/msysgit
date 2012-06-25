#!/bin/sh

cd "$(dirname "$0")"
srcdir=$(pwd)

mirror=http://zlib.net/
file=zlib-1.2.7.tar.gz
dir=${file%.tar.gz}

die () {
	echo "$*" >&2
	exit 1
}

# download it
if ! (test -f $file || curl $mirror$file -o $file)
then
	echo "Could not download $file"
	echo "If you do not have a direct network connection please download"
	echo "$mirror$file"
	echo "place it in $srcdir and restart this script"
	exit 1
fi

# unpack it
test -d $dir || tar xzf $file || die "Failed to unpack archive"

# initialize Git repository
test -d $dir/.git ||
(cd $dir &&
 git init &&
 git config core.autocrlf false &&
 git add . &&
 git commit -m "Import of $file"
) || die "Failed to create repository"

# compile it
sysroot="$(pwd)/sysroot/x86_64-w64-mingw32"
cross="$(pwd)/sysroot/bin/x86_64-w64-mingw32"
test -f $dir/example.exe || {
	(cd $dir &&
	 CC="$cross-gcc.exe" AR="$cross-ar.exe" RANLIB="$cross-ranlib.exe" \
	 ./configure --static --prefix=$sysroot --uname=CYGWIN &&
	 make) || die "Failed to compile"
}

# install it
test -f $sysroot/lib/libz.a ||
(cd $dir &&
 make install)

for header in zlib.h zconf.h
do
	test -f $sysroot/include/$header ||
	cp $dir/$header $sysroot/include/
done
