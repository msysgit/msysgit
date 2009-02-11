/*
 * dsclient.h - Active Directory
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
#ifndef _DSCLIENT_H
#define _DSCLIENT_H
#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if (_WIN32_WINNT >= 0x0500)
/*--- Active Directory Reference - Active Directory Functions - Active Directory Display Functions - BFFCallBack */
#define DSBM_QUERYINSERTW 0x0064
#define DSBM_QUERYINSERTA 0x0065
#define DSBM_CHANGEIMAGESTATE 0x0066
#define DSBM_HELP 0x0067
#define DSBM_CONTEXTMENU 0x0068
#ifdef UNICODE
#define DSBM_QUERYINSERT DSBM_QUERYINSERTW
#else
#define DSBM_QUERYINSERT DSBM_QUERYINSERTA
#endif
/*--- Active Directory Reference - Active Directory Structures - Active Directory Display Structures */
typedef struct _DOMAINDESC {
	LPWSTR pszName;
	LPWSTR pszPath;
	LPWSTR pszNCName;
	LPWSTR pszTrustParent;
	LPWSTR pszObjectClass;
	ULONG ulFlags;
	BOOL fDownLevel;
	struct _DOMAINDESC* pdChildList;
	struct _DOMAINDESC* pdNextSibling;
} DOMAIN_DESC,DOMAINDESC,*PDOMAIN_DESC,*LPDOMAINDESC;
typedef struct {
	DWORD dsSize;
	DWORD dwCount;
	DOMAINDESC aDomains[1];
} DOMAINTREE,DOMAIN_TREE,*PDOMAIN_TREE,*LPDOMAINTREE;
#define DSB_MAX_DISPLAYNAME_CHARS 64
typedef struct {
	DWORD cbStruct;
	LPCWSTR pszADsPath;
	LPCWSTR pszClass;
	DWORD dwMask;
	DWORD dwState;
	DWORD dwStateMask;
	CHAR szDisplayName[DSB_MAX_DISPLAYNAME_CHARS];
	CHAR szIconLocation[MAX_PATH];
	INT iIconResID;
} DSBITEMA,*PDSBITEMA;
typedef struct {
	DWORD cbStruct;
	LPCWSTR pszADsPath;
	LPCWSTR pszClass;
	DWORD dwMask;
	DWORD dwState;
	DWORD dwStateMask;
	CHAR szDisplayName[DSB_MAX_DISPLAYNAME_CHARS];
	CHAR szIconLocation[MAX_PATH];
	INT iIconResID;
} DSBITEMW,*PDSBITEMW;
#define DSBF_STATE 0x00000001
#define DSBF_ICONLOCATION 0x00000002
#define DSBF_DISPLAYNAME 0x00000004
#define DSBS_CHECKED 0x00000001
#define DSBS_HIDDEN 0x00000002
#define DSBS_ROOT 0x00000004
typedef struct {
	DWORD cbStruct;
	HWND hwndOwner;
	LPCSTR pszCaption;
	LPCSTR pszTitle;
	LPCWSTR pszRoot;
	LPWSTR pszPath;
	ULONG cchPath;
	DWORD dwFlags;
	BFFCALLBACK pfnCallback;
	LPARAM lParam;
	DWORD dwReturnFormat;
	LPCWSTR pUserName;
	LPCWSTR pPassword;
	LPWSTR pszObjectClass;
	ULONG cchObjectClass;
} DSBROWSEINFOA,*PDSBROWSEINFOA;
typedef struct {
	DWORD cbStruct;
	HWND hwndOwner;
	LPCWSTR pszCaption;
	LPCWSTR pszTitle;
	LPCWSTR pszRoot;
	LPWSTR pszPath;
	ULONG cchPath;
	DWORD dwFlags;
	BFFCALLBACK pfnCallback;
	LPARAM lParam;
	DWORD dwReturnFormat;
	LPCWSTR pUserName;
	LPCWSTR pPassword;
	LPWSTR pszObjectClass;
	ULONG cchObjectClass;
} DSBROWSEINFOW,*PDSBROWSEINFOW;
#define DSBI_NOBUTTONS 0x00000001
#define DSBI_NOLINES 0x00000002
#define DSBI_NOLINESATROOT 0x00000004
#define DSBI_CHECKBOXES 0x00000100
#define DSBI_NOROOT 0x00010000
#define DSBI_INCLUDEHIDDEN 0x00020000
#define DSBI_EXPANDONOPEN 0x00040000
#define DSBI_ENTIREDIRECTORY 0x00090000
#define DSBI_RETURN_FORMAT 0x00100000
#define DSBI_HASCREDENTIALS 0x00200000
#define DSBI_IGNORETREATASLEAF 0x00400000
#define DSBI_SIMPLEAUTHENTICATE 0x00800000
#define DSBI_RETURNOBJECTCLASS 0x01000000
#define DSBI_DONTSIGNSEAL 0x02000000
typedef struct {
	DWORD dwFlags;
	CLSID clsidWizardDialog;
	CLSID clsidWizardPrimaryPage;
	DWORD cWizardExtensions;
	CLSID aWizardExtensions[1];
} DSCLASSCREATIONINFO,*LPDSCLASSCREATIONINFO;
#define DSCCIF_HASWIZARDDIALOG 0x00000001
#define DSCCIF_HASWIZARDPRIMARYPAGE 0x00000002
typedef struct _DSDISPLAYSPECOPTIONS {
	DWORD dwSize;
	DWORD dwFlags;
	DWORD offsetAttribPrefix;
	DWORD offsetUserName;
	DWORD offsetPassword;
	DWORD offsetServer;
	DWORD offsetServerConfigPath;
} DSDISPLAYSPECOPTIONS,*PDSDISPLAYSPECOPTIONS,*LPDSDISPLAYSPECOPTIONS;
#define DSDSOF_HASUSERANDSERVERINFO 0x00000001
#define DSDSOF_SIMPLEAUTHENTICATE 0x00000002
#define DSDSOF_DONTSIGNSEAL 0x00000004
#define DSDSOF_DSAVAILABLE 0x40000000
typedef struct {
	DWORD dwFlags;
	DWORD dwProviderFlags;
	DWORD offsetName;
	DWORD offsetClass;
} DSOBJECT,*LPDSOBJECT;
#define DSOBJECT_ISCONTAINER 0x00000001
#define DSOBJECT_READONLYPAGES 0x80000000
#define DSPROVIDER_UNUSED_0 0x00000001
#define DSPROVIDER_UNUSED_1 0x00000002
#define DSPROVIDER_UNUSED_2 0x00000004
#define DSPROVIDER_UNUSED_3 0x00000008
#define DSPROVIDER_ADVANCED 0x00000010
typedef struct {
	CLSID clsidNamespace;
	UINT cItems;
	DSOBJECT aObjects[1];
} DSOBJECTNAMES,*LPDSOBJECTNAMES;
typedef struct {
	DWORD offsetString;
} DSPROPERTYPAGEINFO,*LPDSPROPERTYPAGEINFO;
#ifdef UNICODE
typedef DSBITEMW DSBITEM,*PDSBITEM;
typedef DSBROWSEINFOW DSBROWSEINFO,*PDSBROWSEINFO;
#else
typedef DSBITEMA DSBITEM,*PDSBITEM;
typedef DSBROWSEINFOA DSBROWSEINFO,*PDSBROWSEINFO;
#endif
#endif /* (_WIN32_WINNT >= 0x0500) */

#ifdef __cplusplus
}
#endif
#endif
