/* asm/socket.h

   Copyright 1996, 1997, 1998, 2001 Red Hat, Inc.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#ifndef _ASM_SOCKET_H
#define _ASM_SOCKET_H

#include <cygwin/if.h>

#define IOCPARM_MASK    0x7f            /* parameters must be < 128 bytes */
#define IOC_VOID        0x20000000      /* no parameters */
#define IOC_OUT         0x40000000      /* copy out parameters */
#define IOC_IN          0x80000000      /* copy in parameters */

#define _IO(x,y)        (IOC_VOID|(x<<8)|y)
#define _IOR(x,y,t)     (IOC_OUT|(((long)sizeof(t)&IOCPARM_MASK)<<16)|(x<<8)|y)
#define _IOW(x,y,t)     (IOC_IN|(((long)sizeof(t)&IOCPARM_MASK)<<16)|(x<<8)|y)

#define SIOCATMARK  _IOR('s',  7, u_long)  /* at oob mark? */
#define FIONREAD    _IOR('f', 127, u_long) /* get # bytes to read */
#define FIONBIO 0x8004667e /* To be compatible with termiost version */
#define REAL_FIONBIO     _IOW('f', 126, u_long) /* set/clear non-blocking i/o */
#define FIOASYNC    _IOW('f', 125, u_long) /* set/clear async i/o */
#define SIOCSHIWAT  _IOW('s',  0, u_long)  /* set high watermark */
#define SIOCGHIWAT  _IOR('s',  1, u_long)  /* get high watermark */
#define SIOCSLOWAT  _IOW('s',  2, u_long)  /* set low watermark */
#define SIOCGLOWAT  _IOR('s',  3, u_long)  /* get low watermark */

/* Needed for if queries */
#define SIOCGIFCONF     _IOW('s', 100, struct ifconf) /* get if list */
#define SIOCGIFFLAGS    _IOW('s', 101, struct ifreq) /* Get if flags */
#define SIOCGIFADDR     _IOW('s', 102, struct ifreq) /* Get if addr */
#define SIOCGIFBRDADDR  _IOW('s', 103, struct ifreq) /* Get if broadcastaddr */
#define SIOCGIFNETMASK  _IOW('s', 104, struct ifreq) /* Get if netmask */
#define SIOCGIFHWADDR   _IOW('s', 105, struct ifreq) /* Get hw addr */
#define SIOCGIFMETRIC   _IOW('s', 106, struct ifreq) /* get metric */
#define SIOCGIFMTU      _IOW('s', 107, struct ifreq) /* get MTU size */

#define SOL_SOCKET      0xffff          /* options for socket level */

#define SO_DEBUG        0x0001          /* turn on debugging info recording */
#define SO_ACCEPTCONN   0x0002          /* socket has had listen() */
#define SO_REUSEADDR    0x0004          /* allow local address reuse */
#define SO_KEEPALIVE    0x0008          /* keep connections alive */
#define SO_DONTROUTE    0x0010          /* just use interface addresses */
#define SO_BROADCAST    0x0020          /* permit sending of broadcast msgs */
#define SO_USELOOPBACK  0x0040          /* bypass hardware when possible */
#define SO_LINGER       0x0080          /* linger on close if data present */
#define SO_OOBINLINE    0x0100          /* leave received OOB data in line */
#define SO_DONTLINGER   (u_int)(~SO_LINGER)

/*
 * Additional options.
 */
#define SO_SNDBUF       0x1001          /* send buffer size */
#define SO_RCVBUF       0x1002          /* receive buffer size */
#define SO_SNDLOWAT     0x1003          /* send low-water mark */
#define SO_RCVLOWAT     0x1004          /* receive low-water mark */
#define SO_SNDTIMEO     0x1005          /* send timeout */
#define SO_RCVTIMEO     0x1006          /* receive timeout */
#define SO_ERROR        0x1007          /* get error status and clear */
#define SO_TYPE         0x1008          /* get socket type */

#endif /* _ASM_SOCKET_H */

