#ifndef _AMVIDEO_H
#define _AMVIDEO_H
#if __GNUC__ >=3
#pragma GCC system_header
#endif

#include <ddraw.h>
#include <strmif.h>

#ifdef __cplusplus
extern "C" {
#endif

#define AMDDS_NONE 0x0000
#define AMDDS_DCIPS 0x0001
#define AMDDS_PS 0x0002
#define AMDDS_RGBOVR 0x0004
#define AMDDS_YUVOVR 0x0008
#define AMDDS_RGBOFF 0x0010
#define AMDDS_YUVOFF 0x0020
#define AMDDS_RGBFLP 0x0040
#define AMDDS_YUVFLP 0x0080
#define AMDDS_ ALL 0x00FF
#define AMDDS_DEFAULT 0x00FF
#define AMDDS_YUV (AMDDS_YUVOFF|AMDDS_YUVOVR|AMDDS_YUVFLP)
#define AMDDS_RGB (AMDDS_RGBOFF|AMDDS_RGBOVR|AMDDS_RGBFLP)
#define AMDDS_PRIMARY (AMDDS_DCIPS|AMDDS_PS)
#define BIT_MASKS_MATCH(pbmi1,pbmi2) ((pbmi1)->dwBitMasks[0] == (pbmi2)->dwBitMasks[0] && (pbmi1)->dwBitMasks[1] == (pbmi2)->dwBitMasks[1] && (pbmi1)->dwBitMasks[2] == (pbmi2)->dwBitMasks[2])
#define PALETTISED(pbmi) ((pbmi)->bmiHeader.biBitCount <= 8)
#define PALETTE_ENTRIES(pbmi) (1 << (pbmi)->bmiHeader.biBitCount)
#define RESET_MASKS(pbmi) (ZeroMemory((PVOID)(pbmi)->dwBitFields,3*sizeof(DWORD)))
#define RESET_PALETTE(pbmi) (ZeroMemory((PVOID)(pbmi)->bmiColors,256*sizeof(RGBQUAD)));
#define SIZE_EGA_PALETTE (16*sizeof(RGBQUAD))
#define SIZE_MASKS (3*sizeof(DWORD))
#define SIZE_PALETTE (256*sizeof(RGBQUAD))
typedef enum {
	AM_PROPERTY_FRAMESTEP_STEP = 1,
	AM_PROPERTY_FRAMESTEP_CANCEL = 2,
	AM_PROPERTY_FRAMESTEP_CANSTEP = 3,
	AM_PROPERTY_FRAMESTEP_CANSTEPMULTIPLE = 4
} AM_PROPERTY_FRAMESTEP;
typedef struct tag_TRUECOLORINFO {
	DWORD dwBitMasks[3];
	RGBQUAD bmiColors[256];
} TRUECOLORINFO;
typedef struct tagVIDEOINFOHEADER {
	RECT rcSource;
	RECT rcTarget;
	DWORD dwBitRate;
	DWORD dwBitErrorRate;
	REFERENCE_TIME AvgTimePerFrame;
	BITMAPINFOHEADER bmiHeader;
} VIDEOINFOHEADER;
typedef struct tagVIDEOINFO {
	RECT rcSource,
	RECT rcTarget,
	DWORD dwBitRate,
	DWORD dwBitErrorRate,
	REFERENCE_TIME AvgTimePerFrame;
	BITMAPINFOHEADER bmiHeader;
	union {
		RGBQUAD bmiColors[256];
		DWORD dwBitMasks[3];
		TRUECOLORINFO TrueColorInfo;
	};
} VIDEOINFO;
typedef struct tagMPEG1VIDEOINFO {
	VIDEOINFOHEADER hdr;
	DWORD dwStartTimeCode;
	DWORD cbSequenceHeader;
	BYTE bSequenceHeader[1];
} MPEG1VIDEOINFO;
typedef struct tagAnalogVideoInfo {
	RECT rcSource;           
	RECT rcTarget;           
	DWORD dwActiveWidth;      
	DWORD dwActiveHeight;     
	REFERENCE_TIME AvgTimePerFrame;    
} ANALOGVIDEOINFO;
typedef struct _AM_FRAMESTEP_STEP {
	DWORD dwFramesToStep;
} AM_FRAMESTEP_STEP;
#define INTERFACE IDirectDrawVideo
DECLARE_INTERFACE_(IDirectDrawVideo, IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,LPVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(CanUseOverlayStretch)(THIS_ long*) PURE;
	STDMETHOD(CanUseScanLine)(THIS_ long*) PURE;
	STDMETHOD(GetCaps)(THIS_ DDCAPS*) PURE;
	STDMETHOD(GetDirectDraw)(THIS_ LPDIRECTDRAW*) PURE;
	STDMETHOD(GetEmulatedCaps)(THIS_ DDCAPS*) PURE;
	STDMETHOD(GetFourCCCodes)(THIS_ DWORD*,DWORD*) PURE;
	STDMETHOD(GetSurfaceDesc)(THIS_ DDSURFACEDESC*) PURE;
	STDMETHOD(GetSurfaceType)(THIS_ DWORD*) PURE;
	STDMETHOD(GetSwitches)(THIS_ DWORD*) PURE;
	STDMETHOD(SetDefault)(THIS) PURE;
	STDMETHOD(SetDirectDraw)(THIS_ LPDIRECTDRAW) PURE;
	STDMETHOD(SetSwitches)(THIS_ DWORD) PURE;
	STDMETHOD(UseOverlayStretch)(THIS_ long) PURE;
	STDMETHOD(UseScanLine)(THIS_ long) PURE;
	STDMETHOD(UseWhenFullScreen)(THIS_ long) PURE;
	STDMETHOD(WillUseFullScreen)(THIS_ long*) PURE;
};
#undef INTERFACE
#define INTERFACE IQualProp
DECLARE_INTERFACE_(IQualProp, IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,LPVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(get_AvgFrameRate)(THIS_ int*) PURE;
	STDMETHOD(get_AvgSyncOffset)(THIS_ int*) PURE;
	STDMETHOD(get_DevSyncOffset)(THIS_ int*) PURE;
	STDMETHOD(get_FramesDrawn)(THIS_ int*) PURE;
	STDMETHOD(get_FramesDroppedInRenderer)(THIS_ int*) PURE;
	STDMETHOD(get_Jitter)(THIS_ int*) PURE;
};
#undef INTERFACE
#define INTERFACE IFullScreenVideo
DECLARE_INTERFACE_(IFullScreenVideo, IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,LPVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(CountModes)(THIS_ long*) PURE;
	STDMETHOD(GetCaption)(THIS_ BSTR*) PURE;
	STDMETHOD(GetClipFactor)(THIS_ long*) PURE;
	STDMETHOD(GetCurrentMode)(THIS_ long*) PURE;
	STDMETHOD(GetMessageDrain)(THIS_ HWND*) PURE;
	STDMETHOD(GetModeInfo)(THIS_ long,long*,long*,long*) PURE;
	STDMETHOD(GetMonitor)(THIS_ long*) PURE;
	STDMETHOD(HideOnDeactivate)(THIS_ long) PURE;
	STDMETHOD(IsHideOnDeactivate)(THIS) PURE;
	STDMETHOD(IsModeAvailable)(THIS_ long) PURE;
	STDMETHOD(IsModeEnabled)(THIS_ long) PURE;
	STDMETHOD(SetCaption)(THIS_ BSTR) PURE;
	STDMETHOD(SetClipFactor)(THIS_ long) PURE;
	STDMETHOD(SetDefault)(THIS) PURE;
	STDMETHOD(SetEnabled)(THIS_ long,long) PURE;
	STDMETHOD(SetMessageDrain)(THIS_ HWND) PURE;
	STDMETHOD(SetMonitor)(THIS_ long) PURE;
};
#undef INTERFACE
#define INTERFACE IFullScreenVideoEx
DECLARE_INTERFACE_(IFullScreenVideoEx, IFullScreenVideo)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID, LPVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(CountModes)(THIS_ long*) PURE;
	STDMETHOD(GetAcceleratorTable)(THIS_ HWND*,HACCEL*) PURE;
	STDMETHOD(GetCaption)(THIS_ BSTR*) PURE;
	STDMETHOD(GetClipFactor)(THIS_ long*) PURE;
	STDMETHOD(GetCurrentMode)(THIS_ long*) PURE;
	STDMETHOD(GetMessageDrain)(THIS_ HWND*) PURE;
	STDMETHOD(GetModeInfo)(THIS_ long,long*,long*,long*) PURE;
	STDMETHOD(GetMonitor)(THIS_ long*) PURE;
	STDMETHOD(HideOnDeactivate)(THIS_ long) PURE;
	STDMETHOD(IsHideOnDeactivate)(THIS) PURE;
	STDMETHOD(IsKeepPixelAspectRatio)(THIS_ long*) PURE;
	STDMETHOD(IsModeAvailable)(THIS_ long) PURE;
	STDMETHOD(IsModeEnabled)(THIS_ long) PURE;
	STDMETHOD(KeepPixelAspectRatio)(THIS_ long) PURE;
	STDMETHOD(SetAcceleratorTable)(THIS_ HWND,HACCEL) PURE;
	STDMETHOD(SetCaption)(THIS_ BSTR) PURE;
	STDMETHOD(SetClipFactor)(THIS_ long) PURE;
	STDMETHOD(SetDefault)(THIS) PURE;
	STDMETHOD(SetEnabled)(THIS_ long,long) PURE;
	STDMETHOD(SetMessageDrain)(THIS_ HWND) PURE;
	STDMETHOD(SetMonitor)(THIS_ long) PURE;
};
#undef INTERFACE

#ifdef __cplusplus
}
#endif
#endif
