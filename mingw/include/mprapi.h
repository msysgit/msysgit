/*
 * mprapi.h - Routing and Remote Access Services
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
#ifndef _MPRAPI_H
#define _MPRAPI_H
#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#include <ras.h>
#include <lmcons.h>

#ifdef __cplusplus
extern "C" {
#endif

#if (_WIN32_WINNT >= 0x0500)
/*--- Router Management Reference - Router Management Enumerated Types */
typedef enum _ROUTER_CONNECTION_STATE {
	ROUTER_IF_STATE_UNREACHABLE,
	ROUTER_IF_STATE_DISCONNECTED,
	ROUTER_IF_STATE_CONNECTING,
	ROUTER_IF_STATE_CONNECTED
} ROUTER_CONNECTION_STATE;
typedef enum _ROUTER_INTERFACE_TYPE {
	ROUTER_IF_TYPE_CLIENT,
	ROUTER_IF_TYPE_HOME_ROUTER,
	ROUTER_IF_TYPE_FULL_ROUTER,
	ROUTER_IF_TYPE_DEDICATED,
	ROUTER_IF_TYPE_INTERNAL,
	ROUTER_IF_TYPE_LOOPBACK,
	ROUTER_IF_TYPE_TUNNEL1,
	ROUTER_IF_TYPE_DIALOUT
} ROUTER_INTERFACE_TYPE;
#define MPR_INTERFACE_ADMIN_DISABLED 0x00000002
#define MPR_INTERFACE_CONNECTION_FAILURE 0x00000004
#define MPR_INTERFACE_DIALOUT_HOURS_RESTRICTION 0x00000010
#define MPR_INTERFACE_OUT_OF_RESOURCES 0x00000001
#define MPR_INTERFACE_SERVICE_PAUSED 0x00000008
#define MPR_INTERFACE_NO_MEDIA_SENSE 0x00000020
#define MPR_INTERFACE_NO_DEVICE 0x00000040
/*--- Router Management MIB Reference - Transport and Protocol Constants */
#define PID_ATALK 0x00000029
#define PID_IP 0x00000021
#define PID_IPX 0x0000002B
#define PID_NBF 0x0000003F
/*--- Remote Access Service Administration Reference - RAS Administration Enumerated Types */
typedef enum _RAS_HARDWARE_CONDITION {
	RAS_HARDWARE_OPERATIONAL,
	RAS_HARDWARE_FAILURE
} RAS_HARDWARE_CONDITION;
typedef enum _RAS_PORT_CONDITION {
	RAS_PORT_NON_OPERATIONAL,
	RAS_PORT_DISCONNECTED,	
	RAS_PORT_CALLING_BACK,
	RAS_PORT_LISTENING,
	RAS_PORT_AUTHENTICATING,
	RAS_PORT_AUTHENTICATED,	
	RAS_PORT_INITIALIZING
} RAS_PORT_CONDITION;
/*--- Remote Access Service Administration Reference - RAS Administration Structures */
#define ATADDRESSLEN 32
typedef struct _PPP_ATCP_INFO {
	DWORD dwError;
	WCHAR wszAddress[ATADDRESSLEN+1];
} PPP_ATCP_INFO;
typedef struct _PPP_CCP_INFO {
	DWORD dwError;
	DWORD dwCompressionAlgorithm;
	DWORD dwOptions;
	DWORD dwRemoteCompressionAlgorithm;
	DWORD dwRemoteOptions;
} PPP_CCP_INFO;
#define RASCCPCA_STAC 0x00000005
#define RASCCPCA_MPPC 0x00000006
#define PPP_CCP_COMPRESSION 0x00000001
#define PPP_CCP_ENCRYPTION40BITOLD 0x00000010
#define PPP_CCP_ENCRYPTION40BIT 0x00000020
#define PPP_CCP_ENCRYPTION128BIT 0x00000040
#define PPP_CCP_ENCRYPTION56BIT 0x00000080
#define PPP_CCP_HISTORYLESS 0x01000000
#define IPADDRESSLEN 15
typedef struct _PPP_IPCP_INFO {
	DWORD dwError;
	WCHAR wszAddress[IPADDRESSLEN+1];
	WCHAR wszRemoteAddress[IPADDRESSLEN+1];
} PPP_IPCP_INFO;
typedef struct _PPP_IPCP_INFO2 {
	DWORD dwError;
	WCHAR wszAddress[IPADDRESSLEN+1];
	WCHAR wszRemoteAddress[IPADDRESSLEN+1];
	DWORD dwOptions;
	DWORD dwRemoteOptons;
} PPP_IPCP_INFO2;
#define IPXADDRESSLEN 22
typedef struct _PPP_IPXCP_INFO {
	DWORD dwError;
	WCHAR wszAddress[IPXADDRESSLEN+1];
} PPP_IPXCP_INFO;
typedef struct _PPP_LCP_INFO {
	DWORD dwError;
	DWORD dwAuthenticationProtocol;
	DWORD dwAuthenticationData;
	DWORD dwRemoteAuthenticationProtocol;
	DWORD dwRemoteAuthenticationData;
	DWORD dwTerminateReason;
	DWORD dwRemoteTerminateReason;
	DWORD dwOptions;
	DWORD dwRemoteOptions;
	DWORD dwEapTypeId;
	DWORD dwRemoteEapTypeId;
} PPP_LCP_INFO;
#define PPP_LCP_PAP 0x0000C023
#define PPP_LCP_SPAP 0x0000C027
#define PPP_LCP_CHAP 0x0000C223
#define PPP_LCP_EAP 0x0000C227
#define PPP_LCP_CHAP_MD5 0x00000005
#define PPP_LCP_CHAP_MS 0x00000080
#define PPP_LCP_CHAP_MSV2 0x00000081
#define PPP_LCP_MULTILINK_FRAMING 0x00000001
typedef struct _PPP_NBFCP_INFO {
	DWORD dwError;
	WCHAR wszWksta[NETBIOS_NAME_LEN+1];
} PPP_NBFCP_INFO;
typedef struct _PPP_INFO {
	PPP_NBFCP_INFO nbf;
	PPP_IPCP_INFO ip;
	PPP_IPXCP_INFO ipx;
	PPP_ATCP_INFO at;
} PPP_INFO;
typedef struct _PPP_INFO_2 {
	PPP_NBFCP_INFO nbf;
	PPP_IPCP_INFO2 ip;
	PPP_IPXCP_INFO ipx;
	PPP_ATCP_INFO at;
	PPP_CCP_INFO ccp;
	PPP_LCP_INFO lcp;
} PPP_INFO_2;
#define MAX_INTERFACE_NAME_LEN 256
typedef struct _RAS_CONNECTION_0 {
	HANDLE hConnection;
	HANDLE hInterface;
	DWORD dwConnectDuration;
	ROUTER_INTERFACE_TYPE dwInterfaceType;
	DWORD dwConnectionFlags;
	WCHAR wszInterfaceName[MAX_INTERFACE_NAME_LEN+1];
	WCHAR wszUserName[UNLEN+1];
	WCHAR wszLogonDomain[DNLEN+1];
	WCHAR wszRemoteComputer[NETBIOS_NAME_LEN+1];
} RAS_CONNECTION_0,*PRAS_CONNECTION_0;
#define RAS_FLAGS_PPP_CONNECTION 0x00000001
#define RAS_FLAGS_MESSENGER_PRESENT 0x00000002
#define RAS_FLAGS_RAS_CONNECTION 0x00000004
#define RAS_FLAGS_QUARANTINE_PRESENT 0x00000008
typedef struct RAS_CONNECTION_1 {
	HANDLE hConnection;
	HANDLE hInterface;
	PPP_INFO PppInfo;
	DWORD dwBytesXmited;
	DWORD dwBytesRcved;
	DWORD dwFramesXmited;
	DWORD dwFramesRcved;
	DWORD dwCrcErr;
	DWORD dwTimeoutErr;
	DWORD dwAlignmentErr;
	DWORD dwHardwareOverrunErr;
	DWORD dwFramingErr;
	DWORD dwBufferOverrunErr;
	DWORD dwCompressionRatioIn;
	DWORD dwCompressionRatioOut;
} RAS_CONNECTION_1,*PRAS_CONNECTION_1;
typedef struct _RAS_CONNECTION_2 {
	HANDLE hConnection;
	WCHAR wszUserName[UNLEN+1];
	ROUTER_INTERFACE_TYPE dwInterfaceType;
	GUID guid;
	PPP_INFO_2 PppInfo2;
} RAS_CONNECTION_2,*PRAS_CONNECTION_2;
#define MAX_PORT_NAME 16
#define MAX_MEDIA_NAME 16
#define MAX_DEVICE_NAME 128
#define MAX_DEVICETYPE_NAME 16
typedef struct _RAS_PORT_0 {
	HANDLE hPort;
	HANDLE hConnection;
	RAS_PORT_CONDITION dwPortCondition;
	DWORD dwTotalNumberOfCalls;
	DWORD dwConnectDuration;
	WCHAR wszPortName[MAX_PORT_NAME+1];
	WCHAR wszMediaName[MAX_MEDIA_NAME+1];
	WCHAR wszDeviceName[MAX_DEVICE_NAME+1];
	WCHAR wszDeviceType[MAX_DEVICETYPE_NAME+1];
} RAS_PORT_0,*PRAS_PORT_0;
typedef struct _RAS_PORT_1 {
	HANDLE hPort;
	HANDLE hConnection;
	RAS_HARDWARE_CONDITION dwHardwareCondition;
	DWORD dwLineSpeed;
	DWORD dwBytesXmited;
	DWORD dwBytesRcved;
	DWORD dwFramesXmited;
	DWORD dwFramesRcved;
	DWORD dwCrcErr;
	DWORD dwTimeoutErr;
	DWORD dwAlignmentErr;
	DWORD dwHardwareOverrunErr;
	DWORD dwFramingErr;
	DWORD dwBufferOverrunErr;
	DWORD dwCompressionRatioIn;
	DWORD dwCompressionRatioOut;
} RAS_PORT_1,*PRAS_PORT_1;
#define MAX_PHONE_NUMBER_LEN 128
typedef struct _RAS_USER_0 {
	BYTE bfPrivilege;
	WCHAR wszPhoneNumber[MAX_PHONE_NUMBER_LEN+1];
} RAS_USER_0,*PRAS_USER_0;
#define RASPRIV_NoCallback 0x01
#define RASPRIV_AdminSetCallback 0x02
#define RASPRIV_CallerSetCallback 0x04
#define RASPRIV_DialinPrivilege 0x08
#define RASPRIV_CallbackType 0x07
typedef struct _RAS_USER_1 {
	BYTE bfPrivilege;
	WCHAR wszPhoneNumber[MAX_PHONE_NUMBER_LEN+1];
	BYTE bfPrivilege2;
} RAS_USER_1,*PRAS_USER_1;
#define RASPRIV2_DialinPolicy 0x01
/*--- Router Management Reference - Router Management Structures */
typedef struct _MPR_CREDENTIALSEX_0 {
	DWORD  dwSize;
	LPBYTE lpbCredentialsInfo;
} MPR_CREDENTIALSEX_0,*PMPR_CREDENTIALSEX_0;
#if (_WIN32_WINNT >= 0x0502)
typedef struct _MPR_CREDENTIALSEX_1 {
	DWORD  dwSize;
	LPBYTE lpbCredentialsInfo;
} MPR_CREDENTIALSEX_1,*PMPR_CREDENTIALSEX_1;
#endif
#define MPR_MaxDeviceType RAS_MaxDeviceType
#define MPR_MaxDeviceName RAS_MaxDeviceName
#define MPR_MaxPadType RAS_MaxPadType
#define MPR_MaxX25Address RAS_MaxX25Address
#define MPR_MaxFacilities RAS_MaxFacilities
#define MPR_MaxUserData RAS_MaxUserData
#define MPR_MaxPhoneNumber RAS_MaxPhoneNumber
typedef struct _MPR_DEVICE_0 {
	WCHAR szDeviceType[MPR_MaxDeviceType+1];
	WCHAR szDeviceName[MPR_MaxDeviceName+1];
} MPR_DEVICE_0,*PMPR_DEVICE_0;
typedef struct _MPR_DEVICE_1 {
	WCHAR szDeviceType[MPR_MaxDeviceType+1];
	WCHAR szDeviceName[MPR_MaxDeviceName+1];
	WCHAR szLocalPhoneNumber[MPR_MaxPhoneNumber+1];
	PWCHAR szAlternates;
} MPR_DEVICE_1,*PMPR_DEVICE_1;
#define MAX_TRANSPORT_NAME_LEN 40
typedef struct _MPR_IFTRANSPORT_0 {
	DWORD dwTransportId;
	HANDLE hIfTransport;
	WCHAR wszIfTransportName[MAX_TRANSPORT_NAME_LEN+1];
} MPR_IFTRANSPORT_0,*PMPR_IFTRANSPORT_0;
typedef struct _MPR_INTERFACE_0 {
	WCHAR wszInterfaceName[MAX_INTERFACE_NAME_LEN+1];
	HANDLE hInterface;
	BOOL fEnabled;
	ROUTER_INTERFACE_TYPE dwIfType;
	ROUTER_CONNECTION_STATE dwConnectionState;
	DWORD fUnReachabilityReasons;
	DWORD dwLastError;
} MPR_INTERFACE_0,*PMPR_INTERFACE_0;
typedef struct _MPR_INTERFACE_1 {
	WCHAR wszInterfaceName[MAX_INTERFACE_NAME_LEN+1];
	HANDLE hInterface;
	BOOL fEnabled;
	ROUTER_INTERFACE_TYPE IfType;
	ROUTER_CONNECTION_STATE dwConnectionState;
	DWORD fUnReachabilityReasons;
	DWORD dwLastError;
	LPWSTR lpwsDialoutHoursRestriction;
} MPR_INTERFACE_1,*PMPR_INTERFACE_1;
typedef struct _MPR_INTERFACE_2 {
	WCHAR wszInterfaceName[MAX_INTERFACE_NAME_LEN+1];
	HANDLE hInterface;
	BOOL fEnabled;
	ROUTER_INTERFACE_TYPE dwIfType;
	ROUTER_CONNECTION_STATE dwConnectionState;
	DWORD fUnReachabilityReasons;
	DWORD dwLastError;
	DWORD dwfOptions;
	WCHAR szLocalPhoneNumber[RAS_MaxPhoneNumber+1];
	PWCHAR szAlternates;
	DWORD ipaddr;
	DWORD ipaddrDns;
	DWORD ipaddrDnsAlt;
	DWORD ipaddrWins;
	DWORD ipaddrWinsAlt;
	DWORD dwfNetProtocols;
	WCHAR szDeviceType[MPR_MaxDeviceType+1];
	WCHAR szDeviceName[MPR_MaxDeviceName+1];
	WCHAR szX25PadType[MPR_MaxPadType+1];
	WCHAR szX25Address[MPR_MaxX25Address+1];
	WCHAR szX25Facilities[MPR_MaxFacilities+1];
	WCHAR szX25UserData[MPR_MaxUserData+1];
	DWORD dwChannels;
	DWORD dwSubEntries;
	DWORD dwDialMode;
	DWORD dwDialExtraPercent;
	DWORD dwDialExtraSampleSeconds;
	DWORD dwHangUpExtraPercent;
	DWORD dwHangUpExtraSampleSeconds;
	DWORD dwIdleDisconnectSeconds;
	DWORD dwType;
	DWORD dwEncryptionType;
	DWORD dwCustomAuthKey;
	DWORD dwCustomAuthDataSize;
	LPBYTE lpbCustomAuthData;
	GUID guidId;
	DWORD dwVpnStrategy;
} MPR_INTERFACE_2,*PMPR_INTERFACE_2;
#define MPRIO_SpecificIpAddr RASEO_SpecificIpAddr
#define MPRIO_SpecificNameServers RASEO_SpecificNameServers
#define MPRIO_IpHeaderCompression RASEO_IpHeaderCompression
#define MPRIO_RemoteDefaultGateway RASEO_RemoteDefaultGateway
#define MPRIO_DisableLcpExtensions RASEO_DisableLcpExtensions
#define MPRIO_SwCompression RASEO_SwCompression
#define MPRIO_RequireEncryptedPw RASEO_RequireEncryptedPw
#define MPRIO_RequireMsEncryptedPw RASEO_RequireMsEncryptedPw
#define MPRIO_RequireDataEncryption RASEO_RequireDataEncryption
#define MPRIO_NetworkLogon RASEO_NetworkLogon
#define MPRIO_UseLogonCredentials RASEO_UseLogonCredentials
#define MPRIO_PromoteAlternates RASEO_PromoteAlternates
#define MPRIO_SecureLocalFiles RASEO_SecureLocalFiles
#define MPRIO_RequireEAP RASEO_RequireEAP
#define MPRIO_RequirePAP RASEO_RequirePAP
#define MPRIO_RequireSPAP RASEO_RequireSPAP
#define MPRIO_SharedPhoneNumbers RASEO_SharedPhoneNumbers
#define MPRIO_RequireCHAP RASEO_RequireCHAP
#define MPRIO_RequireMsCHAP RASEO_RequireMsCHAP
#define MPRIO_RequireMsCHAP2 RASEO_RequireMsCHAP2
#define MPRNP_Ipx RASNP_Ipx
#define MPRNP_Ip RASNP_Ip
#define MPRDT_Modem RASDT_Modem
#define MPRDT_Isdn RASDT_Isdn
#define MPRDT_X25 RASDT_X25
#define MPRDT_Vpn RASDT_Vpn
#define MPRDT_Pad RASDT_Pad
#define MPRDT_Generic RASDT_Generic
#define MPRDT_Serial RASDT_Serial
#define MPRDT_FrameRelay RASDT_FrameRelay
#define MPRDT_Atm RASDT_Atm
#define MPRDT_Sonet RASDT_Sonet
#define MPRDT_SW56 RASDT_SW56
#define MPRDT_Irda RASDT_Irda
#define MPRDT_Parallel RASDT_Parallel
#define MPRDM_DialAll RASEDM_DialAll
#define MPRDM_DialAsNeeded RASEDM_DialAsNeeded
#define MPRIDS_Disabled RASIDS_Disabled
#define MPRIDS_UseGlobalValue RASIDS_UseGlobalValue
#define MPRET_Phone RASET_Phone
#define MPRET_Vpn RASET_Vpn
#define MPRET_Direct RASET_Direct
#define MPR_ET_None ET_None
#define MPR_ET_Require ET_Require
#define MPR_ET_RequireMax ET_RequireMax
#define MPR_ET_Optional ET_Optional
#define MPR_VS_Default VS_Default	
#define MPR_VS_PptpOnly VS_PptpOnly
#define MPR_VS_PptpFirst VS_PptpFirst
#define MPR_VS_L2tpOnly VS_L2tpOnly
#define MPR_VS_L2tpFirst VS_L2tpFirst
#if (_WIN32_WINNT>=0x0600)
typedef struct _MPR_INTERFACE_3 {
	WCHAR wszInterfaceName[MAX_INTERFACE_NAME_LEN+1];
	HANDLE hInterface;
	BOOL fEnabled;
	ROUTER_INTERFACE_TYPE dwIfType;
	ROUTER_CONNECTION_STATE dwConnectionState;
	DWORD fUnReachabilityReasons;
	DWORD dwLastError;
	DWORD dwfOptions;
	WCHAR szLocalPhoneNumber[RAS_MaxPhoneNumber+1];
	PWCHAR szAlternates;
	DWORD ipaddr;
	DWORD ipaddrDns;
	DWORD ipaddrDnsAlt;
	DWORD ipaddrWins;
	DWORD ipaddrWinsAlt;
	DWORD dwfNetProtocols;
	WCHAR szDeviceType[MPR_MaxDeviceType+1];
	WCHAR szDeviceName[MPR_MaxDeviceName+1];
	WCHAR szX25PadType[MPR_MaxPadType+1];
	WCHAR szX25Address[MPR_MaxX25Address+1];
	WCHAR szX25Facilities[MPR_MaxFacilities+1];
	WCHAR szX25UserData[MPR_MaxUserData+1];
	DWORD dwChannels;
	DWORD dwSubEntries;
	DWORD dwDialMode;
	DWORD dwDialExtraPercent;
	DWORD dwDialExtraSampleSeconds;
	DWORD dwHangUpExtraPercent;
	DWORD dwHangUpExtraSampleSeconds;
	DWORD dwIdleDisconnectSeconds;
	DWORD dwType;
	DWORD dwEncryptionType;
	DWORD dwCustomAuthKey;
	DWORD dwCustomAuthDataSize;
	LPBYTE lpbCustomAuthData;
	GUID guidId;
	DWORD dwVpnStrategy;
	ULONG AddressCount;
	IN6_ADDR ipv6addrDns;
	IN6_ADDR ipv6addrDnsAlt;
	IN6_ADDR* ipv6addr;
} MPR_INTERFACE_3,*PMPR_INTERFACE_3;
#endif
typedef struct _MPR_SERVER_0 {
	BOOL fLanOnlyMode;
	DWORD dwUpTime;
	DWORD dwTotalPorts;
	DWORD dwPortsInUse;
} MPR_SERVER_0,*PMPR_SERVER_0;
#if (_WIN32_WINNT >= 0x0502)
typedef struct _MPR_SERVER_1 {
	DWORD dwNumPptpPorts;
	DWORD dwPptpPortFlags;
	DWORD dwNumL2tpPorts;
	DWORD dwL2tpPortFlags;
} MPR_SERVER_1,*PMPR_SERVER_1;
#define MPR_ENABLE_RAS_ON_DEVICE 0x00000001
#define MPR_ENABLE_ROUTING_ON_DEVICE 0x00000002
#endif
typedef struct _MPR_TRANSPORT_0 {
	DWORD dwTransportId;
	HANDLE hTransport;
	WCHAR wszTransportName[MAX_TRANSPORT_NAME_LEN+1];
} MPR_TRANSPORT_0,*PMPR_TRANSPORT_0;
typedef HANDLE RAS_SERVER_HANDLE;
typedef HANDLE MPR_SERVER_HANDLE;
/*--- Remote Access Service Administration Reference - RAS Administration Functions */
DWORD WINAPI MprAdminConnectionClearStats(RAS_SERVER_HANDLE,HANDLE);
DWORD WINAPI MprAdminConnectionEnum(RAS_SERVER_HANDLE,DWORD,LPBYTE*,DWORD,LPDWORD,LPDWORD,LPDWORD);
DWORD WINAPI MprAdminConnectionGetInfo(RAS_SERVER_HANDLE,DWORD,HANDLE,LPBYTE*);
DWORD WINAPI MprAdminConnectionRemoveQuarantine(HANDLE,HANDLE,BOOL);
DWORD WINAPI MprAdminPortClearStats(RAS_SERVER_HANDLE,HANDLE);
DWORD WINAPI MprAdminPortDisconnect(RAS_SERVER_HANDLE,HANDLE);
DWORD WINAPI MprAdminPortEnum(RAS_SERVER_HANDLE,DWORD,HANDLE,LPBYTE*,DWORD,LPDWORD,LPDWORD,LPDWORD);
DWORD WINAPI MprAdminPortGetInfo(RAS_SERVER_HANDLE,DWORD,HANDLE,LPBYTE);
DWORD WINAPI MprAdminPortReset(RAS_SERVER_HANDLE,HANDLE);
/*--- Remote Access Service Administration Reference - RAS Administration Functions - RAS Admin DLL Functions */
BOOL WINAPI MprAdminAcceptNewConnection(RAS_CONNECTION_0*,RAS_CONNECTION_1*);
BOOL WINAPI MprAdminAcceptNewConnection2(RAS_CONNECTION_0*,RAS_CONNECTION_1*,RAS_CONNECTION_2*);
BOOL WINAPI MprAdminAcceptNewLink(RAS_PORT_0*,RAS_PORT_1*);
#if (_WIN32_WINNT >= 0x0600)
BOOL WINAPI MprAdminAcceptReauthentication(RAS_CONNECTION_0*,RAS_CONNECTION_1*,RAS_CONNECTION_2*,RAS_CONNECTION_3*);
#endif
void WINAPI MprAdminConnectionHangupNotification(RAS_CONNECTION_0*,RAS_CONNECTION_1*);
void WINAPI MprAdminConnectionHangupNotification2(RAS_CONNECTION_0*,RAS_CONNECTION_1*,RAS_CONNECTION_2*);
DWORD WINAPI MprAdminGetIpAddressForUser(WCHAR*,WCHAR*,DWORD*,BOOL*);
#if (_WIN32_WINNT >= 0x0502)
DWORD WINAPI MprAdminInitializeDll(void);
DWORD WINAPI MprAdminTerminateDll(void);
#endif
void WINAPI MprAdminLinkHangupNotification(RAS_PORT_0*,RAS_PORT_1*);
void WINAPI MprAdminReleaseIpAddress(WCHAR*,WCHAR*,DWORD*);
/*--- Remote Access Service Administration Reference - RAS Administration Functions - RAS User Administration Functions */
DWORD WINAPI MprAdminGetPDCServer(const WCHAR*,const WCHAR*,LPWSTR);
DWORD WINAPI MprAdminSendUserMessage(MPR_SERVER_HANDLE,HANDLE,LPWSTR);
DWORD WINAPI MprAdminUserGetInfo(const WCHAR*,const WCHAR*,DWORD,LPBYTE);
DWORD WINAPI MprAdminUserSetInfo(const WCHAR*,const WCHAR*,DWORD,const LPBYTE);
/*--- Router Management Reference - Router Administration Functions */
DWORD WINAPI MprAdminBufferFree(LPVOID);
DWORD WINAPI MprAdminDeregisterConnectionNotification(MPR_SERVER_HANDLE,HANDLE);
DWORD WINAPI MprAdminEstablishDomainRasServer(PWCHAR,PWCHAR,BOOL);
DWORD WINAPI MprAdminGetErrorString(DWORD,LPWSTR*);
DWORD WINAPI MprAdminInterfaceConnect(MPR_SERVER_HANDLE,HANDLE,HANDLE,BOOL);
DWORD WINAPI MprAdminInterfaceCreate(MPR_SERVER_HANDLE,DWORD,LPBYTE,HANDLE*);
DWORD WINAPI MprAdminInterfaceDelete(MPR_SERVER_HANDLE,HANDLE);
DWORD WINAPI MprAdminInterfaceDeviceGetInfo(MPR_SERVER_HANDLE,HANDLE,DWORD,DWORD,LPBYTE*);
DWORD WINAPI MprAdminInterfaceDeviceSetInfo(MPR_SERVER_HANDLE,HANDLE,DWORD,DWORD,LPBYTE);
DWORD WINAPI MprAdminInterfaceDisconnect(MPR_SERVER_HANDLE,HANDLE);
DWORD WINAPI MprAdminInterfaceEnum(MPR_SERVER_HANDLE,DWORD,LPBYTE*,DWORD,LPDWORD,LPDWORD,LPDWORD);
DWORD WINAPI MprAdminInterfaceGetCredentials(LPWSTR,LPWSTR,LPWSTR,LPWSTR,LPWSTR);
DWORD WINAPI MprAdminInterfaceGetHandle(MPR_SERVER_HANDLE,LPWSTR,HANDLE*,BOOL);
DWORD WINAPI MprAdminInterfaceGetInfo(MPR_SERVER_HANDLE,HANDLE,DWORD,LPBYTE*);
DWORD WINAPI MprAdminInterfaceQueryUpdateResult(MPR_SERVER_HANDLE,HANDLE,DWORD,LPDWORD);
DWORD WINAPI MprAdminInterfaceSetCredentials(LPWSTR,LPWSTR,LPWSTR,LPWSTR,LPWSTR);
DWORD WINAPI MprAdminInterfaceSetCredentialsEx(MPR_SERVER_HANDLE,HANDLE,DWORD,LPBYTE);
DWORD WINAPI MprAdminInterfaceSetInfo(MPR_SERVER_HANDLE,HANDLE,DWORD,LPBYTE);
DWORD WINAPI MprAdminInterfaceTransportAdd(MPR_SERVER_HANDLE,HANDLE,DWORD,LPBYTE,DWORD);
DWORD WINAPI MprAdminInterfaceTransportGetInfo(MPR_SERVER_HANDLE,HANDLE,DWORD,LPBYTE*,LPDWORD);
DWORD WINAPI MprAdminInterfaceTransportRemove(MPR_SERVER_HANDLE,HANDLE,DWORD);
DWORD WINAPI MprAdminInterfaceTransportSetInfo(MPR_SERVER_HANDLE,HANDLE,DWORD,LPBYTE,DWORD);
DWORD WINAPI MprAdminInterfaceUpdatePhonebookInfo(MPR_SERVER_HANDLE,HANDLE);
DWORD WINAPI MprAdminInterfaceUpdateRoutes(MPR_SERVER_HANDLE,HANDLE,DWORD,HANDLE);
DWORD WINAPI MprAdminIsDomainRasServer(PWCHAR,PWCHAR,PBOOL);
BOOL WINAPI MprAdminIsServiceRunning(LPWSTR);
DWORD WINAPI MprAdminRegisterConnectionNotification(MPR_SERVER_HANDLE,HANDLE);
DWORD WINAPI MprAdminServerConnect(LPWSTR,MPR_SERVER_HANDLE*);
void WINAPI MprAdminServerDisconnect(MPR_SERVER_HANDLE);
DWORD WINAPI MprAdminServerGetCredentials(MPR_SERVER_HANDLE,DWORD,LPBYTE*);
DWORD WINAPI MprAdminInterfaceGetCredentialsEx(MPR_SERVER_HANDLE,HANDLE,DWORD,LPBYTE*);
DWORD WINAPI MprAdminServerGetInfo(MPR_SERVER_HANDLE,DWORD,LPBYTE*);
DWORD WINAPI MprAdminServerSetCredentials(MPR_SERVER_HANDLE,DWORD,LPBYTE);
DWORD WINAPI MprAdminServerSetInfo(MPR_SERVER_HANDLE,DWORD,LPBYTE);
DWORD WINAPI MprAdminTransportCreate(MPR_SERVER_HANDLE,DWORD,LPWSTR,LPBYTE,DWORD,LPBYTE,DWORD,LPWSTR);
DWORD WINAPI MprAdminTransportGetInfo(MPR_SERVER_HANDLE,DWORD,LPBYTE*,LPDWORD,LPBYTE*,LPDWORD);
DWORD WINAPI MprAdminTransportSetInfo(MPR_SERVER_HANDLE,DWORD,LPBYTE,DWORD,LPBYTE,DWORD);
/*--- Router Management Reference - Router Configuration Functions */
DWORD WINAPI MprConfigBufferFree(LPVOID);
DWORD WINAPI MprConfigGetFriendlyName(HANDLE,PWCHAR,PWCHAR,DWORD);
DWORD WINAPI MprConfigGetGuidName(HANDLE,PWCHAR,PWCHAR,DWORD);
DWORD WINAPI MprConfigInterfaceCreate(HANDLE,DWORD,LPBYTE,HANDLE*);
DWORD WINAPI MprConfigInterfaceDelete(HANDLE,HANDLE);
DWORD WINAPI MprConfigInterfaceEnum(HANDLE,DWORD,LPBYTE*,DWORD,LPDWORD,LPDWORD,LPDWORD);
DWORD WINAPI MprConfigInterfaceGetHandle(HANDLE,LPWSTR,HANDLE*);
DWORD WINAPI MprConfigInterfaceGetInfo(HANDLE,HANDLE,DWORD,LPBYTE*,LPDWORD);
DWORD WINAPI MprConfigInterfaceSetInfo(HANDLE,HANDLE,DWORD,LPBYTE);
DWORD WINAPI MprConfigInterfaceTransportAdd(HANDLE,HANDLE,DWORD,LPWSTR,LPBYTE,DWORD,HANDLE*);
DWORD WINAPI MprConfigInterfaceTransportEnum(HANDLE,HANDLE,DWORD,LPBYTE*,DWORD,LPDWORD,LPDWORD,LPDWORD);
DWORD WINAPI MprConfigInterfaceTransportGetHandle(HANDLE,HANDLE,DWORD,HANDLE*);
DWORD WINAPI MprConfigInterfaceTransportGetInfo(HANDLE,HANDLE,HANDLE,LPBYTE*,LPDWORD);
DWORD WINAPI MprConfigInterfaceTransportRemove(HANDLE,HANDLE,HANDLE);
DWORD WINAPI MprConfigInterfaceTransportSetInfo(HANDLE,HANDLE,HANDLE,LPBYTE,DWORD);
DWORD WINAPI MprConfigServerBackup(HANDLE,LPWSTR);
DWORD WINAPI MprConfigServerConnect(LPWSTR,HANDLE*);
void WINAPI MprConfigServerDisconnect(HANDLE);
DWORD WINAPI MprConfigServerGetInfo(HANDLE,DWORD,LPBYTE*);
DWORD WINAPI MprConfigServerInstall(DWORD,PVOID);
DWORD WINAPI MprConfigServerRestore(HANDLE,LPWSTR);
DWORD WINAPI MprConfigServerSetInfo(HANDLE,DWORD,LPBYTE);
DWORD WINAPI MprConfigTransportCreate(HANDLE,DWORD,LPWSTR,LPBYTE,DWORD,LPBYTE,DWORD,LPWSTR,HANDLE);
DWORD WINAPI MprConfigTransportDelete(HANDLE,HANDLE);
DWORD WINAPI MprConfigTransportEnum(HANDLE,DWORD,LPBYTE*,DWORD,LPDWORD,LPDWORD,LPDWORD);
DWORD WINAPI MprConfigTransportGetHandle(HANDLE,DWORD,HANDLE*);
DWORD WINAPI MprConfigTransportGetInfo(HANDLE,HANDLE,LPBYTE*,LPDWORD,LPBYTE*,LPDWORD,LPWSTR*);
DWORD WINAPI MprConfigTransportSetInfo(HANDLE,HANDLE,LPBYTE,DWORD,LPBYTE,DWORD,LPWSTR);
/*--- Router Management Reference - Information Header Functions */
DWORD WINAPI MprInfoBlockAdd(LPVOID,DWORD,DWORD,DWORD,LPBYTE,LPVOID*);
DWORD WINAPI MprInfoBlockFind(LPVOID,DWORD,LPDWORD,LPDWORD,LPBYTE*);
DWORD WINAPI MprInfoBlockQuerySize(LPVOID);
DWORD WINAPI MprInfoBlockRemove(LPVOID,DWORD,LPVOID*);
DWORD WINAPI MprInfoBlockSet(LPVOID,DWORD,DWORD,DWORD,LPBYTE,LPVOID*);
DWORD WINAPI MprInfoCreate(DWORD,LPVOID*);
DWORD WINAPI MprInfoDelete(LPVOID);
DWORD WINAPI MprInfoDuplicate(LPVOID,LPVOID*);
DWORD WINAPI MprInfoRemoveAll(LPVOID,LPVOID*);
/*--- Router Management MIB Reference - Router Management MIB Functions */
typedef HANDLE MIB_SERVER_HANDLE;
DWORD WINAPI MprAdminMIBBufferFree(LPVOID);
DWORD WINAPI MprAdminMIBEntryCreate(MIB_SERVER_HANDLE,DWORD,DWORD,LPVOID,DWORD);
DWORD WINAPI MprAdminMIBEntryDelete(MIB_SERVER_HANDLE,DWORD,DWORD,LPVOID,DWORD);
DWORD WINAPI MprAdminMIBEntryGet(MIB_SERVER_HANDLE,DWORD,DWORD,LPVOID,DWORD,LPVOID*,LPDWORD);
DWORD WINAPI MprAdminMIBEntryGetFirst(MIB_SERVER_HANDLE,DWORD,DWORD,LPVOID,DWORD,LPVOID*,LPDWORD);
DWORD WINAPI MprAdminMIBEntryGetNext(MIB_SERVER_HANDLE,DWORD,DWORD,LPVOID,DWORD,LPVOID*,LPDWORD);
DWORD WINAPI MprAdminMIBEntrySet(MIB_SERVER_HANDLE,DWORD,DWORD,LPVOID,DWORD);
DWORD WINAPI MprAdminMIBGetTrapInfo(MIB_SERVER_HANDLE,DWORD,DWORD,LPVOID,DWORD,LPVOID*,LPDWORD);
DWORD WINAPI MprAdminMIBServerConnect(LPWSTR,MIB_SERVER_HANDLE*);
void WINAPI MprAdminMIBServerDisconnect(MIB_SERVER_HANDLE);
DWORD WINAPI MprAdminMIBSetTrapInfo(DWORD,DWORD,HANDLE,LPVOID,DWORD,LPVOID*,LPDWORD);
#endif /* (_WIN32_WINNT >= 0x0500) */

#ifdef __cplusplus
}
#endif
#endif
