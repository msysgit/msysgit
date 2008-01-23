# This file is part of Autoconf.                       -*- Autoconf -*-
# Macros that test for specific, unclassified, features.
#
# Copyright (C) 1992, 1993, 1994, 1995, 1996, 1998, 1999, 2000, 2001,
# 2002 Free Software Foundation, Inc.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.
#
# As a special exception, the Free Software Foundation gives unlimited
# permission to copy, distribute and modify the configure scripts that
# are the output of Autoconf.  You need not follow the terms of the GNU
# General Public License when using or distributing such scripts, even
# though portions of the text of Autoconf appear in them.  The GNU
# General Public License (GPL) does govern all other use of the material
# that constitutes the Autoconf program.
#
# Certain portions of the Autoconf source text are designed to be copied
# (in certain cases, depending on the input) into the output of
# Autoconf.  We call these the "data" portions.  The rest of the Autoconf
# source text consists of comments plus executable code that decides which
# of the data portions to output in any given case.  We call these
# comments and executable code the "non-data" portions.  Autoconf never
# copies any of the non-data portions into its output.
#
# This special exception to the GPL applies to versions of Autoconf
# released by the Free Software Foundation.  When you make and
# distribute a modified version of Autoconf, you may extend this special
# exception to the GPL to apply to your modified version as well, *unless*
# your modified version has the potential to copy into its output some
# of the text that was the non-data portion of the version that you started
# with.  (In other words, unless your change moves or copies text from
# the non-data portions to the data portions.)  If your modification has
# such potential, you must delete any notice of this special exception
# to the GPL from your modified version.
#
# Written by David MacKenzie, with help from
# Franc,ois Pinard, Karl Berry, Richard Pixley, Ian Lance Taylor,
# Roland McGrath, Noah Friedman, david d zuhn, and many others.


## ------------------------- ##
## Checks for declarations.  ##
## ------------------------- ##


# AC_DECL_SYS_SIGLIST
# -------------------
AN_IDENTIFIER([sys_siglist],     [AC_CHECK_DECLS([sys_siglist])])
AU_DEFUN([AC_DECL_SYS_SIGLIST],
[AC_CHECK_DECLS([sys_siglist])
])# AC_DECL_SYS_SIGLIST




## -------------------------------------- ##
## Checks for operating system services.  ##
## -------------------------------------- ##


# AC_SYS_INTERPRETER
# ------------------
AC_DEFUN([AC_SYS_INTERPRETER],
[AC_CACHE_CHECK(whether @%:@! works in shell scripts, ac_cv_sys_interpreter,
[echo '#! /bin/cat
exit 69
' >conftest
chmod u+x conftest
(SHELL=/bin/sh; export SHELL; ./conftest >/dev/null)
if test $? -ne 69; then
   ac_cv_sys_interpreter=yes
else
   ac_cv_sys_interpreter=no
fi
rm -f conftest])
interpval=$ac_cv_sys_interpreter
])


