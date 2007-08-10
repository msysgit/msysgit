#ifndef _BASETYPS_H
#define _BASETYPS_H
#if __GNUC__ >=3
#pragma GCC system_header
#endif

#ifndef _OBJC_NO_COM_
# ifdef __cplusplus
#  define EXTERN_C extern "C"
# else
#  define EXTERN_C extern
# endif  /* __cplusplus */ 
# ifndef __int64
#  define __int64 long long
# endif
# ifndef __int32
#  define __int32 long
# endif
# ifndef __int16
#  define __int16 short
# endif
# ifndef __int8
#  define __int8 char
# endif
# ifndef __small
#  define __small char
# endif
# ifndef __hyper
#  define __hyper long long
# endif
# define STDMETHODCALLTYPE	__stdcall
# define STDMETHODVCALLTYPE	__cdecl
# define STDAPICALLTYPE	__stdcall
# define STDAPIVCALLTYPE	__cdecl
# define STDAPI	EXTERN_C HRESULT STDAPICALLTYPE
# define STDAPI_(t)	EXTERN_C t STDAPICALLTYPE
# define STDMETHODIMP	HRESULT STDMETHODCALLTYPE
# define STDMETHODIMP_(t)	t STDMETHODCALLTYPE
# define STDAPIV	EXTERN_C HRESULT STDAPIVCALLTYPE
# define STDAPIV_(t)	EXTERN_C t STDAPIVCALLTYPE
# define STDMETHODIMPV	HRESULT STDMETHODVCALLTYPE
# define STDMETHODIMPV_(t)	t STDMETHODVCALLTYPE
/* Newer MS compilers support the __interface keyword, but
   that has a specific meaning that is enforced by the compiler.
   For now, just get 'interface' out of the global namespace
   for __OBJC__ */
