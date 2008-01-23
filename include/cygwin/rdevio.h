/* cygwin/rdevio.h

   Copyright 1999, 2001 Red Hat, Inc.

   Written by Corinna Vinschen <corinna@vinschen.de>

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

/*
 * cygwin/rdevio.h header file for Cygwin.
 *
 * Written by C. Vinschen.
 */

#ifndef _CYGWIN_RDEVIO_H
#define _CYGWIN_RDEVIO_H

/* structure for RDIOCDOP - raw device operation */
struct rdop {
	short		rd_op;
	unsigned long	rd_parm;
};

/* Raw device operations */
#define RDSETBLK	1	/* set buffer for driver */

/* structure for RDIOCGET - get raw device */
struct rdget {
	unsigned long	bufsiz;
};

/*
 * ioctl commands
*/
#define RDIOCDOP	_IOW('r', 128, struct rdop)
#define RDIOCGET	_IOR('r', 129, struct rdget)

#endif /* _CYGWIN_RDEVIO_H */