AU_DEFUN([AC_HAVE_POUNDBANG],
[AC_SYS_INTERPRETER
AC_DIAGNOSE([obsolete],
[$0: Remove this warning when you adjust your code to use
      `AC_SYS_INTERPRETER'.])])


AU_DEFUN([AC_ARG_ARRAY],
[AC_DIAGNOSE([obsolete],
[$0: no longer implemented: don't do unportable things
with arguments. Remove this warning when you adjust your code.])])


# _AC_SYS_LARGEFILE_TEST_INCLUDES
# -------------------------------
m4_define([_AC_SYS_LARGEFILE_TEST_INCLUDES],
[@%:@include <sys/types.h>
 /* Check that off_t can represent 2**63 - 1 correctly.
    We can't simply define LARGE_OFF_T to be 9223372036854775807,
    since some C++ compilers masquerading as C compilers
    incorrectly reject 9223372036854775807.  */
@%:@define LARGE_OFF_T (((off_t) 1 << 62) - 1 + ((off_t) 1 << 62))
  int off_t_is_large[[(LARGE_OFF_T % 2147483629 == 721
		       && LARGE_OFF_T % 2147483647 == 1)
		      ? 1 : -1]];[]dnl
])


# _AC_SYS_LARGEFILE_MACRO_VALUE(C-MACRO, VALUE,
#                               CACHE-VAR,
#                               DESCRIPTION,
#                               [INCLUDES], [FUNCTION-BODY])
# ----------------------------------------------------------
m4_define([_AC_SYS_LARGEFILE_MACRO_VALUE],
[AC_CACHE_CHECK([for $1 value needed for large files], [$3],
[while :; do
  $3=no
  AC_COMPILE_IFELSE([AC_LANG_PROGRAM([$5], [$6])],
  		    [break])
  AC_COMPILE_IFELSE([AC_LANG_PROGRAM([@%:@define $1 $2
$5], [$6])],
  		    [$3=$2; break])
  break
done])
if test "$$3" != no; then
  AC_DEFINE_UNQUOTED([$1], [$$3], [$4])
fi
rm -f conftest*[]dnl
])# _AC_SYS_LARGEFILE_MACRO_VALUE


# AC_SYS_LARGEFILE
# ----------------
# By default, many hosts won't let programs access large files;
# one must use special compiler options to get large-file access to work.
# For more details about this brain damage please see:
# http://www.sas.com/standards/large.file/x_open.20Mar96.html
AC_DEFUN([AC_SYS_LARGEFILE],
[AC_ARG_ENABLE(largefile,
               [  --disable-largefile     omit support for large files])
if test "$enable_largefile" != no; then

  AC_CACHE_CHECK([for special C compiler options needed for large files],
    ac_cv_sys_largefile_CC,
    [ac_cv_sys_largefile_CC=no
     if test "$GCC" != yes; then
       ac_save_CC=$CC
       while :; do
     	 # IRIX 6.2 and later do not support large files by default,
     	 # so use the C compiler's -n32 option if that helps.
         AC_LANG_CONFTEST([AC_LANG_PROGRAM([_AC_SYS_LARGEFILE_TEST_INCLUDES])])
     	 AC_COMPILE_IFELSE([], [break])
     	 CC="$CC -n32"
     	 AC_COMPILE_IFELSE([], [ac_cv_sys_largefile_CC=' -n32'; break])
         break
       done
       CC=$ac_save_CC
       rm -f conftest.$ac_ext
    fi])
  if test "$ac_cv_sys_largefile_CC" != no; then
    CC=$CC$ac_cv_sys_largefile_CC
  fi

  _AC_SYS_LARGEFILE_MACRO_VALUE(_FILE_OFFSET_BITS, 64,
    ac_cv_sys_file_offset_bits,
    [Number of bits in a file offset, on hosts where this is settable.],
    [_AC_SYS_LARGEFILE_TEST_INCLUDES])
  _AC_SYS_LARGEFILE_MACRO_VALUE(_LARGE_FILES, 1,
    ac_cv_sys_large_files,
    [Define for large files, on AIX-style hosts.],
    [_AC_SYS_LARGEFILE_TEST_INCLUDES])
fi
])# AC_SYS_LARGEFILE


# AC_SYS_LONG_FILE_NAMES
# ----------------------
# Security: use a temporary directory as the most portable way of
# creating files in /tmp securely.  Removing them leaves a race
# condition, set -C is not portably guaranteed to use O_EXCL, so still
# leaves a race, and not all systems have the `mktemp' utility.  We
# still test for existence first in case of broken systems where the
# mkdir succeeds even when the directory exists.  Broken systems may
# retain a race, but they probably have other security problems
# anyway; this should be secure on well-behaved systems.  In any case,
# use of `mktemp' is probably inappropriate here since it would fail in
# attempting to create different file names differing after the 14th
# character on file systems without long file names.
AC_DEFUN([AC_SYS_LONG_FILE_NAMES],
[AC_CACHE_CHECK(for long file names, ac_cv_sys_long_file_names,
[ac_cv_sys_long_file_names=yes
# Test for long file names in all the places we know might matter:
#      .		the current directory, where building will happen
#      $prefix/lib	where we will be installing things
#      $exec_prefix/lib	likewise
# eval it to expand exec_prefix.
#      $TMPDIR		if set, where it might want to write temporary files
# if $TMPDIR is not set:
#      /tmp		where it might want to write temporary files
#      /var/tmp		likewise
#      /usr/tmp		likewise
if test -n "$TMPDIR" && test -d "$TMPDIR" && test -w "$TMPDIR"; then
  ac_tmpdirs=$TMPDIR
else
  ac_tmpdirs='/tmp /var/tmp /usr/tmp'
fi
for ac_dir in  . $ac_tmpdirs `eval echo $prefix/lib $exec_prefix/lib` ; do
  test -d $ac_dir || continue
  test -w $ac_dir || continue # It is less confusing to not echo anything here.
  ac_xdir=$ac_dir/cf$$
  (umask 077 && mkdir $ac_xdir 2>/dev/null) || continue
  ac_tf1=$ac_xdir/conftest9012345
  ac_tf2=$ac_xdir/conftest9012346
  (echo 1 >$ac_tf1) 2>/dev/null
  (echo 2 >$ac_tf2) 2>/dev/null
  ac_val=`cat $ac_tf1 2>/dev/null`
  if test ! -f $ac_tf1 || test "$ac_val" != 1; then
    ac_cv_sys_long_file_names=no
    rm -rf $ac_xdir 2>/dev/null
    break
  fi
  rm -rf $ac_xdir 2>/dev/null
done])
if test $ac_cv_sys_long_file_names = yes; then
  AC_DEFINE(HAVE_LONG_FILE_NAMES, 1,
            [Define to 1 if you support file names longer than 14 characters.])
fi
])


# AC_SYS_RESTARTABLE_SYSCALLS
# ---------------------------
# If the system automatically restarts a system call that is
# interrupted by a signal, define `HAVE_RESTARTABLE_SYSCALLS'.
AC_DEFUN([AC_SYS_RESTARTABLE_SYSCALLS],
[AC_DIAGNOSE([obsolete],
[$0: System call restartability is now typically set at runtime.
Remove this `AC_SYS_RESTARTABLE_SYSCALLS'
and adjust your code to use `sigaction' with `SA_RESTART' instead.])dnl
AC_REQUIRE([AC_HEADER_SYS_WAIT])dnl
AC_CHECK_HEADERS(unistd.h)
AC_CACHE_CHECK(for restartable system calls, ac_cv_sys_restartable_syscalls,
[AC_RUN_IFELSE([AC_LANG_SOURCE(
[/* Exit 0 (true) if wait returns something other than -1,
   i.e. the pid of the child, which means that wait was restarted
   after getting the signal.  */

#include <sys/types.h>
#include <signal.h>
#if HAVE_UNISTD_H
# include <unistd.h>
#endif
#if HAVE_SYS_WAIT_H
# include <sys/wait.h>
#endif

/* Some platforms explicitly require an extern "C" signal handler
   when using C++. */
#ifdef __cplusplus
extern "C" void ucatch (int dummy) { }
#else
void ucatch (dummy) int dummy; { }
#endif

int
main ()
{
  int i = fork (), status;

  if (i == 0)
    {
      sleep (3);
      kill (getppid (), SIGINT);
      sleep (3);
      exit (0);
    }

  signal (SIGINT, ucatch);

  status = wait (&i);
  if (status == -1)
    wait (&i);

  exit (status == -1);
}])],
               [ac_cv_sys_restartable_syscalls=yes],
               [ac_cv_sys_restartable_syscalls=no])])
if test $ac_cv_sys_restartable_syscalls = yes; then
  AC_DEFINE(HAVE_RESTARTABLE_SYSCALLS, 1,
            [Define to 1 if system calls automatically restart after
             interruption by a signal.])
fi
])# AC_SYS_RESTARTABLE_SYSCALLS


# AC_SYS_POSIX_TERMIOS
# --------------------
AC_DEFUN([AC_SYS_POSIX_TERMIOS],
[AC_CACHE_CHECK([POSIX termios], ac_cv_sys_posix_termios,
[AC_LINK_IFELSE([AC_LANG_PROGRAM([[#include <sys/types.h>
#include <unistd.h>
#include <termios.h>
]],
             [/* SunOS 4.0.3 has termios.h but not the library calls.  */
   tcgetattr(0, 0);])],
             ac_cv_sys_posix_termios=yes,
             ac_cv_sys_posix_termios=no)])
])# AC_SYS_POSIX_TERMIOS




## ------------------------------------ ##
## Checks for not-quite-Unix variants.  ##
## ------------------------------------ ##


# AC_GNU_SOURCE
# --------------
AC_DEFUN([AC_GNU_SOURCE],
[AH_VERBATIM([_GNU_SOURCE],
[/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# undef _GNU_SOURCE
#endif])dnl
AC_BEFORE([$0], [AC_COMPILE_IFELSE])dnl
AC_BEFORE([$0], [AC_RUN_IFELSE])dnl
AC_DEFINE([_GNU_SOURCE])
])


# AC_CYGWIN
# ---------
# Check for Cygwin.  This is a way to set the right value for
# EXEEXT.
AU_DEFUN([AC_CYGWIN],
[AC_CANONICAL_HOST
AC_DIAGNOSE([obsolete],
            [$0 is obsolete: use AC_CANONICAL_HOST and $host_os])dnl
case $host_os in
  *cygwin* ) CYGWIN=yes;;
         * ) CYGWIN=no;;
esac
])# AC_CYGWIN


# AC_EMXOS2
# ---------
# Check for EMX on OS/2.  This is another way to set the right value
# for EXEEXT.
AU_DEFUN([AC_EMXOS2],
[AC_CANONICAL_HOST
AC_DIAGNOSE([obsolete],
            [$0 is obsolete: use AC_CANONICAL_HOST and $host_os])dnl
case $host_os in
  *emx* ) EMXOS2=yes;;
      * ) EMXOS2=no;;
esac
])# AC_EMXOS2


# AC_MINGW32
# ----------
# Check for mingw32.  This is another way to set the right value for
# EXEEXT.
AU_DEFUN([AC_MINGW32],
[AC_CANONICAL_HOST
AC_DIAGNOSE([obsolete],
            [$0 is obsolete: use AC_CANONICAL_HOST and $host_os])dnl
case $host_os in
  *mingw32* ) MINGW32=yes;;
          * ) MINGW32=no;;
esac
])# AC_MINGW32