# define _COM_interface	struct
# ifndef __OBJC__
#  define interface	_COM_interface
# endif
# if defined(__cplusplus) && !defined(CINTERFACE)
#  define STDMETHOD(m)	virtual HRESULT STDMETHODCALLTYPE m
#  define STDMETHOD_(t,m)	virtual t STDMETHODCALLTYPE m
#  define PURE	=0
#  define THIS_
#  define THIS	void
/*
  __attribute__((com_interface)) is obsolete in __GNUC__ >= 3
  g++ vtables are now COM-compatible by default
*/
#  if defined(__GNUC__) &&  __GNUC__ < 3 && !defined(NOCOMATTRIBUTE)
#   define DECLARE_INTERFACE(i) _COM_interface __attribute__((com_interface)) i
#   define DECLARE_INTERFACE_(i,b) _COM_interface __attribute__((com_interface)) i : public b
#  else
#   define DECLARE_INTERFACE(i) _COM_interface i
#   define DECLARE_INTERFACE_(i,b) _COM_interface i : public b
#  endif
# else
#  define STDMETHOD(m)	HRESULT(STDMETHODCALLTYPE *m)
#  define STDMETHOD_(t,m)	t(STDMETHODCALLTYPE *m)
#  define PURE
#  define THIS_	INTERFACE *,
#  define THIS	INTERFACE *
#  ifndef CONST_VTABLE
#   define CONST_VTABLE
#  endif
#  define DECLARE_INTERFACE(i) \
   typedef _COM_interface i { CONST_VTABLE struct i##Vtbl *lpVtbl; } i; \
   typedef CONST_VTABLE struct i##Vtbl i##Vtbl; \
   CONST_VTABLE struct i##Vtbl
#  define DECLARE_INTERFACE_(i,b) DECLARE_INTERFACE(i)
# endif
# define BEGIN_INTERFACE
# define END_INTERFACE

# define FWD_DECL(i) typedef _COM_interface i i
# if defined(__cplusplus) && !defined(CINTERFACE)
#  define IENUM_THIS(T)
#  define IENUM_THIS_(T)
# else
#  define IENUM_THIS(T) T*
#  define IENUM_THIS_(T) T*,
# endif
# define DECLARE_ENUMERATOR_(I,T) \
         DECLARE_INTERFACE_(I,IUnknown) \
         { \
	  STDMETHOD(QueryInterface)(IENUM_THIS_(I) REFIID,PVOID*) PURE; \
	  STDMETHOD_(ULONG,AddRef)(IENUM_THIS(I)) PURE; \
	  STDMETHOD_(ULONG,Release)(IENUM_THIS(I)) PURE; \
	  STDMETHOD(Next)(IENUM_THIS_(I) ULONG,T*,ULONG*) PURE; \
	  STDMETHOD(Skip)(IENUM_THIS_(I) ULONG) PURE; \
	  STDMETHOD(Reset)(IENUM_THIS(I)) PURE; \
	  STDMETHOD(Clone)(IENUM_THIS_(I) I**) PURE; \
         }
# define DECLARE_ENUMERATOR(T) DECLARE_ENUMERATOR_(IEnum##T,T)

#endif /* _OBJC_NO_COM_ */

#ifdef _GUID_DEFINED
# warning _GUID_DEFINED is deprecated, use GUID_DEFINED instead
#endif

#if ! (defined _GUID_DEFINED || defined GUID_DEFINED) /* also defined in winnt.h */
#define GUID_DEFINED
typedef struct _GUID
{
    unsigned long Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char Data4[8];
} GUID,*REFGUID,*LPGUID;
#endif /* GUID_DEFINED */
#ifndef UUID_DEFINED
#define UUID_DEFINED
typedef GUID UUID;
#endif /* UUID_DEFINED */
#ifndef __IID_DEFINED__
#define __IID_DEFINED__
typedef GUID IID;
#endif /* __IID_DEFINED__ */
typedef GUID CLSID;
typedef CLSID *LPCLSID;
typedef IID *LPIID;
typedef IID *REFIID;
typedef CLSID *REFCLSID;
typedef GUID FMTID;
typedef FMTID *REFFMTID;
typedef unsigned long error_status_t;
#define uuid_t UUID
typedef unsigned long PROPID;

#ifndef _REFGUID_DEFINED
#if defined (__cplusplus) && !defined (CINTERFACE)
#define REFGUID const GUID&
#define REFIID const IID&
#define REFCLSID const CLSID&
#define REFFMTID const FMTID&
#else
#define REFGUID const GUID* const
#define REFIID const IID* const
#define REFCLSID const CLSID* const
#define REFFMTID const FMTID* const
#endif
#define _REFGUID_DEFINED
#define _REFIID_DEFINED
#define _REFCLSID_DEFINED
#define _REFFMTID_DEFINED
#endif
#ifndef GUID_SECTION
#define GUID_SECTION ".text"
#endif
/* Explicit naming of .text section for readonly data is only
   needed for older GGC (pre-2.95).
   More recent (3.4) GCC puts readonly data in .rdata.  */
#if defined (__GNUC__) && (__GNUC__ <= 2 && __GNUC_MINOR__ < 95) 
#define GUID_SECT __attribute__ ((section (GUID_SECTION)))
#else
#define GUID_SECT
#endif
#if !defined(INITGUID) || (defined(INITGUID) && defined(__cplusplus))
#define GUID_EXT EXTERN_C
#else
#define GUID_EXT
#endif
#ifdef INITGUID
#define DEFINE_GUID(n,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) GUID_EXT const GUID n GUID_SECT = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}
#define DEFINE_OLEGUID(n,l,w1,w2) DEFINE_GUID(n,l,w1,w2,0xC0,0,0,0,0,0,0,0x46)
#else
#define DEFINE_GUID(n,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) GUID_EXT const GUID n
#define DEFINE_OLEGUID(n,l,w1,w2) DEFINE_GUID(n,l,w1,w2,0xC0,0,0,0,0,0,0,0x46)
#endif
#endif 
