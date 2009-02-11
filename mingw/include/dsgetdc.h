/*
 * dsgetdc.h - Active Directory
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
#ifndef _DSGETDC_H
#define _DSGETDC_H
#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*--- Active Directory Reference - Active Directory Structures - Directory Service Structures */
#if (_WIN32_WINNT >= 0x0500)
#define DS_FORCE_REDISCOVERY 0x00000001
#define DS_DIRECTORY_SERVICE_REQUIRED 0x00000010
#define DS_DIRECTORY_SERVICE_PREFERRED 0x00000020
#define DS_GC_SERVER_REQUIRED 0x00000040
#define DS_PDC_REQUIRED 0x00000080
#define DS_BACKGROUND_ONLY 0x00000100
#define DS_IP_REQUIRED 0x00000200
#define DS_KDC_REQUIRED 0x00000400
#define DS_TIMESERV_REQUIRED 0x00000800
#define DS_WRITABLE_REQUIRED 0x00001000
#define DS_GOOD_TIMESERV_PREFERRED 0x00002000
#define DS_AVOID_SELF 0x00004000
#define DS_ONLY_LDAP_NEEDED 0x00008000
#define DS_IS_FLAT_NAME 0x00010000
#define DS_IS_DNS_NAME 0x00020000
#define DS_RETURN_DNS_NAME 0x40000000
#define DS_RETURN_FLAT_NAME 0x80000000
typedef struct _DOMAIN_CONTROLLER_INFOA {
	LPSTR DomainControllerName;
	LPSTR DomainControllerAddress;
	ULONG DomainControllerAddressType;
	GUID DomainGuid;
	LPSTR DomainName;
	LPSTR DnsForestName;
	ULONG Flags;
	LPSTR DcSiteName;
	LPSTR ClientSiteName;
} DOMAIN_CONTROLLER_INFOA,*PDOMAIN_CONTROLLER_INFOA;
typedef struct _DOMAIN_CONTROLLER_INFOW {
	LPWSTR DomainControllerName;
	LPWSTR DomainControllerAddress;
	ULONG DomainControllerAddressType;
	GUID DomainGuid;
	LPWSTR DomainName;
	LPWSTR DnsForestName;
	ULONG Flags;
	LPWSTR DcSiteName;
	LPWSTR ClientSiteName;
} DOMAIN_CONTROLLER_INFOW,*PDOMAIN_CONTROLLER_INFOW;
#define DS_INET_ADDRESS 0x0001
#define DS_NETBIOS_ADDRESS 0x0002
#define DS_PDC_FLAG 0x00000001
#define DS_GC_FLAG 0x00000004
#define DS_DS_FLAG 0x00000010
#define DS_KDC_FLAG 0x00000020
#define DS_TIMESERV_FLAG 0x00000040
#define DS_WRITABLE_FLAG 0x00000100
#define DS_DNS_CONTROLLER_FLAG 0x20000000
#define DS_DNS_DOMAIN_FLAG 0x40000000
#define DS_DNS_FOREST_FLAG 0x80000000
typedef struct _DS_DOMAIN_TRUSTSA {
	LPSTR NetbiosDomainName;
	LPSTR DnsDomainName;
	ULONG Flags;
	ULONG ParentIndex;
	ULONG TrustType;
	ULONG TrustAttributes;
	PSID DomainSid;
	GUID DomainGuid;
} DS_DOMAIN_TRUSTSA,*PDS_DOMAIN_TRUSTSA;
typedef struct _DS_DOMAIN_TRUSTSW {
	LPWSTR NetbiosDomainName;
	LPWSTR DnsDomainName;
	ULONG Flags;
	ULONG ParentIndex;
	ULONG TrustType;
	ULONG TrustAttributes;
	PSID DomainSid;
	GUID DomainGuid;
} DS_DOMAIN_TRUSTSW,*PDS_DOMAIN_TRUSTSW;
#define DS_DOMAIN_IN_FOREST 0x0001
#define DS_DOMAIN_DIRECT_OUTBOUND 0x0002
#define DS_DOMAIN_TREE_ROOT 0x0004
#define DS_DOMAIN_PRIMARY 0x0008
#define DS_DOMAIN_NATIVE_MODE 0x0010
#define DS_DOMAIN_DIRECT_INBOUND 0x0020

DWORD WINAPI DsGetDcNameW(LPCWSTR, LPCWSTR, GUID*, LPCWSTR, ULONG, PDOMAIN_CONTROLLER_INFOW*);
DWORD WINAPI DsGetDcNameA(LPCSTR, LPCSTR, GUID*, LPCSTR, ULONG, PDOMAIN_CONTROLLER_INFOA*);

#ifdef UNICODE
typedef DOMAIN_CONTROLLER_INFOW DOMAIN_CONTROLLER_INFO,*PDOMAIN_CONTROLLER_INFO;
typedef DS_DOMAIN_TRUSTSW DS_DOMAIN_TRUSTS,*PDS_DOMAIN_TRUSTS;
#define DsGetDcName DsGetDcNameW
#else
typedef DOMAIN_CONTROLLER_INFOA DOMAIN_CONTROLLER_INFO,*PDOMAIN_CONTROLLER_INFO;
typedef DS_DOMAIN_TRUSTSA DS_DOMAIN_TRUSTS,*PDS_DOMAIN_TRUSTS;
#define DsGetDcName DsGetDcNameA
#endif
#endif /* (_WIN32_WINNT >= 0x0500) */

#ifdef __cplusplus
}
#endif
#endif
