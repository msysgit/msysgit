/*

	d3d9.h - Header file for the Direct3D9 API

	Written by Filip Navara <xnavara@volny.cz>

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

*/

#ifndef _D3D9_H
#define _D3D9_H
#if __GNUC__ >=3
#pragma GCC system_header
#endif

#ifndef DIRECT3D_VERSION
#define DIRECT3D_VERSION  0x0900
#endif

#if (DIRECT3D_VERSION >= 0x0900)

#include <objbase.h>
#include "d3d9types.h"
#include "d3d9caps.h"

#define D3D_SDK_VERSION	31
#define D3DCREATE_FPU_PRESERVE	0x02
#define D3DCREATE_MULTITHREADED	0x04
#define D3DCREATE_PUREDEVICE	0x10
#define D3DCREATE_SOFTWARE_VERTEXPROCESSING	0x20
#define D3DCREATE_HARDWARE_VERTEXPROCESSING	0x40
#define D3DCREATE_MIXED_VERTEXPROCESSING	0x80
#define D3DSPD_IUNKNOWN	1
#define D3DSGR_NO_CALIBRATION	0
#define D3DSGR_CALIBRATE	1
#define MAKE_D3DHRESULT(code)	MAKE_HRESULT(1,0x876,code)
#define MAKE_D3DSTATUS(code)	MAKE_HRESULT(0,0x876,code)
#define D3D_OK	0
#define D3DOK_NOAUTOGEN	MAKE_D3DSTATUS(2159)
#define D3DERR_WRONGTEXTUREFORMAT	MAKE_D3DHRESULT(2072)
#define D3DERR_UNSUPPORTEDCOLOROPERATION	MAKE_D3DHRESULT(2073)
#define D3DERR_UNSUPPORTEDCOLORARG	MAKE_D3DHRESULT(2074)
#define D3DERR_UNSUPPORTEDALPHAOPERATION	MAKE_D3DHRESULT(2075)
#define D3DERR_UNSUPPORTEDALPHAARG	MAKE_D3DHRESULT(2076)
#define D3DERR_TOOMANYOPERATIONS	MAKE_D3DHRESULT(2077)
#define D3DERR_CONFLICTINGTEXTUREFILTER	MAKE_D3DHRESULT(2078)
#define D3DERR_UNSUPPORTEDFACTORVALUE	MAKE_D3DHRESULT(2079)
#define D3DERR_CONFLICTINGRENDERSTATE	MAKE_D3DHRESULT(2081)
#define D3DERR_UNSUPPORTEDTEXTUREFILTER	MAKE_D3DHRESULT(2082)
#define D3DERR_CONFLICTINGTEXTUREPALETTE	MAKE_D3DHRESULT(2086)
#define D3DERR_DRIVERINTERNALERROR	MAKE_D3DHRESULT(2087)
#define D3DERR_NOTFOUND	MAKE_D3DHRESULT(2150)
#define D3DERR_MOREDATA	MAKE_D3DHRESULT(2151)
#define D3DERR_DEVICELOST	MAKE_D3DHRESULT(2152)
#define D3DERR_DEVICENOTRESET	MAKE_D3DHRESULT(2153)
#define D3DERR_NOTAVAILABLE	MAKE_D3DHRESULT(2154)
#define D3DERR_OUTOFVIDEOMEMORY	MAKE_D3DHRESULT(380)
#define D3DERR_INVALIDDEVICE	MAKE_D3DHRESULT(2155)
#define D3DERR_INVALIDCALL	MAKE_D3DHRESULT(2156)
#define D3DERR_DRIVERINVALIDCALL	MAKE_D3DHRESULT(2157)
#define D3DERR_WASSTILLDRAWING	MAKE_D3DHRESULT(540)
#define D3DADAPTER_DEFAULT	0
#define D3DCURSOR_IMMEDIATE_UPDATE	1
#define D3DENUM_HOST_ADAPTER	1
#define D3DPRESENTFLAG_LOCKABLE_BACKBUFFER	1
#define D3DPV_DONOTCOPYDATA	1
#define D3DENUM_NO_WHQL_LEVEL	2
#define D3DPRESENT_BACK_BUFFERS_MAX	3
#define VALID_D3DENUM_FLAGS	3
#define D3DMAXNUMPRIMITIVES	0xFFFF
#define D3DMAXNUMVERTICES	0xFFFF
#define D3DCURRENT_DISPLAY_MODE	0xEFFFFF

#ifdef __cplusplus
extern "C" {
#endif
extern const GUID IID_IDirect3D9;
extern const GUID IID_IDirect3DDevice9;
extern const GUID IID_IDirect3DVolume9;
extern const GUID IID_IDirect3DSwapChain9;
extern const GUID IID_IDirect3DResource9;
extern const GUID IID_IDirect3DSurface9;
extern const GUID IID_IDirect3DVertexBuffer9;
extern const GUID IID_IDirect3DIndexBuffer9;
extern const GUID IID_IDirect3DBaseTexture9;
extern const GUID IID_IDirect3DCubeTexture9;
extern const GUID IID_IDirect3DTexture9;
extern const GUID IID_IDirect3DVolumeTexture9;
extern const GUID IID_IDirect3DVertexDeclaration9;
extern const GUID IID_IDirect3DVertexShader9;
extern const GUID IID_IDirect3DPixelShader9;
extern const GUID IID_IDirect3DStateBlock9;
extern const GUID IID_IDirect3DQuery9;
#ifdef __cplusplus
};
#endif

typedef _COM_interface IDirect3D9 IDirect3D9;
typedef _COM_interface IDirect3DDevice9 IDirect3DDevice9;
typedef _COM_interface IDirect3DVolume9 IDirect3DVolume9;
typedef _COM_interface IDirect3DSwapChain9 IDirect3DSwapChain9;
typedef _COM_interface IDirect3DResource9 IDirect3DResource9;
typedef _COM_interface IDirect3DSurface9 IDirect3DSurface9;
typedef _COM_interface IDirect3DVertexBuffer9 IDirect3DVertexBuffer9;
typedef _COM_interface IDirect3DIndexBuffer9 IDirect3DIndexBuffer9;
typedef _COM_interface IDirect3DBaseTexture9 IDirect3DBaseTexture9;
typedef _COM_interface IDirect3DCubeTexture9 IDirect3DCubeTexture9;
typedef _COM_interface IDirect3DTexture9 IDirect3DTexture9;
typedef _COM_interface IDirect3DVolumeTexture9 IDirect3DVolumeTexture9;
typedef _COM_interface IDirect3DVertexDeclaration9 IDirect3DVertexDeclaration9;
typedef _COM_interface IDirect3DVertexShader9 IDirect3DVertexShader9;
typedef _COM_interface IDirect3DPixelShader9 IDirect3DPixelShader9;
typedef _COM_interface IDirect3DStateBlock9 IDirect3DStateBlock9;
typedef _COM_interface IDirect3DQuery9 IDirect3DQuery9;

