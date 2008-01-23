/* sys/poll.h

   Copyright 2000, 2001 Red Hat, Inc.

   This file is part of Cygwin.

   This software is a copyrighted work licensed under the terms of the
   Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
   details. */

#ifndef _SYS_POLL_H
#define _SYS_POLL_H

#include <sys/cdefs.h>

__BEGIN_DECLS

#define POLLIN  1       /* Set if data to read. */
#define POLLPRI 2       /* Set if urgent data to read. */
#define POLLOUT 4       /* Set if writing data wouldn't block. */
#define POLLERR   8     /* An error occured. */
#define POLLHUP  16     /* Shutdown or close happened. */
#define POLLNVAL 32     /* Invalid file descriptor. */

#define NPOLLFILE 64    /* Number of canonical fd's in one call to poll(). */

/* The following values are defined by XPG4. */
#define POLLRDNORM POLLIN
#define POLLRDBAND POLLPRI
#define POLLWRNORM POLLOUT
#define POLLWRBAND POLLOUT

struct pollfd {
  int fd;
  short events;
  short revents;
};

extern int poll __P ((struct pollfd *fds, unsigned int nfds, int timeout));

__END_DECLS

#endif /* _SYS_POLL_H */
