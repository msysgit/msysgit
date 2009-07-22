#ifndef _KS_H
#define _KS_H
#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*--- DirectShow Reference - DirectShow Structures */
typedef struct {
	ULONG Size;
	ULONG Count;
} KSMULTIPLE_ITEM,*PKSMULTIPLE_ITEM;

#ifdef __cplusplus
}
#endif
#endif
