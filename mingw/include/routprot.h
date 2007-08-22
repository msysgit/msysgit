/*
	routprot.h - Routing and Remote Access Services

	This file is part of a free library for the Win32 API.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/
#ifndef _ROUTPROT_H
#define _ROUTPROT_H
#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*--- Router Management MIB Reference - Transport and Protocol Constants */
#define PROTO_IP_OTHER 0x00000001
#define PROTO_IP_LOCAL 0x00000002
#define PROTO_IP_NETMGMT 0x00000003
#define PROTO_IP_ICMP 0x00000004
#define PROTO_IP_EGP 0x00000005
#define PROTO_IP_GGP 0x00000006
#define PROTO_IP_HELLO 0x00000007
#define PROTO_IP_RIP 0x00000008
#define PROTO_IP_IS_IS 0x00000009
#define PROTO_IP_ES_IS 0x0000000A
#define PROTO_IP_CISCO 0x0000000B
#define PROTO_IP_BBN 0x0000000C
#define PROTO_IP_OSPF 0x0000000D
#define PROTO_IP_BGP 0x0000000E
#define PROTO_IP_BOOTP 0x0000270F
#define PROTO_IP_NT_AUTOSTATIC 0x00002712
#define PROTO_IP_NT_STATIC 0x00002716
#define PROTO_IP_NT_STATIC_NON_DOD 0x00002717
#define IPRTRMGR_PID 10000
#define IPX_PROTOCOL_BASE 0x0001FFFF
#define IPX_PROTOCOL_RIP 0x00020000
#define IPX_PROTOCOL_SAP 0x00020001
#define IPX_PROTOCOL_NLSP 0x00020002
/*--- Router Management Reference - Router Management Structures */
#if (_WIN32_WINNT >= 0x0500)
typedef struct IP_ADAPTER_BINDING_INFO {
	ULONG AddressCount;
	DWORD RemoteAddress;
	ULONG Mtu;
	ULONGLONG Speed;
	IP_LOCAL_BINDING Address[];
} IP_ADAPTER_BINDING_INFO,*PIP_ADAPTER_BINDING_INFO;
typedef struct IP_LOCAL_BINDING {
	DWORD Address;
	DWORD Mask;
} IP_LOCAL_BINDING,*PIP_LOCAL_BINDING;
typedef struct IPX_ADAPTER_BINDING_INFO {
	ULONG AdapterIndex;
	UCHAR Network[4];
	UCHAR LocalNode[6];
	UCHAR RemoteNode[6];
	ULONG MaxPacketSize;
	ULONG LinkSpeed;
} IPX_ADAPTER_BINDING_INFO,*PIPX_ADAPTER_BINDING_INFO;
#endif /* (_WIN32_WINNT >= 0x0500) */

#ifdef __cplusplus
}
#endif
#endif
