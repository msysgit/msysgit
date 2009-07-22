#ifndef _ICM_H
#define _ICM_H
#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if (_WIN32_WINDOWS >= 0x0410 || _WIN32_WINNT >= 0x0500)
#define MAX_COLOR_CHANNELS 8
#define PROFILE_FILENAME 1
#define PROFILE_MEMBUFFER 2
#define PROFILE_READ 1
#define PROFILE_READWRITE 2
#define CLASS_SCANNER 0x73636E72
#define CLASS_MONITOR 0x6D6E7472
#define CLASS_PRINTER 0x70727472
#define CLASS_LINK 0x6C696E6B
#define CLASS_COLORSPAC 0x73706163
#define CLASS_ABSTRACT 0x61627374
#define CLASS_NAMED 0x6E6D636C
#define SPACE_XYZ 0x58595A20
#define SPACE_Lab 0x4C616220
#define SPACE_Luv 0x4C757620
#define SPACE_YCbCr 0x59436272
#define SPACE_Yxy 0x59787920
#define SPACE_RGB 0x52474220
#define SPACE_GRAY 0x47524159
#define SPACE_HSV 0x48535620
#define SPACE_HLS 0x484C5320
#define SPACE_CMYK 0x434D594B
#define SPACE_CMY 0x434D5920
#define SPACE_2_CHANNEL 0x32434C52
#define SPACE_3_CHANNEL 0x33434C52
#define SPACE_4_CHANNEL 0x34434C52
#define SPACE_5_CHANNEL 0x35434C52
#define SPACE_6_CHANNEL 0x36434C52
#define SPACE_7_CHANNEL 0x37434C52
#define SPACE_8_CHANNEL 0x38434C52
#define FLAG_EMBEDDEDPROFILE 1
#define FLAG_DEPENDENTONDATA 2
#define ATTRIB_TRANSPARENCY 1
#define ATTRIB_MATTE 2
#define INTENT_PERCEPTUAL 0
#define INTENT_RELATIVE_COLORIMETRIC 1
#define INTENT_SATURATION 2
#define INTENT_ABSOLUTE_COLORIMETRIC 3
#define COLOR_MATCH_VERSION 0x200
#define CMS_DISABLEICM 0x1
#define CMS_ENABLEPROOFING 0x2
#define CMS_SETRENDERINTENT 0x4
#define CMS_SETPROOFINTENT 0x8
#define CMS_SETMONITORPROFILE 0x10
#define CMS_SETPRINTERPROFILE 0x20
#define CMS_SETTARGETPROFILE 0x40
#define CMS_USEHOOK 0x80
#define CMS_USEAPPLYCALLBACK 0x100
#define CMS_USEDESCRIPTION 0x200
#define CMS_TARGETOVERFLOW 0x20000000
#define CMS_PRINTERROVERFLOW 0x40000000
#define CMS_MONITOROVERFLOW 0x80000000

DECLARE_HANDLE(HPROFILE);
typedef HPROFILE *PHPROFILE,*LPHPROFILE;
DECLARE_HANDLE(HTRANSFORM);\

typedef BOOL (CALLBACK *PBMCALLBACKFN)(ULONG,ULONG,LPARAM);
struct _tagCOLORMATCHSETUPA;
struct _tagCOLORMATCHSETUPW;
typedef BOOL (CALLBACK *PCMSCALLBACKA)(struct _tagCOLORMATCHSETUPA*,LPARAM);
typedef BOOL (CALLBACK *PCMSCALLBACKW)(struct _tagCOLORMATCHSETUPW*,LPARAM);

