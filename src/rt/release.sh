#!/bin/sh

release=MSYS-1_0_11
dir=msys/rt
cvs=:pserver:anonymous@mingw.cvs.sf.net:/cvsroot/mingw

die () {
	echo "$*" >&2
	exit 1
}

cd "$(dirname "$0")"
mkdir -p build
cd build

debug=
test "a$1" = "a--debug" && debug=t
debug_clean=
test "$debug" = "$(cat debug.txt 2>/dev/null)" || debug_clean=t
echo "$debug" > debug.txt

test -e $release/$dir ||
(
mkdir -p $release &&
cd $release &&
cvs -d$cvs co -r$release $dir) ||
die "Could not check out from CVS"

cd $release/$dir || {
  echo "Huh? $release does not exist."
  exit 1
}

test -d .git || {
git init &&
git config core.autocrlf false &&
git add . &&
git commit -m "Import of $release"
} ||
die "Error: Initializing git repository from MSYS source fails."

current=$(git rev-list --all | wc -l) &&
total=$(ls ../../../../patches/*.patch | wc -l) &&
i=1 &&
while test $i -le $total
do
	test $i -lt $current ||
	git am ../../../../patches/$(printf "%04d" $i)*.patch || break
	i=$(($i+1))
done ||
die "Error: Applying patches failed."

test -f /bin/cc.exe || ln gcc.exe /bin/cc.exe ||
die "Could not make sure that MSys cc is found instead of MinGW one"

(export MSYSTEM=MSYS &&
 (test -d bld || mkdir bld) &&
 cd bld &&
 DLL=i686-pc-msys/winsup/cygwin/new-msys-1.0.dll &&
 (test -f Makefile && test -z "$debug_clean" ||
  ../src/configure --prefix=/usr) &&
 (test -z "$debug" || perl -i.bak -pe 's/-O2//g' $(find -name Makefile)) &&
 (test -z "$debug_clean" || make clean) &&
 (make || test -f $DLL) &&
 (test ! -z "$debug" || strip $DLL) &&
 rebase -b 0x68000000 $DLL &&
 mv $DLL /bin/) &&
cd / &&
hash=$(git hash-object -w bin/new-msys-1.0.dll) &&
git update-index --cacheinfo 100755 $hash bin/msys-1.0.dll &&
git commit -s -m "Updated msys-1.0.dll to $release" &&
/share/msysGit/post-checkout-hook HEAD^ HEAD 1
