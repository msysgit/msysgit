#ifndef _OBJSAFE_H
#define _OBJSAFE_H
#if __GNUC__ >=3
#pragma GCC system_header
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define INTERFACESAFE_FOR_UNTRUSTED_CALLER 0x00000001
#define INTERFACESAFE_FOR_UNTRUSTED_DATA 0x00000002

EXTERN_C const IID IID_IObjectSafety;
#define INTERFACE IObjectSafety
DECLARE_INTERFACE_(IObjectSafety,IUnknown)
{
	STDMETHOD(GetInterfaceSafetyOptions)(THIS_ REFIID,DWORD*,DWORD*) PURE;
	STDMETHOD(SetInterfaceSafetyOptions)(THIS_ REFIID,DWORD,DWORD) PURE;
};
#undef INTERFACE

#ifdef __cplusplus
}
#endif
#endif
