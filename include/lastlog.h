/* lastlog.h

   Copyright 2001 Red Hat, Inc.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#ifndef _LASTLOG_H
#define _LASTLOG_H

#include <utmp.h>

struct lastlog {
	long ll_time;
	char ll_line[UT_LINESIZE];
	char ll_host[UT_HOSTSIZE];
};

#endif
