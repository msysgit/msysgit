/*
 * dsrole.h - Active Directory
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
#ifndef _DSROLE_H
#define _DSROLE_H
#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if (_WIN32_WINNT >= 0x0500)
/*--- Active Directory Reference - Active Directory Enumerations */
typedef enum {
	DsRole_RoleStandaloneWorkstation,
	DsRole_RoleMemberWorkstation,
	DsRole_RoleStandaloneServer,
	DsRole_RoleMemberServer,
	DsRole_RoleBackupDomainController,
	DsRole_RolePrimaryDomainController
} DSROLE_MACHINE_ROLE;
typedef enum {
	DsRoleOperationIdle,
	DsRoleOperationActive,
	DsRoleOperationNeedReboot
} DSROLE_OPERATION_STATE;
typedef enum {
	DsRolePrimaryDomainInfoBasic,
	DsRoleUpgradeStatus,
	DsRoleOperationState
} DSROLE_PRIMARY_DOMAIN_INFO_LEVEL;
typedef enum {
	DsRoleServerUnknown,
	DsRoleServerPrimary,
	DsRoleServerBackup
} DSROLE_SERVER_STATE;
/*--- Active Directory Reference - Active Directory Structures - Directory Service Structures */
typedef struct {
	DSROLE_OPERATION_STATE OperationState;
} DSROLE_OPERATION_STATE_INFO;
typedef struct _DSROLE_PRIMARY_DOMAIN_INFO_BASIC {
	DSROLE_MACHINE_ROLE MachineRole;
	ULONG Flags;
	LPWSTR DomainNameFlat;
	LPWSTR DomainNameDns;
	LPWSTR DomainForestName;
	GUID DomainGuid;
} DSROLE_PRIMARY_DOMAIN_INFO_BASIC,*PDSROLE_PRIMARY_DOMAIN_INFO_BASIC;
#define DSROLE_PRIMARY_DS_RUNNING 0x00000001
#define DSROLE_PRIMARY_DS_MIXED_MODE 0x00000002
#define DSROLE_UPGRADE_IN_PROGRESS 0x00000004
#define DSROLE_PRIMARY_DOMAIN_GUID_PRESENT 0x01000000
typedef struct _DSROLE_UPGRADE_STATUS_INFO {
	ULONG OperationState;
	DSROLE_SERVER_STATE PreviousServerState;
} DSROLE_UPGRADE_STATUS_INFO,*PDSROLE_UPGRADE_STATUS_INFO;
#endif /* (_WIN32_WINNT >= 0x0500) */

#ifdef __cplusplus
}
#endif
#endif
