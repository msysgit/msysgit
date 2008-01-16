#!/bin/sh

cd "$(dirname "$0")" && . ../common/update-lib.sh

check_pristine

package=zlib
version=1.2.3
url=http://www.zlib.net
d=zlib-$version
tar=$d.tar.gz
configure_options=--prefix=

download &&
extract &&
setup &&
compile

# update index
FILELIST=fileList.txt

pre_install

(cd $d && make install) || exit

post_install

