#!/bin/sh

cd "$(dirname "$0")" && . ../common/update-lib.sh

check_pristine

package=CVS
version=1.11.22
url=http://ftp.gnu.org/non-gnu/cvs/source/stable/$version
d=cvs-$version
tar=$d.tar.bz2
configure_options=--prefix=

download_extract_setup_and_compile

# update index
FILELIST=fileList.txt

pre_install

(cd $d && make install) || exit

post_install

