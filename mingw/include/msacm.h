/*author: Adrian Sandor
  written for MinGW*/
#ifndef _MSACM_H
#define _MSACM_H

#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef HANDLE HACMDRIVERID, HACMDRIVER, *LPHACMDRIVER; /*they're handles, right?*/

/*found through experimentation*/
#define ACMDRIVERDETAILS_SHORTNAME_CHARS 32
#define ACMDRIVERDETAILS_LONGNAME_CHARS 128
#define ACMDRIVERDETAILS_COPYRIGHT_CHARS 80
#define ACMDRIVERDETAILS_LICENSING_CHARS 128

/*I don't know the right values for these macros*/
#define ACMFORMATDETAILS_FORMAT_CHARS 256
#define ACMFORMATTAGDETAILS_FORMATTAG_CHARS 256
#define ACMDRIVERDETAILS_FEATURES_CHARS 256

/*msdn.microsoft.com/library/default.asp?url=/library/en-us/multimed/htm/_win32_acmformatdetails_str.asp*/
typedef struct {
	DWORD          cbStruct;
	DWORD          dwFormatIndex;
	DWORD          dwFormatTag;
	DWORD          fdwSupport;
	LPWAVEFORMATEX pwfx;
	DWORD          cbwfx;
	char szFormat[ACMFORMATDETAILS_FORMAT_CHARS];
} ACMFORMATDETAILSA, *LPACMFORMATDETAILSA;
typedef struct {
	DWORD          cbStruct;
	DWORD          dwFormatIndex;
	DWORD          dwFormatTag;
	DWORD          fdwSupport;
	LPWAVEFORMATEX pwfx;
	DWORD          cbwfx;
	WCHAR szFormat[ACMFORMATDETAILS_FORMAT_CHARS];
} ACMFORMATDETAILSW, *LPACMFORMATDETAILSW;

/*msdn.microsoft.com/library/default.asp?url=/library/en-us/multimed/htm/_win32_acmformattagdetails_str.asp*/
typedef struct {
	DWORD cbStruct;
	DWORD dwFormatTagIndex;
	DWORD dwFormatTag;
	DWORD cbFormatSize;
	DWORD fdwSupport;
	DWORD cStandardFormats;
	char szFormatTag[ACMFORMATTAGDETAILS_FORMATTAG_CHARS];
} ACMFORMATTAGDETAILSA, *LPACMFORMATTAGDETAILSA;
typedef struct {
	DWORD cbStruct;
	DWORD dwFormatTagIndex;
	DWORD dwFormatTag;
	DWORD cbFormatSize;
	DWORD fdwSupport;
	DWORD cStandardFormats;
	WCHAR szFormatTag[ACMFORMATTAGDETAILS_FORMATTAG_CHARS];
} ACMFORMATTAGDETAILSW, *LPACMFORMATTAGDETAILSW;

/*msdn.microsoft.com/library/default.asp?url=/library/en-us/multimed/htm/_win32_acmdriverdetails_str.asp*/
typedef struct {
	DWORD  cbStruct;
	FOURCC fccType;
	FOURCC fccComp;
	WORD   wMid;
	WORD   wPid;
	DWORD  vdwACM;
	DWORD  vdwDriver;
	DWORD  fdwSupport;
	DWORD  cFormatTags;
	DWORD  cFilterTags;
	HICON  hicon;
	char  szShortName[ACMDRIVERDETAILS_SHORTNAME_CHARS];
	char  szLongName[ACMDRIVERDETAILS_LONGNAME_CHARS];
	char  szCopyright[ACMDRIVERDETAILS_COPYRIGHT_CHARS];
	char  szLicensing[ACMDRIVERDETAILS_LICENSING_CHARS];
	char  szFeatures[ACMDRIVERDETAILS_FEATURES_CHARS];
} ACMDRIVERDETAILSA, *LPACMDRIVERDETAILSA;
typedef struct {
	DWORD  cbStruct;
	FOURCC fccType;
	FOURCC fccComp;
	WORD   wMid;
	WORD   wPid;
	DWORD  vdwACM;
	DWORD  vdwDriver;
	DWORD  fdwSupport;
	DWORD  cFormatTags;
	DWORD  cFilterTags;
	HICON  hicon;
	WCHAR  szShortName[ACMDRIVERDETAILS_SHORTNAME_CHARS];
	WCHAR  szLongName[ACMDRIVERDETAILS_LONGNAME_CHARS];
	WCHAR  szCopyright[ACMDRIVERDETAILS_COPYRIGHT_CHARS];
	WCHAR  szLicensing[ACMDRIVERDETAILS_LICENSING_CHARS];
	WCHAR  szFeatures[ACMDRIVERDETAILS_FEATURES_CHARS];
} ACMDRIVERDETAILSW, *LPACMDRIVERDETAILSW;

/*msdn.microsoft.com/library/default.asp?url=/library/en-us/multimed/htm/_win32_acmformatenumcallback.asp*/
typedef BOOL (CALLBACK *ACMFORMATENUMCBA) (
	HACMDRIVERID        hadid,
	LPACMFORMATDETAILSA pafd,
	DWORD_PTR           dwInstance,
	DWORD               fdwSupport
);
typedef BOOL (CALLBACK *ACMFORMATENUMCBW) (
	HACMDRIVERID        hadid,
	LPACMFORMATDETAILSW pafd,
	DWORD_PTR           dwInstance,
	DWORD               fdwSupport
);

