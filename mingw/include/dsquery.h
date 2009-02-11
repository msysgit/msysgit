/*
 * dsquery.h - Active Directory
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
#ifndef _DSQUERY_H
#define _DSQUERY_H
#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*--- Active Directory Reference - Active Directory Structures - Active Directory Display Structures */
#if (_WIN32_WINNT >= 0x0500)
typedef struct {
	DWORD dwFlags;
	INT fmt;
	INT cx;
	INT idsName;
	LONG offsetProperty;
	DWORD dwReserved;
} DSCOLUMN,*LPDSCOLUMN;
#define DSCOLUMNPROP_ADSPATH -1
#define DSCOLUMNPROP_OBJECTCLASS -2
typedef struct {
	DWORD cbStruct;
	LONG cClasses;
	DWORD offsetClass[1];
} DSQUERYCLASSLIST,*LPDSQUERYCLASSLIST;
typedef struct {
	DWORD cbStruct;
	DWORD dwFlags;
	LPWSTR pDefaultScope;
	LPWSTR pDefaultSaveLocation;
	LPWSTR pUserName;
	LPWSTR pPassword;
	LPWSTR pServer;
} DSQUERYINITPARAMS,*LPDSQUERYINITPARAMS;
#define DSQPF_NOSAVE 0x00000001
#define DSQPF_SAVELOCATION 0x00000002
#define DSQPF_SHOWHIDDENOBJECTS 0x00000004
#define DSQPF_ENABLEADMINFEATURES 0x00000008
#define DSQPF_ENABLEADVANCEDFEATURES 0x00000010
#define DSQPF_HASCREDENTIALS 0x00000020
#define DSQPF_NOCHOOSECOLUMNS 0x00000040
typedef struct {
	DWORD cbStruct;
	DWORD dwFlags;
	HINSTANCE hInstance;
	LONG offsetQuery;
	LONG iColumns;
	DWORD dwReserved;
	DSCOLUMN aColumns[1];
} DSQUERYPARAMS,*LPDSQUERYPARAMS;
#endif /* (_WIN32_WINNT >= 0x0500) */

#ifdef __cplusplus
}
#endif
#endif
