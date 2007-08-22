#ifndef _USP10_H
#define _USP10_H
#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif
#pragma pack(push,1)

#define SCRIPT_UNDEFINED 0
#define USP_E_SCRIPT_NOT_IN_FONT  MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x200)
#define	SGCM_RTL	0x00000001
#define	SSA_PASSWORD	0x00000001
#define	SSA_TAB 	0x00000002	
#define	SSA_CLIP	0x00000004
#define	SSA_FIT 	0x00000008
#define	SSA_DZWG	0x00000010
#define	SSA_FALLBACK	0x00000020
#define	SSA_BREAK	0x00000040
#define	SSA_GLYPHS      0x00000080
#define	SSA_RTL         0x00000100
#define	SSA_GCP 	0x00000200
#define	SSA_HOTKEY	0x00000400
#define	SSA_METAFILE	0x00000800
#define	SSA_LINK	0x00001000
#define	SSA_HIDEHOTKEY	0x00002000
#define	SSA_HOTKEYONLY	0x00002400
#define	SSA_FULLMEASURE	0x04000000
#define	SSA_LPKANSIFALLBACK 0x08000000
#define	SSA_PIDX	0x10000000
#define	SSA_LAYOUTRTL	0x20000000
#define	SSA_DONTGLYPH	0x40000000
#define	SSA_NOKASHIDA	0x80000000
#define SIC_COMPLEX     1
#define	SIC_ASCIIDIGIT	2     
#define	SIC_NEUTRAL     4
#define	SCRIPT_DIGITSUBSTITUTE_CONTEXT	0
#define	SCRIPT_DIGITSUBSTITUTE_NONE	1
#define	SCRIPT_DIGITSUBSTITUTE_NATIONAL	2
#define	SCRIPT_DIGITSUBSTITUTE_TRADITIONAL 3
  
typedef enum tag_SCRIPT_JUSTIFY {
  SCRIPT_JUSTIFY_NONE = 0, 
  SCRIPT_JUSTIFY_ARABIC_BLANK = 1, 
  SCRIPT_JUSTIFY_CHARACTER = 2, 
  SCRIPT_JUSTIFY_RESERVED1 = 3, 
  SCRIPT_JUSTIFY_BLANK = 4, 
  SCRIPT_JUSTIFY_RESERVED2 = 5, 
  SCRIPT_JUSTIFY_RESERVED3 = 6, 
  SCRIPT_JUSTIFY_ARABIC_NORMAL = 7, 
  SCRIPT_JUSTIFY_ARABIC_KASHIDA = 8, 
  SCRIPT_JUSTIFY_ARABIC_ALEF = 9, 
  SCRIPT_JUSTIFY_ARABIC_HA = 10, 
  SCRIPT_JUSTIFY_ARABIC_RA = 11, 
  SCRIPT_JUSTIFY_ARABIC_BA = 12, 
  SCRIPT_JUSTIFY_ARABIC_BARA = 13, 
  SCRIPT_JUSTIFY_ARABIC_SEEN = 14, 
  SCRIPT_JUSTIFY_ARABIC_SEEN_M = 15 
} SCRIPT_JUSTIFY;
  
