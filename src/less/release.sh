#!/bin/sh

cd "$(dirname "$0")" && . ../common/update-lib.sh

#check_pristine

export MSYSTEM=MSYS

# build libtermcap first
test -f /lib/libtermcap.a || (
	termcapdir=../msys/msys/packages/termcap/1.3.1 &&
	test -d $termcapdir ||
	(
		cd ../.. &&
		git submodule update --init src/msys
	) &&
	cd $termcapdir &&
	(test -f Makefile || ./configure) &&
	make &&
	cp libtermcap.a /lib
) || die "Failed to build libtermcap.a"

# get and compile less
package=Less
version=444
url=http://www.greenwoodsoftware.com/less
d=less-$version
tar=$d.tar.gz
configure_options="--prefix="

download_extract_setup_and_compile

# update index
FILELIST=fileList.txt

pre_install

(cd $d && make install-strip) ||
die "Failed to install less binaries"

post_install