typedef CHAR COLOR_NAME[32];
typedef COLOR_NAME *PCOLOR_NAME,*LPCOLOR_NAME;
typedef DWORD TAGTYPE,*PTAGTYPE,*LPTAGTYPE;
typedef enum 
{
  BM_x555RGB      = 0x0000,
  BM_x555XYZ      = 0x0101,
  BM_x555Yxy,
  BM_x555Lab,
  BM_x555G3CH,
  BM_RGBTRIPLETS  = 0x0002,
  BM_BGRTRIPLETS  = 0x0004,
  BM_XYZTRIPLETS  = 0x0201,
  BM_YxyTRIPLETS,
  BM_LabTRIPLETS,
  BM_G3CHTRIPLETS,
  BM_5CHANNEL,
  BM_6CHANNEL,
  BM_7CHANNEL,
  BM_8CHANNEL,
  BM_GRAY,
  BM_xRGBQUADS    = 0x0008,
  BM_xBGRQUADS    = 0x0010,
  BM_xG3CHQUADS   = 0x0304,
  BM_KYMCQUADS,
  BM_CMYKQUADS    = 0x0020,
  BM_10b_RGB      = 0x0009,
  BM_10b_XYZ      = 0x0401,
  BM_10b_Yxy,
  BM_10b_Lab,
  BM_10b_G3CH,
  BM_NAMED_INDEX,
  BM_16b_RGB      = 0x000A,
  BM_16b_XYZ      = 0x0501,
  BM_16b_Yxy,
  BM_16b_Lab,
  BM_16b_G3CH,
  BM_16b_GRAY,
  BM_565RGB       = 0x0001
} BMFORMAT,*PBMFORMAT,*LPBMFORMAT;
typedef enum 
{
  COLOR_GRAY       =   1,
  COLOR_RGB,
  COLOR_XYZ,
  COLOR_Yxy,
  COLOR_Lab,
  COLOR_3_CHANNEL,
  COLOR_CMYK,
  COLOR_5_CHANNEL,
  COLOR_6_CHANNEL,
  COLOR_7_CHANNEL,
  COLOR_8_CHANNEL,
  COLOR_NAMED
} COLORTYPE,*PCOLORTYPE,*LPCOLORTYPE;
struct GRAYCOLOR {
  WORD    gray;
};
struct RGBCOLOR {
  WORD    red;
  WORD    green;
  WORD    blue;
};
struct CMYKCOLOR {
  WORD    cyan;
  WORD    magenta;
  WORD    yellow;
  WORD    black;
};
struct XYZCOLOR {
  WORD    X;
  WORD    Y;
  WORD    Z;
};
struct YxyCOLOR {
  WORD    Y;
  WORD    x;
  WORD    y;
};
struct LabCOLOR {
  WORD    L;
  WORD    a;
  WORD    b;
};
struct GENERIC3CHANNEL {
  WORD    ch1;
  WORD    ch2;
  WORD    ch3;
};
struct NAMEDCOLOR {
  DWORD   dwIndex;
};
struct HiFiCOLOR {
  BYTE    channel[MAX_COLOR_CHANNELS];
};
typedef union tagCOLOR {
  struct GRAYCOLOR        gray;
  struct RGBCOLOR         rgb;
  struct CMYKCOLOR        cmyk;
  struct XYZCOLOR         XYZ;
  struct YxyCOLOR         Yxy;
  struct LabCOLOR         Lab;
  struct GENERIC3CHANNEL  gen3ch;
  struct NAMEDCOLOR       named;
  struct HiFiCOLOR        hifi;
} COLOR,*PCOLOR,*LPCOLOR;
typedef struct _tagCOLORMATCHSETUPA {
  DWORD         dwSize;
  DWORD         dwVersion;
  DWORD         dwFlags; 
  HWND          hwndOwner;
  PCSTR         pSourceName; 
  PCSTR         pDisplayName; 
  PCSTR         pPrinterName;
  DWORD         dwRenderIntent; 
  DWORD         dwProofingIntent;
  PSTR          pMonitorProfile; 
  DWORD         ccMonitorProfile;
  PSTR          pPrinterProfile; 
  DWORD         ccPrinterProfile;
  PSTR          pTargetProfile; 
  DWORD         ccTargetProfile;
  DLGPROC       lpfnHook; 
  LPARAM        lParam;
  PCMSCALLBACKA lpfnApplyCallback;
  LPARAM        lParamApplyCallback; 
} COLORMATCHSETUPA,*PCOLORMATCHSETUPA,*LPCOLORMATCHSETUPA;
typedef struct _tagCOLORMATCHSETUPW {
  DWORD         dwSize;
  DWORD         dwVersion;
  DWORD         dwFlags; 
  HWND          hwndOwner;
  PCWSTR        pSourceName; 
  PCWSTR        pDisplayName; 
  PCWSTR        pPrinterName;
  DWORD         dwRenderIntent; 
  DWORD         dwProofingIntent;
  PWSTR         pMonitorProfile; 
  DWORD         ccMonitorProfile;
  PWSTR         pPrinterProfile; 
  DWORD         ccPrinterProfile;
  PWSTR         pTargetProfile; 
  DWORD         ccTargetProfile;
  DLGPROC       lpfnHook; 
  LPARAM        lParam;
  PCMSCALLBACKW lpfnApplyCallback;
  LPARAM        lParamApplyCallback; 
} COLORMATCHSETUPW,*PCOLORMATCHSETUPW,*LPCOLORMATCHSETUPW;
typedef struct tagENUMTYPEW {
  DWORD   dwSize;
  DWORD   dwVersion;
  DWORD   dwFields;
  PCWSTR  pDeviceName;
  DWORD   dwMediaType;
  DWORD   dwDitheringMode;
  DWORD   dwResolution[2];
  DWORD   dwCMMType;
  DWORD   dwClass;
  DWORD   dwDataColorSpace;
  DWORD   dwConnectionSpace;
  DWORD   dwSignature;
  DWORD   dwPlatform;
  DWORD   dwProfileFlags;
  DWORD   dwManufacturer;
  DWORD   dwModel;
  DWORD   dwAttributes[2];
  DWORD   dwRenderingIntent;
  DWORD   dwCreator;
  DWORD   dwDeviceClass;
} ENUMTYPEW,*PENUMTYPEW,*LPENUMTYPEW;
typedef struct tagENUMTYPEA {
  DWORD   dwSize;
  DWORD   dwVersion;
  DWORD   dwFields;
  PCSTR   pDeviceName;
  DWORD   dwMediaType;
  DWORD   dwDitheringMode;
  DWORD   dwResolution[2];
  DWORD   dwCMMType;
  DWORD   dwClass;
  DWORD   dwDataColorSpace;
  DWORD   dwConnectionSpace;
  DWORD   dwSignature;
  DWORD   dwPlatform;
  DWORD   dwProfileFlags;
  DWORD   dwManufacturer;
  DWORD   dwModel;
  DWORD   dwAttributes[2];
  DWORD   dwRenderingIntent;
  DWORD   dwCreator;
  DWORD   dwDeviceClass;
} ENUMTYPEA,*PENUMTYPEA,*LPENUMTYPEA;
typedef struct tagNAMED_PROFILE_INFO{
  DWORD         dwFlags;
  DWORD         dwCount;
  DWORD         dwCountDevCoordinates;
  COLOR_NAME    szPrefix;
  COLOR_NAME    szSuffix;
} NAMED_PROFILE_INFO,*PNAMED_PROFILE_INFO,*LPNAMED_PROFILE_INFO;
typedef struct tagPROFILE {
  DWORD    dwType;
  PVOID    pProfileData;
  DWORD    cbDataSize;
} PROFILE,*PPROFILE,*LPPROFILE;
typedef struct tagPROFILEHEADER {
  DWORD   phSize;
  DWORD   phCMMType;
  DWORD   phVersion;
  DWORD   phClass;
  DWORD   phDataColorSpace;
  DWORD   phConnectionSpace;
  DWORD   phDateTime[3];
  DWORD   phSignature;
  DWORD   phPlatform;
  DWORD   phProfileFlags;
  DWORD   phManufacturer;
  DWORD   phModel;
  DWORD   phAttributes[2];
  DWORD   phRenderingIntent;
  CIEXYZ  phIlluminant;
  DWORD   phCreator;
  BYTE    phReserved[44];
} PROFILEHEADER,*PPROFILEHEADER,*LPPROFILEHEADER;