typedef struct tagGOFFSET {
  LONG  du;
  LONG  dv;
} GOFFSET;
typedef ULONG OPENTYPE_TAG;
typedef struct opentype_feature_record{
  OPENTYPE_TAG    tagFeature;
  LONG            lParameter;
} OPENTYPE_FEATURE_RECORD;
typedef struct tag_SCRIPT_STATE { 
  WORD uBidiLevel :5; 
  WORD fOverrideDirection :1; 
  WORD fInhibitSymSwap :1; 
  WORD fCharShape :1; 
  WORD fDigitSubstitute :1; 
  WORD fInhibitLigate :1; 
  WORD fDisplayZWG :1; 
  WORD fArabicNumContext :1; 
  WORD fGcpClusters :1; 
  WORD fReserved :1; 
  WORD fEngineReserved :2; 
} SCRIPT_STATE;
typedef struct tag_SCRIPT_ANALYSIS {
  WORD eScript       :10; 
  WORD fRTL          :1; 
  WORD fLayoutRTL    :1; 
  WORD fLinkBefore   :1; 
  WORD fLinkAfter    :1; 
  WORD fLogicalOrder :1; 
  WORD fNoGlyphIndex :1; 
  SCRIPT_STATE s ; 
} SCRIPT_ANALYSIS;
typedef void *SCRIPT_CACHE;
typedef struct script_charprop {
    WORD           fCanGlyphAlone : 1;
    WORD           reserved       : 15;
} SCRIPT_CHARPROP;
typedef struct tag_SCRIPT_CONTROL { 
  DWORD uDefaultLanguage :16; 
  DWORD fContextDigits :1; 
  DWORD fInvertPreBoundDir :1; 
  DWORD fInvertPostBoundDir :1; 
  DWORD fLinkStringBefore :1; 
  DWORD fLinkStringAfter :1; 
  DWORD fNeutralOverride :1; 
  DWORD fNumericOverride :1; 
  DWORD fLegacyBidiClass :1; 
  DWORD fReserved :8; 
} SCRIPT_CONTROL;
typedef struct tag_SCRIPT_DIGITSUBSTITUTE {
  DWORD NationalDigitLanguage    : 16;
  DWORD TraditionalDigitLanguage : 16;
  DWORD DigitSubstitute          :8;
  DWORD dwReserved;
} SCRIPT_DIGITSUBSTITUTE;
typedef struct {
  int   cBytes; 
  WORD  wgBlank; 
  WORD  wgDefault; 
  WORD  wgInvalid; 
  WORD  wgKashida; 
  int   iKashidaWidth; 
} SCRIPT_FONTPROPERTIES;
typedef struct tag_SCRIPT_VISATTR { 
  WORD uJustification :4; 
  WORD fClusterStart :1; 
  WORD fDiacritic :1; 
  WORD fZeroWidth :1; 
  WORD fReserved :1; 
  WORD fShapeReserved :8; 
} SCRIPT_VISATTR;
typedef struct script_glyphprop { 
    SCRIPT_VISATTR sva;
    WORD reserved;
} SCRIPT_GLYPHPROP;
typedef struct tag_SCRIPT_ITEM { 
  int iCharPos; 
  SCRIPT_ANALYSIS a; 
} SCRIPT_ITEM;
typedef struct tag_SCRIPT_LOGATTR { 
  BYTE fSoftBreak :1; 
  BYTE fWhiteSpace :1; 
  BYTE fCharStop :1; 
  BYTE fWordStop :1; 
  BYTE fInvalid :1; 
  BYTE fReserved :3; 
} SCRIPT_LOGATTR;
typedef struct {
  DWORD   langid              :16;  
  DWORD   fNumeric            :1;
  DWORD   fComplex            :1;
  DWORD   fNeedsWordBreaking  :1;   
  DWORD   fNeedsCaretInfo     :1;
  DWORD   bCharSet            :8;   
  DWORD   fControl            :1;   
  DWORD   fPrivateUseArea     :1;   
  DWORD   fNeedsCharacterJustify :1;
  DWORD   fInvalidGlyph       :1;
  DWORD   fInvalidLogAttr     :1;
  DWORD   fCDM                :1;
  DWORD   fAmbiguousCharSet   :1;
  DWORD   fClusterSizeVaries  :1;
  DWORD   fRejectInvalid      :1;
} SCRIPT_PROPERTIES;
typedef void *SCRIPT_STRING_ANALYSIS;
typedef struct tag_SCRIPT_TABDEF {
  int cTabStops;
  int iScale;
  int *pTabStops;
  int iTabOrigin;
} SCRIPT_TABDEF;
typedef struct textrange_properties{
    OPENTYPE_FEATURE_RECORD*  potfRecords;
    int                       cotfRecords;
} TEXTRANGE_PROPERTIES;


