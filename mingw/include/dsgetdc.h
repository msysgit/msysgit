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
#ifdef UNICODE
typedef DOMAIN_CONTROLLER_INFOW DOMAIN_CONTROLLER_INFO,*PDOMAIN_CONTROLLER_INFO;
typedef DS_DOMAIN_TRUSTSW DS_DOMAIN_TRUSTS,*PDS_DOMAIN_TRUSTS;
#else
typedef DOMAIN_CONTROLLER_INFOA DOMAIN_CONTROLLER_INFO,*PDOMAIN_CONTROLLER_INFO;
typedef DS_DOMAIN_TRUSTSA DS_DOMAIN_TRUSTS,*PDS_DOMAIN_TRUSTS;
#endif
#endif /* (_WIN32_WINNT >= 0x0500) */

#ifdef __cplusplus
}
#endif
#endif
