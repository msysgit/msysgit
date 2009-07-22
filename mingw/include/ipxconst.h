/*
 * ipxconst.h - Routing and Remote Access Services
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
#ifndef _IPXCONST_H
#define _IPXCONST_H
#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*--- Router Management Reference - Router Information Structures - IPX Information Structures */
#if (_WIN32_WINNT >= 0x0500)
#define ADMIN_STATE_DISABLED 0x00000001
#define ADMIN_STATE_ENABLED 0x00000002
#define ADMIN_STATE_ENABLED_ONLY_FOR_NETBIOS_STATIC_ROUTING 0x00000003
#define ADMIN_STATE_ENABLED_ONLY_FOR_OPER_STATE_UP 0x00000004
#endif /* (_WIN32_WINNT >= 0x0500) */

#ifdef __cplusplus
}
#endif
#endif
