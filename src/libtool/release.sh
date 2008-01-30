#!/bin/sh

cd "$(dirname "$0")" && . ../common/update-lib.sh

check_pristine

package=libtool
version=1.5.24
url=http://ftp.gnu.org/gnu/libtool
d=libtool-$version
tar=$d.tar.gz
configure_options="--prefix= --build=i686-pc-mingw32"

download &&
extract &&
setup &&
compile

# update index
FILELIST=fileList.txt

pre_install

(cd $d && make install) || exit

post_install

