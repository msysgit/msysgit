/*
 * ntdsbcli.h - Active Directory
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
#ifndef _NTDSBCLI_H
#define _NTDSBCLI_H
#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*--- Active Directory Reference - Active Directory Structures - Directory Backup Structures */
#if (_WIN32_WINNT >= 0x0500)
typedef struct {
	LPSTR szDatabaseName;
	LPSTR szNewDatabaseName;
} EDB_RSTMAPA,*PEDB_RSTMAPA;
typedef struct {
	LPWSTR szDatabaseName;
	LPWSTR szNewDatabaseName;
} EDB_RSTMAPW,*PEDB_RSTMAPW;
#ifdef UNICODE
typedef EDB_RSTMAPW EDB_RSTMAP,*PEDB_RSTMAP;
#else
typedef EDB_RSTMAPA EDB_RSTMAP,*PEDB_RSTMAP;
#endif
#endif /* (_WIN32_WINNT >= 0x0500) */

#ifdef __cplusplus
}
#endif
#endif
