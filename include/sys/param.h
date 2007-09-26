/* sys/param.h

   Copyright 2001 Red Hat, Inc.

   This software is a copyrighted work licensed under the terms of the
   Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
   details. */

#ifndef _SYS_PARAM_H
#define _SYS_PARAM_H

#include <sys/types.h>
/* Linux includes limits.h, but this is not universally done. */
#include <limits.h>

/* Max number of open files.  The Posix version is OPEN_MAX.  */
/* Number of fds is virtually unlimited in cygwin, but we must provide
   some reasonable value for Posix conformance */
#define NOFILE		8192

/* Max number of groups; must keep in sync with NGROUPS_MAX in limits.h */
#define NGROUPS		16

/* Ticks/second for system calls such as times() */
/* FIXME: is this the appropriate value? */
#define HZ		1000

/* Max hostname size that can be dealt with */
/* FIXME: is this the appropriate value? */
#define MAXHOSTNAMELEN	64

/* This is defined to be the same as MAX_PATH which is used internally.
   The Posix version is PATH_MAX.  */
#define MAXPATHLEN      (260 - 1 /*NUL*/)

/* Some autoconf'd packages check for endianness.  When cross-building we
   can't run programs on the target.  Fortunately, autoconf supports the
   definition of byte order in sys/param.h (that's us!).
   The values here are the same as used in gdb/defs.h (are the more
   appropriate values?).  */
#define BIG_ENDIAN	4321
#define LITTLE_ENDIAN	1234

/* All known win32 systems are little endian.  */
#define BYTE_ORDER	LITTLE_ENDIAN

#ifndef NULL
#define NULL            0L
#endif

#endif
