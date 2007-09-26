/* sys/smallprint.h

   Copyright 1998, 2001 Red Hat, Inc.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#ifndef _SYS_SMALLPRINT_H
#define _SYS_SMALLPRINT_H

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

int __small_sprintf (char *__dst, const char *__fmt, ...);
int __small_vsprintf (char *__dst, const char *__fmt, va_list __ap);

#ifdef __cplusplus
};
#endif

#endif /* _SYS_SMALLPRINT_H */
