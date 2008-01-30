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
setup

(cd $d &&
for fn in `ls *.c | grep -v example`; do
	libtool --mode=compile gcc -O3 -DUSE_MMAP -g -c -o $fn.lo $fn
done &&
libtool --mode=link gcc -shared -o libz.dll -Wl,--out-implib=libz.dll.a *.lo
)

# update index
FILELIST=fileList.txt

pre_install

(cd $d &&
	cp zconf.h /include/. &&
	cp zlib.h /include/. &&
	cp libz.dll /bin/. &&
	cp libz.dll.a /lib/.
) || exit

post_install

