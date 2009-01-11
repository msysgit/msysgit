#!/bin/sh

release=MSYS-1.0.11-20071204-src
src=$release.tar.bz2
mirror=http://heanet.dl.sourceforge.net/sourceforge/mingw/

mkdir -p build
cd build

if ! test -e $src
then
	curl -o $src $mirror/$src
fi

test -e $release ||
(
tar xjvf $src &&
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
 (test -f Makefile || ../source/configure --prefix=/usr) &&
 (make || test -f i686-pc-msys/winsup/cygwin/new-msys-1.0.dll)) &&
 mv bld/i686-pc-msys/winsup/cygwin/new-msys-1.0.dll /bin/ &&
cat << EOD
The new msys-1.0.dll was built successfully and is available as

	$(cd /bin/ && pwd -W)/new-msys-1.0.dll

Please exit all msysGit instances, replace msys-1.0.dll with that file, and
restart msysGit.
EOD
