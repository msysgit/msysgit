#!/bin/sh

cd "$(dirname "$0")" && . ../common/update-lib.sh

check_pristine

package=Subversion
version=1.4.6
url=http://subversion.tigris.org/downloads
d=subversion-$version
tar=$d.tar.bz2
tar2=subversion-deps-$version.tar.bz2
configure_options="--prefix= --disable-static --enable-shared --build=i686-pc-mingw32"

# check for presence of libz (MSys), perl >= 5.8
perl -e 'require 5.8.0' || exit
test -f /include/zconf.h || {
	echo "MSys version of libz required."
	exit 1
}

download &&
extract &&
(tar=$tar2 &&
 d=$d/apr &&
 download &&
 extract) &&
perl -i.bak -pe 's/CYGWIN/MSYS/g;s/cygwin/msys/g' \
	$(find $d -name config.guess) $(find $d -name config.sub) &&
apply_patches &&
(cd $d && ./autogen.sh && cd neon && ./autogen.sh) &&
setup &&
perl -i.bak -pe 's/(deplibs_check_method=).*/\1pass_all/' \
	$(find $d -name libtool) &&
perl -i.bak -pe 's/(old_library=")(libexpat.a")/\1.libs\/\2/' \
	$d/apr-util/xml/expat/lib/libexpat.la &&
(cd $d && make LDFLAGS="-no-undefined -Wl,-enable-auto-import -L/lib" )

# update index
FILELIST=fileList.txt

pre_install

(cd $d && make install) || exit

(cd $d && 
   make swig-pl-lib LDFLAGS="-no-undefined -Wl,-enable-auto-import -L/lib" LIBS="-L/lib/perl5/5.8.8/msys/CORE -lperl" && 
     make install-swig-pl-lib &&
 cd subversion/bindings/swig/perl/native &&
 perl Makefile.PL &&
 mv ../libsvn_swig_perl/.libs/Makefile* ./ &&
 make CCFLAGS=-Dstrtoll=strtol LDLOADLIBS="-L/lib -lsvn_ra_dav-1 -lsvn_ra_svn-1 -lsvn_ra_local-1 -lsvn_repos-1 -lsvn_fs-1 -lsvn_fs_fs-1 -lsvn_delta-1 -lsvn_subr-1 -laprutil-0 -lapr-0 -lneon -lexpat -lsvn_swig_perl-1 -lsvn_diff-1 -lsvn_client-1 -lsvn_ra-1 -lsvn_wc-1 -L/lib/perl5/5.8.8/msys/CORE/ -lperl -L/lib -lz" &&
 make install) || exit

post_install

