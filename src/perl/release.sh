#!/bin/sh

cd "$(dirname "$0")" ; . ../common/update-lib.sh

check_pristine

package=perl
url=ftp://ftp.funet.fi/pub/CPAN/src/5.0
version=5.8.8
md5='b8c118d4360846829beb30b02a6b91a7'

d=perl-$version
tar=$d.tar.gz

download

echo "Verifying md5 sum ..." 
echo "$md5 *$tar" | md5sum -c --status || { echo 'Invalid md5 sum :('; exit 1; }

extract

apply_patches

MSYSTEM=MSYS
export MSYSTEM

( cd "$d" ; test -f config.sh || ./Configure -de ) || die "Configure failure"

compile

[ "$1" = -n ] && die "DEBUG: aborting before install"

FILELIST=fileList.txt
pre_install

# TODO! why is msys-perl5_8.dll not installed properly?
(cd "$d"; LIB= make install ) || exit

post_install

