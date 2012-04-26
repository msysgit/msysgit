#!/bin/sh

cd "$(dirname "$0")"
srcdir=$(pwd)

mirror=http://zlib.net/
file=zlib-1.2.6.tar.gz
dir=${file%.tar.gz}

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
test -d $dir || tar xzf $file || exit

# initialize Git repository
test -d $dir/.git ||
(cd $dir && git init && git add . && git commit -m initial) || exit

# patch it
if ! grep DISABLED_MINGW $dir/configure > /dev/null 2>&1
then
	(cd $dir && git apply --verbose ../patch/zlib-config.patch) || exit
fi

# compile it
sysroot="$(pwd)/sysroot/x86_64-w64-mingw32"
cross="$(pwd)/sysroot/bin/x86_64-w64-mingw32"
test -f $dir/example.exe || {
	(cd $dir &&
	 CC="$cross-gcc.exe" AR="$cross-ar.exe" RANLIB="$cross-ranlib.exe" \
	 ./configure --static --prefix=$sysroot &&
	 make) || exit
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
