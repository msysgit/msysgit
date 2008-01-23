#ifndef _ACLAPI_H
#define _ACLAPI_H

#include <windows.h>
#include <accctrl.h>

#ifdef __cplusplus
extern "C" {
#endif
VOID WINAPI BuildExplicitAccessWithNameA(PEXPLICIT_ACCESS_A,LPSTR,DWORD,ACCESS_MODE,DWORD);
VOID WINAPI BuildExplicitAccessWithNameW(PEXPLICIT_ACCESS_W,LPWSTR,DWORD,ACCESS_MODE,DWORD);
DWORD WINAPI BuildSecurityDescriptorA(PTRUSTEE_A,PTRUSTEE_A ,ULONG,PEXPLICIT_ACCESS_A,
  ULONG,PEXPLICIT_ACCESS_A,PSECURITY_DESCRIPTOR,PULONG,PSECURITY_DESCRIPTOR*);
DWORD WINAPI BuildSecurityDescriptorW(PTRUSTEE_W,PTRUSTEE_W ,ULONG,PEXPLICIT_ACCESS_W,
  ULONG,PEXPLICIT_ACCESS_W,PSECURITY_DESCRIPTOR,PULONG,PSECURITY_DESCRIPTOR*);
VOID WINAPI BuildTrusteeWithNameA(PTRUSTEE_A,LPSTR);
VOID WINAPI BuildTrusteeWithNameW(PTRUSTEE_W,LPWSTR);
VOID WINAPI BuildTrusteeWithObjectsAndNameA(PTRUSTEE_A,POBJECTS_AND_NAME_A,SE_OBJECT_TYPE,
  LPSTR,LPSTR,LPSTR);
VOID WINAPI BuildTrusteeWithObjectsAndNameW(PTRUSTEE_W,POBJECTS_AND_NAME_W,SE_OBJECT_TYPE,
  LPWSTR,LPWSTR,LPWSTR);
VOID WINAPI BuildTrusteeWithObjectsAndSidA(PTRUSTEE_A,POBJECTS_AND_SID,GUID*,GUID*,PSID);
VOID WINAPI BuildTrusteeWithObjectsAndSidW(PTRUSTEE_W,POBJECTS_AND_SID,GUID*,GUID*,PSID);
VOID WINAPI BuildTrusteeWithSidA(PTRUSTEE_A,PSID);
VOID WINAPI BuildTrusteeWithSidW(PTRUSTEE_W,PSID);
DWORD WINAPI GetAuditedPermissionsFromAclA(PACL,PTRUSTEE_A,PACCESS_MASK,PACCESS_MASK);
DWORD WINAPI GetAuditedPermissionsFromAclW(PACL,PTRUSTEE_W,PACCESS_MASK,PACCESS_MASK);
DWORD WINAPI GetEffectiveRightsFromAclA(PACL,PTRUSTEE_A,PACCESS_MASK);
DWORD WINAPI GetEffectiveRightsFromAclW(PACL,PTRUSTEE_W,PACCESS_MASK);
DWORD WINAPI GetExplicitEntriesFromAclA(PACL,PULONG,PEXPLICIT_ACCESS_A*);
DWORD WINAPI GetExplicitEntriesFromAclW(PACL,PULONG,PEXPLICIT_ACCESS_W*);
DWORD WINAPI GetNamedSecurityInfoA(LPSTR,SE_OBJECT_TYPE,SECURITY_INFORMATION,
  PSID*,PSID*,PACL*,PACL*,PSECURITY_DESCRIPTOR*);
DWORD WINAPI GetNamedSecurityInfoW(LPWSTR,SE_OBJECT_TYPE,SECURITY_INFORMATION,
  PSID*,PSID*,PACL*,PACL*,PSECURITY_DESCRIPTOR*);
DWORD WINAPI GetSecurityInfo(HANDLE,SE_OBJECT_TYPE,SECURITY_INFORMATION,
  PSID*,PSID*,PACL*,PACL*,PSECURITY_DESCRIPTOR*);
TRUSTEE_FORM WINAPI GetTrusteeFormA(PTRUSTEE_A);
TRUSTEE_FORM WINAPI GetTrusteeFormW(PTRUSTEE_W);
LPSTR WINAPI GetTrusteeNameA(PTRUSTEE_A);
LPWSTR WINAPI GetTrusteeNameW(PTRUSTEE_W);
TRUSTEE_TYPE WINAPI GetTrusteeTypeA(PTRUSTEE_A);
TRUSTEE_TYPE WINAPI GetTrusteeTypeW(PTRUSTEE_W);
DWORD WINAPI LookupSecurityDescriptorPartsA(PTRUSTEE_A*,PTRUSTEE_A*,PULONG,PEXPLICIT_ACCESS_A*,
  PULONG,PEXPLICIT_ACCESS_A*,PSECURITY_DESCRIPTOR);
DWORD WINAPI LookupSecurityDescriptorPartsW(PTRUSTEE_W*,PTRUSTEE_W*,PULONG,PEXPLICIT_ACCESS_W*,
  PULONG,PEXPLICIT_ACCESS_W*,PSECURITY_DESCRIPTOR);
DWORD WINAPI SetEntriesInAclA(ULONG,PEXPLICIT_ACCESS_A,PACL,PACL*);
DWORD WINAPI SetEntriesInAclW(ULONG,PEXPLICIT_ACCESS_W,PACL,PACL*);
DWORD WINAPI SetNamedSecurityInfoA(LPSTR,SE_OBJECT_TYPE,SECURITY_INFORMATION,PSID,PSID,PACL,PACL);
DWORD WINAPI SetNamedSecurityInfoW(LPWSTR,SE_OBJECT_TYPE,SECURITY_INFORMATION,PSID,PSID,PACL,PACL);
DWORD WINAPI SetSecurityInfo(HANDLE,SE_OBJECT_TYPE,SECURITY_INFORMATION,PSID,PSID,PACL,PACL);

/* These are deprecated by MS and not documented in Aug 2001 PSDK 
BuildImpersonateExplicitAccessWithName[AW]
BuildImpersonateTrustee[AW]
GetMultipleTrustee[AW]
GetMultipleTrusteeOperation[AW]
*/

#ifdef UNICODE
#define BuildExplicitAccessWithName  BuildExplicitAccessWithNameW
#define BuildSecurityDescriptor  BuildSecurityDescriptorW
#define BuildTrusteeWithName  BuildTrusteeWithNameW
#define BuildTrusteeWithObjectsAndName  BuildTrusteeWithObjectsAndNameW
#define BuildTrusteeWithObjectsAndSid  BuildTrusteeWithObjectsAndSidW
#define BuildTrusteeWithSid  BuildTrusteeWithSidW
#define GetAuditedPermissionsFromAcl  GetAuditedPermissionsFromAclW
#define GetEffectiveRightsFromAcl  GetEffectiveRightsFromAclW
#define GetExplicitEntriesFromAcl  GetExplicitEntriesFromAclW
#define GetNamedSecurityInfo  GetNamedSecurityInfoW
#define GetTrusteeForm  GetTrusteeFormW
#define GetTrusteeName  GetTrusteeNameW
#define GetTrusteeType  GetTrusteeTypeW
#define LookupSecurityDescriptorParts  LookupSecurityDescriptorPartsW
#define SetEntriesInAcl  SetEntriesInAclW
#define SetNamedSecurityInfo  SetNamedSecurityInfoW
#else
#define BuildExplicitAccessWithName  BuildExplicitAccessWithNameA
#define BuildSecurityDescriptor  BuildSecurityDescriptorA
#define BuildTrusteeWithName  BuildTrusteeWithNameA
#define BuildTrusteeWithObjectsAndName  BuildTrusteeWithObjectsAndNameA
#define BuildTrusteeWithObjectsAndSid  BuildTrusteeWithObjectsAndSidA
#define BuildTrusteeWithSid  BuildTrusteeWithSidA
#define GetAuditedPermissionsFromAcl  GetAuditedPermissionsFromAclA
#define GetEffectiveRightsFromAcl  GetEffectiveRightsFromAclA
#define GetExplicitEntriesFromAcl  GetExplicitEntriesFromAclA
#define GetNamedSecurityInfo  GetNamedSecurityInfoA
#define GetTrusteeForm  GetTrusteeFormA
#define GetTrusteeName  GetTrusteeNameA
#define GetTrusteeType  GetTrusteeTypeA
#define LookupSecurityDescriptorParts  LookupSecurityDescriptorPartsA
#define SetEntriesInAcl  SetEntriesInAclA
#define SetNamedSecurityInfo  SetNamedSecurityInfoA
#endif  /* UNICODE */

#ifdef __cplusplus
}
#endif
#endif

