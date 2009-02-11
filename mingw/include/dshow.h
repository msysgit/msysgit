#ifndef _DSHOW_H
#define _DSHOW_H
#if __GNUC__ >=3
#pragma GCC system_header
#endif

#include <strmif.h>
#include <amaudio.h>
#include <amvideo.h>
#include <evcode.h>
#include <audevcod.h>
#include <dvdevcod.h>
#include <errors.h>
#include <vptype.h>
#include <ks.h>
#include <vidcap.h>
#include <bdatypes.h>
#include <dvdmedia.h>
#include <il21dec.h>
#include <ddraw.h> /* DDSCAPS2, DDPIXELFORMAT */
#ifndef _WINGDI_H
#include <wingdi.h> /* BITMAPINFOHEADER */
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*--- DirectShow Reference - DirectShow Enumerated Types */
typedef enum _AM_ASPECT_RATIO_MODE {
	AM_ARMODE_STRETCHED,
	AM_ARMODE_LETTER_BOX,
	AM_ARMODE_CROP,
	AM_ARMODE_STRETCHED_AS_PRIMARY
} AM_ASPECT_RATIO_MODE;
typedef enum _AM_WST_DRAWBGMODE {
	AM_WST_DRAWBGMODE_Opaque,
	AM_WST_DRAWBGMODE_Transparent
} AM_WST_DRAWBGMODE,*PAM_WST_DRAWBGMODE;
typedef enum _AM_WST_LEVEL {
	AM_WST_LEVEL_1_5 = 0
} AM_WST_LEVEL,*PAM_WST_LEVEL;
typedef enum _AM_WST_SERVICE {
	AM_WST_SERVICE_None = 0,
	AM_WST_SERVICE_Text,
	AM_WST_SERVICE_IDS,
	AM_WST_SERVICE_Invalid
} AM_WST_SERVICE,*PAM_WST_SERVICE;
typedef enum _AM_WST_STATE {
	AM_WST_STATE_Off = 0,
	AM_WST_STATE_On
} AM_WST_STATE,*PAM_WST_STATE;
typedef enum _AM_WST_STYLE {
	AM_WST_STYLE_None = 0,
	AM_WST_STYLE_Invers
} AM_WST_STYLE,*PAM_WST_STYLE;
typedef enum {
	AM_EXSEEK_CANSEEK= 1,
	AM_EXSEEK_CANSCAN = 2,
	AM_EXSEEK_MARKERSEEK = 4,
	AM_EXSEEK_SCANWITHOUTCLOCK = 8,
	AM_EXSEEK_NOSTANDARDREPAINT = 16,
	AM_EXSEEK_BUFFERING = 32,
	AM_EXSEEK_SENDS_VIDEOFRAMEREADY = 64
} AMExtendedSeekingCapabilities;
/*--- DirectShow Reference - DirectShow Structures */
typedef struct _AM_WST_PAGE {
	DWORD dwPageNr;
	DWORD dwSubPageNr;
	BYTE *pucPageData;
} AM_WST_PAGE,*PAM_WST_PAGE;
typedef struct _tag_AMVABeginFrameInfo{
	DWORD dwDestSurfaceIndex;
	LPVOID pInputData;
	DWORD dwSizeInputData;
	LPVOID pOutputData;
	DWORD dwSizeOutputData;
 } AMVABeginFrameInfo,*LPAMVABeginFrameInfo;
typedef struct _tag_AMVACompBufferInfo{
	DWORD dwNumCompBuffers;
	DWORD dwWidthToCreate;
	DWORD dwHeightToCreate;
	DWORD dwBytesToAllocate;
	DDSCAPS2 ddCompCaps;
	DDPIXELFORMAT ddPixelFormat;
} AMVACompBufferInfo,*LPAMVACompBufferInfo;
typedef struct _tag_AMVAEndFrameInfo{
	DWORD dwSizeMiscData;
	LPVOID pMiscData;
} AMVAEndFrameInfo,*LPAMVAEndFrameInfo;
typedef struct _tag_AMVAInternalMemInfo{
	DWORD dwScratchMemAlloc;
} AMVAInternalMemInfo,*LPAMVAInternalMemInfo;
typedef struct _tag_AMVAUncompBufferInfo{
	DWORD dwMinNumSurfaces;
	DWORD dwMaxNumSurfaces;
	DDPIXELFORMAT ddUncompPixelFormat;
} AMVAUncompBufferInfo,*LPAMVAUncompBufferInfo;
 typedef struct _tag_AMVAUncompDataInfo{
	DWORD dwUncompWidth;
	DWORD dwUncompHeight;
	DDPIXELFORMAT ddUncompPixelFormat;
} AMVAUncompDataInfo,*LPAMVAUncompDataInfo;

#ifdef __cplusplus
}
#endif
#endif
