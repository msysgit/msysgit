/*
 * fltdefs.h - Routing and Remote Access Services
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
#ifndef _FLTDEFS_H
#define _FLTDEFS_H
#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*--- Packet Filtering Reference - Packet Filtering Enumerated Types */
#if (_WIN32_WINNT >= 0x0500)
typedef enum _GlobalFilter {
	GF_FRAGMENTS = 2,
	GF_STRONGHOST = 8,
	GF_FRAGCACHE = 9
} GLOBAL_FILTER,*PGLOBAL_FILTER;
typedef enum _PfAddresType {
	PF_IPV4,
	PF_IPV6
} PFADDRESSTYPE,*PPFADDRESSTYPE;
typedef enum _PfForwardAction {
	PF_ACTION_FORWARD = 0,
	PF_ACTION_DROP
} PFFORWARD_ACTION,*PPFFORWARD_ACTION;
typedef enum _PfFrameType {
	PFFT_FILTER = 1,
	PFFT_FRAG = 2,
	PFFT_SPOOF = 3
} PFFRAMETYPE,*PPFFRAMETYPE;
#endif /* (_WIN32_WINNT >= 0x0500) */

#ifdef __cplusplus
}
#endif
#endif
