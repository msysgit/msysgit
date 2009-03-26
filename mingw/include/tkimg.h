/*
 * tkimg.h --
 *
 *	Interface to tkimg Base package.
 *
 * Copyright (c) 2002 Andreas Kupries <andreas_kupries@users.sourceforge.net>
 *
 * Zveno Pty Ltd makes this software and associated documentation
 * available free of charge for any purpose.  You may make copies
 * of the software but you must include all of this notice on any copy.
 *
 * Zveno Pty Ltd does not warrant that this software is error free
 * or fit for any purpose.  Zveno Pty Ltd disclaims any liability for
 * all claims, expenses, losses, damages and costs any user may incur
 * as a result of using, copying or modifying the software.
 *
 * $Id: tkimg.h,v 1.4 2004/06/03 21:54:42 andreas_kupries Exp $
 *
 */

#ifndef __TKIMG_H__
#define __TKIMG_H__

#include <stdio.h> /* stdout, and other definitions */
#include "tk.h"

/*
 * Used to block the rest of this header file from resource compilers so
 * we can just get the version info.
 */
#ifndef RC_INVOKED

/* TIP 27 update. If CONST84 is not defined we are compiling against a
 * core before 8.4 and have to disable some CONST'ness.
 */

#ifndef CONST84
#   define CONST84
#endif

/*
 * Fix the Borland bug that's in the EXTERN macro from tcl.h.
 */
#ifndef TCL_EXTERN
#   undef DLLIMPORT
#   undef DLLEXPORT
#   if defined(STATIC_BUILD)
#	define DLLIMPORT
#	define DLLEXPORT
#   elif (defined(__WIN32__) && (defined(_MSC_VER) || (__BORLANDC__ >= 0x0550) || (defined(__GNUC__) && defined(__declspec)))) || (defined(MAC_TCL) && FUNCTION_DECLSPEC)
#	define DLLIMPORT __declspec(dllimport)
#	define DLLEXPORT __declspec(dllexport)
#   elif defined(__BORLANDC__)
#	define OLDBORLAND 1
#	define DLLIMPORT __import
#	define DLLEXPORT __export
#   else
#	define DLLIMPORT
#	define DLLEXPORT
#   endif
    /* Avoid name mangling from C++ compilers. */
#   ifdef __cplusplus
#	define TCL_EXTRNC extern "C"
#   else
#	define TCL_EXTRNC extern
#   endif
    /* Pre-5.5 Borland requires the attributes be placed after the */
    /* return type. */
#   ifdef OLDBORLAND
#	define TCL_EXTERN(RTYPE) TCL_EXTRNC RTYPE TCL_STORAGE_CLASS
#   else
#	define TCL_EXTERN(RTYPE) TCL_EXTRNC TCL_STORAGE_CLASS RTYPE
#   endif
#endif

/*
 * These macros are used to control whether functions are being declared for
 * import or export in Windows, 
 * They map to no-op declarations on non-Windows systems.
 * Assumes that tcl.h defines DLLEXPORT & DLLIMPORT correctly.
 * The default build on windows is for a DLL, which causes the DLLIMPORT
 * and DLLEXPORT macros to be nonempty. To build a static library, the
 * macro STATIC_BUILD should be defined before the inclusion of tcl.h
 *
 * If a function is being declared while it is being built
 * to be included in a shared library, then it should have the DLLEXPORT
 * storage class.  If is being declared for use by a module that is going to
 * link against the shared library, then it should have the DLLIMPORT storage
 * class.  If the symbol is beind declared for a static build or for use from a
 * stub library, then the storage class should be empty.
 *
 * The convention is that a macro called BUILD_xxxx, where xxxx is the
 * name of a library we are building, is set on the compile line for sources
 * that are to be placed in the library.  When this macro is set, the
 * storage class will be set to DLLEXPORT.  At the end of the header file, the
 * storage class will be reset to DLLIMPORt.
 */

#undef TCL_STORAGE_CLASS
#ifdef BUILD_tkimg
# define TCL_STORAGE_CLASS DLLEXPORT
#else
# ifdef USE_TKIMG_STUBS
#  define TCL_STORAGE_CLASS
# else
#  define TCL_STORAGE_CLASS DLLIMPORT
# endif
#endif

