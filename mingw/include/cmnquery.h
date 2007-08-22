/*
 * cmnquery.h - Active Directory
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
#ifndef _CMNQUERY_H
#define _CMNQUERY_H
#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*--- Active Directory Reference - Active Directory Structures - Active Directory Display Structures */
#if (_WIN32_WINNT >= 0x0500)
typedef struct {
	DWORD cbStruct;
	DWORD dwFlags;
	CLSID clsid;
	HICON hIcon;
	LPWSTR pszTitle;
} CQFORM,*LPCQFORM;
#define CQFF_NOGLOBALPAGES 0x00000001
#define CQFF_ISOPTIONAL 0x00000002
typedef struct {
	DWORD cbStruct;
	DWORD dwFlags;
	LPCQPAGEPROC pPageProc;
	HINSTANCE hInstance;
	INT idPageName;
	INT idPageTemplate;
	DLGPROC pDlgProc;
	LPARAM lParam;
} CQPAGE,*LPCQPAGE;
/*********
typedef struct {
	DWORD cbStruct;
	DWORD dwFlags;
	CLSID clsidHandler;
	LPVOID pHandlerParameters;
	CLSID clsidDefaultForm;
	IPersistQuery* pPersistQuery;
	union {
		void* pFormParameters;
		IPropertyBag* ppbFormParameters;
	};
} OPENQUERYWINDOW,*LPOPENQUERYWINDOW;
*********/
#define OQWF_OKCANCEL 0x00000001
#define OQWF_DEFAULTFORM 0x00000002
#define OQWF_SINGLESELECT 0x00000004
#define OQWF_LOADQUERY 0x00000008
#define OQWF_REMOVESCOPES 0x00000010
#define OQWF_REMOVEFORMS 0x00000020
#define OQWF_ISSUEONOPEN 0x00000040
#define OQWF_SHOWOPTIONAL 0x00000080
#define OQWF_SAVEQUERYONOK 0x00000200
#define OQWF_HIDEMENUS 0x00000400
#define OQWF_HIDESEARCHUI 0x00000800
#define OQWF_PARAMISPROPERTYBAG 0x80000000
/*--- Active Directory Reference - Active Directory Functions - Active Directory Display Functions */
typedef HRESULT (CALLBACK* CQAddFormsProc)(LPARAM,LPCQFORM);
typedef HRESULT (CALLBACK* CQAddPagesProc)(LPARAM,REFCLSID,LPCQPAGE);
typedef HRESULT (CALLBACK* CQPageProc)(LPCQPAGE,HWND,UINT,WPARAM,LPARAM);
#endif /* (_WIN32_WINNT >= 0x0500) */

#ifdef __cplusplus
}
#endif
#endif
