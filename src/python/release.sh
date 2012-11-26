#!/bin/sh

cd "$(dirname "$0")" && . ../common/update-lib.sh

package=Python
version=2.7.3
url=http://www.python.org/ftp/python/$version
d=$package-$version
tar=$d.tar.bz2
configure_options=--enable-shared
export CPPFLAGS="-IPC"

download &&
extract &&
test -d $d/.git || (
	cd $d &&
	git init &&
	rm -rf .git/hooks &&
	git add . &&
	git commit -m initial &&
	git am ../patches/*
) &&
setup &&
rm -f $d/pyconfig.h &&
cp $d/PC/pyconfig.h $d &&
(cd "$d" &&
	make &&
	index=$(/share/msysGit/pre-install.sh) &&
	make install &&
	/share/msysGit/post-install.sh $INDEX Install $DIR
) &&
echo "Finished building"
