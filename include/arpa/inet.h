/* arpa/inet.h

   Copyright 1997, 1998, 2001 Red Hat, Inc.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#ifndef _ARPA_INET_H
#define _ARPA_INET_H

#include <netinet/in.h>

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef __INSIDE_CYGWIN_NET__
unsigned long	 inet_addr (const char *);
int		 inet_aton (const char *, struct in_addr *);
unsigned long	 inet_lnaof (struct in_addr);
struct in_addr	 inet_makeaddr (unsigned long , unsigned long);
unsigned int	 inet_netof (struct in_addr);
unsigned int	 inet_network (const char *);
char		*inet_ntoa (struct in_addr);
#endif

#ifdef __cplusplus
};
#endif

#endif /* _ARPA_INET_H */
