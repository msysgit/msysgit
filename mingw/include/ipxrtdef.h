/*
 * ipxrtdef.h - Routing and Remote Access Services
 *
 * THIS SOFTWARE IS NOT COPYRIGHTED
 *
 * This source code is offered for use in the public domain.  You may use,
 * modify or distribute it freely.
 *
 * This code is distributed in the hope that it will be useful but
 * WITHOUT ANY WARRANTY.  ALL WARRANTIES, EXPRESS OR IMPLIED ARE HEREBY
 * DISCLAIMED.  This includes but is not limited to warranties of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#ifndef _IPXRTDEF_H
#define _IPXRTDEF_H
#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#include <stm.h>
#include <ipxconst.h>

#ifdef __cplusplus
extern "C" {
#endif

/*--- Router Management Reference - Router Information Enumeration Types */
#define IPX_INTERFACE_INFO_TYPE 0x0001
#define IPX_STATIC_ROUTE_INFO_TYPE 0x0002
#define IPX_STATIC_SERVICE_INFO_TYPE 0x0003
#define IPX_SERVICE_FILTER_INFO_TYPE 0x0004
#define IPX_ROUTE_FILTER_INFO_TYPE 0x0005
#define IPX_IN_TRAFFIC_FILTER_INFO_TYPE 0x0006
#define IPX_ADAPTER_INFO_TYPE 0x0007
#define IPXWAN_INTERFACE_INFO_TYPE 0x0008
#define IPX_GLOBAL_INFO_TYPE 0x0009
#define IPX_STATIC_NETBIOS_NAME_INFO_TYPE 0x000A
#define IPX_IN_TRAFFIC_FILTER_GLOBAL_INFO_TYPE 0x000B
#define IPX_OUT_TRAFFIC_FILTER_INFO_TYPE 0x000C
#define IPX_OUT_TRAFFIC_FILTER_GLOBAL_INFO_TYPE 0x000D
/*--- Router Management Reference - Router Information Structures - IPX Information Structures */
#if (_WIN32_WINNT >= 0x0500)
typedef struct _IPX_IF_INFO {
	ULONG AdminState;
	ULONG NetbiosAccept;
	ULONG NetbiosDeliver;
} IPX_IF_INFO,*PIPX_IF_INFO;
typedef IPX_SERVER_ENTRY IPX_STATIC_SERVICE_INFO,*PIPX_STATIC_SERVICE_INFO;
typedef struct _IPXWAN_IF_INFO {
	ULONG AdminState;
} IPXWAN_IF_INFO,*PIPXWAN_IF_INFO;
#endif

#ifdef __cplusplus
}
#endif
#endif