BOOL WINAPI AssociateColorProfileWithDeviceA(PCSTR,PCSTR,PCSTR);
BOOL WINAPI AssociateColorProfileWithDeviceW(PCWSTR,PCWSTR,PCWSTR);
BOOL WINAPI CheckBitmapBits(HTRANSFORM,PVOID,BMFORMAT,DWORD,DWORD,DWORD,PBYTE,PBMCALLBACKFN,LPARAM);
BOOL WINAPI CheckColors(HTRANSFORM,PCOLOR,DWORD,COLORTYPE,PBYTE);
BOOL WINAPI CloseColorProfile(HPROFILE);
BOOL WINAPI ConvertColorNameToIndex(HPROFILE,PCOLOR_NAME,PDWORD,DWORD);
BOOL WINAPI ConvertIndexToColorName(HPROFILE,PDWORD,PCOLOR_NAME,DWORD);
HTRANSFORM WINAPI CreateColorTransformA(LPLOGCOLORSPACEA,HPROFILE,HPROFILE,DWORD);
HTRANSFORM WINAPI CreateColorTransformW(LPLOGCOLORSPACEW,HPROFILE,HPROFILE,DWORD);
BOOL WINAPI CreateDeviceLinkProfile(PHPROFILE,DWORD,PDWORD,DWORD,DWORD,PBYTE*,DWORD);
HTRANSFORM WINAPI CreateMultiProfileTransform(PHPROFILE,DWORD,PDWORD,DWORD,DWORD,DWORD);
BOOL WINAPI CreateProfileFromLogColorSpaceA(LPLOGCOLORSPACEA,PBYTE*);
BOOL WINAPI CreateProfileFromLogColorSpaceW(LPLOGCOLORSPACEW,PBYTE*);
BOOL WINAPI DeleteColorTransform(HTRANSFORM);
BOOL WINAPI DisassociateColorProfileFromDeviceA(PCSTR,PCSTR,PCSTR);
BOOL WINAPI DisassociateColorProfileFromDeviceW(PCWSTR,PCWSTR,PCWSTR);
BOOL WINAPI EnumColorProfilesA(PCSTR,PENUMTYPEA,PBYTE,PDWORD,PDWORD);
BOOL WINAPI EnumColorProfilesW(PCWSTR,PENUMTYPEW,PBYTE,PDWORD,PDWORD);
DWORD WINAPI GetCMMInfo(HTRANSFORM,DWORD);
BOOL WINAPI GetColorDirectoryA(PCSTR,PSTR,PDWORD);
BOOL WINAPI GetColorDirectoryW(PCWSTR,PWSTR,PDWORD);
BOOL WINAPI GetColorProfileElement(HPROFILE,TAGTYPE,DWORD,PDWORD,PVOID,PBOOL);
BOOL WINAPI GetColorProfileElementTag(HPROFILE,DWORD,PTAGTYPE);
BOOL WINAPI GetColorProfileFromHandle(HPROFILE,PBYTE,PDWORD);
BOOL WINAPI GetColorProfileHeader(HPROFILE,PPROFILEHEADER);
BOOL WINAPI GetCountColorProfileElements(HPROFILE,PDWORD);
BOOL WINAPI GetNamedProfileInfo(HPROFILE,PNAMED_PROFILE_INFO);
BOOL WINAPI GetPS2ColorRenderingDictionary(HPROFILE,DWORD,PBYTE,PDWORD,PBOOL);
BOOL WINAPI GetPS2ColorRenderingIntent(HPROFILE,DWORD,PBYTE,PDWORD);
BOOL WINAPI GetPS2ColorSpaceArray(HPROFILE,DWORD,DWORD,PBYTE,PDWORD,PBOOL);
BOOL WINAPI GetStandardColorSpaceProfileA(PCSTR,DWORD,PSTR,PDWORD);
BOOL WINAPI GetStandardColorSpaceProfileW(PCWSTR,DWORD,PWSTR,PDWORD);
BOOL WINAPI InstallColorProfileA(PCSTR,PCSTR);
BOOL WINAPI InstallColorProfileW(PCWSTR,PCWSTR);
BOOL WINAPI IsColorProfileTagPresent(HPROFILE,TAGTYPE,PBOOL);
BOOL WINAPI IsColorProfileValid(HPROFILE,PBOOL);
HPROFILE WINAPI OpenColorProfileA(PPROFILE,DWORD,DWORD,DWORD);
HPROFILE WINAPI OpenColorProfileW(PPROFILE,DWORD,DWORD,DWORD);
BOOL WINAPI RegisterCMMA(PCSTR,DWORD,PCSTR);
BOOL WINAPI RegisterCMMW(PCWSTR,DWORD,PCWSTR);
BOOL WINAPI SelectCMM(DWORD);
BOOL WINAPI SetColorProfileElement(HPROFILE,TAGTYPE,DWORD,PDWORD,PVOID);
BOOL WINAPI SetColorProfileElementReference(HPROFILE,TAGTYPE,TAGTYPE);
BOOL WINAPI SetColorProfileElementSize(HPROFILE,TAGTYPE,DWORD);
BOOL WINAPI SetColorProfileHeader(HPROFILE,PPROFILEHEADER);
BOOL WINAPI SetStandardColorSpaceProfileA(PCSTR,DWORD,PCSTR);
BOOL WINAPI SetStandardColorSpaceProfileW(PCWSTR,DWORD,PCSTR);
BOOL WINAPI SetupColorMatchingA(PCOLORMATCHSETUPA);
BOOL WINAPI SetupColorMatchingW(PCOLORMATCHSETUPW);
BOOL WINAPI TranslateBitmapBits(HTRANSFORM,PVOID,BMFORMAT,DWORD,DWORD,DWORD,PVOID,BMFORMAT,DWORD,PBMCALLBACKFN,ULONG);
BOOL WINAPI TranslateColors(HTRANSFORM,PCOLOR,DWORD,COLORTYPE,PCOLOR,COLORTYPE);
BOOL WINAPI UninstallColorProfileA(PCSTR,PCSTR,BOOL);
BOOL WINAPI UninstallColorProfileW(PCWSTR,PCWSTR,BOOL);
BOOL WINAPI UnregisterCMMA(PCSTR,DWORD);
BOOL WINAPI UnregisterCMMW(PCWSTR,DWORD);