## -------------------------- ##
## Checks for UNIX variants.  ##
## -------------------------- ##


# These are kludges which should be replaced by a single POSIX check.
# They aren't cached, to discourage their use.

# AC_AIX
# ------
AC_DEFUN([AC_AIX],
[AH_VERBATIM([_ALL_SOURCE],
[/* Define to 1 if on AIX 3.
   System headers sometimes define this.
   We just want to avoid a redefinition error message.  */
@%:@ifndef _ALL_SOURCE
@%:@ undef _ALL_SOURCE
@%:@endif])dnl
AC_BEFORE([$0], [AC_COMPILE_IFELSE])dnl
AC_BEFORE([$0], [AC_RUN_IFELSE])dnl
AC_MSG_CHECKING([for AIX])
AC_EGREP_CPP(yes,
[#ifdef _AIX
  yes
#endif
],
[AC_MSG_RESULT([yes])
AC_DEFINE(_ALL_SOURCE)],
[AC_MSG_RESULT([no])])
])# AC_AIX


# AC_MINIX
# --------
AC_DEFUN([AC_MINIX],
[AC_BEFORE([$0], [AC_COMPILE_IFELSE])dnl
AC_BEFORE([$0], [AC_RUN_IFELSE])dnl
AC_CHECK_HEADER(minix/config.h, MINIX=yes, MINIX=)
if test "$MINIX" = yes; then
  AC_DEFINE(_POSIX_SOURCE, 1,
            [Define to 1 if you need to in order for `stat' and other things to
             work.])
  AC_DEFINE(_POSIX_1_SOURCE, 2,
            [Define to 2 if the system does not provide POSIX.1 features except
             with this defined.])
  AC_DEFINE(_MINIX, 1,
            [Define to 1 if on MINIX.])
fi
])# AC_MINIX


# AC_ISC_POSIX
# ------------
AC_DEFUN([AC_ISC_POSIX], [AC_SEARCH_LIBS(strerror, cposix)])


# AC_XENIX_DIR
# ------------
AU_DEFUN(AC_XENIX_DIR,
[# You shouldn't need to depend upon XENIX.  Remove this test if useless.
AC_MSG_CHECKING([for Xenix])
AC_EGREP_CPP(yes,
[#if defined(M_XENIX) && !defined(M_UNIX)
  yes
@%:@endif],
             [AC_MSG_RESULT([yes]); XENIX=yes],
             [AC_MSG_RESULT([no]); XENIX=])

AC_HEADER_DIRENT[]dnl
])


# AC_DYNIX_SEQ
# ------------
AU_DEFUN([AC_DYNIX_SEQ], [AC_FUNC_GETMNTENT])


# AC_IRIX_SUN
# -----------
AU_DEFUN([AC_IRIX_SUN],
[AC_FUNC_GETMNTENT
AC_CHECK_LIB(sun, getpwnam)])


# AC_SCO_INTL
# -----------
AU_DEFUN([AC_SCO_INTL], [AC_FUNC_STRFTIME])
