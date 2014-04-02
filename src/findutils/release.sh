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

apply_patches

# `make` tries to reconfigure, if patched files are newer than aclocal.m4
find "$d"/ -name configure -o -name Makefile -o -name '*.in' -print0 |
xargs -0 -r touch

(cd "$d" && ../msys-build-findutils)

FILELIST=fileList.txt

strip _build/xargs/xargs.exe
cp _build/xargs/xargs.exe /bin/

post_install
