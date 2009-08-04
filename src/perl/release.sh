#!/bin/sh

cd "$(dirname "$0")" && . ../common/update-lib.sh

# Make sure that the working directory is clean and does not have untracked
# files; otherwise our semi-automatic finding the new files will not work!
check_pristine

package=Perl
version=5.8.8
url=ftp://ftp.funet.fi/pub/CPAN/src
d=perl-$version
tar=$d.tar.gz
configure_options=-de

export MSYSTEM=MSYS

download &&
extract &&
apply_patches &&
setup

# Remove old Perl files stored in fileList.txt
FILELIST=fileList.txt

pre_install

# TODO! why is msys-perl5_8.dll not installed properly?
(cd $d && LIB= make install) || exit

post_install
