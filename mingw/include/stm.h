#ifndef _STM_H
#define _STM_H
#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if (_WIN32_WINNT >= 0x0500)
typedef struct _IPX_SERVER_ENTRY {
	USHORT Type;
	UCHAR Name[48];
	UCHAR Network[4];
	UCHAR Node[6];
	UCHAR Socket[2];
	USHORT HopCount;
} IPX_SERVER_ENTRY,*PIPX_SERVER_ENTRY;
#endif

#ifdef __cplusplus
}
#endif
#endif
