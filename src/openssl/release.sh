#!/bin/sh

cd "$(dirname "$0")" && . ../common/update-lib.sh

check_pristine

package=openssl
version=1.0.1i
url=http://www.openssl.org/source
d=$package-$version
tar=$d.tar.gz

download &&
extract &&
apply_patches

export CPPFLAGS="${CPPFLAGS} -D__CYGWIN__"
export LDFLAGS="${LDFLAGS} -s -Wl,--enable-auto-import"
export SHARED_LDFLAGS="${SHARED_LDFLAGS} -Wl,--enable-auto-import"

(cd "$d" && ./Configure --prefix=/usr \
  --openssldir=/usr/ssl \
  --enginesdir=/usr/lib/openssl/engines \
  --libdir=lib \
  shared \
  zlib \
  no-idea \
  no-rc5 \
  no-asm \
  Msys) || die "Could not configure"


(cd "$d" && make depend) || die "Could not make depend"

(cd "$d" &&
	make LDFLAGS="$LDFLAGS" SHARED_LDFLAGS="$SHARED_LDFLAGS"
	) || die "Could not make"

# update index
FILELIST=fileList.txt

pre_install

(cd "$d" && make install) || die "Could not install"

post_install
