#ifndef _ACLUI_H
#define _ACLUI_H
#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#ifndef _OBJC_NO_COM
#include <objbase.h>
#include <commctrl.h>
#include <accctrl.h>
#endif

#if !defined(_ACLUI_)
#define ACLUIAPI	DECLSPEC_IMPORT WINAPI
#else
#define ACLUIAPI	WINAPI
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _SI_OBJECT_INFO
{
	DWORD dwFlags;
	HINSTANCE hInstance;
	LPWSTR pszServerName;
	LPWSTR pszObjectName;
	LPWSTR pszPageTitle;
	GUID guidObjectType;
} SI_OBJECT_INFO, *PSI_OBJECT_INFO;

/* values for SI_OBJECT_INFO.dwFlags */
#define SI_EDIT_PERMS				0x00000000L
#define SI_EDIT_OWNER				0x00000001L
#define SI_EDIT_AUDITS				0x00000002L
#define SI_CONTAINER				0x00000004L
#define SI_READONLY					0x00000008L
#define SI_ADVANCED					0x00000010L
#define SI_RESET					0x00000020L
#define SI_OWNER_READONLY			0x00000040L
#define SI_EDIT_PROPERTIES			0x00000080L
#define SI_OWNER_RECURSE			0x00000100L
#define SI_NO_ACL_PROTECT			0x00000200L
#define SI_NO_TREE_APPLY			0x00000400L
#define SI_PAGE_TITLE				0x00000800L
#define SI_SERVER_IS_DC				0x00001000L
#define SI_RESET_DACL_TREE			0x00004000L
#define SI_RESET_SACL_TREE			0x00008000L
#define SI_OBJECT_GUID				0x00010000L
#define SI_EDIT_EFFECTIVE			0x00020000L
#define SI_RESET_DACL				0x00040000L
#define SI_RESET_SACL				0x00080000L
#define SI_RESET_OWNER				0x00100000L
#define SI_NO_ADDITIONAL_PERMISSION	0x00200000L
#define SI_MAY_WRITE				0x10000000L

#define SI_EDIT_ALL     (SI_EDIT_PERMS | SI_EDIT_OWNER | SI_EDIT_AUDITS)


typedef struct _SI_ACCESS
{
	const GUID* pguid;
	ACCESS_MASK mask;
	LPCWSTR pszName;
	DWORD dwFlags;
} SI_ACCESS, *PSI_ACCESS;

/* values for SI_ACCESS.dwFlags */
#define SI_ACCESS_SPECIFIC			0x00010000L
#define SI_ACCESS_GENERAL			0x00020000L
#define SI_ACCESS_CONTAINER			0x00040000L
#define SI_ACCESS_PROPERTY			0x00080000L


typedef struct _SI_INHERIT_TYPE
{
	const GUID* pguid;
	ULONG dwFlags;
	LPCWSTR pszName;
} SI_INHERIT_TYPE, *PSI_INHERIT_TYPE;

/* values for SI_INHERIT_TYPE.dwFlags
   INHERIT_ONLY_ACE, CONTAINER_INHERIT_ACE, OBJECT_INHERIT_ACE
   defined elsewhere */


typedef enum _SI_PAGE_TYPE
{
	SI_PAGE_PERM = 0, 
	SI_PAGE_ADVPERM, 
	SI_PAGE_AUDIT, 
	SI_PAGE_OWNER
} SI_PAGE_TYPE;


#define PSPCB_SI_INITDIALOG	(WM_USER + 1)

#ifndef __ISecurityInformation_INTERFACE_DEFINED__
#define __ISecurityInformation_INTERFACE_DEFINED__
#define INTERFACE ISecurityInformation
DECLARE_INTERFACE_(ISecurityInformation, IUnknown)
{
		STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
		STDMETHOD_(ULONG,AddRef)(THIS) PURE;
		STDMETHOD_(ULONG,Release)(THIS) PURE;
		
		STDMETHOD(GetObjectInformation)(THIS_ PSI_OBJECT_INFO) PURE;
		STDMETHOD(GetSecurity)(THIS_ SECURITY_INFORMATION,PSECURITY_DESCRIPTOR*,BOOL) PURE;
		STDMETHOD(SetSecurity)(THIS_ SECURITY_INFORMATION,PSECURITY_DESCRIPTOR) PURE;
		STDMETHOD(GetAccessRights)(THIS_ const GUID*,DWORD,PSI_ACCESS*,ULONG*,ULONG*) PURE;
		STDMETHOD(MapGeneric)(THIS_ const GUID*,UCHAR*,ACCESS_MASK*) PURE;
		STDMETHOD(GetInheritTypes)(THIS_ PSI_INHERIT_TYPE*,ULONG*) PURE;
		STDMETHOD(PropertySheetPageCallback)(THIS_ HWND,UINT,SI_PAGE_TYPE) PURE;
};
#undef INTERFACE
typedef ISecurityInformation *LPSECURITYINFO;
#endif

/*
 * TODO: ISecurityInformation2, IEffectivePermission, ISecurityObjectTypeInfo
 */

extern DECLSPEC_IMPORT const IID IID_ISecurityInformation;


HPROPSHEETPAGE ACLUIAPI CreateSecurityPage(LPSECURITYINFO psi);
BOOL ACLUIAPI EditSecurity(HWND hwndOwner, LPSECURITYINFO psi);

#ifdef __cplusplus
}
#endif

#endif
