#!/bin/sh

cd "$(dirname "$0")" && . ../common/update-lib.sh

#check_pristine


package=openssh
version=6.0p1
url=http://mirror.bytemark.co.uk/OpenBSD/OpenSSH/portable/
d=$package-$version
tar=$d.tar.gz
configure_options=--prefix=

download_extract_setup_and_compile

# update index
FILELIST=fileList.txt

pre_install

(cd $d && make install) || exit

post_install

