/*
 * hidsdi.h
 *
 * This file is part of the w32api package.
 *
 * THIS SOFTWARE IS NOT COPYRIGHTED
 *
 * This source code is offered for use in the public domain. You may
 * use, modify or distribute it freely.
 *
 * This code is distributed in the hope that it will be useful but
 * WITHOUT ANY WARRANTY. ALL WARRANTIES, EXPRESS OR IMPLIED ARE HEREBY
 * DISCLAIMED. This includes but is not limited to warranties of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef _HIDSDI_H
#define _HIDSDI_H

#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <ddk/hidusage.h>
#include <ddk/hidpi.h>

#ifndef WINHIDSDI
#define WINHIDSDI DECLSPEC_IMPORT
#endif

#include <pshpack4.h>

typedef struct _HIDD_CONFIGURATION {
	PVOID cookie;
 	ULONG size;
	ULONG RingBufferSize;
} HIDD_CONFIGURATION, *PHIDD_CONFIGURATION;

typedef struct _HIDD_ATTRIBUTES {
	ULONG Size; 
	USHORT VendorID;
	USHORT ProductID;
	USHORT VersionNumber;
} HIDD_ATTRIBUTES, *PHIDD_ATTRIBUTES;

WINHIDSDI BOOL WINAPI HidD_GetAttributes (HANDLE, PHIDD_ATTRIBUTES);
WINHIDSDI VOID WINAPI HidD_GetHidGuid (LPGUID);
WINHIDSDI BOOL WINAPI HidD_GetPreparsedData(HANDLE, PHIDP_PREPARSED_DATA  *);
WINHIDSDI BOOL WINAPI HidD_FreePreparsedData(PHIDP_PREPARSED_DATA);
WINHIDSDI BOOL WINAPI HidD_FlushQueue (HANDLE);
WINHIDSDI BOOL WINAPI HidD_GetConfiguration (HANDLE, PHIDD_CONFIGURATION, ULONG);                
WINHIDSDI BOOL WINAPI HidD_SetConfiguration (HANDLE, PHIDD_CONFIGURATION, ULONG);
WINHIDSDI BOOL WINAPI HidD_GetFeature (HANDLE, PVOID, ULONG);
WINHIDSDI BOOL WINAPI HidD_SetFeature (HANDLE, PVOID, ULONG);
WINHIDSDI BOOL WINAPI HidD_GetNumInputBuffers (HANDLE, PULONG);
WINHIDSDI BOOL WINAPI HidD_SetNumInputBuffers (HANDLE HidDeviceObject, ULONG);
WINHIDSDI BOOL WINAPI HidD_GetPhysicalDescriptor (HANDLE, PVOID, ULONG);
WINHIDSDI BOOL WINAPI HidD_GetManufacturerString (HANDLE, PVOID, ULONG);
WINHIDSDI BOOL WINAPI HidD_GetProductString ( HANDLE, PVOID, ULONG);
WINHIDSDI BOOL WINAPI HidD_GetIndexedString ( HANDLE, ULONG, PVOID, ULONG);
WINHIDSDI BOOL WINAPI HidD_GetSerialNumberString (HANDLE, PVOID, ULONG);

#include <poppack.h>

#ifdef __cplusplus
}
#endif

#endif /* _HIDSDI_H */