HRESULT WINAPI ScriptApplyDigitSubstitution(const SCRIPT_DIGITSUBSTITUTE*,SCRIPT_CONTROL*,SCRIPT_STATE*);
HRESULT WINAPI ScriptApplyLogicalWidth(const int *,int,int,const WORD *,const SCRIPT_VISATTR *,const int *,const SCRIPT_ANALYSIS *,ABC *,int *);
HRESULT WINAPI ScriptBreak(const WCHAR *,int,const SCRIPT_ANALYSIS *,SCRIPT_LOGATTR *);
HRESULT WINAPI ScriptCacheGetHeight(HDC,SCRIPT_CACHE *,long *);
HRESULT WINAPI ScriptCPtoX(int,BOOL,int,int,const WORD *,const SCRIPT_VISATTR *,const int *,const SCRIPT_ANALYSIS *,int *);
HRESULT WINAPI ScriptFreeCache(SCRIPT_CACHE *);
HRESULT WINAPI ScriptGetCMap(HDC,SCRIPT_CACHE *,const WCHAR*,int,DWORD,WORD *);
HRESULT WINAPI ScriptGetFontAlternateGlyphs(HDC,SCRIPT_CACHE*,SCRIPT_ANALYSIS*,OPENTYPE_TAG,OPENTYPE_TAG,OPENTYPE_TAG,WORD,int,WORD*,int*);
HRESULT WINAPI ScriptGetFontFeatureTags(HDC,SCRIPT_CACHE*,SCRIPT_ANALYSIS*,OPENTYPE_TAG,OPENTYPE_TAG,int,OPENTYPE_TAG*,int*);
HRESULT WINAPI ScriptGetFontLanguageTags(HDC,SCRIPT_CACHE*,SCRIPT_ANALYSIS*,OPENTYPE_TAG,int,OPENTYPE_TAG*,int*);
HRESULT WINAPI ScriptGetFontProperties(HDC,SCRIPT_CACHE *,SCRIPT_FONTPROPERTIES *);
HRESULT WINAPI ScriptGetFontScriptTags(HDC,SCRIPT_CACHE*,SCRIPT_ANALYSIS*,int,OPENTYPE_TAG*,int*);
HRESULT WINAPI ScriptGetGlyphABCWidth(HDC,SCRIPT_CACHE *,WORD,ABC *);
HRESULT WINAPI ScriptGetLogicalWidths(const SCRIPT_ANALYSIS *,int,int,const int *,const WORD *,const SCRIPT_VISATTR *,int *);
HRESULT WINAPI ScriptGetProperties(const SCRIPT_PROPERTIES ***,int *);
HRESULT WINAPI ScriptIsComplex(const WCHAR *,int,DWORD);
HRESULT WINAPI ScriptItemize(const WCHAR *,int,int,const SCRIPT_CONTROL *,const SCRIPT_STATE *,SCRIPT_ITEM *,int *);
HRESULT WINAPI ScriptItemizeOpenType(const WCHAR*,int,int,const SCRIPT_CONTROL*,const SCRIPT_STATE*,SCRIPT_ITEM*,OPENTYPE_TAG*,int*);
HRESULT WINAPI ScriptJustify(const SCRIPT_VISATTR *,const int *,int,int,int,int *);
HRESULT WINAPI ScriptLayout(int,const BYTE *,int *,int *);
HRESULT WINAPI ScriptPlace(HDC,SCRIPT_CACHE *,const WORD *,int,const SCRIPT_VISATTR *,SCRIPT_ANALYSIS *,int *,GOFFSET *,ABC *);
HRESULT WINAPI ScriptPlaceOpenType(HDC,SCRIPT_CACHE*,SCRIPT_ANALYSIS*,OPENTYPE_TAG,OPENTYPE_TAG,int*,TEXTRANGE_PROPERTIES**,int,const WCHAR*,const WORD*,const SCRIPT_CHARPROP*,int,const WORD*,const SCRIPT_GLYPHPROP*,int,int*,GOFFSET*,ABC*);
HRESULT WINAPI ScriptPositionSingleGlyph(HDC,SCRIPT_CACHE*,SCRIPT_ANALYSIS*,OPENTYPE_TAG,OPENTYPE_TAG,OPENTYPE_TAG,LONG,WORD,int,GOFFSET,int*,GOFFSET*);
HRESULT WINAPI ScriptRecordDigitSubstitution(LCID,SCRIPT_DIGITSUBSTITUTE *);
HRESULT WINAPI ScriptShape(HDC,SCRIPT_CACHE *,const WCHAR *,int,int,SCRIPT_ANALYSIS *,WORD *,WORD *,SCRIPT_VISATTR *,int *);
HRESULT WINAPI ScriptShapeOpenType(HDC,SCRIPT_CACHE*,SCRIPT_ANALYSIS*,OPENTYPE_TAG,OPENTYPE_TAG,int*,TEXTRANGE_PROPERTIES**,int,const WCHAR*,int,int,WORD*,SCRIPT_CHARPROP*,WORD*,SCRIPT_GLYPHPROP*,int*);
HRESULT WINAPI ScriptStringAnalyse(HDC,const void *,int,int,int,DWORD,int,SCRIPT_CONTROL *,SCRIPT_STATE *,const int *,SCRIPT_TABDEF *,const BYTE *,SCRIPT_STRING_ANALYSIS *);
HRESULT WINAPI ScriptStringCPtoX(SCRIPT_STRING_ANALYSIS,int,BOOL,int *);
HRESULT WINAPI ScriptStringFree(SCRIPT_STRING_ANALYSIS *);
HRESULT WINAPI ScriptStringGetLogicalWidths(SCRIPT_STRING_ANALYSIS,int *);
HRESULT WINAPI ScriptStringGetOrder(SCRIPT_STRING_ANALYSIS,UINT *);
HRESULT WINAPI ScriptStringOut(SCRIPT_STRING_ANALYSIS,int,int,UINT,const RECT *,int,int,BOOL);
const int*WINAPI ScriptString_pcOutChars(SCRIPT_STRING_ANALYSIS);
const SCRIPT_LOGATTR* WINAPI ScriptString_pLogAttr(SCRIPT_STRING_ANALYSIS);
const SIZE* WINAPI ScriptString_pSize(SCRIPT_STRING_ANALYSIS);
HRESULT WINAPI ScriptStringValidate(SCRIPT_STRING_ANALYSIS);
HRESULT WINAPI ScriptStringXtoCP(SCRIPT_STRING_ANALYSIS,int,int *,int *);
HRESULT WINAPI ScriptSubstituteSingleGlyph(HDC,SCRIPT_CACHE*,SCRIPT_ANALYSIS*,OPENTYPE_TAG,OPENTYPE_TAG,OPENTYPE_TAG,LONG,WORD,WORD*);
HRESULT WINAPI ScriptTextOut(const HDC,SCRIPT_CACHE *,int,int,UINT,const RECT *,const SCRIPT_ANALYSIS *,const WCHAR *,int,const WORD *,int,const int *,const int *,const GOFFSET *);
HRESULT WINAPI ScriptXtoCP(int,int,int,const WORD *,const SCRIPT_VISATTR *,const int *,const SCRIPT_ANALYSIS *,int *,int *);

  
#pragma pack(pop)
#ifdef __cplusplus
}
#endif

#endif /* ndef _USP10_H_ */
