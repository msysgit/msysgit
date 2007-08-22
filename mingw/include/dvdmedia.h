#ifndef _DVDMEDIA_H
#define _DVDMEDIA_H
#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#ifndef _STRMIF_H
#include <strmif.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*--- DirectShow Reference - DirectShow Structures - AM_SAMPLE2_PROPERTIES Structure */
#define AM_VIDEO_FLAG_FIELD_MASK 0x0003
#define AM_VIDEO_FLAG_INTERLEAVED_FRAME 0x0000
#define AM_VIDEO_FLAG_FIELD1 0x0001
#define AM_VIDEO_FLAG_FIELD2 0x0002
#define AM_VIDEO_FLAG_FIELD1FIRST 0x0004
#define AM_VIDEO_FLAG_WEAVE 0x0008
#define AM_VIDEO_FLAG_REPEAT_FIELD 0x0040
/*--- DirectShow Reference - DirectShow Enumerated Types */
enum AM_MPEG2Level {
	AM_MPEG2Level_Low = 1,
	AM_MPEG2Level_Main,
	AM_MPEG2Level_High1440,
	AM_MPEG2Level_High
};
enum AM_MPEG2Profile {
	AM_MPEG2Profile_Simple = 1,
	AM_MPEG2Profile_Main,
	AM_MPEG2Profile_SNRScalable,
	AM_MPEG2Profile_SpatiallyScalable,
	AM_MPEG2Profile_High
};
typedef enum {
	AM_RATE_ChangeRate = 1,
	AM_RATE_FullDataRateMax = 2,
	AM_RATE_ReverseDecode = 3,
	AM_RATE_DecoderPosition = 4,
	AM_RATE_DecoderVersion = 5
} AM_PROPERTY_DVD_RATE_CHANGE;
/*--- DirectShow Reference - DirectShow Structures */
typedef struct tagVIDEOINFOHEADER2 {
	RECT rcSource;
	RECT rcTarget;
	DWORD dwBitRate;
	DWORD dwBitErrorRate;
	REFERENCE_TIME AvgTimePerFrame;
	DWORD dwInterlaceFlags;
	DWORD dwCopyProtectFlags;
	DWORD dwPictAspectRatioX; 
	DWORD dwPictAspectRatioY; 
	union {
		DWORD dwControlFlags;
		DWORD dwReserved1;
	};
	DWORD dwReserved2;
	BITMAPINFOHEADER bmiHeader;
} VIDEOINFOHEADER2;
#define AMINTERLACE_IsInterlaced 0x00000001
#define AMINTERLACE_1FieldPerSample 0x00000002
#define AMINTERLACE_Field1First 0x00000004
#define AMINTERLACE_FieldPatField1Only 0x00000000
#define AMINTERLACE_FieldPatField2Only 0x00000010
#define AMINTERLACE_FieldPatBothRegular 0x00000020
#define AMINTERLACE_FieldPatBothIrregular 0x00000030
#define AMINTERLACE_DisplayModeBobOnly 0x00000000
#define AMINTERLACE_DisplayModeWeaveOnly 0x00000040
#define AMINTERLACE_DisplayModeBobOrWeave 0x00000080
#define AMINTERLACE_FieldPatternMask 0x00000030
#define AMINTERLACE_DisplayModeMask 0x000000C0
#define AMCONTROL_USED 0x00000001
#define AMCONTROL_PAD_TO_4x3 0x00000002
#define AMCONTROL_PAD_TO_16x9 0x00000004
#define AMCONTROL_COLORINFO_PRESENT 0x00000008
typedef struct tagMPEG2VIDEOINFO {
	VIDEOINFOHEADER2 hdr;
	DWORD dwStartTimeCode;
	DWORD cbSequenceHeader;
	DWORD dwProfile;
	DWORD dwLevel;
	DWORD dwFlags;
	DWORD dwSequenceHeader[1];
} MPEG2VIDEOINFO;
#define AMMPEG2_DoPanScan 0x00000001
#define AMMPEG2_DVDLine21Field1 0x00000002
#define AMMPEG2_DVDLine21Field2 0x00000004
#define AMMPEG2_SourceIsLetterboxed 0x00000008
#define AMMPEG2_FilmCameraMode 0x00000010
#define AMMPEG2_LetterboxAnalogOut 0x00000020
#define AMMPEG2_DSS_UserData 0x00000040
#define AMMPEG2_DVB_UserData 0x00000080
#define AMMPEG2_27MhzTimebase 0x00000100
#define AMMPEG2_WidescreenAnalogOut 0x00000200

#ifdef __cplusplus
}
#endif
#endif
