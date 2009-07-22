#ifndef _QEDIT_H
#define _QEDIT_H
#if __GNUC__ >=3
#pragma GCC system_header
#endif

#ifndef _STRMIF_H
#include <strmif.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*--- DirectShow Reference - Constants and GUIDs - Error and Success Codes */
#define S_WARN_OUTPUTRESET 0x00009DD4
#define E_NOTINTREE 0x80040400
#define E_RENDER_ENGINE_IS_BROKEN 0x80040401
#define E_MUST_INIT_RENDERER 0x80040402
#define E_NOTDETERMINED 0x80040403
#define E_NO_TIMELINE 0x80040404
/*--- DirectShow Editing Services - C++ Reference - Structures */
typedef struct {
	BSTR Name;
	DISPID dispID;
	LONG nValues;
} DEXTER_PARAM;
typedef struct {
	VARIANT v;
	REFERENCE_TIME rt;
	DWORD dwInterp;
} DEXTER_VALUE;
typedef struct _SCompFmt0 {
	long nFormatId;
	AM_MEDIA_TYPE MediaType;
} SCompFmt0;
/*--- DirectShow Editing Services - C++ Reference - Enumerated Types */
typedef enum {
	DEXTERF_BOUNDING = -1,
	DEXTERF_EXACTLY_AT = 0,
	DEXTERF_FORWARDS = 1
} DEXTERF_TRACK_SEARCH_FLAGS;
typedef enum {
	TIMELINE_MAJOR_TYPE_COMPOSITE = 1,
	TIMELINE_MAJOR_TYPE_TRACK = 2,
	TIMELINE_MAJOR_TYPE_SOURCE = 4,
	TIMELINE_MAJOR_TYPE_TRANSITION = 8,
	TIMELINE_MAJOR_TYPE_EFFECT = 16,
	TIMELINE_MAJOR_TYPE_GROUP = 128
} TIMELINE_MAJOR_TYPE;
/*--- DirectShow Editing Services - C++ Reference - Constants */
#define CONNECTF_DYNAMIC_NONE 0x00
#define CONNECTF_DYNAMIC_SOURCES 0x01
#define CONNECTF_DYNAMIC_EFFECTS 0x02
#define SFN_VALIDATEF_CHECK 0x01
#define SFN_VALIDATEF_POPUP 0x02
#define SFN_VALIDATEF_TELLME 0x04
#define SFN_VALIDATEF_REPLACE 0x08
#define SFN_VALIDATEF_USELOCAL 0x10
#define SFN_VALIDATEF_NOFIND 0x20
#define SFN_VALIDATEF_IGNOREMUTED 0x40
#define RESIZEF_STRETCH 0
#define RESIZEF_CROP 1
#define RESIZEF_PRESERVEASPECTRATIO 2
#define RESIZEF_PRESERVEASPECTRATIO_NOLETTERBOX 3

#ifdef __cplusplus
}
#endif
#endif