#undef INTERFACE
#define INTERFACE IDirect3D9
DECLARE_INTERFACE_(IDirect3D9,IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(RegisterSoftwareDevice)(THIS_ void* pInitializeFunction) PURE;
	STDMETHOD_(UINT,GetAdapterCount)(THIS) PURE;
	STDMETHOD(GetAdapterIdentifier)(THIS_ UINT,DWORD,D3DADAPTER_IDENTIFIER9*) PURE;
	STDMETHOD_(UINT,GetAdapterModeCount)(THIS_ UINT,D3DFORMAT) PURE;
	STDMETHOD(EnumAdapterModes)(THIS_ UINT,D3DFORMAT,UINT,D3DDISPLAYMODE*) PURE;
	STDMETHOD(GetAdapterDisplayMode)(THIS_ UINT,D3DDISPLAYMODE*) PURE;
	STDMETHOD(CheckDeviceType)(THIS_ UINT,D3DDEVTYPE,D3DFORMAT,D3DFORMAT,BOOL) PURE;
	STDMETHOD(CheckDeviceFormat)(THIS_ UINT,D3DDEVTYPE,D3DFORMAT,DWORD,D3DRESOURCETYPE,D3DFORMAT) PURE;
	STDMETHOD(CheckDeviceMultiSampleType)(THIS_ UINT,D3DDEVTYPE,D3DFORMAT,BOOL,D3DMULTISAMPLE_TYPE,DWORD*) PURE;
	STDMETHOD(CheckDepthStencilMatch)(THIS_ UINT,D3DDEVTYPE,D3DFORMAT,D3DFORMAT,D3DFORMAT) PURE;
	STDMETHOD(CheckDeviceFormatConversion)(THIS_ UINT,D3DDEVTYPE,D3DFORMAT,D3DFORMAT) PURE;
	STDMETHOD(GetDeviceCaps)(THIS_ UINT,D3DDEVTYPE,D3DCAPS9*) PURE;
	STDMETHOD_(HMONITOR,GetAdapterMonitor)(THIS_ UINT) PURE;
	STDMETHOD(CreateDevice)(THIS_ UINT,D3DDEVTYPE,HWND,DWORD,D3DPRESENT_PARAMETERS*,IDirect3DDevice9**) PURE;
};
typedef struct IDirect3D9 *LPDIRECT3D9, *PDIRECT3D9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3D9_QueryInterface(p,a,b)	(p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3D9_AddRef(p)	(p)->lpVtbl->AddRef(p)
#define IDirect3D9_Release(p)	(p)->lpVtbl->Release(p)
#define IDirect3D9_RegisterSoftwareDevice(p,a)	(p)->lpVtbl->RegisterSoftwareDevice(p,a)
#define IDirect3D9_GetAdapterCount(p)	(p)->lpVtbl->GetAdapterCount(p)
#define IDirect3D9_GetAdapterIdentifier(p,a,b,c)	(p)->lpVtbl->GetAdapterIdentifier(p,a,b,c)
#define IDirect3D9_GetAdapterModeCount(p,a,b)	(p)->lpVtbl->GetAdapterModeCount(p,a,b)
#define IDirect3D9_EnumAdapterModes(p,a,b,c,d)	(p)->lpVtbl->EnumAdapterModes(p,a,b,c,d)
#define IDirect3D9_GetAdapterDisplayMode(p,a,b)	(p)->lpVtbl->GetAdapterDisplayMode(p,a,b)
#define IDirect3D9_CheckDeviceType(p,a,b,c,d,e)	(p)->lpVtbl->CheckDeviceType(p,a,b,c,d,e)
#define IDirect3D9_CheckDeviceFormat(p,a,b,c,d,e,f)	(p)->lpVtbl->CheckDeviceFormat(p,a,b,c,d,e,f)
#define IDirect3D9_CheckDeviceMultiSampleType(p,a,b,c,d,e,f)	(p)->lpVtbl->CheckDeviceMultiSampleType(p,a,b,c,d,e,f)
#define IDirect3D9_CheckDepthStencilMatch(p,a,b,c,d,e)	(p)->lpVtbl->CheckDepthStencilMatch(p,a,b,c,d,e)
#define IDirect3D9_CheckDeviceFormatConversion(p,a,b,c,d)	(p)->lpVtbl->CheckDeviceFormatConversion(p,a,b,c,d)
#define IDirect3D9_GetDeviceCaps(p,a,b,c)	(p)->lpVtbl->GetDeviceCaps(p,a,b,c)
#define IDirect3D9_GetAdapterMonitor(p,a)	(p)->lpVtbl->GetAdapterMonitor(p,a)
#define IDirect3D9_CreateDevice(p,a,b,c,d,e,f)	(p)->lpVtbl->CreateDevice(p,a,b,c,d,e,f)
#else
#define IDirect3D9_QueryInterface(p,a,b)	(p)->QueryInterface(a,b)
#define IDirect3D9_AddRef(p)	(p)->AddRef()
#define IDirect3D9_Release(p)	(p)->Release()
#define IDirect3D9_RegisterSoftwareDevice(p,a)	(p)->RegisterSoftwareDevice(a)
#define IDirect3D9_GetAdapterCount(p)	(p)->GetAdapterCount()
#define IDirect3D9_GetAdapterIdentifier(p,a,b,c)	(p)->GetAdapterIdentifier(a,b,c)
#define IDirect3D9_GetAdapterModeCount(p,a,b)	(p)->GetAdapterModeCount(a,b)
#define IDirect3D9_EnumAdapterModes(p,a,b,c,d)	(p)->EnumAdapterModes(a,b,c,d)
#define IDirect3D9_GetAdapterDisplayMode(p,a,b)	(p)->GetAdapterDisplayMode(a,b)
#define IDirect3D9_CheckDeviceType(p,a,b,c,d,e)	(p)->CheckDeviceType(a,b,c,d,e)
#define IDirect3D9_CheckDeviceFormat(p,a,b,c,d,e,f)	(p)->CheckDeviceFormat(a,b,c,d,e,f)
#define IDirect3D9_CheckDeviceMultiSampleType(p,a,b,c,d,e,f)	(p)->CheckDeviceMultiSampleType(a,b,c,d,e,f)
#define IDirect3D9_CheckDepthStencilMatch(p,a,b,c,d,e)	(p)->CheckDepthStencilMatch(a,b,c,d,e)
#define IDirect3D9_CheckDeviceFormatConversion(p,a,b,c,d)	(p)->CheckDeviceFormatConversion(a,b,c,d)
#define IDirect3D9_GetDeviceCaps(p,a,b,c)	(p)->GetDeviceCaps(a,b,c)
#define IDirect3D9_GetAdapterMonitor(p,a)	(p)->GetAdapterMonitor(a)
#define IDirect3D9_CreateDevice(p,a,b,c,d,e,f)	(p)->CreateDevice(a,b,c,d,e,f)
#endif

#undef INTERFACE
#define INTERFACE IDirect3DDevice9
DECLARE_INTERFACE_(IDirect3DDevice9,IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(TestCooperativeLevel)(THIS) PURE;
	STDMETHOD_(UINT,GetAvailableTextureMem)(THIS) PURE;
	STDMETHOD(EvictManagedResources)(THIS) PURE;
	STDMETHOD(GetDirect3D)(THIS_ IDirect3D9**) PURE;
	STDMETHOD(GetDeviceCaps)(THIS_ D3DCAPS9*) PURE;
	STDMETHOD(GetDisplayMode)(THIS_ UINT,D3DDISPLAYMODE*) PURE;
	STDMETHOD(GetCreationParameters)(THIS_ D3DDEVICE_CREATION_PARAMETERS*) PURE;
	STDMETHOD(SetCursorProperties)(THIS_ UINT,UINT,IDirect3DSurface9*) PURE;
	STDMETHOD_(void,SetCursorPosition)(THIS_ int,int,DWORD) PURE;
	STDMETHOD_(BOOL,ShowCursor)(THIS_ BOOL) PURE;
	STDMETHOD(CreateAdditionalSwapChain)(THIS_ D3DPRESENT_PARAMETERS*,IDirect3DSwapChain9**) PURE;
	STDMETHOD(GetSwapChain)(THIS_ UINT,IDirect3DSwapChain9**) PURE;
	STDMETHOD_(UINT,GetNumberOfSwapChains)(THIS) PURE;
	STDMETHOD(Reset)(THIS_ D3DPRESENT_PARAMETERS*) PURE;
	STDMETHOD(Present)(THIS_ CONST RECT*,CONST RECT*,HWND,CONST RGNDATA*) PURE;
	STDMETHOD(GetBackBuffer)(THIS_ UINT,UINT,D3DBACKBUFFER_TYPE,IDirect3DSurface9**) PURE;
	STDMETHOD(GetRasterStatus)(THIS_ UINT,D3DRASTER_STATUS*) PURE;
	STDMETHOD(SetDialogBoxMode)(THIS_ BOOL) PURE;
	STDMETHOD_(void,SetGammaRamp)(THIS_ UINT,DWORD,CONST D3DGAMMARAMP*) PURE;
	STDMETHOD_(void,GetGammaRamp)(THIS_ UINT,D3DGAMMARAMP*) PURE;
	STDMETHOD(CreateTexture)(THIS_ UINT,UINT,UINT,DWORD,D3DFORMAT,D3DPOOL,IDirect3DTexture9**,HANDLE*) PURE;
	STDMETHOD(CreateVolumeTexture)(THIS_ UINT,UINT,UINT,UINT,DWORD,D3DFORMAT,D3DPOOL,IDirect3DVolumeTexture9**,HANDLE*) PURE;
	STDMETHOD(CreateCubeTexture)(THIS_ UINT,UINT,DWORD,D3DFORMAT,D3DPOOL,IDirect3DCubeTexture9**, HANDLE*) PURE;
	STDMETHOD(CreateVertexBuffer)(THIS_ UINT,DWORD,DWORD,D3DPOOL,IDirect3DVertexBuffer9**, HANDLE*) PURE;
	STDMETHOD(CreateIndexBuffer)(THIS_ UINT,DWORD,D3DFORMAT,D3DPOOL,IDirect3DIndexBuffer9**,HANDLE*) PURE;
	STDMETHOD(CreateRenderTarget)(THIS_ UINT,UINT,D3DFORMAT,D3DMULTISAMPLE_TYPE,DWORD,BOOL,IDirect3DSurface9**,HANDLE*) PURE;
	STDMETHOD(CreateDepthStencilSurface)(THIS_ UINT,UINT,D3DFORMAT,D3DMULTISAMPLE_TYPE,DWORD,BOOL,IDirect3DSurface9**,HANDLE*) PURE;
	STDMETHOD(UpdateSurface)(THIS_ IDirect3DSurface9*,CONST RECT*,IDirect3DSurface9*,CONST POINT*) PURE;
	STDMETHOD(UpdateTexture)(THIS_ IDirect3DBaseTexture9*,IDirect3DBaseTexture9*) PURE;
	STDMETHOD(GetRenderTargetData)(THIS_ IDirect3DSurface9*,IDirect3DSurface9*) PURE;
	STDMETHOD(GetFrontBufferData)(THIS_ UINT,IDirect3DSurface9*) PURE;
	STDMETHOD(StretchRect)(THIS_ IDirect3DSurface9*,CONST RECT*,IDirect3DSurface9*,CONST RECT*,D3DTEXTUREFILTERTYPE) PURE;
	STDMETHOD(ColorFill)(THIS_ IDirect3DSurface9*,CONST RECT*,D3DCOLOR) PURE;
	STDMETHOD(CreateOffscreenPlainSurface)(THIS_ UINT,UINT,D3DFORMAT,D3DPOOL,IDirect3DSurface9**,HANDLE*) PURE;
	STDMETHOD(SetRenderTarget)(THIS_ DWORD,IDirect3DSurface9*) PURE;
	STDMETHOD(GetRenderTarget)(THIS_ DWORD,IDirect3DSurface9**) PURE;
	STDMETHOD(SetDepthStencilSurface)(THIS_ IDirect3DSurface9*) PURE;
	STDMETHOD(GetDepthStencilSurface)(THIS_ IDirect3DSurface9**) PURE;
	STDMETHOD(BeginScene)(THIS) PURE;
	STDMETHOD(EndScene)(THIS) PURE;
	STDMETHOD(Clear)(THIS_ DWORD,CONST D3DRECT*,DWORD,D3DCOLOR,float,DWORD) PURE;
	STDMETHOD(SetTransform)(THIS_ D3DTRANSFORMSTATETYPE,CONST D3DMATRIX*) PURE;
	STDMETHOD(GetTransform)(THIS_ D3DTRANSFORMSTATETYPE,D3DMATRIX*) PURE;
	STDMETHOD(MultiplyTransform)(THIS_ D3DTRANSFORMSTATETYPE,CONST D3DMATRIX*) PURE;
	STDMETHOD(SetViewport)(THIS_ CONST D3DVIEWPORT9*) PURE;
	STDMETHOD(GetViewport)(THIS_ D3DVIEWPORT9*) PURE;
	STDMETHOD(SetMaterial)(THIS_ CONST D3DMATERIAL9*) PURE;
	STDMETHOD(GetMaterial)(THIS_ D3DMATERIAL9*) PURE;
	STDMETHOD(SetLight)(THIS_ DWORD,CONST D3DLIGHT9*) PURE;
	STDMETHOD(GetLight)(THIS_ DWORD,D3DLIGHT9*) PURE;
	STDMETHOD(LightEnable)(THIS_ DWORD,BOOL) PURE;
	STDMETHOD(GetLightEnable)(THIS_ DWORD,BOOL*) PURE;
	STDMETHOD(SetClipPlane)(THIS_ DWORD,CONST float*) PURE;
	STDMETHOD(GetClipPlane)(THIS_ DWORD,float*) PURE;
	STDMETHOD(SetRenderState)(THIS_ D3DRENDERSTATETYPE,DWORD) PURE;
	STDMETHOD(GetRenderState)(THIS_ D3DRENDERSTATETYPE,DWORD*) PURE;
	STDMETHOD(CreateStateBlock)(THIS_ D3DSTATEBLOCKTYPE,IDirect3DStateBlock9**) PURE;
	STDMETHOD(BeginStateBlock)(THIS) PURE;
	STDMETHOD(EndStateBlock)(THIS_ IDirect3DStateBlock9**) PURE;
	STDMETHOD(SetClipStatus)(THIS_ CONST D3DCLIPSTATUS9*) PURE;
	STDMETHOD(GetClipStatus)(THIS_ D3DCLIPSTATUS9*) PURE;
	STDMETHOD(GetTexture)(THIS_ DWORD,IDirect3DBaseTexture9**) PURE;
	STDMETHOD(SetTexture)(THIS_ DWORD,IDirect3DBaseTexture9*) PURE;
	STDMETHOD(GetTextureStageState)(THIS_ DWORD,D3DTEXTURESTAGESTATETYPE,DWORD*) PURE;
	STDMETHOD(SetTextureStageState)(THIS_ DWORD,D3DTEXTURESTAGESTATETYPE,DWORD) PURE;
	STDMETHOD(GetSamplerState)(THIS_ DWORD,D3DSAMPLERSTATETYPE,DWORD*) PURE;
	STDMETHOD(SetSamplerState)(THIS_ DWORD,D3DSAMPLERSTATETYPE,DWORD) PURE;
	STDMETHOD(ValidateDevice)(THIS_ DWORD*) PURE;
	STDMETHOD(SetPaletteEntries)(THIS_ UINT,CONST PALETTEENTRY*) PURE;
	STDMETHOD(GetPaletteEntries)(THIS_ UINT,PALETTEENTRY*) PURE;
	STDMETHOD(SetCurrentTexturePalette)(THIS_ UINT) PURE;
	STDMETHOD(GetCurrentTexturePalette)(THIS_ UINT*) PURE;
	STDMETHOD(SetScissorRect)(THIS_ CONST RECT*) PURE;
	STDMETHOD(GetScissorRect)(THIS_ RECT*) PURE;
	STDMETHOD(SetSoftwareVertexProcessing)(THIS_ BOOL) PURE;
	STDMETHOD_(BOOL,GetSoftwareVertexProcessing)(THIS) PURE;
	STDMETHOD(SetNPatchMode)(THIS_ float) PURE;
	STDMETHOD_(float,GetNPatchMode)(THIS) PURE;
	STDMETHOD(DrawPrimitive)(THIS_ D3DPRIMITIVETYPE,UINT,UINT) PURE;
	STDMETHOD(DrawIndexedPrimitive)(THIS_ D3DPRIMITIVETYPE,INT,UINT,UINT,UINT,UINT) PURE;
	STDMETHOD(DrawPrimitiveUP)(THIS_ D3DPRIMITIVETYPE,UINT,CONST void*,UINT) PURE;
	STDMETHOD(DrawIndexedPrimitiveUP)(THIS_ D3DPRIMITIVETYPE,UINT,UINT,UINT,CONST void*,D3DFORMAT,CONST void*,UINT) PURE;
	STDMETHOD(ProcessVertices)(THIS_ UINT,UINT,UINT,IDirect3DVertexBuffer9*,IDirect3DVertexDeclaration9*,DWORD) PURE;
	STDMETHOD(CreateVertexDeclaration)(THIS_ CONST D3DVERTEXELEMENT9*,IDirect3DVertexDeclaration9**) PURE;
	STDMETHOD(SetVertexDeclaration)(THIS_ IDirect3DVertexDeclaration9*) PURE;
	STDMETHOD(GetVertexDeclaration)(THIS_ IDirect3DVertexDeclaration9**) PURE;
	STDMETHOD(SetFVF)(THIS_ DWORD) PURE;
	STDMETHOD(GetFVF)(THIS_ DWORD*) PURE;
	STDMETHOD(CreateVertexShader)(THIS_ CONST DWORD*,IDirect3DVertexShader9**) PURE;
	STDMETHOD(SetVertexShader)(THIS_ IDirect3DVertexShader9*) PURE;
	STDMETHOD(GetVertexShader)(THIS_ IDirect3DVertexShader9**) PURE;
	STDMETHOD(SetVertexShaderConstantF)(THIS_ UINT,CONST float*,UINT) PURE;
	STDMETHOD(GetVertexShaderConstantF)(THIS_ UINT,float*,UINT) PURE;
	STDMETHOD(SetVertexShaderConstantI)(THIS_ UINT,CONST int*,UINT) PURE;
	STDMETHOD(GetVertexShaderConstantI)(THIS_ UINT,int*,UINT) PURE;
	STDMETHOD(SetVertexShaderConstantB)(THIS_ UINT,CONST BOOL*,UINT) PURE;
	STDMETHOD(GetVertexShaderConstantB)(THIS_ UINT,BOOL*,UINT) PURE;
	STDMETHOD(SetStreamSource)(THIS_ UINT,IDirect3DVertexBuffer9*,UINT,UINT) PURE;
	STDMETHOD(GetStreamSource)(THIS_ UINT,IDirect3DVertexBuffer9**,UINT*,UINT*) PURE;
	STDMETHOD(SetStreamSourceFreq)(THIS_ UINT,UINT) PURE;
	STDMETHOD(GetStreamSourceFreq)(THIS_ UINT,UINT*) PURE;
	STDMETHOD(SetIndices)(THIS_ IDirect3DIndexBuffer9*) PURE;
	STDMETHOD(GetIndices)(THIS_ IDirect3DIndexBuffer9**) PURE;
	STDMETHOD(CreatePixelShader)(THIS_ CONST DWORD*,IDirect3DPixelShader9**) PURE;
	STDMETHOD(SetPixelShader)(THIS_ IDirect3DPixelShader9*) PURE;
	STDMETHOD(GetPixelShader)(THIS_ IDirect3DPixelShader9**) PURE;
	STDMETHOD(SetPixelShaderConstantF)(THIS_ UINT,CONST float*,UINT) PURE;
	STDMETHOD(GetPixelShaderConstantF)(THIS_ UINT,float*,UINT) PURE;
	STDMETHOD(SetPixelShaderConstantI)(THIS_ UINT,CONST int*,UINT) PURE;
	STDMETHOD(GetPixelShaderConstantI)(THIS_ UINT,int*,UINT) PURE;
	STDMETHOD(SetPixelShaderConstantB)(THIS_ UINT,CONST BOOL*,UINT) PURE;
	STDMETHOD(GetPixelShaderConstantB)(THIS_ UINT,BOOL*,UINT) PURE;
	STDMETHOD(DrawRectPatch)(THIS_ UINT,CONST float*,CONST D3DRECTPATCH_INFO*) PURE;
	STDMETHOD(DrawTriPatch)(THIS_ UINT,CONST float*,CONST D3DTRIPATCH_INFO*) PURE;
	STDMETHOD(DeletePatch)(THIS_ UINT) PURE;
	STDMETHOD(CreateQuery)(THIS_ D3DQUERYTYPE,IDirect3DQuery9**) PURE;
};
typedef struct IDirect3DDevice9 *LPDIRECT3DDEVICE9, *PDIRECT3DDEVICE9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DDevice9_QueryInterface(p,a,b)	(p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DDevice9_AddRef(p)	(p)->lpVtbl->AddRef(p)
#define IDirect3DDevice9_Release(p)	(p)->lpVtbl->Release(p)
#define IDirect3DDevice9_TestCooperativeLevel(p)	(p)->lpVtbl->TestCooperativeLevel(p)
#define IDirect3DDevice9_GetAvailableTextureMem(p)	(p)->lpVtbl->GetAvailableTextureMem(p)
#define IDirect3DDevice9_EvictManagedResources(p)	(p)->lpVtbl->EvictManagedResources(p)
#define IDirect3DDevice9_GetDirect3D(p,a)	(p)->lpVtbl->GetDirect3D(p,a)
#define IDirect3DDevice9_GetDeviceCaps(p,a)	(p)->lpVtbl->GetDeviceCaps(p,a)
#define IDirect3DDevice9_GetDisplayMode(p,a,b)	(p)->lpVtbl->GetDisplayMode(p,a,b)
#define IDirect3DDevice9_GetCreationParameters(p,a)	(p)->lpVtbl->GetCreationParameters(p,a)
#define IDirect3DDevice9_SetCursorProperties(p,a,b,c)	(p)->lpVtbl->SetCursorProperties(p,a,b,c)
#define IDirect3DDevice9_SetCursorPosition(p,a,b,c)	(p)->lpVtbl->SetCursorPosition(p,a,b,c)
#define IDirect3DDevice9_ShowCursor(p,a)	(p)->lpVtbl->ShowCursor(p,a)
#define IDirect3DDevice9_CreateAdditionalSwapChain(p,a,b)	(p)->lpVtbl->CreateAdditionalSwapChain(p,a,b)
#define IDirect3DDevice9_GetSwapChain(p,a,b)	(p)->lpVtbl->GetSwapChain(p,a,b)
#define IDirect3DDevice9_GetNumberOfSwapChains(p)	(p)->lpVtbl->GetNumberOfSwapChains(p)
#define IDirect3DDevice9_Reset(p,a)	(p)->lpVtbl->Reset(p,a)
#define IDirect3DDevice9_Present(p,a,b,c,d)	(p)->lpVtbl->Present(p,a,b,c,d)
#define IDirect3DDevice9_GetBackBuffer(p,a,b,c,d)	(p)->lpVtbl->GetBackBuffer(p,a,b,c,d)
#define IDirect3DDevice9_GetRasterStatus(p,a,b)	(p)->lpVtbl->GetRasterStatus(p,a,b)
#define IDirect3DDevice9_SetDialogBoxMode(p,a)	(p)->lpVtbl->SetDialogBoxMode(p,a)
#define IDirect3DDevice9_SetGammaRamp(p,a,b,c)	(p)->lpVtbl->SetGammaRamp(p,a,b,c)
#define IDirect3DDevice9_GetGammaRamp(p,a,b)	(p)->lpVtbl->GetGammaRamp(p,a,b)
#define IDirect3DDevice9_CreateTexture(p,a,b,c,d,e,f,g,h)	(p)->lpVtbl->CreateTexture(p,a,b,c,d,e,f,g,h)
#define IDirect3DDevice9_CreateVolumeTexture(p,a,b,c,d,e,f,g,h,i)	(p)->lpVtbl->CreateVolumeTexture(p,a,b,c,d,e,f,g,h,i)
#define IDirect3DDevice9_CreateCubeTexture(p,a,b,c,d,e,f,g)	(p)->lpVtbl->CreateCubeTexture(p,a,b,c,d,e,f,g)
#define IDirect3DDevice9_CreateVertexBuffer(p,a,b,c,d,e,f)	(p)->lpVtbl->CreateVertexBuffer(p,a,b,c,d,e,f)
#define IDirect3DDevice9_CreateIndexBuffer(p,a,b,c,d,e,f)	(p)->lpVtbl->CreateIndexBuffer(p,a,b,c,d,e,f)
#define IDirect3DDevice9_CreateRenderTarget(p,a,b,c,d,e,f,g,h)	(p)->lpVtbl->CreateRenderTarget(p,a,b,c,d,e,f,g,h)
#define IDirect3DDevice9_CreateDepthStencilSurface(p,a,b,c,d,e,f,g,h)	(p)->lpVtbl->CreateDepthStencilSurface(p,a,b,c,d,e,f,g,h)
#define IDirect3DDevice9_UpdateSurface(p,a,b,c,d)	(p)->lpVtbl->UpdateSurface(p,a,b,c,d)
#define IDirect3DDevice9_UpdateTexture(p,a,b)	(p)->lpVtbl->UpdateTexture(p,a,b)
#define IDirect3DDevice9_GetRenderTargetData(p,a,b)	(p)->lpVtbl->GetRenderTargetData(p,a,b)
#define IDirect3DDevice9_GetFrontBufferData(p,a,b)	(p)->lpVtbl->GetFrontBufferData(p,a,b)
#define IDirect3DDevice9_StretchRect(p,a,b,c,d,e)	(p)->lpVtbl->StretchRect(p,a,b,c,d,e)
#define IDirect3DDevice9_ColorFill(p,a,b,c)	(p)->lpVtbl->ColorFill(p,a,b,c)
#define IDirect3DDevice9_CreateOffscreenPlainSurface(p,a,b,c,d,e,f)	(p)->lpVtbl->CreateOffscreenPlainSurface(p,a,b,c,d,e,f)
#define IDirect3DDevice9_SetRenderTarget(p,a,b)	(p)->lpVtbl->SetRenderTarget(p,a,b)
#define IDirect3DDevice9_GetRenderTarget(p,a,b)	(p)->lpVtbl->GetRenderTarget(p,a,b)
#define IDirect3DDevice9_SetDepthStencilSurface(p,a)	(p)->lpVtbl->SetDepthStencilSurface(p,a)
#define IDirect3DDevice9_GetDepthStencilSurface(p,a)	(p)->lpVtbl->GetDepthStencilSurface(p,a)
#define IDirect3DDevice9_BeginScene(p)	(p)->lpVtbl->BeginScene(p)
#define IDirect3DDevice9_EndScene(p)	(p)->lpVtbl->EndScene(p)
#define IDirect3DDevice9_Clear(p,a,b,c,d,e,f)	(p)->lpVtbl->Clear(p,a,b,c,d,e,f)
#define IDirect3DDevice9_SetTransform(p,a,b)	(p)->lpVtbl->SetTransform(p,a,b)
#define IDirect3DDevice9_GetTransform(p,a,b)	(p)->lpVtbl->GetTransform(p,a,b)
#define IDirect3DDevice9_MultiplyTransform(p,a,b)	(p)->lpVtbl->MultiplyTransform(p,a,b)
#define IDirect3DDevice9_SetViewport(p,a)	(p)->lpVtbl->SetViewport(p,a)
#define IDirect3DDevice9_GetViewport(p,a)	(p)->lpVtbl->GetViewport(p,a)
#define IDirect3DDevice9_SetMaterial(p,a)	(p)->lpVtbl->SetMaterial(p,a)
#define IDirect3DDevice9_GetMaterial(p,a)	(p)->lpVtbl->GetMaterial(p,a)
#define IDirect3DDevice9_SetLight(p,a,b)	(p)->lpVtbl->SetLight(p,a,b)
#define IDirect3DDevice9_GetLight(p,a,b)	(p)->lpVtbl->GetLight(p,a,b)
#define IDirect3DDevice9_LightEnable(p,a,b)	(p)->lpVtbl->LightEnable(p,a,b)
#define IDirect3DDevice9_GetLightEnable(p,a,b)	(p)->lpVtbl->GetLightEnable(p,a,b)
#define IDirect3DDevice9_SetClipPlane(p,a,b)	(p)->lpVtbl->SetClipPlane(p,a,b)
#define IDirect3DDevice9_GetClipPlane(p,a,b)	(p)->lpVtbl->GetClipPlane(p,a,b)
#define IDirect3DDevice9_SetRenderState(p,a,b)	(p)->lpVtbl->SetRenderState(p,a,b)
#define IDirect3DDevice9_GetRenderState(p,a,b)	(p)->lpVtbl->GetRenderState(p,a,b)
#define IDirect3DDevice9_CreateStateBlock(p,a,b)	(p)->lpVtbl->CreateStateBlock(p,a,b)
#define IDirect3DDevice9_BeginStateBlock(p)	(p)->lpVtbl->BeginStateBlock(p)
#define IDirect3DDevice9_EndStateBlock(p,a)	(p)->lpVtbl->EndStateBlock(p,a)
#define IDirect3DDevice9_SetClipStatus(p,a)	(p)->lpVtbl->SetClipStatus(p,a)
#define IDirect3DDevice9_GetClipStatus(p,a)	(p)->lpVtbl->GetClipStatus(p,a)
#define IDirect3DDevice9_GetTexture(p,a,b)	(p)->lpVtbl->GetTexture(p,a,b)
#define IDirect3DDevice9_SetTexture(p,a,b)	(p)->lpVtbl->SetTexture(p,a,b)
#define IDirect3DDevice9_GetTextureStageState(p,a,b,c)	(p)->lpVtbl->GetTextureStageState(p,a,b,c)
#define IDirect3DDevice9_SetTextureStageState(p,a,b,c)	(p)->lpVtbl->SetTextureStageState(p,a,b,c)
#define IDirect3DDevice9_GetSamplerState(p,a,b,c)	(p)->lpVtbl->GetSamplerState(p,a,b,c)
#define IDirect3DDevice9_SetSamplerState(p,a,b,c)	(p)->lpVtbl->SetSamplerState(p,a,b,c)
#define IDirect3DDevice9_ValidateDevice(p,a)	(p)->lpVtbl->ValidateDevice(p,a)
#define IDirect3DDevice9_SetPaletteEntries(p,a,b)	(p)->lpVtbl->SetPaletteEntries(p,a,b)
#define IDirect3DDevice9_GetPaletteEntries(p,a,b)	(p)->lpVtbl->GetPaletteEntries(p,a,b)
#define IDirect3DDevice9_SetCurrentTexturePalette(p,a)	(p)->lpVtbl->SetCurrentTexturePalette(p,a)
#define IDirect3DDevice9_GetCurrentTexturePalette(p,a)	(p)->lpVtbl->GetCurrentTexturePalette(p,a)
#define IDirect3DDevice9_SetScissorRect(p,a)	(p)->lpVtbl->SetScissorRect(p,a)
#define IDirect3DDevice9_GetScissorRect(p,a)	(p)->lpVtbl->GetScissorRect(p,a)
#define IDirect3DDevice9_SetSoftwareVertexProcessing(p,a)	(p)->lpVtbl->SetSoftwareVertexProcessing(p,a)
#define IDirect3DDevice9_GetSoftwareVertexProcessing(p)	(p)->lpVtbl->GetSoftwareVertexProcessing(p)
#define IDirect3DDevice9_SetNPatchMode(p,a)	(p)->lpVtbl->SetNPatchMode(p,a)
#define IDirect3DDevice9_GetNPatchMode(p)	(p)->lpVtbl->GetNPatchMode(p)
#define IDirect3DDevice9_DrawPrimitive(p,a,b,c)	(p)->lpVtbl->DrawPrimitive(p,a,b,c)
#define IDirect3DDevice9_DrawIndexedPrimitive(p,a,b,c,d,e,f)	(p)->lpVtbl->DrawIndexedPrimitive(p,a,b,c,d,e,f)
#define IDirect3DDevice9_DrawPrimitiveUP(p,a,b,c,d)	(p)->lpVtbl->DrawPrimitiveUP(p,a,b,c,d)
#define IDirect3DDevice9_DrawIndexedPrimitiveUP(p,a,b,c,d,e,f,g,h)	(p)->lpVtbl->DrawIndexedPrimitiveUP(p,a,b,c,d,e,f,g,h)
#define IDirect3DDevice9_ProcessVertices(p,a,b,c,d,e,f)	(p)->lpVtbl->ProcessVertices(p,a,b,c,d,e,f)
#define IDirect3DDevice9_CreateVertexDeclaration(p,a,b)	(p)->lpVtbl->CreateVertexDeclaration(p,a,b)
#define IDirect3DDevice9_SetVertexDeclaration(p,a)	(p)->lpVtbl->SetVertexDeclaration(p,a)
#define IDirect3DDevice9_GetVertexDeclaration(p,a)	(p)->lpVtbl->GetVertexDeclaration(p,a)
#define IDirect3DDevice9_SetFVF(p,a)	(p)->lpVtbl->SetFVF(p,a)
#define IDirect3DDevice9_GetFVF(p,a)	(p)->lpVtbl->GetFVF(p,a)
#define IDirect3DDevice9_CreateVertexShader(p,a,b)	(p)->lpVtbl->CreateVertexShader(p,a,b)
#define IDirect3DDevice9_SetVertexShader(p,a)	(p)->lpVtbl->SetVertexShader(p,a)
#define IDirect3DDevice9_GetVertexShader(p,a)	(p)->lpVtbl->GetVertexShader(p,a)
#define IDirect3DDevice9_SetVertexShaderConstantF(p,a,b,c)	(p)->lpVtbl->SetVertexShaderConstantF(p,a,b,c)
#define IDirect3DDevice9_GetVertexShaderConstantF(p,a,b,c)	(p)->lpVtbl->GetVertexShaderConstantF(p,a,b,c)
#define IDirect3DDevice9_SetVertexShaderConstantI(p,a,b,c)	(p)->lpVtbl->SetVertexShaderConstantI(p,a,b,c)
#define IDirect3DDevice9_GetVertexShaderConstantI(p,a,b,c)	(p)->lpVtbl->GetVertexShaderConstantI(p,a,b,c)
#define IDirect3DDevice9_SetVertexShaderConstantB(p,a,b,c)	(p)->lpVtbl->SetVertexShaderConstantB(p,a,b,c)
#define IDirect3DDevice9_GetVertexShaderConstantB(p,a,b,c)	(p)->lpVtbl->GetVertexShaderConstantB(p,a,b,c)
#define IDirect3DDevice9_SetStreamSource(p,a,b,c,d)	(p)->lpVtbl->SetStreamSource(p,a,b,c,d)
#define IDirect3DDevice9_GetStreamSource(p,a,b,c,d)	(p)->lpVtbl->GetStreamSource(p,a,b,c,d)
#define IDirect3DDevice9_SetStreamSourceFreq(p,a,b)	(p)->lpVtbl->SetStreamSourceFreq(p,a,b)
#define IDirect3DDevice9_GetStreamSourceFreq(p,a,b)	(p)->lpVtbl->GetStreamSourceFreq(p,a,b)
#define IDirect3DDevice9_SetIndices(p,a)	(p)->lpVtbl->SetIndices(p,a)
#define IDirect3DDevice9_GetIndices(p,a)	(p)->lpVtbl->GetIndices(p,a)
#define IDirect3DDevice9_CreatePixelShader(p,a,b)	(p)->lpVtbl->CreatePixelShader(p,a,b)
#define IDirect3DDevice9_SetPixelShader(p,a)	(p)->lpVtbl->SetPixelShader(p,a)
#define IDirect3DDevice9_GetPixelShader(p,a)	(p)->lpVtbl->GetPixelShader(p,a)
#define IDirect3DDevice9_SetPixelShaderConstantF(p,a,b,c)	(p)->lpVtbl->SetPixelShaderConstantF(p,a,b,c)
#define IDirect3DDevice9_GetPixelShaderConstantF(p,a,b,c)	(p)->lpVtbl->GetPixelShaderConstantF(p,a,b,c)
#define IDirect3DDevice9_SetPixelShaderConstantI(p,a,b,c)	(p)->lpVtbl->SetPixelShaderConstantI(p,a,b,c)
#define IDirect3DDevice9_GetPixelShaderConstantI(p,a,b,c)	(p)->lpVtbl->GetPixelShaderConstantI(p,a,b,c)
#define IDirect3DDevice9_SetPixelShaderConstantB(p,a,b,c)	(p)->lpVtbl->SetPixelShaderConstantB(p,a,b,c)
#define IDirect3DDevice9_GetPixelShaderConstantB(p,a,b,c)	(p)->lpVtbl->GetPixelShaderConstantB(p,a,b,c)
#define IDirect3DDevice9_DrawRectPatch(p,a,b,c)	(p)->lpVtbl->DrawRectPatch(p,a,b,c)
#define IDirect3DDevice9_DrawTriPatch(p,a,b,c)	(p)->lpVtbl->DrawTriPatch(p,a,b,c)
#define IDirect3DDevice9_DeletePatch(p,a)	(p)->lpVtbl->DeletePatch(p,a)
#define IDirect3DDevice9_CreateQuery(p,a,b)	(p)->lpVtbl->CreateQuery(p,a,b)
#else
#define IDirect3DDevice9_QueryInterface(p,a,b)	(p)->QueryInterface(a,b)
#define IDirect3DDevice9_AddRef(p)	(p)->AddRef()
#define IDirect3DDevice9_Release(p)	(p)->Release()
#define IDirect3DDevice9_TestCooperativeLevel(p)	(p)->TestCooperativeLevel()
#define IDirect3DDevice9_GetAvailableTextureMem(p)	(p)->GetAvailableTextureMem()
#define IDirect3DDevice9_EvictManagedResources(p)	(p)->EvictManagedResources()
#define IDirect3DDevice9_GetDirect3D(p,a)	(p)->GetDirect3D(a)
#define IDirect3DDevice9_GetDeviceCaps(p,a)	(p)->GetDeviceCaps(a)
#define IDirect3DDevice9_GetDisplayMode(p,a,b)	(p)->GetDisplayMode(a,b)
#define IDirect3DDevice9_GetCreationParameters(p,a)	(p)->GetCreationParameters(a)
#define IDirect3DDevice9_SetCursorProperties(p,a,b,c)	(p)->SetCursorProperties(a,b,c)
#define IDirect3DDevice9_SetCursorPosition(p,a,b,c)	(p)->SetCursorPosition(a,b,c)
#define IDirect3DDevice9_ShowCursor(p,a)	(p)->ShowCursor(a)
#define IDirect3DDevice9_CreateAdditionalSwapChain(p,a,b)	(p)->CreateAdditionalSwapChain(a,b)
#define IDirect3DDevice9_GetSwapChain(p,a,b)	(p)->GetSwapChain(a,b)
#define IDirect3DDevice9_GetNumberOfSwapChains(p)	(p)->GetNumberOfSwapChains()
#define IDirect3DDevice9_Reset(p,a)	(p)->Reset(a)
#define IDirect3DDevice9_Present(p,a,b,c,d)	(p)->Present(a,b,c,d)
#define IDirect3DDevice9_GetBackBuffer(p,a,b,c,d)	(p)->GetBackBuffer(a,b,c,d)
#define IDirect3DDevice9_GetRasterStatus(p,a,b)	(p)->GetRasterStatus(a,b)
#define IDirect3DDevice9_SetDialogBoxMode(p,a)	(p)->SetDialogBoxMode(a)
#define IDirect3DDevice9_SetGammaRamp(p,a,b,c)	(p)->SetGammaRamp(a,b,c)
#define IDirect3DDevice9_GetGammaRamp(p,a,b)	(p)->GetGammaRamp(a,b)
#define IDirect3DDevice9_CreateTexture(p,a,b,c,d,e,f,g,h)	(p)->CreateTexture(a,b,c,d,e,f,g,h)
#define IDirect3DDevice9_CreateVolumeTexture(p,a,b,c,d,e,f,g,h,i)	(p)->CreateVolumeTexture(a,b,c,d,e,f,g,h,i)
#define IDirect3DDevice9_CreateCubeTexture(p,a,b,c,d,e,f,g)	(p)->CreateCubeTexture(a,b,c,d,e,f,g)
#define IDirect3DDevice9_CreateVertexBuffer(p,a,b,c,d,e,f)	(p)->CreateVertexBuffer(a,b,c,d,e,f)
#define IDirect3DDevice9_CreateIndexBuffer(p,a,b,c,d,e,f)	(p)->CreateIndexBuffer(a,b,c,d,e,f)
#define IDirect3DDevice9_CreateRenderTarget(p,a,b,c,d,e,f,g,h)	(p)->CreateRenderTarget(a,b,c,d,e,f,g,h)
#define IDirect3DDevice9_CreateDepthStencilSurface(p,a,b,c,d,e,f,g,h)	(p)->CreateDepthStencilSurface(a,b,c,d,e,f,g,h)
#define IDirect3DDevice9_UpdateSurface(p,a,b,c,d)	(p)->UpdateSurface(a,b,c,d)
#define IDirect3DDevice9_UpdateTexture(p,a,b)	(p)->UpdateTexture(a,b)
#define IDirect3DDevice9_GetRenderTargetData(p,a,b)	(p)->GetRenderTargetData(a,b)
#define IDirect3DDevice9_GetFrontBufferData(p,a,b)	(p)->GetFrontBufferData(a,b)
#define IDirect3DDevice9_StretchRect(p,a,b,c,d,e)	(p)->StretchRect(a,b,c,d,e)
#define IDirect3DDevice9_ColorFill(p,a,b,c)	(p)->ColorFill(a,b,c)
#define IDirect3DDevice9_CreateOffscreenPlainSurface(p,a,b,c,d,e,f)	(p)->CreateOffscreenPlainSurface(a,b,c,d,e,f)
#define IDirect3DDevice9_SetRenderTarget(p,a,b)	(p)->SetRenderTarget(a,b)
#define IDirect3DDevice9_GetRenderTarget(p,a,b)	(p)->GetRenderTarget(a,b)
#define IDirect3DDevice9_SetDepthStencilSurface(p,a)	(p)->SetDepthStencilSurface(a)
#define IDirect3DDevice9_GetDepthStencilSurface(p,a)	(p)->GetDepthStencilSurface(a)
#define IDirect3DDevice9_BeginScene(p)	(p)->BeginScene()
#define IDirect3DDevice9_EndScene(p)	(p)->EndScene()
#define IDirect3DDevice9_Clear(p,a,b,c,d,e,f)	(p)->Clear(a,b,c,d,e,f)
#define IDirect3DDevice9_SetTransform(p,a,b)	(p)->SetTransform(a,b)
#define IDirect3DDevice9_GetTransform(p,a,b)	(p)->GetTransform(a,b)
#define IDirect3DDevice9_MultiplyTransform(p,a,b)	(p)->MultiplyTransform(a,b)
#define IDirect3DDevice9_SetViewport(p,a)	(p)->SetViewport(a)
#define IDirect3DDevice9_GetViewport(p,a)	(p)->GetViewport(a)
#define IDirect3DDevice9_SetMaterial(p,a)	(p)->SetMaterial(a)
#define IDirect3DDevice9_GetMaterial(p,a)	(p)->GetMaterial(a)
#define IDirect3DDevice9_SetLight(p,a,b)	(p)->SetLight(a,b)
#define IDirect3DDevice9_GetLight(p,a,b)	(p)->GetLight(a,b)
#define IDirect3DDevice9_LightEnable(p,a,b)	(p)->LightEnable(a,b)
#define IDirect3DDevice9_GetLightEnable(p,a,b)	(p)->GetLightEnable(a,b)
#define IDirect3DDevice9_SetClipPlane(p,a,b)	(p)->SetClipPlane(a,b)
#define IDirect3DDevice9_GetClipPlane(p,a,b)	(p)->GetClipPlane(a,b)
#define IDirect3DDevice9_SetRenderState(p,a,b)	(p)->SetRenderState(a,b)
#define IDirect3DDevice9_GetRenderState(p,a,b)	(p)->GetRenderState(a,b)
#define IDirect3DDevice9_CreateStateBlock(p,a,b)	(p)->CreateStateBlock(a,b)
#define IDirect3DDevice9_BeginStateBlock(p)	(p)->BeginStateBlock()
#define IDirect3DDevice9_EndStateBlock(p,a)	(p)->EndStateBlock(a)
#define IDirect3DDevice9_SetClipStatus(p,a)	(p)->SetClipStatus(a)
#define IDirect3DDevice9_GetClipStatus(p,a)	(p)->GetClipStatus(a)
#define IDirect3DDevice9_GetTexture(p,a,b)	(p)->GetTexture(a,b)
#define IDirect3DDevice9_SetTexture(p,a,b)	(p)->SetTexture(a,b)
#define IDirect3DDevice9_GetTextureStageState(p,a,b,c)	(p)->GetTextureStageState(a,b,c)
#define IDirect3DDevice9_SetTextureStageState(p,a,b,c)	(p)->SetTextureStageState(a,b,c)
#define IDirect3DDevice9_GetSamplerState(p,a,b,c)	(p)->GetSamplerState(a,b,c)
#define IDirect3DDevice9_SetSamplerState(p,a,b,c)	(p)->SetSamplerState(a,b,c)
#define IDirect3DDevice9_ValidateDevice(p,a)	(p)->ValidateDevice(a)
#define IDirect3DDevice9_SetPaletteEntries(p,a,b)	(p)->SetPaletteEntries(a,b)
#define IDirect3DDevice9_GetPaletteEntries(p,a,b)	(p)->GetPaletteEntries(a,b)
#define IDirect3DDevice9_SetCurrentTexturePalette(p,a)	(p)->SetCurrentTexturePalette(a)
#define IDirect3DDevice9_GetCurrentTexturePalette(p,a)	(p)->GetCurrentTexturePalette(a)
#define IDirect3DDevice9_SetScissorRect(p,a)	(p)->SetScissorRect(a)
#define IDirect3DDevice9_GetScissorRect(p,a)	(p)->GetScissorRect(a)
#define IDirect3DDevice9_SetSoftwareVertexProcessing(p,a)	(p)->SetSoftwareVertexProcessing(a)
#define IDirect3DDevice9_GetSoftwareVertexProcessing(p)	(p)->GetSoftwareVertexProcessing()
#define IDirect3DDevice9_SetNPatchMode(p,a)	(p)->SetNPatchMode(a)
#define IDirect3DDevice9_GetNPatchMode(p)	(p)->GetNPatchMode()
#define IDirect3DDevice9_DrawPrimitive(p,a,b,c)	(p)->DrawPrimitive(a,b,c)
#define IDirect3DDevice9_DrawIndexedPrimitive(p,a,b,c,d,e,f)	(p)->DrawIndexedPrimitive(a,b,c,d,e,f)
#define IDirect3DDevice9_DrawPrimitiveUP(p,a,b,c,d)	(p)->DrawPrimitiveUP(a,b,c,d)
#define IDirect3DDevice9_DrawIndexedPrimitiveUP(p,a,b,c,d,e,f,g,h)	(p)->DrawIndexedPrimitiveUP(a,b,c,d,e,f,g,h)
#define IDirect3DDevice9_ProcessVertices(p,a,b,c,d,e,f)	(p)->ProcessVertices(a,b,c,d,e,f)
#define IDirect3DDevice9_CreateVertexDeclaration(p,a,b)	(p)->CreateVertexDeclaration(a,b)
#define IDirect3DDevice9_SetVertexDeclaration(p,a)	(p)->SetVertexDeclaration(a)
#define IDirect3DDevice9_GetVertexDeclaration(p,a)	(p)->GetVertexDeclaration(a)
#define IDirect3DDevice9_SetFVF(p,a)	(p)->SetFVF(a)
#define IDirect3DDevice9_GetFVF(p,a)	(p)->GetFVF(a)
#define IDirect3DDevice9_CreateVertexShader(p,a,b)	(p)->CreateVertexShader(a,b)
#define IDirect3DDevice9_SetVertexShader(p,a)	(p)->SetVertexShader(a)
#define IDirect3DDevice9_GetVertexShader(p,a)	(p)->GetVertexShader(a)
#define IDirect3DDevice9_SetVertexShaderConstantF(p,a,b,c)	(p)->SetVertexShaderConstantF(a,b,c)
#define IDirect3DDevice9_GetVertexShaderConstantF(p,a,b,c)	(p)->GetVertexShaderConstantF(a,b,c)
#define IDirect3DDevice9_SetVertexShaderConstantI(p,a,b,c)	(p)->SetVertexShaderConstantI(a,b,c)
#define IDirect3DDevice9_GetVertexShaderConstantI(p,a,b,c)	(p)->GetVertexShaderConstantI(a,b,c)
#define IDirect3DDevice9_SetVertexShaderConstantB(p,a,b,c)	(p)->SetVertexShaderConstantB(a,b,c)
#define IDirect3DDevice9_GetVertexShaderConstantB(p,a,b,c)	(p)->GetVertexShaderConstantB(a,b,c)
#define IDirect3DDevice9_SetStreamSource(p,a,b,c,d)	(p)->SetStreamSource(a,b,c,d)
#define IDirect3DDevice9_GetStreamSource(p,a,b,c,d)	(p)->GetStreamSource(a,b,c,d)
#define IDirect3DDevice9_SetStreamSourceFreq(p,a,b)	(p)->SetStreamSourceFreq(a,b)
#define IDirect3DDevice9_GetStreamSourceFreq(p,a,b)	(p)->GetStreamSourceFreq(a,b)
#define IDirect3DDevice9_SetIndices(p,a)	(p)->SetIndices(a)
#define IDirect3DDevice9_GetIndices(p,a)	(p)->GetIndices(a)
#define IDirect3DDevice9_CreatePixelShader(p,a,b)	(p)->CreatePixelShader(a,b)
#define IDirect3DDevice9_SetPixelShader(p,a)	(p)->SetPixelShader(a)
#define IDirect3DDevice9_GetPixelShader(p,a)	(p)->GetPixelShader(a)
#define IDirect3DDevice9_SetPixelShaderConstantF(p,a,b,c)	(p)->SetPixelShaderConstantF(a,b,c)
#define IDirect3DDevice9_GetPixelShaderConstantF(p,a,b,c)	(p)->GetPixelShaderConstantF(a,b,c)
#define IDirect3DDevice9_SetPixelShaderConstantI(p,a,b,c)	(p)->SetPixelShaderConstantI(a,b,c)
#define IDirect3DDevice9_GetPixelShaderConstantI(p,a,b,c)	(p)->GetPixelShaderConstantI(a,b,c)
#define IDirect3DDevice9_SetPixelShaderConstantB(p,a,b,c)	(p)->SetPixelShaderConstantB(a,b,c)
#define IDirect3DDevice9_GetPixelShaderConstantB(p,a,b,c)	(p)->GetPixelShaderConstantB(a,b,c)
#define IDirect3DDevice9_DrawRectPatch(p,a,b,c)	(p)->DrawRectPatch(a,b,c)
#define IDirect3DDevice9_DrawTriPatch(p,a,b,c)	(p)->DrawTriPatch(a,b,c)
#define IDirect3DDevice9_DeletePatch(p,a)	(p)->DeletePatch(a)
#define IDirect3DDevice9_CreateQuery(p,a,b)	(p)->CreateQuery(a,b)
#endif

#undef INTERFACE
#define INTERFACE IDirect3DVolume9
DECLARE_INTERFACE_(IDirect3DVolume9,IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9**) PURE;
	STDMETHOD(SetPrivateData)(THIS_ REFGUID,CONST void*,DWORD,DWORD) PURE;
	STDMETHOD(GetPrivateData)(THIS_ REFGUID,void*,DWORD*) PURE;
	STDMETHOD(FreePrivateData)(THIS_ REFGUID) PURE;
	STDMETHOD(GetContainer)(THIS_ REFIID,void**) PURE;
	STDMETHOD(GetDesc)(THIS_ D3DVOLUME_DESC*) PURE;
	STDMETHOD(LockBox)(THIS_ D3DLOCKED_BOX*,CONST D3DBOX*,DWORD) PURE;
	STDMETHOD(UnlockBox)(THIS) PURE;
};
typedef struct IDirect3DVolume9 *LPDIRECT3DVOLUME9, *PDIRECT3DVOLUME9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DVolume9_QueryInterface(p,a,b)	(p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DVolume9_AddRef(p)	(p)->lpVtbl->AddRef(p)
#define IDirect3DVolume9_Release(p)	(p)->lpVtbl->Release(p)
#define IDirect3DVolume9_GetDevice(p,a)	(p)->lpVtbl->GetDevice(p,a)
#define IDirect3DVolume9_SetPrivateData(p,a,b,c,d)	(p)->lpVtbl->SetPrivateData(p,a,b,c,d)
#define IDirect3DVolume9_GetPrivateData(p,a,b,c)	(p)->lpVtbl->GetPrivateData(p,a,b,c)
#define IDirect3DVolume9_FreePrivateData(p,a)	(p)->lpVtbl->FreePrivateData(p,a)
#define IDirect3DVolume9_GetContainer(p,a,b)	(p)->lpVtbl->GetContainer(p,a,b)
#define IDirect3DVolume9_GetDesc(p,a)	(p)->lpVtbl->GetDesc(p,a)
#define IDirect3DVolume9_LockBox(p,a,b,c)	(p)->lpVtbl->LockBox(p,a,b,c)
#define IDirect3DVolume9_UnlockBox(p)	(p)->lpVtbl->UnlockBox(p)
#else
#define IDirect3DVolume9_QueryInterface(p,a,b)	(p)->QueryInterface(a,b)
#define IDirect3DVolume9_AddRef(p)	(p)->AddRef()
#define IDirect3DVolume9_Release(p)	(p)->Release()
#define IDirect3DVolume9_GetDevice(p,a)	(p)->GetDevice(a)
#define IDirect3DVolume9_SetPrivateData(p,a,b,c,d)	(p)->SetPrivateData(a,b,c,d)
#define IDirect3DVolume9_GetPrivateData(p,a,b,c)	(p)->GetPrivateData(a,b,c)
#define IDirect3DVolume9_FreePrivateData(p,a)	(p)->FreePrivateData(a)
#define IDirect3DVolume9_GetContainer(p,a,b)	(p)->GetContainer(a,b)
#define IDirect3DVolume9_GetDesc(p,a)	(p)->GetDesc(a)
#define IDirect3DVolume9_LockBox(p,a,b,c)	(p)->LockBox(a,b,c)
#define IDirect3DVolume9_UnlockBox(p)	(p)->UnlockBox()
#endif

#undef INTERFACE
#define INTERFACE IDirect3DSwapChain9
DECLARE_INTERFACE_(IDirect3DSwapChain9,IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(Present)(THIS_ CONST RECT*,CONST RECT*,HWND,CONST RGNDATA*,DWORD) PURE;
	STDMETHOD(GetFrontBufferData)(THIS_ IDirect3DSurface9*) PURE;
	STDMETHOD(GetBackBuffer)(THIS_ UINT,D3DBACKBUFFER_TYPE,IDirect3DSurface9**) PURE;
	STDMETHOD(GetRasterStatus)(THIS_ D3DRASTER_STATUS*) PURE;
	STDMETHOD(GetDisplayMode)(THIS_ D3DDISPLAYMODE*) PURE;
	STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9**) PURE;
	STDMETHOD(GetPresentParameters)(THIS_ D3DPRESENT_PARAMETERS*) PURE;
};
typedef struct IDirect3DSwapChain9 *LPDIRECT3DSWAPCHAIN9, *PDIRECT3DSWAPCHAIN9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DSwapChain9_QueryInterface(p,a,b)	(p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DSwapChain9_AddRef(p)	(p)->lpVtbl->AddRef(p)
#define IDirect3DSwapChain9_Release(p)	(p)->lpVtbl->Release(p)
#define IDirect3DSwapChain9_Present(p,a,b,c,d,e)	(p)->lpVtbl->Present(p,a,b,c,d,e)
#define IDirect3DSwapChain9_GetFrontBufferData(p,a)	(p)->lpVtbl->GetFrontBufferData(p,a)
#define IDirect3DSwapChain9_GetBackBuffer(p,a,b,c)	(p)->lpVtbl->GetBackBuffer(p,a,b,c)
#define IDirect3DSwapChain9_GetRasterStatus(p,a)	(p)->lpVtbl->GetRasterStatus(p,a)
#define IDirect3DSwapChain9_GetDisplayMode(p,a)	(p)->lpVtbl->GetDisplayMode(p,a)
#define IDirect3DSwapChain9_GetDevice(p,a)	(p)->lpVtbl->GetDevice(p,a)
#define IDirect3DSwapChain9_GetPresentParameters(p,a)	(p)->lpVtbl->GetPresentParameters(p,a)
#else
#define IDirect3DSwapChain9_QueryInterface(p,a,b)	(p)->QueryInterface(a,b)
#define IDirect3DSwapChain9_AddRef(p)	(p)->AddRef()
#define IDirect3DSwapChain9_Release(p)	(p)->Release()
#define IDirect3DSwapChain9_Present(p,a,b,c,d,e)	(p)->Present(a,b,c,d,e)
#define IDirect3DSwapChain9_GetFrontBufferData(p,a)	(p)->GetFrontBufferData(a)
#define IDirect3DSwapChain9_GetBackBuffer(p,a,b,c)	(p)->GetBackBuffer(a,b,c)
#define IDirect3DSwapChain9_GetRasterStatus(p,a)	(p)->GetRasterStatus(a)
#define IDirect3DSwapChain9_GetDisplayMode(p,a)	(p)->GetDisplayMode(a)
#define IDirect3DSwapChain9_GetDevice(p,a)	(p)->GetDevice(a)
#define IDirect3DSwapChain9_GetPresentParameters(p,a)	(p)->GetPresentParameters(a)
#endif

#undef INTERFACE
#define INTERFACE IDirect3DResource9
DECLARE_INTERFACE_(IDirect3DResource9,IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9**) PURE;
	STDMETHOD(SetPrivateData)(THIS_ REFGUID,CONST void*,DWORD,DWORD) PURE;
	STDMETHOD(GetPrivateData)(THIS_ REFGUID,void*,DWORD*) PURE;
	STDMETHOD(FreePrivateData)(THIS_ REFGUID) PURE;
	STDMETHOD_(DWORD,SetPriority)(THIS_ DWORD) PURE;
	STDMETHOD_(DWORD,GetPriority)(THIS) PURE;
	STDMETHOD_(void,PreLoad)(THIS) PURE;
	STDMETHOD_(D3DRESOURCETYPE,GetType)(THIS) PURE;
};
typedef struct IDirect3DResource9 *LPDIRECT3DRESOURCE9, *PDIRECT3DRESOURCE9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DResource9_QueryInterface(p,a,b)	(p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DResource9_AddRef(p)	(p)->lpVtbl->AddRef(p)
#define IDirect3DResource9_Release(p)	(p)->lpVtbl->Release(p)
#define IDirect3DResource9_GetDevice(p,a)	(p)->lpVtbl->GetDevice(p,a)
#define IDirect3DResource9_SetPrivateData(p,a,b,c,d)	(p)->lpVtbl->SetPrivateData(p,a,b,c,d)
#define IDirect3DResource9_GetPrivateData(p,a,b,c)	(p)->lpVtbl->GetPrivateData(p,a,b,c)
#define IDirect3DResource9_FreePrivateData(p,a)	(p)->lpVtbl->FreePrivateData(p,a)
#define IDirect3DResource9_SetPriority(p,a)	(p)->lpVtbl->SetPriority(p,a)
#define IDirect3DResource9_GetPriority(p)	(p)->lpVtbl->GetPriority(p)
#define IDirect3DResource9_PreLoad(p)	(p)->lpVtbl->PreLoad(p)
#define IDirect3DResource9_GetType(p)	(p)->lpVtbl->GetType(p)
#else
#define IDirect3DResource9_QueryInterface(p,a,b)	(p)->QueryInterface(a,b)
#define IDirect3DResource9_AddRef(p)	(p)->AddRef()
#define IDirect3DResource9_Release(p)	(p)->Release()
#define IDirect3DResource9_GetDevice(p,a)	(p)->GetDevice(a)
#define IDirect3DResource9_SetPrivateData(p,a,b,c,d)	(p)->SetPrivateData(a,b,c,d)
#define IDirect3DResource9_GetPrivateData(p,a,b,c)	(p)->GetPrivateData(a,b,c)
#define IDirect3DResource9_FreePrivateData(p,a)	(p)->FreePrivateData(a)
#define IDirect3DResource9_SetPriority(p,a)	(p)->SetPriority(a)
#define IDirect3DResource9_GetPriority(p)	(p)->GetPriority()
#define IDirect3DResource9_PreLoad(p)	(p)->PreLoad()
#define IDirect3DResource9_GetType(p)	(p)->GetType()
#endif

#undef INTERFACE
#define INTERFACE IDirect3DSurface9
DECLARE_INTERFACE_(IDirect3DSurface9,IDirect3DResource9)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9**) PURE;
	STDMETHOD(SetPrivateData)(THIS_ REFGUID,CONST void*,DWORD,DWORD) PURE;
	STDMETHOD(GetPrivateData)(THIS_ REFGUID,void*,DWORD*) PURE;
	STDMETHOD(FreePrivateData)(THIS_ REFGUID) PURE;
	STDMETHOD_(DWORD,SetPriority)(THIS_ DWORD) PURE;
	STDMETHOD_(DWORD,GetPriority)(THIS) PURE;
	STDMETHOD_(void,PreLoad)(THIS) PURE;
	STDMETHOD_(D3DRESOURCETYPE,GetType)(THIS) PURE;
	STDMETHOD(GetContainer)(THIS_ REFIID,void**) PURE;
	STDMETHOD(GetDesc)(THIS_ D3DSURFACE_DESC*) PURE;
	STDMETHOD(LockRect)(THIS_ D3DLOCKED_RECT*,CONST RECT*,DWORD) PURE;
	STDMETHOD(UnlockRect)(THIS) PURE;
	STDMETHOD(GetDC)(THIS_ HDC*) PURE;
	STDMETHOD(ReleaseDC)(THIS_ HDC) PURE;
};
typedef struct IDirect3DSurface9 *LPDIRECT3DSURFACE9, *PDIRECT3DSURFACE9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DSurface9_QueryInterface(p,a,b)	(p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DSurface9_AddRef(p)	(p)->lpVtbl->AddRef(p)
#define IDirect3DSurface9_Release(p)	(p)->lpVtbl->Release(p)
#define IDirect3DSurface9_GetDevice(p,a)	(p)->lpVtbl->GetDevice(p,a)
#define IDirect3DSurface9_SetPrivateData(p,a,b,c,d)	(p)->lpVtbl->SetPrivateData(p,a,b,c,d)
#define IDirect3DSurface9_GetPrivateData(p,a,b,c)	(p)->lpVtbl->GetPrivateData(p,a,b,c)
#define IDirect3DSurface9_FreePrivateData(p,a)	(p)->lpVtbl->FreePrivateData(p,a)
#define IDirect3DSurface9_SetPriority(p,a)	(p)->lpVtbl->SetPriority(p,a)
#define IDirect3DSurface9_GetPriority(p)	(p)->lpVtbl->GetPriority(p)
#define IDirect3DSurface9_PreLoad(p)	(p)->lpVtbl->PreLoad(p)
#define IDirect3DSurface9_GetType(p)	(p)->lpVtbl->GetType(p)
#define IDirect3DSurface9_GetContainer(p,a,b)	(p)->lpVtbl->GetContainer(p,a,b)
#define IDirect3DSurface9_GetDesc(p,a)	(p)->lpVtbl->GetDesc(p,a)
#define IDirect3DSurface9_LockRect(p,a,b,c)	(p)->lpVtbl->LockRect(p,a,b,c)
#define IDirect3DSurface9_UnlockRect(p)	(p)->lpVtbl->UnlockRect(p)
#define IDirect3DSurface9_GetDC(p,a)	(p)->lpVtbl->GetDC(p,a)
#define IDirect3DSurface9_ReleaseDC(p,a)	(p)->lpVtbl->ReleaseDC(p,a)
#else
#define IDirect3DSurface9_QueryInterface(p,a,b)	(p)->QueryInterface(a,b)
#define IDirect3DSurface9_AddRef(p)	(p)->AddRef()
#define IDirect3DSurface9_Release(p)	(p)->Release()
#define IDirect3DSurface9_GetDevice(p,a)	(p)->GetDevice(a)
#define IDirect3DSurface9_SetPrivateData(p,a,b,c,d)	(p)->SetPrivateData(a,b,c,d)
#define IDirect3DSurface9_GetPrivateData(p,a,b,c)	(p)->GetPrivateData(a,b,c)
#define IDirect3DSurface9_FreePrivateData(p,a)	(p)->FreePrivateData(a)
#define IDirect3DSurface9_SetPriority(p,a)	(p)->SetPriority(a)
#define IDirect3DSurface9_GetPriority(p)	(p)->GetPriority()
#define IDirect3DSurface9_PreLoad(p)	(p)->PreLoad()
#define IDirect3DSurface9_GetType(p)	(p)->GetType()
#define IDirect3DSurface9_GetContainer(p,a,b)	(p)->GetContainer(a,b)
#define IDirect3DSurface9_GetDesc(p,a)	(p)->GetDesc(a)
#define IDirect3DSurface9_LockRect(p,a,b,c)	(p)->LockRect(a,b,c)
#define IDirect3DSurface9_UnlockRect(p)	(p)->UnlockRect()
#define IDirect3DSurface9_GetDC(p,a)	(p)->GetDC(a)
#define IDirect3DSurface9_ReleaseDC(p,a)	(p)->ReleaseDC(a)
#endif

#undef INTERFACE
#define INTERFACE IDirect3DVertexBuffer9
DECLARE_INTERFACE_(IDirect3DVertexBuffer9,IDirect3DResource9)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9**) PURE;
	STDMETHOD(SetPrivateData)(THIS_ REFGUID,CONST void*,DWORD,DWORD) PURE;
	STDMETHOD(GetPrivateData)(THIS_ REFGUID,void*,DWORD*) PURE;
	STDMETHOD(FreePrivateData)(THIS_ REFGUID) PURE;
	STDMETHOD_(DWORD,SetPriority)(THIS_ DWORD) PURE;
	STDMETHOD_(DWORD,GetPriority)(THIS) PURE;
	STDMETHOD_(void,PreLoad)(THIS) PURE;
	STDMETHOD_(D3DRESOURCETYPE,GetType)(THIS) PURE;
	STDMETHOD(Lock)(THIS_ UINT,UINT,void**,DWORD) PURE;
	STDMETHOD(Unlock)(THIS) PURE;
	STDMETHOD(GetDesc)(THIS_ D3DVERTEXBUFFER_DESC*) PURE;
};
typedef struct IDirect3DVertexBuffer9 *LPDIRECT3DVERTEXBUFFER9, *PDIRECT3DVERTEXBUFFER9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DVertexBuffer9_QueryInterface(p,a,b)	(p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DVertexBuffer9_AddRef(p)	(p)->lpVtbl->AddRef(p)
#define IDirect3DVertexBuffer9_Release(p)	(p)->lpVtbl->Release(p)
#define IDirect3DVertexBuffer9_GetDevice(p,a)	(p)->lpVtbl->GetDevice(p,a)
#define IDirect3DVertexBuffer9_SetPrivateData(p,a,b,c,d)	(p)->lpVtbl->SetPrivateData(p,a,b,c,d)
#define IDirect3DVertexBuffer9_GetPrivateData(p,a,b,c)	(p)->lpVtbl->GetPrivateData(p,a,b,c)
#define IDirect3DVertexBuffer9_FreePrivateData(p,a)	(p)->lpVtbl->FreePrivateData(p,a)
#define IDirect3DVertexBuffer9_SetPriority(p,a)	(p)->lpVtbl->SetPriority(p,a)
#define IDirect3DVertexBuffer9_GetPriority(p)	(p)->lpVtbl->GetPriority(p)
#define IDirect3DVertexBuffer9_PreLoad(p)	(p)->lpVtbl->PreLoad(p)
#define IDirect3DVertexBuffer9_GetType(p)	(p)->lpVtbl->GetType(p)
#define IDirect3DVertexBuffer9_Lock(p,a,b,c,d)	(p)->lpVtbl->Lock(p,a,b,c,d)
#define IDirect3DVertexBuffer9_Unlock(p)	(p)->lpVtbl->Unlock(p)
#define IDirect3DVertexBuffer9_GetDesc(p,a)	(p)->lpVtbl->GetDesc(p,a)
#else
#define IDirect3DVertexBuffer9_QueryInterface(p,a,b)	(p)->QueryInterface(a,b)
#define IDirect3DVertexBuffer9_AddRef(p)	(p)->AddRef()
#define IDirect3DVertexBuffer9_Release(p)	(p)->Release()
#define IDirect3DVertexBuffer9_GetDevice(p,a)	(p)->GetDevice(a)
#define IDirect3DVertexBuffer9_SetPrivateData(p,a,b,c,d)	(p)->SetPrivateData(a,b,c,d)
#define IDirect3DVertexBuffer9_GetPrivateData(p,a,b,c)	(p)->GetPrivateData(a,b,c)
#define IDirect3DVertexBuffer9_FreePrivateData(p,a)	(p)->FreePrivateData(a)
#define IDirect3DVertexBuffer9_SetPriority(p,a)	(p)->SetPriority(a)
#define IDirect3DVertexBuffer9_GetPriority(p)	(p)->GetPriority()
#define IDirect3DVertexBuffer9_PreLoad(p)	(p)->PreLoad()
#define IDirect3DVertexBuffer9_GetType(p)	(p)->GetType()
#define IDirect3DVertexBuffer9_Lock(p,a,b,c,d)	(p)->Lock(a,b,c,d)
#define IDirect3DVertexBuffer9_Unlock(p)	(p)->Unlock()
#define IDirect3DVertexBuffer9_GetDesc(p,a)	(p)->GetDesc(a)
#endif

#undef INTERFACE
#define INTERFACE IDirect3DIndexBuffer9
DECLARE_INTERFACE_(IDirect3DIndexBuffer9,IDirect3DResource9)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9**) PURE;
	STDMETHOD(SetPrivateData)(THIS_ REFGUID,CONST void*,DWORD,DWORD) PURE;
	STDMETHOD(GetPrivateData)(THIS_ REFGUID,void*,DWORD*) PURE;
	STDMETHOD(FreePrivateData)(THIS_ REFGUID) PURE;
	STDMETHOD_(DWORD,SetPriority)(THIS_ DWORD) PURE;
	STDMETHOD_(DWORD,GetPriority)(THIS) PURE;
	STDMETHOD_(void,PreLoad)(THIS) PURE;
	STDMETHOD_(D3DRESOURCETYPE,GetType)(THIS) PURE;
	STDMETHOD(Lock)(THIS_ UINT,UINT,void**,DWORD) PURE;
	STDMETHOD(Unlock)(THIS) PURE;
	STDMETHOD(GetDesc)(THIS_ D3DINDEXBUFFER_DESC*) PURE;
};
typedef struct IDirect3DIndexBuffer9 *LPDIRECT3DINDEXBUFFER9, *PDIRECT3DINDEXBUFFER9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DIndexBuffer9_QueryInterface(p,a,b)	(p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DIndexBuffer9_AddRef(p)	(p)->lpVtbl->AddRef(p)
#define IDirect3DIndexBuffer9_Release(p)	(p)->lpVtbl->Release(p)
#define IDirect3DIndexBuffer9_GetDevice(p,a)	(p)->lpVtbl->GetDevice(p,a)
#define IDirect3DIndexBuffer9_SetPrivateData(p,a,b,c,d)	(p)->lpVtbl->SetPrivateData(p,a,b,c,d)
#define IDirect3DIndexBuffer9_GetPrivateData(p,a,b,c)	(p)->lpVtbl->GetPrivateData(p,a,b,c)
#define IDirect3DIndexBuffer9_FreePrivateData(p,a)	(p)->lpVtbl->FreePrivateData(p,a)
#define IDirect3DIndexBuffer9_SetPriority(p,a)	(p)->lpVtbl->SetPriority(p,a)
#define IDirect3DIndexBuffer9_GetPriority(p)	(p)->lpVtbl->GetPriority(p)
#define IDirect3DIndexBuffer9_PreLoad(p)	(p)->lpVtbl->PreLoad(p)
#define IDirect3DIndexBuffer9_GetType(p)	(p)->lpVtbl->GetType(p)
#define IDirect3DIndexBuffer9_Lock(p,a,b,c,d)	(p)->lpVtbl->Lock(p,a,b,c,d)
#define IDirect3DIndexBuffer9_Unlock(p)	(p)->lpVtbl->Unlock(p)
#define IDirect3DIndexBuffer9_GetDesc(p,a)	(p)->lpVtbl->GetDesc(p,a)
#else
#define IDirect3DIndexBuffer9_QueryInterface(p,a,b)	(p)->QueryInterface(a,b)
#define IDirect3DIndexBuffer9_AddRef(p)	(p)->AddRef()
#define IDirect3DIndexBuffer9_Release(p)	(p)->Release()
#define IDirect3DIndexBuffer9_GetDevice(p,a)	(p)->GetDevice(a)
#define IDirect3DIndexBuffer9_SetPrivateData(p,a,b,c,d)	(p)->SetPrivateData(a,b,c,d)
#define IDirect3DIndexBuffer9_GetPrivateData(p,a,b,c)	(p)->GetPrivateData(a,b,c)
#define IDirect3DIndexBuffer9_FreePrivateData(p,a)	(p)->FreePrivateData(a)
#define IDirect3DIndexBuffer9_SetPriority(p,a)	(p)->SetPriority(a)
#define IDirect3DIndexBuffer9_GetPriority(p)	(p)->GetPriority()
#define IDirect3DIndexBuffer9_PreLoad(p)	(p)->PreLoad()
#define IDirect3DIndexBuffer9_GetType(p)	(p)->GetType()
#define IDirect3DIndexBuffer9_Lock(p,a,b,c,d)	(p)->Lock(a,b,c,d)
#define IDirect3DIndexBuffer9_Unlock(p)	(p)->Unlock()
#define IDirect3DIndexBuffer9_GetDesc(p,a)	(p)->GetDesc(a)
#endif

#undef INTERFACE
#define INTERFACE IDirect3DBaseTexture9
DECLARE_INTERFACE_(IDirect3DBaseTexture9,IDirect3DResource9)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9**) PURE;
	STDMETHOD(SetPrivateData)(THIS_ REFGUID,CONST void*,DWORD,DWORD) PURE;
	STDMETHOD(GetPrivateData)(THIS_ REFGUID,void*,DWORD*) PURE;
	STDMETHOD(FreePrivateData)(THIS_ REFGUID) PURE;
	STDMETHOD_(DWORD,SetPriority)(THIS_ DWORD) PURE;
	STDMETHOD_(DWORD,GetPriority)(THIS) PURE;
	STDMETHOD_(void,PreLoad)(THIS) PURE;
	STDMETHOD_(D3DRESOURCETYPE,GetType)(THIS) PURE;
	STDMETHOD_(DWORD,SetLOD)(THIS_ DWORD) PURE;
	STDMETHOD_(DWORD,GetLOD)(THIS) PURE;
	STDMETHOD_(DWORD,GetLevelCount)(THIS) PURE;
	STDMETHOD(SetAutoGenFilterType)(THIS_ D3DTEXTUREFILTERTYPE) PURE;
	STDMETHOD_(D3DTEXTUREFILTERTYPE,GetAutoGenFilterType)(THIS) PURE;
	STDMETHOD_(void,GenerateMipSubLevels)(THIS) PURE;
};
typedef struct IDirect3DBaseTexture9 *LPDIRECT3DBASETEXTURE9, *PDIRECT3DBASETEXTURE9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DBaseTexture9_QueryInterface(p,a,b)	(p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DBaseTexture9_AddRef(p)	(p)->lpVtbl->AddRef(p)
#define IDirect3DBaseTexture9_Release(p)	(p)->lpVtbl->Release(p)
#define IDirect3DBaseTexture9_GetDevice(p,a)	(p)->lpVtbl->GetDevice(p,a)
#define IDirect3DBaseTexture9_SetPrivateData(p,a,b,c,d)	(p)->lpVtbl->SetPrivateData(p,a,b,c,d)
#define IDirect3DBaseTexture9_GetPrivateData(p,a,b,c)	(p)->lpVtbl->GetPrivateData(p,a,b,c)
#define IDirect3DBaseTexture9_FreePrivateData(p,a)	(p)->lpVtbl->FreePrivateData(p,a)
#define IDirect3DBaseTexture9_SetPriority(p,a)	(p)->lpVtbl->SetPriority(p,a)
#define IDirect3DBaseTexture9_GetPriority(p)	(p)->lpVtbl->GetPriority(p)
#define IDirect3DBaseTexture9_PreLoad(p)	(p)->lpVtbl->PreLoad(p)
#define IDirect3DBaseTexture9_GetType(p)	(p)->lpVtbl->GetType(p)
#define IDirect3DBaseTexture9_SetLOD(p,a)	(p)->lpVtbl->SetLOD(p,a)
#define IDirect3DBaseTexture9_GetLOD(p)	(p)->lpVtbl->GetLOD(p)
#define IDirect3DBaseTexture9_GetLevelCount(p)	(p)->lpVtbl->GetLevelCount(p)
#define IDirect3DBaseTexture9_SetAutoGenFilterType(p,a)	(p)->lpVtbl->SetAutoGenFilterType(p,a)
#define IDirect3DBaseTexture9_GetAutoGenFilterType(p)	(p)->lpVtbl->GetAutoGenFilterType(p)
#define IDirect3DBaseTexture9_GenerateMipSubLevels(p)	(p)->lpVtbl->GenerateMipSubLevels(p)
#else
#define IDirect3DBaseTexture9_QueryInterface(p,a,b)	(p)->QueryInterface(a,b)
#define IDirect3DBaseTexture9_AddRef(p)	(p)->AddRef()
#define IDirect3DBaseTexture9_Release(p)	(p)->Release()
#define IDirect3DBaseTexture9_GetDevice(p,a)	(p)->GetDevice(a)
#define IDirect3DBaseTexture9_SetPrivateData(p,a,b,c,d)	(p)->SetPrivateData(a,b,c,d)
#define IDirect3DBaseTexture9_GetPrivateData(p,a,b,c)	(p)->GetPrivateData(a,b,c)
#define IDirect3DBaseTexture9_FreePrivateData(p,a)	(p)->FreePrivateData(a)
#define IDirect3DBaseTexture9_SetPriority(p,a)	(p)->SetPriority(a)
#define IDirect3DBaseTexture9_GetPriority(p)	(p)->GetPriority()
#define IDirect3DBaseTexture9_PreLoad(p)	(p)->PreLoad()
#define IDirect3DBaseTexture9_GetType(p)	(p)->GetType()
#define IDirect3DBaseTexture9_SetLOD(p,a)	(p)->SetLOD(a)
#define IDirect3DBaseTexture9_GetLOD(p)	(p)->GetLOD()
#define IDirect3DBaseTexture9_GetLevelCount(p)	(p)->GetLevelCount()
#define IDirect3DBaseTexture9_SetAutoGenFilterType(p,a)	(p)->SetAutoGenFilterType(a)
#define IDirect3DBaseTexture9_GetAutoGenFilterType(p)	(p)->GetAutoGenFilterType()
#define IDirect3DBaseTexture9_GenerateMipSubLevels(p)	(p)->GenerateMipSubLevels()
#endif

#undef INTERFACE
#define INTERFACE IDirect3DCubeTexture9
DECLARE_INTERFACE_(IDirect3DCubeTexture9,IDirect3DBaseTexture9)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9**) PURE;
	STDMETHOD(SetPrivateData)(THIS_ REFGUID,CONST void*,DWORD,DWORD) PURE;
	STDMETHOD(GetPrivateData)(THIS_ REFGUID,void*,DWORD*) PURE;
	STDMETHOD(FreePrivateData)(THIS_ REFGUID) PURE;
	STDMETHOD_(DWORD,SetPriority)(THIS_ DWORD) PURE;
	STDMETHOD_(DWORD,GetPriority)(THIS) PURE;
	STDMETHOD_(void,PreLoad)(THIS) PURE;
	STDMETHOD_(D3DRESOURCETYPE,GetType)(THIS) PURE;
	STDMETHOD_(DWORD,SetLOD)(THIS_ DWORD) PURE;
	STDMETHOD_(DWORD,GetLOD)(THIS) PURE;
	STDMETHOD_(DWORD,GetLevelCount)(THIS) PURE;
	STDMETHOD(SetAutoGenFilterType)(THIS_ D3DTEXTUREFILTERTYPE) PURE;
	STDMETHOD_(D3DTEXTUREFILTERTYPE,GetAutoGenFilterType)(THIS) PURE;
	STDMETHOD_(void,GenerateMipSubLevels)(THIS) PURE;
	STDMETHOD(GetLevelDesc)(THIS_ UINT,D3DSURFACE_DESC*) PURE; \
	STDMETHOD(GetCubeMapSurface)(THIS_ D3DCUBEMAP_FACES,UINT,IDirect3DSurface9**) PURE; \
	STDMETHOD(LockRect)(THIS_ D3DCUBEMAP_FACES,UINT,D3DLOCKED_RECT*,CONST RECT*,DWORD) PURE; \
	STDMETHOD(UnlockRect)(THIS_ D3DCUBEMAP_FACES,UINT) PURE; \
	STDMETHOD(AddDirtyRect)(THIS_ D3DCUBEMAP_FACES,CONST RECT*) PURE;
};
typedef struct IDirect3DCubeTexture9 *LPDIRECT3DCUBETEXTURE9, *PDIRECT3DCUBETEXTURE9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DCubeTexture9_QueryInterface(p,a,b)	(p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DCubeTexture9_AddRef(p)	(p)->lpVtbl->AddRef(p)
#define IDirect3DCubeTexture9_Release(p)	(p)->lpVtbl->Release(p)
#define IDirect3DCubeTexture9_GetDevice(p,a)	(p)->lpVtbl->GetDevice(p,a)
#define IDirect3DCubeTexture9_SetPrivateData(p,a,b,c,d)	(p)->lpVtbl->SetPrivateData(p,a,b,c,d)
#define IDirect3DCubeTexture9_GetPrivateData(p,a,b,c)	(p)->lpVtbl->GetPrivateData(p,a,b,c)
#define IDirect3DCubeTexture9_FreePrivateData(p,a)	(p)->lpVtbl->FreePrivateData(p,a)
#define IDirect3DCubeTexture9_SetPriority(p,a)	(p)->lpVtbl->SetPriority(p,a)
#define IDirect3DCubeTexture9_GetPriority(p)	(p)->lpVtbl->GetPriority(p)
#define IDirect3DCubeTexture9_PreLoad(p)	(p)->lpVtbl->PreLoad(p)
#define IDirect3DCubeTexture9_GetType(p)	(p)->lpVtbl->GetType(p)
#define IDirect3DCubeTexture9_SetLOD(p,a)	(p)->lpVtbl->SetLOD(p,a)
#define IDirect3DCubeTexture9_GetLOD(p)	(p)->lpVtbl->GetLOD(p)
#define IDirect3DCubeTexture9_GetLevelCount(p)	(p)->lpVtbl->GetLevelCount(p)
#define IDirect3DCubeTexture9_SetAutoGenFilterType(p,a)	(p)->lpVtbl->SetAutoGenFilterType(p,a)
#define IDirect3DCubeTexture9_GetAutoGenFilterType(p)	(p)->lpVtbl->GetAutoGenFilterType(p)
#define IDirect3DCubeTexture9_GenerateMipSubLevels(p)	(p)->lpVtbl->GenerateMipSubLevels(p)
#define IDirect3DCubeTexture9_GetLevelDesc(p,a,b)	(p)->lpVtbl->GetLevelDesc(p,a,b)
#define IDirect3DCubeTexture9_GetCubeMapSurface(p,a,b,c)	(p)->lpVtbl->GetCubeMapSurface(p,a,b,c)
#define IDirect3DCubeTexture9_LockRect(p,a,b,c,d,e)	(p)->lpVtbl->LockRect(p,a,b,c,d,e)
#define IDirect3DCubeTexture9_UnlockRect(p,a,b)	(p)->lpVtbl->UnlockRect(p,a,b)
#define IDirect3DCubeTexture9_AddDirtyRect(p,a,b)	(p)->lpVtbl->AddDirtyRect(p,a,b)
#else
#define IDirect3DCubeTexture9_QueryInterface(p,a,b)	(p)->QueryInterface(a,b)
#define IDirect3DCubeTexture9_AddRef(p)	(p)->AddRef()
#define IDirect3DCubeTexture9_Release(p)	(p)->Release()
#define IDirect3DCubeTexture9_GetDevice(p,a)	(p)->GetDevice(a)
#define IDirect3DCubeTexture9_SetPrivateData(p,a,b,c,d)	(p)->SetPrivateData(a,b,c,d)
#define IDirect3DCubeTexture9_GetPrivateData(p,a,b,c)	(p)->GetPrivateData(a,b,c)
#define IDirect3DCubeTexture9_FreePrivateData(p,a)	(p)->FreePrivateData(a)
#define IDirect3DCubeTexture9_SetPriority(p,a)	(p)->SetPriority(a)
#define IDirect3DCubeTexture9_GetPriority(p)	(p)->GetPriority()
#define IDirect3DCubeTexture9_PreLoad(p)	(p)->PreLoad()
#define IDirect3DCubeTexture9_GetType(p)	(p)->GetType()
#define IDirect3DCubeTexture9_SetLOD(p,a)	(p)->SetLOD(a)
#define IDirect3DCubeTexture9_GetLOD(p)	(p)->GetLOD()
#define IDirect3DCubeTexture9_GetLevelCount(p)	(p)->GetLevelCount()
#define IDirect3DCubeTexture9_SetAutoGenFilterType(p,a)	(p)->SetAutoGenFilterType(a)
#define IDirect3DCubeTexture9_GetAutoGenFilterType(p)	(p)->GetAutoGenFilterType()
#define IDirect3DCubeTexture9_GenerateMipSubLevels(p)	(p)->GenerateMipSubLevels()
#define IDirect3DCubeTexture9_GetLevelDesc(p,a,b)	(p)->GetLevelDesc(a,b)
#define IDirect3DCubeTexture9_GetCubeMapSurface(p,a,b,c)	(p)->GetCubeMapSurface(a,b,c)
#define IDirect3DCubeTexture9_LockRect(p,a,b,c,d,e)	(p)->LockRect(a,b,c,d,e)
#define IDirect3DCubeTexture9_UnlockRect(p,a,b)	(p)->UnlockRect(a,b)
#define IDirect3DCubeTexture9_AddDirtyRect(p,a,b)	(p)->AddDirtyRect(a,b)
#endif

#undef INTERFACE
#define INTERFACE IDirect3DTexture9
DECLARE_INTERFACE_(IDirect3DTexture9,IDirect3DBaseTexture9)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9**) PURE;
	STDMETHOD(SetPrivateData)(THIS_ REFGUID,CONST void*,DWORD,DWORD) PURE;
	STDMETHOD(GetPrivateData)(THIS_ REFGUID,void*,DWORD*) PURE;
	STDMETHOD(FreePrivateData)(THIS_ REFGUID) PURE;
	STDMETHOD_(DWORD,SetPriority)(THIS_ DWORD) PURE;
	STDMETHOD_(DWORD,GetPriority)(THIS) PURE;
	STDMETHOD_(void,PreLoad)(THIS) PURE;
	STDMETHOD_(D3DRESOURCETYPE,GetType)(THIS) PURE;
	STDMETHOD_(DWORD,SetLOD)(THIS_ DWORD) PURE;
	STDMETHOD_(DWORD,GetLOD)(THIS) PURE;
	STDMETHOD_(DWORD,GetLevelCount)(THIS) PURE;
	STDMETHOD(SetAutoGenFilterType)(THIS_ D3DTEXTUREFILTERTYPE) PURE;
	STDMETHOD_(D3DTEXTUREFILTERTYPE,GetAutoGenFilterType)(THIS) PURE;
	STDMETHOD_(void,GenerateMipSubLevels)(THIS) PURE;
	STDMETHOD(GetLevelDesc)(THIS_ UINT,D3DSURFACE_DESC*) PURE;
	STDMETHOD(GetSurfaceLevel)(THIS_ UINT,IDirect3DSurface9**) PURE;
	STDMETHOD(LockRect)(THIS_ UINT,D3DLOCKED_RECT*,CONST RECT*,DWORD) PURE;
	STDMETHOD(UnlockRect)(THIS_ UINT) PURE;
	STDMETHOD(AddDirtyRect)(THIS_ CONST RECT*) PURE;
};
typedef struct IDirect3DTexture9 *LPDIRECT3DTEXTURE9, *PDIRECT3DTEXTURE9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DTexture9_QueryInterface(p,a,b)	(p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DTexture9_AddRef(p)	(p)->lpVtbl->AddRef(p)
#define IDirect3DTexture9_Release(p)	(p)->lpVtbl->Release(p)
#define IDirect3DTexture9_GetDevice(p,a)	(p)->lpVtbl->GetDevice(p,a)
#define IDirect3DTexture9_SetPrivateData(p,a,b,c,d)	(p)->lpVtbl->SetPrivateData(p,a,b,c,d)
#define IDirect3DTexture9_GetPrivateData(p,a,b,c)	(p)->lpVtbl->GetPrivateData(p,a,b,c)
#define IDirect3DTexture9_FreePrivateData(p,a)	(p)->lpVtbl->FreePrivateData(p,a)
#define IDirect3DTexture9_SetPriority(p,a)	(p)->lpVtbl->SetPriority(p,a)
#define IDirect3DTexture9_GetPriority(p)	(p)->lpVtbl->GetPriority(p)
#define IDirect3DTexture9_PreLoad(p)	(p)->lpVtbl->PreLoad(p)
#define IDirect3DTexture9_GetType(p)	(p)->lpVtbl->GetType(p)
#define IDirect3DTexture9_SetLOD(p,a)	(p)->lpVtbl->SetLOD(p,a)
#define IDirect3DTexture9_GetLOD(p)	(p)->lpVtbl->GetLOD(p)
#define IDirect3DTexture9_GetLevelCount(p)	(p)->lpVtbl->GetLevelCount(p)
#define IDirect3DTexture9_SetAutoGenFilterType(p,a)	(p)->lpVtbl->SetAutoGenFilterType(p,a)
#define IDirect3DTexture9_GetAutoGenFilterType(p)	(p)->lpVtbl->GetAutoGenFilterType(p)
#define IDirect3DTexture9_GenerateMipSubLevels(p)	(p)->lpVtbl->GenerateMipSubLevels(p)
#define IDirect3DTexture9_GetLevelDesc(p,a,b)	(p)->lpVtbl->GetLevelDesc(p,a,b)
#define IDirect3DTexture9_GetSurfaceLevel(p,a,b)	(p)->lpVtbl->GetSurfaceLevel(p,a,b)
#define IDirect3DTexture9_LockRect(p,a,b,c,d)	(p)->lpVtbl->LockRect(p,a,b,c,d)
#define IDirect3DTexture9_UnlockRect(p,a)	(p)->lpVtbl->UnlockRect(p,a)
#define IDirect3DTexture9_AddDirtyRect(p,a)	(p)->lpVtbl->AddDirtyRect(p,a)
#else
#define IDirect3DTexture9_QueryInterface(p,a,b)	(p)->QueryInterface(a,b)
#define IDirect3DTexture9_AddRef(p)	(p)->AddRef()
#define IDirect3DTexture9_Release(p)	(p)->Release()
#define IDirect3DTexture9_GetDevice(p,a)	(p)->GetDevice(a)
#define IDirect3DTexture9_SetPrivateData(p,a,b,c,d)	(p)->SetPrivateData(a,b,c,d)
#define IDirect3DTexture9_GetPrivateData(p,a,b,c)	(p)->GetPrivateData(a,b,c)
#define IDirect3DTexture9_FreePrivateData(p,a)	(p)->FreePrivateData(a)
#define IDirect3DTexture9_SetPriority(p,a)	(p)->SetPriority(a)
#define IDirect3DTexture9_GetPriority(p)	(p)->GetPriority()
#define IDirect3DTexture9_PreLoad(p)	(p)->PreLoad()
#define IDirect3DTexture9_GetType(p)	(p)->GetType()
#define IDirect3DTexture9_SetLOD(p,a)	(p)->SetLOD(a)
#define IDirect3DTexture9_GetLOD(p)	(p)->GetLOD()
#define IDirect3DTexture9_GetLevelCount(p)	(p)->GetLevelCount()
#define IDirect3DTexture9_SetAutoGenFilterType(p,a)	(p)->SetAutoGenFilterType(a)
#define IDirect3DTexture9_GetAutoGenFilterType(p)	(p)->GetAutoGenFilterType()
#define IDirect3DTexture9_GenerateMipSubLevels(p)	(p)->GenerateMipSubLevels()
#define IDirect3DTexture9_GetLevelDesc(p,a,b)	(p)->GetLevelDesc(a,b)
#define IDirect3DTexture9_GetSurfaceLevel(p,a,b)	(p)->GetSurfaceLevel(a,b)
#define IDirect3DTexture9_LockRect(p,a,b,c,d)	(p)->LockRect(a,b,c,d)
#define IDirect3DTexture9_UnlockRect(p,a)	(p)->UnlockRect(a)
#define IDirect3DTexture9_AddDirtyRect(p,a)	(p)->AddDirtyRect(a)
#endif

#undef INTERFACE
#define INTERFACE IDirect3DVolumeTexture9
DECLARE_INTERFACE_(IDirect3DVolumeTexture9,IDirect3DBaseTexture9)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9**) PURE;
	STDMETHOD(SetPrivateData)(THIS_ REFGUID,CONST void*,DWORD,DWORD) PURE;
	STDMETHOD(GetPrivateData)(THIS_ REFGUID,void*,DWORD*) PURE;
	STDMETHOD(FreePrivateData)(THIS_ REFGUID) PURE;
	STDMETHOD_(DWORD,SetPriority)(THIS_ DWORD) PURE;
	STDMETHOD_(DWORD,GetPriority)(THIS) PURE;
	STDMETHOD_(void,PreLoad)(THIS) PURE;
	STDMETHOD_(D3DRESOURCETYPE,GetType)(THIS) PURE;
	STDMETHOD_(DWORD,SetLOD)(THIS_ DWORD) PURE;
	STDMETHOD_(DWORD,GetLOD)(THIS) PURE;
	STDMETHOD_(DWORD,GetLevelCount)(THIS) PURE;
	STDMETHOD(SetAutoGenFilterType)(THIS_ D3DTEXTUREFILTERTYPE) PURE;
	STDMETHOD_(D3DTEXTUREFILTERTYPE,GetAutoGenFilterType)(THIS) PURE;
	STDMETHOD_(void,GenerateMipSubLevels)(THIS) PURE;
    STDMETHOD(GetLevelDesc)(THIS_ UINT,D3DVOLUME_DESC*) PURE;
    STDMETHOD(GetVolumeLevel)(THIS_ UINT,IDirect3DVolume9**) PURE;
    STDMETHOD(LockBox)(THIS_ UINT,D3DLOCKED_BOX*,CONST D3DBOX*,DWORD) PURE;
    STDMETHOD(UnlockBox)(THIS_ UINT) PURE;
    STDMETHOD(AddDirtyBox)(THIS_ CONST D3DBOX*) PURE;
};
typedef struct IDirect3DVolumeTexture9 *LPDIRECT3DVOLUMETEXTURE9, *PDIRECT3DVOLUMETEXTURE9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DVolumeTexture9_QueryInterface(p,a,b)	(p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DVolumeTexture9_AddRef(p)	(p)->lpVtbl->AddRef(p)
#define IDirect3DVolumeTexture9_Release(p)	(p)->lpVtbl->Release(p)
#define IDirect3DVolumeTexture9_GetDevice(p,a)	(p)->lpVtbl->GetDevice(p,a)
#define IDirect3DVolumeTexture9_SetPrivateData(p,a,b,c,d)	(p)->lpVtbl->SetPrivateData(p,a,b,c,d)
#define IDirect3DVolumeTexture9_GetPrivateData(p,a,b,c)	(p)->lpVtbl->GetPrivateData(p,a,b,c)
#define IDirect3DVolumeTexture9_FreePrivateData(p,a)	(p)->lpVtbl->FreePrivateData(p,a)
#define IDirect3DVolumeTexture9_SetPriority(p,a)	(p)->lpVtbl->SetPriority(p,a)
#define IDirect3DVolumeTexture9_GetPriority(p)	(p)->lpVtbl->GetPriority(p)
#define IDirect3DVolumeTexture9_PreLoad(p)	(p)->lpVtbl->PreLoad(p)
#define IDirect3DVolumeTexture9_GetType(p)	(p)->lpVtbl->GetType(p)
#define IDirect3DVolumeTexture9_SetLOD(p,a)	(p)->lpVtbl->SetLOD(p,a)
#define IDirect3DVolumeTexture9_GetLOD(p)	(p)->lpVtbl->GetLOD(p)
#define IDirect3DVolumeTexture9_GetLevelCount(p)	(p)->lpVtbl->GetLevelCount(p)
#define IDirect3DVolumeTexture9_SetAutoGenFilterType(p,a)	(p)->lpVtbl->SetAutoGenFilterType(p,a)
#define IDirect3DVolumeTexture9_GetAutoGenFilterType(p)	(p)->lpVtbl->GetAutoGenFilterType(p)
#define IDirect3DVolumeTexture9_GenerateMipSubLevels(p)	(p)->lpVtbl->GenerateMipSubLevels(p)
#define IDirect3DVolumeTexture9_GetLevelDesc(p,a,b)	(p)->lpVtbl->GetLevelDesc(p,a,b)
#define IDirect3DVolumeTexture9_GetVolumeLevel(p,a,b)	(p)->lpVtbl->GetVolumeLevel(p,a,b)
#define IDirect3DVolumeTexture9_LockBox(p,a,b,c,d)	(p)->lpVtbl->LockBox(p,a,b,c,d)
#define IDirect3DVolumeTexture9_UnlockBox(p,a)	(p)->lpVtbl->UnlockBox(p,a)
#define IDirect3DVolumeTexture9_AddDirtyBox(p,a)	(p)->lpVtbl->AddDirtyBox(p,a)
#else
#define IDirect3DVolumeTexture9_QueryInterface(p,a,b)	(p)->QueryInterface(a,b)
#define IDirect3DVolumeTexture9_AddRef(p)	(p)->AddRef()
#define IDirect3DVolumeTexture9_Release(p)	(p)->Release()
#define IDirect3DVolumeTexture9_GetDevice(p,a)	(p)->GetDevice(a)
#define IDirect3DVolumeTexture9_SetPrivateData(p,a,b,c,d)	(p)->SetPrivateData(a,b,c,d)
#define IDirect3DVolumeTexture9_GetPrivateData(p,a,b,c)	(p)->GetPrivateData(a,b,c)
#define IDirect3DVolumeTexture9_FreePrivateData(p,a)	(p)->FreePrivateData(a)
#define IDirect3DVolumeTexture9_SetPriority(p,a)	(p)->SetPriority(a)
#define IDirect3DVolumeTexture9_GetPriority(p)	(p)->GetPriority()
#define IDirect3DVolumeTexture9_PreLoad(p)	(p)->PreLoad()
#define IDirect3DVolumeTexture9_GetType(p)	(p)->GetType()
#define IDirect3DVolumeTexture9_SetLOD(p,a)	(p)->SetLOD(a)
#define IDirect3DVolumeTexture9_GetLOD(p)	(p)->GetLOD()
#define IDirect3DVolumeTexture9_GetLevelCount(p)	(p)->GetLevelCount()
#define IDirect3DVolumeTexture9_SetAutoGenFilterType(p,a)	(p)->SetAutoGenFilterType(a)
#define IDirect3DVolumeTexture9_GetAutoGenFilterType(p)	(p)->GetAutoGenFilterType()
#define IDirect3DVolumeTexture9_GenerateMipSubLevels(p)	(p)->GenerateMipSubLevels()
#define IDirect3DVolumeTexture9_GetLevelDesc(p,a,b)	(p)->GetLevelDesc(a,b)
#define IDirect3DVolumeTexture9_GetVolumeLevel(p,a,b)	(p)->GetVolumeLevel(a,b)
#define IDirect3DVolumeTexture9_LockBox(p,a,b,c,d)	(p)->LockBox(a,b,c,d)
#define IDirect3DVolumeTexture9_UnlockBox(p,a)	(p)->UnlockBox(a)
#define IDirect3DVolumeTexture9_AddDirtyBox(p,a)	(p)->AddDirtyBox(a)
#endif

#undef INTERFACE
#define INTERFACE IDirect3DVertexDeclaration9
DECLARE_INTERFACE_(IDirect3DVertexDeclaration9,IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9**) PURE;
	STDMETHOD(GetDeclaration)(THIS_ D3DVERTEXELEMENT9*,UINT*) PURE;
};
typedef struct IDirect3DVertexDeclaration9 *LPDIRECT3DVERTEXDECLARATION9, *PDIRECT3DVERTEXDECLARATION9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DVertexDeclaration9_QueryInterface(p,a,b)	(p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DVertexDeclaration9_AddRef(p)	(p)->lpVtbl->AddRef(p)
#define IDirect3DVertexDeclaration9_Release(p)	(p)->lpVtbl->Release(p)
#define IDirect3DVertexDeclaration9_GetDevice(p,a)	(p)->lpVtbl->GetDevice(p,a)
#define IDirect3DVertexDeclaration9_GetDeclaration(p,a,b)	(p)->lpVtbl->GetDeclaration(p,a,b)
#else
#define IDirect3DVertexDeclaration9_QueryInterface(p,a,b)	(p)->QueryInterface(a,b)
#define IDirect3DVertexDeclaration9_AddRef(p)	(p)->AddRef()
#define IDirect3DVertexDeclaration9_Release(p)	(p)->Release()
#define IDirect3DVertexDeclaration9_GetDevice(p,a)	(p)->GetDevice(a)
#define IDirect3DVertexDeclaration9_GetDeclaration(p,a,b)	(p)->GetDeclaration(a,b)
#endif

#undef INTERFACE
#define INTERFACE IDirect3DVertexShader9
DECLARE_INTERFACE_(IDirect3DVertexShader9,IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9**) PURE;
	STDMETHOD(GetFunction)(THIS_ void*,UINT*) PURE;
};
typedef struct IDirect3DVertexShader9 *LPDIRECT3DVERTEXSHADER9, *PDIRECT3DVERTEXSHADER9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DVertexShader9_QueryInterface(p,a,b)	(p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DVertexShader9_AddRef(p)	(p)->lpVtbl->AddRef(p)
#define IDirect3DVertexShader9_Release(p)	(p)->lpVtbl->Release(p)
#define IDirect3DVertexShader9_GetDevice(p,a)	(p)->lpVtbl->GetDevice(p,a)
#define IDirect3DVertexShader9_GetFunction(p,a,b)	(p)->lpVtbl->GetFunction(p,a,b)
#else
#define IDirect3DVertexShader9_QueryInterface(p,a,b)	(p)->QueryInterface(a,b)
#define IDirect3DVertexShader9_AddRef(p)	(p)->AddRef()
#define IDirect3DVertexShader9_Release(p)	(p)->Release()
#define IDirect3DVertexShader9_GetDevice(p,a)	(p)->GetDevice(a)
#define IDirect3DVertexShader9_GetFunction(p,a,b)	(p)->GetFunction(a,b)
#endif

#undef INTERFACE
#define INTERFACE IDirect3DPixelShader9
DECLARE_INTERFACE_(IDirect3DPixelShader9,IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9**) PURE;
	STDMETHOD(GetFunction)(THIS_ void*,UINT*) PURE;
};
typedef struct IDirect3DPixelShader9 *LPDIRECT3DPIXELSHADER9, *PDIRECT3DPIXELSHADER9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DPixelShader9_QueryInterface(p,a,b)	(p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DPixelShader9_AddRef(p)	(p)->lpVtbl->AddRef(p)
#define IDirect3DPixelShader9_Release(p)	(p)->lpVtbl->Release(p)
#define IDirect3DPixelShader9_GetDevice(p,a)	(p)->lpVtbl->GetDevice(p,a)
#define IDirect3DPixelShader9_GetFunction(p,a,b)	(p)->lpVtbl->GetFunction(p,a,b)
#else
#define IDirect3DPixelShader9_QueryInterface(p,a,b)	(p)->QueryInterface(a,b)
#define IDirect3DPixelShader9_AddRef(p)	(p)->AddRef()
#define IDirect3DPixelShader9_Release(p)	(p)->Release()
#define IDirect3DPixelShader9_GetDevice(p,a)	(p)->GetDevice(a)
#define IDirect3DPixelShader9_GetFunction(p,a,b)	(p)->GetFunction(a,b)
#endif

#undef INTERFACE
#define INTERFACE IDirect3DStateBlock9
DECLARE_INTERFACE_(IDirect3DStateBlock9,IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9**) PURE;
	STDMETHOD(Capture)(THIS) PURE;
	STDMETHOD(Apply)(THIS) PURE;
};
typedef struct IDirect3DStateBlock9 *LPDIRECT3DSTATEBLOCK9, *PDIRECT3DSTATEBLOCK9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DStateBlock9_QueryInterface(p,a,b)	(p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DStateBlock9_AddRef(p)	(p)->lpVtbl->AddRef(p)
#define IDirect3DStateBlock9_Release(p)	(p)->lpVtbl->Release(p)
#define IDirect3DStateBlock9_GetDevice(p,a)	(p)->lpVtbl->GetDevice(p,a)
#define IDirect3DStateBlock9_Capture(p)	(p)->lpVtbl->Capture(p)
#define IDirect3DStateBlock9_Apply(p)	(p)->lpVtbl->Apply(p)
#else
#define IDirect3DStateBlock9_QueryInterface(p,a,b)	(p)->QueryInterface(a,b)
#define IDirect3DStateBlock9_AddRef(p)	(p)->AddRef()
#define IDirect3DStateBlock9_Release(p)	(p)->Release()
#define IDirect3DStateBlock9_GetDevice(p,a)	(p)->GetDevice(a)
#define IDirect3DStateBlock9_Capture(p)	(p)->Capture()
#define IDirect3DStateBlock9_Apply(p)	(p)->Apply()
#endif

#undef INTERFACE
#define INTERFACE IDirect3DQuery9
DECLARE_INTERFACE_(IDirect3DQuery9,IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9**) PURE;
	STDMETHOD_(D3DQUERYTYPE, GetType)(THIS) PURE;
	STDMETHOD_(DWORD, GetDataSize)(THIS) PURE;
	STDMETHOD(Issue)(THIS_ DWORD) PURE;
	STDMETHOD(GetData)(THIS_ void*,DWORD,DWORD) PURE;
};
typedef struct IDirect3DQuery9 *LPDIRECT3DQUERY9, *PDIRECT3DQUERY9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DQuery9_QueryInterface(p,a,b)	(p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DQuery9_AddRef(p)	(p)->lpVtbl->AddRef(p)
#define IDirect3DQuery9_Release(p)	(p)->lpVtbl->Release(p)
#define IDirect3DQuery9_GetDevice(p,a)	(p)->lpVtbl->GetDevice(p,a)
#define IDirect3DQuery9_GetType(p)	(p)->lpVtbl->GetType(p)
#define IDirect3DQuery9_GetDataSize(p)	(p)->lpVtbl->GetDataSize(p)
#define IDirect3DQuery9_Issue(p,a)	(p)->lpVtbl->Issue(p,a)
#define IDirect3DQuery9_GetData(p,a,b,c)	(p)->lpVtbl->GetData(p,a,b,c)
#else
#define IDirect3DQuery9_QueryInterface(p,a,b)	(p)->QueryInterface(a,b)
#define IDirect3DQuery9_AddRef(p)	(p)->AddRef()
#define IDirect3DQuery9_Release(p)	(p)->Release()
#define IDirect3DQuery9_GetDevice(p,a)	(p)->GetDevice(a)
#define IDirect3DQuery9_GetType(p)	(p)->GetType()
#define IDirect3DQuery9_GetDataSize(p)	(p)->GetDataSize()
#define IDirect3DQuery9_Issue(p,a)	(p)->Issue(a)
#define IDirect3DQuery9_GetData(p,a,b,c)	(p)->GetData(a,b,c)
#endif

#ifdef __cplusplus
extern "C" IDirect3D9* WINAPI Direct3DCreate9(UINT SDKVersion);
#else
extern IDirect3D9* WINAPI Direct3DCreate9(UINT SDKVersion);
#endif

#endif
#endif
