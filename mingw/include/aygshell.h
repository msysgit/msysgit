#ifndef _AYGSHELL_H
#define _AYGSHELL_H
#if __GNUC__ >=3
#pragma GCC system_header
#endif

#if _WIN32_WCE >= 400

#include <windef.h>             /* shellapi needs this */
#include <basetyps.h>
#include <shellapi.h>           /* for WINSHELLAPI */

typedef struct tagSHMENUBARINFO {
  DWORD cbSize;
  HWND hwndParent;
  DWORD dwFlags;
  UINT nToolBarId;
  HINSTANCE hInstRes;
  int nBmpId;
  int cBmpImages;
  HWND hwndMB;
  COLORREF clrBk;
} SHMENUBARINFO, *PSHMENUBARINFO;

typedef struct tagSHACTIVATEINFO {
  DWORD cbSize;
  HWND hwndLastFocus;
  UINT fSipUp :1;
  UINT fSipOnDeactivation :1;
  UINT fActive :1;
  UINT fReserved :29;
} SHACTIVATEINFO, *PSHACTIVATEINFO;

WINSHELLAPI BOOL WINAPI SHCreateMenuBar(SHMENUBARINFO*);
WINSHELLAPI HWND WINAPI SHFindMenuBar(HWND);
WINSHELLAPI HRESULT WINAPI SHCreateNewItem(HWND,REFCLSID);
WINSHELLAPI BOOL WINAPI SHFullScreen(HWND,DWORD);
WINSHELLAPI BOOL WINAPI SHSipInfo(UINT,UINT,PVOID,UINT);
/* next exported by ordinal only: @84 */
WINSHELLAPI BOOL WINAPI SHHandleWMActivate(HWND,WPARAM,LPARAM,SHACTIVATEINFO*,DWORD);
/* next exported by ordinal only: @83 */
WINSHELLAPI BOOL WINAPI SHHandleWMSettingChange(HWND,WPARAM,LPARAM,SHACTIVATEINFO*);

/* The following are not in device ROMs. */
extern BOOL SHInvokeContextMenuCommand(HWND,UINT,HANDLE);

#endif /* _WIN32_WCE >= 400 */

#endif
