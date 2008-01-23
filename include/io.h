/* io.h

   Copyright 1999, 2000, 2001 Red Hat, Inc.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#ifndef _IO_H_
#define _IO_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
 * Function to return a Win32 HANDLE from a fd.
 */
extern long get_osfhandle(int);
extern int setmode (int __fd, int __mode);

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* _IO_H_ */