#ifdef UNICODE
typedef PCMSCALLBACKW PCMSCALLBACK;
typedef COLORMATCHSETUPW COLORMATCHSETUP,*PCOLORMATCHSETUP,*LPCOLORMATCHSETUP;
typedef ENUMTYPEW ENUMTYPE,*PENUMTYPE,*LPENUMTYPE;
#define AssociateColorProfileWithDevice AssociateColorProfileWithDeviceW
#define CreateColorTransform CreateColorTransformW
#define CreateProfileFromLogColorSpace CreateProfileFromLogColorSpaceW
#define DisassociateColorProfileFromDevice DisassociateColorProfileFromDeviceW
#define EnumColorProfiles EnumColorProfilesW
#define GetColorDirectory GetColorDirectoryW
#define GetStandardColorSpaceProfile GetStandardColorSpaceProfileW
#define InstallColorProfile InstallColorProfileW
#define OpenColorProfile OpenColorProfileW
#define RegisterCMM RegisterCMMW
#define SetStandardColorSpaceProfile SetStandardColorSpaceProfileW
#define SetupColorMatching SetupColorMatchingW
#define UninstallColorProfile UninstallColorProfileW
#define UnregisterCMM UnregisterCMMW
#else /* UNICODE */
typedef PCMSCALLBACKA PCMSCALLBACK;
typedef COLORMATCHSETUPA COLORMATCHSETUP,*PCOLORMATCHSETUP,*LPCOLORMATCHSETUP;
typedef ENUMTYPEA ENUMTYPE,*PENUMTYPE,*LPENUMTYPE;
#define AssociateColorProfileWithDevice AssociateColorProfileWithDeviceA
#define CreateColorTransform CreateColorTransformA
#define CreateProfileFromLogColorSpace CreateProfileFromLogColorSpaceA
#define DisassociateColorProfileFromDevice DisassociateColorProfileFromDeviceA
#define EnumColorProfiles EnumColorProfilesA
#define GetColorDirectory GetColorDirectoryA
#define GetStandardColorSpaceProfile GetStandardColorSpaceProfileA
#define InstallColorProfile InstallColorProfileA
#define OpenColorProfile OpenColorProfileA
#define RegisterCMM RegisterCMMA
#define SetStandardColorSpaceProfile SetStandardColorSpaceProfileA
#define SetupColorMatching SetupColorMatchingA
#define UninstallColorProfile UninstallColorProfileA
#define UnregisterCMM UnregisterCMMA
#endif /* !UNICODE */

#endif /* (_WIN32_WINDOWS >= 0x0410 || _WIN32_WINNT >= 0x0500) */

#ifdef __cplusplus
}
#endif

#endif /* _ICM_H */
