/*
 * ipinfoid.h - Routing and Remote Access Services
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
#ifndef _IPINFOID_H
#define _IPINFOID_H
#if __GNUC__ >= 3
#pragma GCC system_header
#endif

/*--- Router Management Reference - Router Information Enumeration Types */
#define IP_IN_FILTER_INFO 0xFFFF0001
#define IP_OUT_FILTER_INFO 0xFFFF0002
#define IP_GLOBAL_INFO 0xFFFF0003
#define IP_INTERFACE_STATUS_INFO 0xFFFF0004
#define IP_ROUTE_INFO 0xFFFF0005
#define IP_PROT_PRIORITY_INFO 0xFFFF0006
#define IP_ROUTER_DISC_INFO 0xFFFF0007
#define IP_DEMAND_DIAL_FILTER_INFO 0xFFFF0009
#define IP_MCAST_HEARBEAT_INFO 0xFFFF000A
#define IP_MCAST_BOUNDARY_INFO 0xFFFF000B
#define IP_IPINIP_CFG_INFO 0xFFFF000C
#define IP_IFFILTER_INFO 0xFFFF000D
#define IP_MCAST_LIMIT_INFO 0xFFFF000E
/*#define IP_DEMAND_DIAL_FILTER_INFO_V6 */
/*#define IP_FILTER_ENABLE_INFO_V6 */
/*#define IP_IN_FILTER_INFO_V6 */
/*#define IP_IFFILTER_INFO_V6 */
/*#define IP_OUT_FILTER_INFO_V6 */
/*#define IPV6_GLOBAL_INFO */
/*#define IPV6_ROUTE_INFO */

#endif
