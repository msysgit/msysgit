#!/bin/sh

cd "$(dirname "$0")" && . ../common/update-lib.sh

package=swig
version=1.3.33
url=http://superb-west.dl.sourceforge.net/sourceforge/swig
d=swig-$version
tar=$d.tar.gz
configure_options="--prefix= --build=i686-pc-mingw32 --without-tcl --without-python --without-java --without-gcj --without-guile --without-mzscheme --without-ruby --without-ocaml --without-php4 --without-pike --without-chicken --without-csharp --without-lua --without-allegrocl --without-clisp --without-r"

download &&
extract &&
setup &&
compile

# update index
FILELIST=fileList.txt

pre_install

(cd $d && make install) || exit

post_install

