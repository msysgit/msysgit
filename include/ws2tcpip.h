/*
 *  ws2tcpip.h : TCP/IP specific extensions in Windows Sockets 2
 *
 * Portions Copyright (c) 1980, 1983, 1988, 1993
 * The Regents of the University of California.  All rights reserved.
 *
 */

#ifndef _WS2TCPIP_H
#define _WS2TCPIP_H

#include <winsock2.h>

/* 
 * The IP_* macros are also defined in winsock.h, but some values are different there.
 * The values defined in winsock.h for 1.1 and used in wsock32.dll are consistent
 * with the original values Steve Deering defined in his document "IP Multicast Extensions
 * for 4.3BSD UNIX related systems (MULTICAST 1.2 Release)." However, these conflicted with
 * the definitions for some IPPROTO_IP level socket options already assigned by BSD,
 * so Berkeley changed all the values by adding 7.  WinSock2 (ws2_32.dll)  uses
 * the BSD 4.4 compatible values defined here.
 *
 * See also: msdn kb article Q257460
 * http://support.microsoft.com/support/kb/articles/Q257/4/60.asp
 */

/* This is also defined in winsock.h; value hasn't changed */
#define	IP_OPTIONS  1

#define	IP_HDRINCL  2
/*
 * These are also be defined in winsock.h,
 * but values have changed for WinSock2 interface
 */
#define	IP_TOS  3   /* old (winsock 1.1) value 8 */
#define	IP_TTL  4  /* old value 7 */
#define	IP_MULTICAST_IF 	9 /* old value 2 */
#define	IP_MULTICAST_TTL    10 /* old value 3 */
#define	IP_MULTICAST_LOOP   11 /* old value 4 */
#define	IP_ADD_MEMBERSHIP   12 /* old value 5 */
#define	IP_DROP_MEMBERSHIP  13 /* old value 6 */
#define IP_DONTFRAGMENT 14 /* old value 9 */

#define IP_DEFAULT_MULTICAST_TTL 1 
#define IP_DEFAULT_MULTICAST_LOOP 1 
#define IP_MAX_MEMBERSHIPS 20 

#define TCP_EXPEDITED_1122  2

#define UDP_NOCHECKSUM	1

#define IFF_UP  1
#define IFF_BROADCAST   2
#define IFF_LOOPBACK    4
#define IFF_POINTTOPOINT    8
#define IFF_MULTICAST   16

#define SIO_GET_INTERFACE_LIST  _IOR('t', 127, u_long)	

/*
 *   ip_mreq also in winsock.h for WinSock1.1,
 *   but online msdn docs say it is defined here for WinSock2.
 */ 
struct ip_mreq {
	struct in_addr imr_multiaddr;
	struct in_addr imr_interface;
};

typedef struct _INTERFACE_INFO {
	u_long		iiFlags;
    struct sockaddr iiAddress;
	struct sockaddr iiBroadcastAddress;
	struct sockaddr iiNetmask;
} INTERFACE_INFO, *LPINTERFACE_INFO;


/* ipv6 */ 

/*
 * According to online msdn documentation (12 Dec 2000), two separate implentations
 * of ipv6 are available (1) the Microsoft IPv6 Technology Preview  (requires W2K SP1)
 * and (2) the MS Research IPV6 implementation (requires NT4 or W2K).
 * Neither are production level implementations.    
 */

#if 0
/*
 * The following is based on what online msdn PSDK docs say as at 5 Dec 2000
 */
struct in_addr6 /* sic */ { u_char s6_addr[16]; };
typedef struct in_addr6 IN6_ADDR,  *PIN6_ADDR, *LPIN6_ADDR;

typedef struct sockaddr_in6 {
		short	sin6_family;
		u_short sin6_port;
		u_long	sin6_flowinfo;
		struct in_addr6 sin6_addr;
} SOCKADDR_IN6, *PSOCKADDR_IN6, *LPSOCKADDR_IN6;

#elif 0
/*
 * In the FAQ section of Microsoft IPv6 Technology Preview for Windows 2000
 * (dated 12 Dec 2000) it says that the Preview and the MS Research implemntation
 * support RFC 2553, and in particular, uses the sockaddr_in6 structure defined
 * in Section 3.3. That would look something like this:
*/
#include <stdint.h>
struct in6_addr { /* this is the standard name */
        union {
                uint8_t   _u6_addr8[16];
                uint16_t  _u6_addr16[8];
                uint32_t  _u6_addr32[4];
             /* uint64_t  _u6_addr64[2];*/ 
        } _u6_addr;
};
typedef struct in6_addr IN6_ADDR,  *PIN6_ADDR, *LPIN6_ADDR;
#define s6_addr   _u6_addr._u6_addr8

struct sockaddr_in6 {
    uint16_t sin6_family; /* AF_INET6 */
	uint16_t sin6_port; /* transport layer port # */
	uint32_t sin6_flowinfo; /* IPv6 traffic class & flow info */
	struct in6_addr sin6_addr;  /* IPv6 address */
    uint32_t sin6_scope_id;  /* set of interfaces for a scope */
};
typedef struct sockaddr_in6  SOCKADDR_IN6, *PSOCKADDR_IN6, *LPSOCKADDR_IN6;

/*
 * Watch this space.
 * These may get moved out to ipv6 specific header(s). along with other
 * standard structures and functions specified in RFC 2553.    
 */
#endif

#endif	/* _WS2TCPIP_H */



