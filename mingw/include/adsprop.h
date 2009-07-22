/*
 * adsprop.h - Active Directory
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
#ifndef _ADSPROP_H
#define _ADSPROP_H
#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*--- Active Directory Reference - Active Directory Messages */
#define WM_ADSPROP_NOTIFY_APPLY (WM_USER+1104)
#define WM_ADSPROP_NOTIFY_CHANGE (WM_USER+1103)
#define WM_ADSPROP_NOTIFY_ERROR (WM_USER+1110)
#define WM_ADSPROP_NOTIFY_EXIT (WM_USER+1107)
#define WM_ADSPROP_NOTIFY_FOREGROUND (WM_USER+1106)
#define WM_ADSPROP_NOTIFY_PAGEHWND (WM_USER+1102)
#define WM_ADSPROP_NOTIFY_PAGEINIT (WM_USER+1101)
#define WM_ADSPROP_NOTIFY_SETFOCUS (WM_USER+1105)
/*--- Active Directory Reference - Active Directory Structures - Active Directory MMC Property Page Structures */
#if (_WIN32_WINNT >= 0x0501)
typedef struct {
	HWND hwndPage;
	PWSTR pszPageTitle;
	PWSTR pszObjPath;
	PWSTR pszObjClass;
	HRESULT hr;
	PWSTR pszError;
} ADSPROPERROR,*PADSPROPERROR;
#endif /* (_WIN32_WINNT >= 0x0501) */
#if (_WIN32_WINNT >= 0x0500)
typedef struct {
	DWORD dwSize;
	DWORD dwFlags;
	HRESULT hr;
	IDirectoryObject *pDsObj;
	LPWSTR pwzCN;
	PADS_ATTR_INFO pWritableAttrs;
} ADSPROPINITPARAMS,*PADSPROPINITPARAMS;
#endif /* (_WIN32_WINNT >= 0x0500) */

#ifdef __cplusplus
}
#endif
#endif
