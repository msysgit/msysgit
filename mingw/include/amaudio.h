#ifndef _AMAUDIO_H
#define _AMAUDIO_H
#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#include <dsound.h>

#ifdef __cplusplus
extern "C" {
#endif

#define INTERFACE IAMDirectSound
DECLARE_INTERFACE_(IAMDirectSound, IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,LPVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(GetDirectSoundInterface)(THIS_ LPDIRECTSOUND*) PURE;
	STDMETHOD(GetPrimaryBufferInterface)(THIS_ LPDIRECTSOUNDBUFFER*) PURE;
	STDMETHOD(GetSecondaryBufferInterface)(THIS_ LPDIRECTSOUNDBUFFER*) PURE;
	STDMETHOD(GetFocusWindow)(THIS_ HWND*,BOOL*) PURE ;
	STDMETHOD(ReleaseDirectSoundInterface)(THIS_ LPDIRECTSOUND) PURE;
	STDMETHOD(ReleasePrimaryBufferInterface)(THIS_ LPDIRECTSOUNDBUFFER) PURE;
	STDMETHOD(ReleaseSecondaryBufferInterface)(THIS_ LPDIRECTSOUNDBUFFER) PURE;
	STDMETHOD(SetFocusWindow)(THIS_ HWND,BOOL) PURE ;
};
#undef INTERFACE

#ifdef __cplusplus
}
#endif
#endif
