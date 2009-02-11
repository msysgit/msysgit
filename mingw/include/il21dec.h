#ifndef _IL21DEC_H
#define _IL21DEC_H
#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*--- DirectShow Reference - DirectShow Enumerated Types */
typedef enum _AM_LINE21_CCLEVEL {
	AM_L21_CCLEVEL_TC2
} AM_LINE21_CCLEVEL,*PAM_LINE21_CCLEVEL;
typedef enum _AM_LINE21_CCSERVICE {
	AM_L21_CCSERVICE_None,
	AM_L21_CCSERVICE_Caption1,
	AM_L21_CCSERVICE_Caption2,
	AM_L21_CCSERVICE_Text1,
	AM_L21_CCSERVICE_Text2,
	AM_L21_CCSERVICE_XDS,
} AM_LINE21_CCSERVICE,*PAM_LINE21_CCSERVICE;
typedef enum _AM_LINE21_CCSTATE {
	AM_L21_CCSTATE_Off,
	AM_L21_CCSTATE_On
} AM_LINE21_CCSTATE,*PAM_LINE21_CCSTATE;
typedef enum _AM_LINE21_DRAWBGMODE {
	AM_L21_DRAWBGMODE_Opaque,
	AM_L21_DRAWBGMODE_Transparent
} AM_LINE21_DRAWBGMODE,*PAM_LINE21_DRAWBGMODE;

#ifdef __cplusplus
}
#endif
#endif
