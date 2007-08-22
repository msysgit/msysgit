#ifndef _SDDL_H
#define _SDDL_H
#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#ifndef WINADVAPI
#define WINADVAPI
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if (WINVER >= 0x0500)
WINADVAPI BOOL WINAPI ConvertSidToStringSidA(PSID Sid, LPSTR* StringSid);
WINADVAPI BOOL WINAPI ConvertSidToStringSidW(PSID Sid, LPWSTR* StringSid);
#endif

#ifdef UNICODE
#define ConvertSidToStringSid ConvertSidToStringSidW
#else
#define ConvertSidToStringSid ConvertSidToStringSidA
#endif

#ifdef __cplusplus
}
#endif

#endif /* _SDDL_H */