/*
 *----------------------------------------------------------------------------
 * C API for Tkimg generic layer
 *----------------------------------------------------------------------------
 */

typedef struct tkimg_MFile {
    Tcl_DString *buffer;/* pointer to dynamical string */
    char *data;		/* mmencoded source string */
    int c;		/* bits left over from previous char */
    int state;		/* decoder state (0-4 or IMG_DONE) */
    int length;		/* length of physical line already written */
} tkimg_MFile;

#define IMG_SPECIAL	 (1<<8)
#define IMG_PAD		(IMG_SPECIAL+1)
#define IMG_SPACE	(IMG_SPECIAL+2)
#define IMG_BAD		(IMG_SPECIAL+3)
#define IMG_DONE	(IMG_SPECIAL+4)
#define IMG_CHAN        (IMG_SPECIAL+5)
#define IMG_STRING	(IMG_SPECIAL+6)

#define IMG_TCL		(1<<9)
#define IMG_OBJS	(1<<10)
#define IMG_PERL	(1<<11)
#define IMG_UTF		(1<<12)
#define IMG_NEWPHOTO	(1<<13)

/*
 *----------------------------------------------------------------------------
 * Function prototypes for publically accessible routines
 *----------------------------------------------------------------------------
 */

#include "tkimgDecls.h"

/*
 * Convenience macro dealing with the 8.3 / 8.4 difference regarding
 * the signature of Tk_PhotoPutBlock [TIP 98].
 *
 * Note: The current implementation makes this a compile time decision.
 *       In the future we might realize a runtime decision instead.
 */

#if (TK_MAJOR_VERSION > 8) || ((TK_MAJOR_VERSION == 8) && (TK_MINOR_VERSION > 4))
/* TIP 116 */
#define tkimg_PhotoPutBlockTk(interp,hdl,b,x,y,w,h) Tk_PhotoPutBlock(interp,hdl, b, x, y, w, h, TK_PHOTO_COMPOSITE_OVERLAY)
#elif (TK_MAJOR_VERSION > 8) || ((TK_MAJOR_VERSION == 8) && (TK_MINOR_VERSION > 3))
#define tkimg_PhotoPutBlockTk(interp,hdl,b,x,y,w,h) Tk_PhotoPutBlock(hdl, b, x, y, w, h, TK_PHOTO_COMPOSITE_OVERLAY)
#else
#define tkimg_PhotoPutBlockTk(interp,hdl,b,x,y,w,h) Tk_PhotoPutBlock(hdl, b, x, y, w, h)
#endif

#if (TK_MAJOR_VERSION > 8) || ((TK_MAJOR_VERSION == 8) && (TK_MINOR_VERSION > 4))
#define tkimg_PhotoExpand(hdl,interp,w,h)  Tk_PhotoExpand(interp, hdl, w, h)
#define tkimg_PhotoSetSize(interp,hdl,w,h) Tk_PhotoSetSize(interp, hdl, w, h)
#else
#define tkimg_PhotoExpand(hdl,interp,w,h)  Tk_PhotoExpand(hdl, w, h)
#define tkimg_PhotoSetSize(interp,hdl,w,h) Tk_PhotoSetSize(hdl, w, h)
#endif

/*
 *----------------------------------------------------------------------------
 * Function prototypes for stub initialization.
 *----------------------------------------------------------------------------
 */

#ifdef USE_TKIMG_STUBS
EXTERN CONST char *
Tkimg_InitStubs _ANSI_ARGS_((Tcl_Interp *interp, CONST char *version, int exact));
#else
/*
 * When not using stubs, make it a macro.
 */

#define Tkimg_InitStubs(interp, version, exact) \
    Tcl_PkgRequire(interp, "tkimg", version, exact)
#endif

#undef TCL_STORAGE_CLASS
#define TCL_STORAGE_CLASS DLLIMPORT

#endif /* RC_INVOKED */
#endif /* __TKIMG_H__ */
