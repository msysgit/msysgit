/* wchar.h

   Copyright 1998, 1999, 2000, 2001 Red Hat, Inc.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#ifndef _WCHAR_H
#define _WCHAR_H

#include <sys/cdefs.h>

/* Get wchar_t and wint_t from <stddef.h>.  */
#define __need_wchar_t
#define __need_wint_t
#include <stddef.h>

__BEGIN_DECLS

int wcscmp (const wchar_t *__s1, const wchar_t *__s2);
size_t wcslen (const wchar_t *__s1);

__END_DECLS

#endif /* _WCHAR_H */
