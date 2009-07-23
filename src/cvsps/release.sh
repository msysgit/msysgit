#!/bin/sh

cd "$(dirname "$0")" && . ../common/update-lib.sh


package=cvsps
version=yd
url=git://repo.or.cz/cvsps-yd.git/
d=cvsps-$version
configure_options=--prefix=
FILELIST=fileList.txt

{
	test -d "$d" || git clone $url
} &&
setup &&
compile &&
pre_install &&
(cd $d && make install) &&
post_install

