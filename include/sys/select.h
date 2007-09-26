/* select.h
   Copyright 1998, 1999, 2000, 2001 Red Hat, Inc.

   Written by Geoffrey Noer <noer@cygnus.com>

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#ifndef _SYS_SELECT_H
#define _SYS_SELECT_H

#if !defined (_POSIX_SOURCE) && !defined (__INSIDE_CYGWIN_NET__)

#include <sys/cdefs.h>

/* Get fd_set, and macros like FD_SET */
#include <sys/types.h>

/* Get definition of timeval.  */
#include <sys/time.h>
#include <time.h>

__BEGIN_DECLS

int select __P ((int __n, fd_set *__readfds, fd_set *__writefds,
		 fd_set *__exceptfds, struct timeval *__timeout));

__END_DECLS

#endif /* !_POSIX_SOURCE, !__INSIDE_CYGWIN_NET__ */

#endif /* sys/select.h */
