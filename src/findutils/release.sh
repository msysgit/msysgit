#!/bin/sh

cd "$(dirname "$0")"
. ../common/update-lib.sh
thisdir="$(pwd)"

check_pristine

set -e

package=findutils
version=4.4.2
url=ftp://ftp.gnu.org/pub/gnu/findutils
d=${package}-${version}
tar=${package}-${version}.tar.gz

download
extract

musttouch=
test -d "$d"/.git || musttouch=x
apply_patches

cd $d

# `make` tries to reconfigure, if patched files are newer than aclocal.m4
test $musttouch && find . ! -path "./.git/*" -type f -print0 | xargs -0 -r touch

../msys-build-findutils
cd ..

FILELIST=fileList.txt

strip _build/xargs/xargs.exe
cp _build/xargs/xargs.exe /bin/

post_install
