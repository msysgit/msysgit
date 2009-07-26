#!/bin/sh

cd "$(dirname "$0")" && . ../common/update-lib.sh

package=Subversion
version=1.6.3
url=http://subversion.tigris.org/downloads
d=subversion-$version
tar=$d.tar.bz2
tar2=subversion-deps-$version.tar.bz2
configure_options="--prefix= --disable-static --enable-shared --build=i686-pc-cygwin"

# Make sure that we're running in MSys mode
export MSYSTEM=MSYS
export PATH=/bin:$PATH

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
for config_sub in $(find $d -name config.sub)
do
	if ! grep -i cygwin $config_sub >/dev/null 2>&1
	then
		cp $d/build/config.sub $config_sub
	fi || break
done &&
apply_patches &&
(cd $d && ./autogen.sh && cd neon && ./autogen.sh) &&
setup &&
if test ! -f $d/libtool
then
	cp /bin/libtool $d
fi &&
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
 if test ! -f Makefile
 then
	mv ../libsvn_swig_perl/.libs/Makefile* ./
 fi &&
 make CCFLAGS=-Dstrtoll=strtol LDLOADLIBS="-L/lib -lsvn_ra_svn-1 -lsvn_ra_local-1 -lsvn_repos-1 -lsvn_fs-1 -lsvn_fs_fs-1 -lsvn_delta-1 -lsvn_subr-1 -laprutil-1 -lapr-1 -lneon -lexpat -lsvn_swig_perl-1 -lsvn_diff-1 -lsvn_client-1 -lsvn_ra-1 -lsvn_wc-1 -L/lib/perl5/5.8.8/msys/CORE/ -lperl -L/lib -lz" &&
 make install) || exit

post_install

