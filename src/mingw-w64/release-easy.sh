#!/bin/sh

cd "$(dirname "$0")"
srcdir=$(pwd)

# http://kent.dl.sourceforge.net/sourceforge/
mirror=http://ignum.dl.sourceforge.net/project/mingw-w64/
subdir=Toolchains%20targetting%20Win64/Automated%20Builds/
file=mingw-w64-bin_i686-mingw_20110314.zip
dir=${file%.zip}

# download it
test -f $file || curl $mirror$subdir$file > $file || exit

# unpack & install it
test -f sysroot/.root.init.marker &&
test sysroot/.root.init.marker -nt $file ||
(mkdir -p sysroot &&
 cd sysroot &&
 unzip ../$file &&
 touch .root.init.marker
)
