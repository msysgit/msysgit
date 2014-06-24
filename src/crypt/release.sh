#!/bin/sh

cd "$(dirname "$0")" && . ../common/update-lib.sh

check_pristine

package=crypt
version=1.1-1
url=http://mirrors.kernel.org/sourceware/cygwin/x86/release/crypt/
d=crypt-$version
tar=$d-src.tar.bz2

download &&
extract &&
apply_patches

# update index
FILELIST=fileList.txt

pre_install

opt_flags="-O3 -s -march=i386"
export CFLAGS=${CFLAGS:-"${opt_flags}"}
export CPPFLAGS="${CPPFLAGS} -D__CYGWIN__"
export LDFLAGS="${LDFLAGS} -Wl,--enable-auto-import"

(cd $d &&
	make CPPFLAGS="${CPPFLAGS}" \
	CFLAGS="${CFLAGS}" \
	LDFLAGS="${LDFLAGS}" || die "Could not make $FILE"
)

# install executable files
(cd $d &&
	install msys-crypt-0.dll /bin/ || die "Could not install"
	install libcrypt.dll.a /lib/ || die "Could not install"
) || die "Could not install"

post_install

