#!/bin/sh

cd "$(dirname "$0")" && . ../common/update-lib.sh

package=rebase
version=2.4.2-1
url=http://www.tishler.net/jason/software/rebase
d=rebase-$version
tar=$d-src.tar.bz2
configure_options=--prefix=

download &&
extract &&
test $d/.git || {
	cd $d &&
	git init &&
	rm -rf .git/hooks &&
	git add . &&
	git commit -m initial &&
	git am ../patches/*
} &&
compile &&
cp $d/rebase.exe /bin/ &&
(cd /bin && git add rebase.exe) &&
echo "You can commit rebase.exe now"