/*msdn.microsoft.com/library/default.asp?url=/library/en-us/multimed/htm/_win32_acmformattagenumcallback.asp*/
typedef BOOL (CALLBACK *ACMFORMATTAGENUMCBA) (
	HACMDRIVERID           hadid,
	LPACMFORMATTAGDETAILSA paftd,
	DWORD_PTR              dwInstance,
	DWORD                  fdwSupport
);
typedef BOOL (CALLBACK *ACMFORMATTAGENUMCBW) (
	HACMDRIVERID           hadid,
	LPACMFORMATTAGDETAILSW paftd,
	DWORD_PTR              dwInstance,
	DWORD                  fdwSupport
);

/*msdn.microsoft.com/library/default.asp?url=/library/en-us/multimed/htm/_win32_acmdriverenumcallback.asp*/
typedef BOOL (CALLBACK *ACMDRIVERENUMCB) (
	HACMDRIVERID hadid,
	DWORD_PTR    dwInstance,
	DWORD        fdwSupport
);

/*and now the functions...*/

/*msdn.microsoft.com/library/default.asp?url=/library/en-us/multimed/htm/_win32_acmdriveropen.asp*/
MMRESULT WINAPI acmDriverOpen(LPHACMDRIVER phad, HACMDRIVERID hadid, DWORD fdwOpen);
/*msdn.microsoft.com/library/default.asp?url=/library/en-us/multimed/htm/_win32_acmdriverenum.asp*/
MMRESULT WINAPI acmDriverEnum(ACMDRIVERENUMCB fnCallback, DWORD_PTR dwInstance, DWORD fdwEnum);
/*msdn.microsoft.com/library/default.asp?url=/library/en-us/multimed/htm/_win32_acmformatenum.asp*/
MMRESULT WINAPI acmFormatEnumA(HACMDRIVER had, LPACMFORMATDETAILSA pafd, ACMFORMATENUMCBA fnCallback, DWORD_PTR dwInstance, DWORD fdwEnum);
MMRESULT WINAPI acmFormatEnumW(HACMDRIVER had, LPACMFORMATDETAILSW pafd, ACMFORMATENUMCBW fnCallback, DWORD_PTR dwInstance, DWORD fdwEnum);
/*msdn.microsoft.com/library/default.asp?url=/library/en-us/multimed/htm/_win32_acmdriverclose.asp*/
MMRESULT WINAPI acmDriverClose(HACMDRIVER had, DWORD fdwClose);
/*msdn.microsoft.com/library/default.asp?url=/library/en-us/multimed/htm/_win32_acmdriverdetails.asp*/
MMRESULT WINAPI acmDriverDetailsA(HACMDRIVERID hadid, LPACMDRIVERDETAILSA padd, DWORD fdwDetails);
MMRESULT WINAPI acmDriverDetailsW(HACMDRIVERID hadid, LPACMDRIVERDETAILSW padd, DWORD fdwDetails);
/*msdn.microsoft.com/library/default.asp?url=/library/en-us/multimed/htm/_win32_acmformattagenum.asp*/
MMRESULT WINAPI acmFormatTagEnumA(HACMDRIVER had, LPACMFORMATTAGDETAILSA paftd, ACMFORMATTAGENUMCBA fnCallback, DWORD_PTR dwInstance, DWORD fdwEnum);
MMRESULT WINAPI acmFormatTagEnumW(HACMDRIVER had, LPACMFORMATTAGDETAILSW paftd, ACMFORMATTAGENUMCBW fnCallback, DWORD_PTR dwInstance, DWORD fdwEnum);

#ifdef UNICODE

typedef ACMFORMATDETAILSW ACMFORMATDETAILS, *LPACMFORMATDETAILS;
typedef ACMFORMATTAGDETAILSW ACMFORMATTAGDETAILS, *LPACMFORMATTAGDETAILS;
typedef ACMDRIVERDETAILSW ACMDRIVERDETAILS, *LPACMDRIVERDETAILS;
typedef ACMFORMATENUMCBW ACMFORMATENUMCB;
typedef ACMFORMATTAGENUMCBW ACMFORMATTAGENUMCB;
#define acmFormatEnum acmFormatEnumW
#define acmDriverDetails acmDriverDetailsW
#define acmFormatTagEnum acmFormatTagEnumW

#else /*ifdef UNICODE*/

typedef ACMFORMATDETAILSA ACMFORMATDETAILS, *LPACMFORMATDETAILS;
typedef ACMFORMATTAGDETAILSA ACMFORMATTAGDETAILS, *LPACMFORMATTAGDETAILS;
typedef ACMDRIVERDETAILSA ACMDRIVERDETAILS, *LPACMDRIVERDETAILS;
typedef ACMFORMATENUMCBA ACMFORMATENUMCB;
typedef ACMFORMATTAGENUMCBA ACMFORMATTAGENUMCB;
#define acmFormatEnum acmFormatEnumA
#define acmDriverDetails acmDriverDetailsA
#define acmFormatTagEnum acmFormatTagEnumA

#endif /*ifdef UNICODE*/

#ifdef __cplusplus
}
#endif

#endif
