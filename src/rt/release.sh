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

if test -e $release
then
	echo "Error: Source directory build/$src already exists."
	exit 1
fi

(
tar xjvf $src &&
cd $release &&
git init &&
git config core.autocrlf false &&
git add . &&
git commit -m "Import of $release"
) ||
{ echo "Error: Initializing git repository from MSYS source fails." ; exit 1 ; }

cd $release
git am ../../patches/*.patch ||
{ echo "Error: Applying patches failed." ; exit 1 ; }

winpath=$(pwd -W)

cat <<EOD

The MSYS source is prepared in 

  $winpath

The source has been unpacked, checked in to git, and all necessary
patches have been applied.  You can verifying this by looking at
the git history.

Unfortunately, there is no automatic way to build msys-1.0.dll from
the source, so you now need to manually continue as described on:

   http://www.mingw.org/MinGWiki/index.php/Build%20MSYS

In a properly setup MSYS, you can start the build shell by

   msysdvlpr

In the newly opend build shell you need to run:

   cd $winpath
   mkdir bld
   cd bld
   ../source/configure --prefix=/usr
   make

The replacement for msys-1.0.dll will be created as

   i686-pc-msys/winsup/cygwin/new-msys-1.0.dll

You need to copy the new dll to your msysgit directory.  Note that
this is only possible if no msysgit bash is open.  Otherwise, Windows
refuses to replace the msys-1.0.dll.

EOD
