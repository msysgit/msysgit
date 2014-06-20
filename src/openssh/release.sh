#!/bin/sh

cd "$(dirname "$0")" && . ../common/update-lib.sh

check_pristine

package=openssh
version=5.4p1
url=http://ftp.OpenBSD.org/pub/OpenBSD/OpenSSH/portable/
d=openssh-$version
tar=$d.tar.gz

opt_flags="-O3 -s -march=i386"
export CFLAGS=${CFLAGS:-"${opt_flags}"}
export CPPFLAGS="${CPPFLAGS} -D__CYGWIN__"
export LDFLAGS="${LDFLAGS} -Wl,--enable-auto-import"

configure_options="--prefix=/usr --libexecdir=/libexec \
	--datarootdir=\${prefix}/share
	--without-rpath --sysconfdir=/etc/ssh --with-mantype=man \
	--with-libs=-lminires"


do_textreadmode() {
	test -f /lib/textreadmode.o && return
	cat > "$d"/textreadmode.c <<-"EOF"
/* textreadmode.c

   Copyright 2004 Red Hat, Inc.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#include <windows.h>
#include <sys/fcntl.h>
#include <sys/cygwin.h>

void
cygwin_premain0 (int argc, char **argv, struct per_process *myself)
{
  static struct __cygwin_perfile pf[] =
    {
      {"", O_RDONLY | O_TEXT},
      {NULL, 0}
    };
  cygwin_internal (CW_PERFILE, pf);
}
EOF
	gcc -D__CYGWIN__ -o /lib/textreadmode.o -c "$d"/textreadmode.c &&
	rm -f "$d"/textreadmode.c ||
		die "Could not make textreadmode.o"
}

make_interface_libaries() {
	test -f /lib/libminires.dll.a && return
	(pexports /bin/msys-minires.dll > "$d"/tmp.def &&
	 dlltool -D msys-minires.dll -d "$d"/tmp.def -l /lib/libminires.dll.a &&
	 pexports /bin/msys-z.dll > "$d"/tmp.def &&
	 dlltool -D msys-z.dll -d "$d"/tmp.def -l /lib/libz.dll.a &&
	 pexports /bin/msys-crypto-0.9.8.dll | sed '1 s/-0\.9\.8//' > "$d"/tmp.def &&
	 dlltool -D msys-crypto-0.9.8.dll -d "$d"/tmp.def -l /lib/libcrypto.dll.a &&
	 rm -f "$d"/tmp.def) ||
		die "Could not make interface libraries"
}


download &&
extract &&
apply_patches &&
do_textreadmode &&
make_interface_libaries

(cd "$d" && autoreconf -ivf) || die "Could not autoreconf"

setup
compile

# update index
FILELIST=fileList.txt

pre_install

(cd "$d" && make install) || die "Could not install"

post_install
