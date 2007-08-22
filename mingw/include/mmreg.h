#ifndef _MMREG_H
#define _MMREG_H
#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#ifndef _MMSYSTEM_H
#include <mmsystem.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*--- DirectShow Reference - DirectShow Structures */
typedef struct mpeg1waveformat_tag {
	WAVEFORMATEX wfx;
	WORD fwHeadLayer;
	DWORD dwHeadBitrate;
	WORD fwHeadMode;
	WORD fwHeadModeExt;
	WORD wHeadEmphasis;
	WORD fwHeadFlags;
	DWORD dwPTSLow;
	DWORD dwPTSHigh;
} MPEG1WAVEFORMAT;
#define ACM_MPEG_LAYER1 0x0001
#define ACM_MPEG_LAYER2 0x0002
#define ACM_MPEG_LAYER3 0x0004
#define ACM_MPEG_STEREO 0x0001
#define ACM_MPEG_JOINTSTEREO 0x0002
#define ACM_MPEG_DUALCHANNEL 0x0004
#define ACM_MPEG_SINGLECHANNEL 0x0008
#define ACM_MPEG_PRIVATEBIT 0x0001
#define ACM_MPEG_COPYRIGHT 0x0002
#define ACM_MPEG_ORIGINALHOME 0x0004
#define ACM_MPEG_PROTECTIONBIT 0x0008
#define ACM_MPEG_ID_MPEG1 0x0010
typedef struct {
	WAVEFORMATEX Format;
	union {
		WORD wValidBitsPerSample;
		WORD wSamplesPerBlock;
		WORD wReserved;
	} Samples;
	DWORD dwChannelMask; 
	GUID SubFormat;
} WAVEFORMATEXTENSIBLE,*PWAVEFORMATEXTENSIBLE;
#define SPEAKER_FRONT_LEFT 0x1
#define SPEAKER_FRONT_RIGHT 0x2
#define SPEAKER_FRONT_CENTER 0x4
#define SPEAKER_LOW_FREQUENCY 0x8
#define SPEAKER_BACK_LEFT 0x10
#define SPEAKER_BACK_RIGHT 0x20
#define SPEAKER_FRONT_LEFT_OF_CENTER 0x40
#define SPEAKER_FRONT_RIGHT_OF_CENTER 0x80
#define SPEAKER_BACK_CENTER 0x100
#define SPEAKER_SIDE_LEFT 0x200
#define SPEAKER_SIDE_RIGHT 0x400
#define SPEAKER_TOP_CENTER 0x800
#define SPEAKER_TOP_FRONT_LEFT 	0x1000
#define SPEAKER_TOP_FRONT_CENTER 0x2000
#define SPEAKER_TOP_FRONT_RIGHT 0x4000
#define SPEAKER_TOP_BACK_LEFT 0x8000
#define SPEAKER_TOP_BACK_CENTER 0x10000
#define SPEAKER_TOP_BACK_RIGHT 0x20000

#ifdef __cplusplus
}
#endif
#endif
