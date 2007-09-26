/* tzfile.h

   Copyright 2001 Red Hat, Inc.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#ifndef _TZFILE_H
#define _TZFILE_H

#define SECSPERDAY	(60*60*24)
#define DAYSPERNYEAR	365
#define DAYSPERLYEAR    366

#define isleap(y) (((y) % 4) == 0 && ((y) % 100) != 0 || ((y) % 400) == 0)
#endif
