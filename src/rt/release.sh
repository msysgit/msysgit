#!/bin/sh

release=MSYS-1.0.11-20090120-src
src=$release.tar.gz
mirror=http://heanet.dl.sourceforge.net/sourceforge/mingw

cd "$(dirname "$0")"
mkdir -p build
cd build

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

test 1 -lt $(git rev-list --all | wc -l) ||
git am ../../patches/*.patch ||
{ echo "Error: Applying patches failed." ; exit 1 ; }

(export MSYSTEM=MSYS &&
 (test -d bld || mkdir bld) &&
 cd bld &&
 DLL=i686-pc-msys/winsup/cygwin/new-msys-1.0.dll &&
 (test -f Makefile || ../source/configure --prefix=/usr) &&
 (make || test -f $DLL) &&
 strip $DLL &&
 rebase -b 0x30000000 $DLL &&
 mv $DLL /bin/) &&
cd / &&
hash=$(git hash-object -w bin/new-msys-1.0.dll) &&
git update-index --cacheinfo 100755 $hash bin/msys-1.0.dll &&
git commit -s -m "Updated msys-1.0.dll to ${release%-src}" &&
/share/msysGit/post-checkout-hook HEAD^ HEAD 1
