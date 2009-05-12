#!/bin/sh

release=MSYS-1.0.11-20090120-src
src=$release.tar.gz
mirror=http://heanet.dl.sourceforge.net/sourceforge/mingw

cd "$(dirname "$0")"
mkdir -p build
cd build

debug=
test "a$1" = "a--debug" && debug=t
debug_clean=
test "$debug" = "$(cat debug.txt 2>/dev/null)" || debug_clean=t
echo "$debug" > debug.txt

if ! test -e $src
then
	curl -o $src $mirror/$src
fi

test -e $release ||
(
tar xzvf $src &&
cd $release &&
git init &&
git config core.autocrlf false &&
git add . &&
git commit -m "Import of $release"
) ||
{ echo "Error: Initializing git repository from MSYS source fails." ; exit 1 ; }

cd $release || {
  echo "Huh? $release does not exist."
  exit 1
}

i=$(git rev-list --all | wc -l) &&
total=$(ls ../../patches/*.patch | wc -l) &&
while test $i -le $total
do
	git am ../../patches/$(printf "%04d" $i)*.patch || break
	i=$(($i+1))
done ||
{ echo "Error: Applying patches failed." ; exit 1 ; }

(export MSYSTEM=MSYS &&
 (test -d bld || mkdir bld) &&
 cd bld &&
 DLL=i686-pc-msys/winsup/cygwin/new-msys-1.0.dll &&
 (test -f Makefile && test -z "$debug_clean" ||
  ../source/configure --prefix=/usr) &&
 (test -z "$debug" || perl -i.bak -pe 's/-O2//g' $(find -name Makefile)) &&
 (test -z "$debug_clean" || make clean) &&
 (make || test -f $DLL) &&
 (test ! -z "$debug" || strip $DLL) &&
 rebase -b 0x30000000 $DLL &&
 mv $DLL /bin/) &&
cd / &&
hash=$(git hash-object -w bin/new-msys-1.0.dll) &&
git update-index --cacheinfo 100755 $hash bin/msys-1.0.dll &&
git commit -s -m "Updated msys-1.0.dll to ${release%-src}" &&
/share/msysGit/post-checkout-hook HEAD^ HEAD 1
