#!/bin/sh

cd "$(dirname "$0")" && . ../common/update-lib.sh

package=gnupg
version=1.4.13
d=$package-$version
tar=$d.tar.gz
url=http://www.mirrorservice.org/sites/ftp.gnupg.org/gcrypt/gnupg
sha1=9f2696f3b61cb771053db599e884952c80d2a6e7
configure_options=

download &&
test -d $d || {
	tar xzf $tar && (
		cd $d &&
		git init &&
		git config core.autocrlf false &&
		git add . &&
		git commit -m "Import of $tar"
	)
} || die "Could not check out gnupg source"

test $(cd $d && git rev-list HEAD | wc -l) -gt 1 ||
(cd $d && git am ../patches/*) ||
die "Could not apply patches"

(cd $d &&
CFLAGS='-O3 -m32 -march=pentium-m -mfpmath=sse' LDFLAGS='-s' \
	./configure --prefix=/mingw &&
make &&
index=$(/share/msysGit/pre-install.sh) &&
make install-exec &&
mv /mingw/libexec/gnupg/* /mingw/bin/ &&
rmdir /mingw/libexec/gnupg &&
/share/msysGit/post-install.sh $index "Install $tar"
) || die "Could not install $tar"
