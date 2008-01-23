/* sys/uio.h

   Copyright 1996, 2000, 2001 Red Hat, Inc.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#ifndef _UIO_H_
#define _UIO_H_

/* For size_t */
#include <stddef.h>
/* For ssize_t */
#include <sys/types.h>

#include <sys/cdefs.h>

__BEGIN_DECLS

/*
 * Define the uio buffers used for writev, readv.
 */

struct iovec {
	caddr_t iov_base;
	int iov_len;
};

extern ssize_t readv __P ((int filedes, const struct iovec *vector, int count));
extern ssize_t writev __P ((int filedes, const struct iovec *vector, int count));

__END_DECLS

#endif /* _UIO_H_ */
