/* sys/sysmacros.h

   Copyright 1998, 2001 Red Hat, Inc.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#ifndef _SYS_SYSMACROS_H
#define _SYS_SYSMACROS_H

#define major(dev) ((int)(((dev) >> 8) & 0xff))
#define minor(dev) ((int)((dev) & 0xff))
#define makedev(major, minor) (((major) << 8) | (minor))

#endif /* _SYS_SYSMACROS_H */
