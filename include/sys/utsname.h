/* sys/utsname.h

   Copyright 2001 Red Hat, Inc.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#ifndef _SYS_UTSNAME_H
#define _SYS_UTSNAME_H

#ifdef __cplusplus
extern "C" {
#endif

struct utsname
{
  char sysname[20];
  char nodename[20];
  char release[20];
  char version[20];
  char machine[20];
};

int uname (struct utsname *);

#ifdef __cplusplus
}
#endif

#endif
