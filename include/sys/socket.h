/* sys/socket.h

   Copyright 1996-2001 Red Hat, Inc.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#ifndef _SYS_SOCKET_H
#define _SYS_SOCKET_H

#include <features.h>
#include <cygwin/socket.h>
#include <sys/time.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* SUS symbolic values for the second parm to shutdown(2) */
#define SHUT_RD   0		/* == Win32 SD_RECEIVE */
#define SHUT_WR   1		/* == Win32 SD_SEND    */
#define SHUT_RDWR 2		/* == Win32 SD_BOTH    */

#ifndef __INSIDE_CYGWIN_NET__
  int accept (int, struct sockaddr *__peer, int *);
  int bind (int, const struct sockaddr *__my_addr, int __addrlen);
  int connect (int, const struct sockaddr *, int);
  int getpeername (int, struct sockaddr *__peer, int *);
  int getsockname (int, struct sockaddr *__addr, int *);
  int listen (int, int __n);
  int recv (int, void *__buff, int __len, unsigned int __flags);
  int recvfrom (int, char *__buff, int __len, int __flags,
			 struct sockaddr *__from, int *__fromlen);
  int send (int, const void *__buff, int __len, unsigned int __flags);
  int sendto (int, const void *, int, unsigned int, const struct sockaddr *, int);
  int setsockopt (int __s, int __level, int __optname, const void *optval, int __optlen);
  int getsockopt (int __s, int __level, int __optname, void *__optval, int *__optlen);
  int shutdown (int, int);
  int socket (int __family, int __type, int __protocol);
  int socketpair (int __domain, int __type, int __protocol, int *__socket_vec);

  struct servent *getservbyname (const char *__name, const char *__proto);
#endif

#ifdef __cplusplus
};
#endif

#endif /* _SYS_SOCKET_H */
