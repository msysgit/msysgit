/* dlfcn.h

   Copyright 1998, 1999, 2000, 2001 Red Hat, Inc.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#ifndef _DLFCN_H
#define _DLFCN_H

#ifdef __cplusplus
extern "C" {
#endif

/* declarations used for dynamic linking support routines */
extern void *dlopen (const char *, int);
extern void *dlsym (void *, const char *);
extern int dlclose (void *);
extern char *dlerror (void);

/* specific to CYGWIN */
#define FORK_RELOAD	1
#define FORK_NO_RELOAD	0

extern void dlfork (int);

/* following doesn't exist in Win32 API .... */

/* valid values for mode argument to dlopen */
#define RTLD_LAZY	1	/* lazy function call binding */
#define RTLD_NOW	2	/* immediate function call binding */
#define RTLD_GLOBAL	4	/* symbols in this dlopen'ed obj are visible to other dlopen'ed objs */

#ifdef __cplusplus
}
#endif

#endif /* _DLFCN_H */
