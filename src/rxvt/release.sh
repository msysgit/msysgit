#!/bin/sh

cd "$(dirname "$0")" && . ../common/update-lib.sh

package=rxvt
version=2.7.10
url=http://puzzle.dl.sourceforge.net/sourceforge/rxvt
d=rxvt-$version
tar=$d.tar.gz
configure_options=--prefix=

download &&
extract &&
perl -i.bak -pe 's/CYGWIN/MSYS/g;s/cygwin/msys/g' \
	$(find $d -name config.guess) $(find $d -name config.sub) &&
(test -f $d/config.log || ! test -f $d/Makefile || rm $d/Makefile) &&
apply_patches &&
export CFLAGS=-I"$(pwd)/$d/W11" &&
export LDFLAGS=-L"$(pwd)/$d/W11/lib" &&
setup &&
(d=$d/W11 &&
 compile) &&
compile ||
exit

# update index
FILELIST=fileList.txt

pre_install

(cd $d/W11 &&
 make install) || exit
(cd $d/src &&
 EXEEXT=.exe make install) || exit

post_install

