/*
 * rtutils.h - Routing and Remote Access Services
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
#ifndef _RTUTILS_H
#define _RTUTILS_H
#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*--- Tracing Reference */
#if (_WIN32_WINNT >= 0x0500)
DWORD WINAPI TraceDeregisterA(DWORD);
DWORD WINAPI TraceDeregisterW(DWORD);
DWORD WINAPI TraceDeregisterExA(DWORD,DWORD);
DWORD WINAPI TraceDeregisterExW(DWORD,DWORD);
#define TRACE_NO_SYNCH 0x00000004
#define TraceDumpA(a,b,c,d,e,f) TraceDumpExA((a),0,(b),(c),(d),(e),(f))
#define TraceDumpW(a,b,c,d,e,f) TraceDumpExW((a),0,(b),(c),(d),(e),(f))
DWORD WINAPI TraceDumpExA(DWORD,DWORD,LPBYTE,DWORD,DWORD,BOOL,LPCSTR);
DWORD WINAPI TraceDumpExW(DWORD,DWORD,LPBYTE,DWORD,DWORD,BOOL,LPCWSTR);
DWORD WINAPI TracePrintfA(DWORD,LPCSTR,...);
DWORD WINAPI TracePrintfW(DWORD,LPCWSTR,...);
DWORD WINAPI TracePrintfExA(DWORD,DWORD,LPCSTR,...);
DWORD WINAPI TracePrintfExW(DWORD,DWORD,LPCWSTR,...);
#define TracePutsA(a,b) TracePutsExA((a),0,(b))
#define TracePutsW(a,b) TracePutsExW((a),0,(b))
DWORD WINAPI TracePutsExA(DWORD,DWORD,LPCSTR);
DWORD WINAPI TracePutsExW(DWORD,DWORD,LPCWSTR);
#define TraceRegisterA(a) TraceRegisterExA((a),0)
#define TraceRegisterW(a) TraceRegisterExW((a),0)
DWORD WINAPI TraceRegisterExA(LPCSTR,DWORD);
DWORD WINAPI TraceRegisterExW(LPCWSTR,DWORD);
#define TRACE_USE_FILE 0x00000001
#define TRACE_USE_CONSOLE 0x00000002
#define INVALID_TRACEID 0xFFFFFFFF
#define TraceVprintfA(a,b,c) TraceVprintfExA((a),0,(b),(c))
#define TraceVprintfW(a,b,c) TraceVprintfExW((a),0,(b),(c))
DWORD WINAPI TraceVprintfExA(DWORD,DWORD,LPCSTR,va_list);
DWORD WINAPI TraceVprintfExW(DWORD,DWORD,LPCWSTR,va_list);
#define TRACE_NO_STDINFO 0x00000001
#define TRACE_USE_MASK 0x00000002
#define TRACE_USE_MSEC 0x00000004
#ifdef UNICODE
#define TraceDeregister TraceDeregisterW
#define TraceDeregisterEx TraceDeregisterExW
#define TraceDump TraceDumpW
#define TraceDumpEx TraceDumpExW
#define TracePrintf TracePrintfW
#define TracePrintfEx TracePrintfExW
#define TracePuts TracePutsW
#define TracePutsEx TracePutsExW
#define TraceRegister TraceRegisterW
#define TraceRegisterEx TraceRegisterExW
#define TraceVprintf TraceVprintfW
#define TraceVprintfEx TraceVprintfExW
#else
#define TraceDeregister TraceDeregisterA
#define TraceDeregisterEx TraceDeregisterExA
#define TraceDump TraceDumpA
#define TraceDumpEx TraceDumpExA
#define TracePrintf TracePrintfA
#define TracePrintfEx TracePrintfExA
#define TracePuts TracePutsA
#define TracePutsEx TracePutsExA
#define TraceRegister TraceRegisterA
#define TraceRegisterEx TraceRegisterExA
#define TraceVprintf TraceVprintfA
#define TraceVprintfEx TraceVprintfExA
#endif
#endif /* (_WIN32_WINNT >= 0x0500) */

#ifdef __cplusplus
}
#endif
#endif
