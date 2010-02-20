#!/bin/sh

cd "$(dirname "$0")"
srcdir=$(pwd)

mirror=http://www.zlib.net/
file=zlib-1.2.3.tar.gz
dir=${file%.tar.gz}

# download it
test -f $file || curl $mirror$file > $file || exit

# unpack it
test -d $dir || tar xzf $file || exit

# compile it
sysroot="$(pwd)/sysroot/x86_64-w64-mingw32"
cross="$(pwd)/sysroot/bin/x86_64-w64-mingw32"
test -f $dir/example.exe || {
	(cd $dir &&
	 CC="$cross-gcc.exe" AR="$cross-ar.exe rc" RANLIB="$cross-ranlib.exe" \
	 ./configure --prefix=$sysroot &&
	 make) || exit
}

# install it
test -f $sysroot/lib/libz.a ||
(cd $dir &&
 make install)
