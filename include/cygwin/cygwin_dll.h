/* cygwin_dll.h

   Copyright 1998, 1999, 2000, 2001 Red Hat, Inc.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#ifndef __CYGWIN_CYGWIN_DLL_H__
#define __CYGWIN_CYGWIN_DLL_H__

#include <windows.h>

#ifdef __cplusplus
#define CDECL_BEGIN extern "C" {
#define CDECL_END }
#else
#define CDECL_BEGIN
#define CDECL_END
#endif

#define DECLARE_CYGWIN_DLL(Entry)					      \
									      \
CDECL_BEGIN								      \
  int WINAPI Entry (HINSTANCE h, DWORD reason, void *ptr);	              \
  typedef int (*mainfunc) (int, char **, char **);			      \
  extern int msys_attach_dll (HMODULE, mainfunc);			      \
  extern void msys_detach_dll (DWORD);				      \
CDECL_END								      \
									      \
static HINSTANCE storedHandle;						      \
static DWORD storedReason;						      \
static void* storedPtr;							      \
									      \
static int __dllMain (int a, char **b, char **c)			      \
{									      \
  return Entry (storedHandle, storedReason, storedPtr);		              \
}									      \
									      \
static DWORD dll_index;							      \
									      \
int WINAPI _msys_dll_entry (HINSTANCE h, DWORD reason, void *ptr)	      \
{									      \
  int ret;								      \
  ret = 1;								      \
									      \
  switch (reason)							      \
  {									      \
    case DLL_PROCESS_ATTACH:						      \
    {									      \
      storedHandle = h;							      \
      storedReason = reason;						      \
      storedPtr = ptr;							      \
      dll_index = msys_attach_dll (h, &__dllMain);			      \
      if (dll_index == (DWORD) -1)					      \
	ret = 0;							      \
    }									      \
    break;								      \
									      \
    case DLL_PROCESS_DETACH:						      \
    {									      \
      ret = Entry (h, reason, ptr);					      \
      if (ret)								      \
      {									      \
	msys_detach_dll (dll_index);					      \
	dll_index = (DWORD) -1;						      \
      }									      \
    }									      \
    break;								      \
									      \
    case DLL_THREAD_ATTACH:						      \
    {									      \
      ret = Entry (h, reason, ptr);					      \
    }									      \
    break;								      \
									      \
    case DLL_THREAD_DETACH:						      \
    {									      \
      ret = Entry (h, reason, ptr);					      \
    }									      \
    break;								      \
  }									      \
  return ret;								      \
}									      \
									      \
/* OBSOLETE: This is only provided for source level compatibility. */         \
int WINAPI _msys_nonmsys_dll_entry (HINSTANCE h, DWORD reason, void *ptr) \
{									      \
  return _msys_dll_entry (h, reason, ptr);				      \
}									      \

#endif /* __CYGWIN_CYGWIN_DLL_H__ */
