#ifndef _VIDCAP_H
#define _VIDCAP_H
#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*--- DirectShow Reference - DirectShow Structures */
typedef struct {
	ULONG FromNode;
	ULONG FromNodePin;
	ULONG ToNode;
	ULONG ToNodePin;
} KSTOPOLOGY_CONNECTION;
#define KSFILTER_NODE 0xFFFFFFFF

#ifdef __cplusplus
}
#endif
#endif
