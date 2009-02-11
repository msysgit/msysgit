/*
 * dsadmin.h - Active Directory
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
#ifndef _DSADMIN_H
#define _DSADMIN_H
#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*--- Active Directory Reference - Active Directory Structures - Active Directory Admin Structures */
#if (_WIN32_WINNT >= 0x0500)
typedef struct {
	DWORD dwSize;
	HICON hObjClassIcon;
	LPWSTR lpszWizTitle;
	LPWSTR lpszContDisplayName;
} DSA_NEWOBJ_DISPINFO,*LPDSA_NEWOBJ_DISPINFO;
#endif /* (_WIN32_WINNT >= 0x0500) */

#ifdef __cplusplus
}
#endif
#endif
