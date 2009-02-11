#ifndef _AVIRIFF_H
#define _AVIRIFF_H
#if __GNUC__ >=3
#pragma GCC system_header
#endif

#ifndef _MMSYSTEM_H
#include <mmsystem.h>
#endif
#ifndef _WINGDI_H
#include <wingdi.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*--- DirectShow Reference - DirectShow Structures */
typedef struct _avimainheader {
	FOURCC fcc;
	DWORD cb;
	DWORD dwMicroSecPerFrame;
	DWORD dwMaxBytesPerSec;
	DWORD dwPaddingGranularity;
	DWORD dwFlags;
	DWORD dwTotalFrames;
	DWORD dwInitialFrames;
	DWORD dwStreams;
	DWORD dwSuggestedBufferSize;
	DWORD dwWidth;
	DWORD dwHeight;
	DWORD dwReserved[4];
} AVIMAINHEADER;
#define AVIF_COPYRIGHTED 0x00020000
#define AVIF_HASINDEX 0x00000010
#define AVIF_ISINTERLEAVED 0x00000100
#define AVIF_MUSTUSEINDEX 0x00000020
#define AVIF_WASCAPTUREFILE 0x00010000
typedef struct _avioldindex {
	FOURCC fcc;
	DWORD cb;
	struct _avioldindex_entry {
		DWORD dwChunkId;
		DWORD dwFlags;
		DWORD dwOffset;
		DWORD dwSize;
	} aIndex[];
} AVIOLDINDEX;
#define AVIIF_LIST 0x00000001
#define AVIIF_KEYFRAME 0x00000010
#define AVIIF_NO_TIME 0x00000100
typedef struct {
	BYTE bFirstEntry;
	BYTE bNumEntries;
	WORD wFlags;
	PALETTEENTRY peNew[];
} AVIPALCHANGE;
typedef struct _avistreamheader {
	FOURCC fcc;
	DWORD cb;
	FOURCC fccType;
	FOURCC fccHandler;
	DWORD dwFlags;
	WORD wPriority;
	WORD wLanguage;
	DWORD dwInitialFrames;
	DWORD dwScale;
	DWORD dwRate;
	DWORD dwStart;
	DWORD dwLength;
	DWORD dwSuggestedBufferSize;
	DWORD dwQuality;
	DWORD dwSampleSize;
	struct {
		short int left;
		short int top;
		short int right;
		short int bottom;
	} rcFrame;
} AVISTREAMHEADER;
#define AVISF_DISABLED 0x00000001
#define AVISF_VIDEO_PALCHANGES 0x00010000

#ifdef __cplusplus
}
#endif
#endif
