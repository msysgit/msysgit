/* math.h -- Definitions for the math floating point package.  */

#ifndef  _MATH_H_
#ifdef __cplusplus
extern "C" {
#endif
#define  _MATH_H_

#include <sys/reent.h>
#include <machine/ieeefp.h>
#include "_ansi.h"

#ifndef HUGE_VAL

/* Define HUGE_VAL as infinity, unless HUGE_VAL is already defined
   (which might have been done by something like math-68881.h).  */

union __dmath
{
  __uint32_t i[2];
  double d;
};

/* Declare this as an array without bounds so that no matter what small data
   support a port and/or library has, this reference will be via the general
   method for accessing globals. */
extern __IMPORT const union __dmath __infinity[];

#define HUGE_VAL (__infinity[0].d)

#endif /* ! defined (HUGE_VAL) */

/* Reentrant ANSI C functions.  */

#ifndef __math_68881
extern double atan _PARAMS((double));
extern double cos _PARAMS((double));
extern double sin _PARAMS((double));
extern double tan _PARAMS((double));
extern double tanh _PARAMS((double));
extern double frexp _PARAMS((double, int *));
extern double modf _PARAMS((double, double *));
extern double ceil _PARAMS((double));
extern double fabs _PARAMS((double));
extern double floor _PARAMS((double));
#endif /* ! defined (__math_68881) */

/* Non reentrant ANSI C functions.  */

#ifndef _REENT_ONLY
#ifndef __math_6881
extern double acos _PARAMS((double));
extern double asin _PARAMS((double));
extern double atan2 _PARAMS((double, double));
extern double cosh _PARAMS((double));
extern double sinh _PARAMS((double));
extern double exp _PARAMS((double));
extern double ldexp _PARAMS((double, int));
extern double log _PARAMS((double));
extern double log10 _PARAMS((double));
extern double pow _PARAMS((double, double));
extern double sqrt _PARAMS((double));
extern double fmod _PARAMS((double, double));
#endif /* ! defined (__math_68881) */
#endif /* ! defined (_REENT_ONLY) */

#ifndef __STRICT_ANSI__

/* Non ANSI double precision functions.  */

extern double infinity _PARAMS((void));
extern double nan _PARAMS((void));
extern int isnan _PARAMS((double));
extern int isinf _PARAMS((double));
extern int finite _PARAMS((double));
extern double copysign _PARAMS((double, double));
extern int ilogb _PARAMS((double));

extern double asinh _PARAMS((double));
extern double cbrt _PARAMS((double));
extern double nextafter _PARAMS((double, double));
extern double rint _PARAMS((double));
extern double scalbn _PARAMS((double, int));

#ifndef __math_68881
extern double log1p _PARAMS((double));
extern double expm1 _PARAMS((double));
#endif /* ! defined (__math_68881) */

#ifndef _REENT_ONLY
extern double acosh _PARAMS((double));
extern double atanh _PARAMS((double));
extern double remainder _PARAMS((double, double));
extern double gamma _PARAMS((double));
extern double gamma_r _PARAMS((double, int *));
extern double lgamma _PARAMS((double));
extern double lgamma_r _PARAMS((double, int *));
extern double erf _PARAMS((double));
extern double erfc _PARAMS((double));
extern double y0 _PARAMS((double));
extern double y1 _PARAMS((double));
extern double yn _PARAMS((int, double));
extern double j0 _PARAMS((double));
extern double j1 _PARAMS((double));
extern double jn _PARAMS((int, double));
#define log2(x) (log (x) / M_LOG2_E)

#ifndef __math_68881
extern double hypot _PARAMS((double, double));
#endif

extern double cabs();
extern double drem _PARAMS((double, double));

#endif /* ! defined (_REENT_ONLY) */

/* Single precision versions of ANSI functions.  */

extern float atanf _PARAMS((float));
extern float cosf _PARAMS((float));
extern float sinf _PARAMS((float));
extern float tanf _PARAMS((float));
extern float tanhf _PARAMS((float));
extern float frexpf _PARAMS((float, int *));
extern float modff _PARAMS((float, float *));
extern float ceilf _PARAMS((float));
extern float fabsf _PARAMS((float));
extern float floorf _PARAMS((float));

#ifndef _REENT_ONLY
extern float acosf _PARAMS((float));
extern float asinf _PARAMS((float));
extern float atan2f _PARAMS((float, float));
extern float coshf _PARAMS((float));
extern float sinhf _PARAMS((float));
extern float expf _PARAMS((float));
extern float ldexpf _PARAMS((float, int));
extern float logf _PARAMS((float));
extern float log10f _PARAMS((float));
extern float powf _PARAMS((float, float));
extern float sqrtf _PARAMS((float));
extern float fmodf _PARAMS((float, float));
#endif /* ! defined (_REENT_ONLY) */

/* Other single precision functions.  */

extern float infinityf _PARAMS((void));
extern float nanf _PARAMS((void));
extern int isnanf _PARAMS((float));
extern int isinff _PARAMS((float));
extern int finitef _PARAMS((float));
extern float copysignf _PARAMS((float, float));
extern int ilogbf _PARAMS((float));

extern float asinhf _PARAMS((float));
extern float cbrtf _PARAMS((float));
extern float nextafterf _PARAMS((float, float));
extern float rintf _PARAMS((float));
extern float scalbnf _PARAMS((float, int));
extern float log1pf _PARAMS((float));
extern float expm1f _PARAMS((float));

#ifndef _REENT_ONLY
extern float acoshf _PARAMS((float));
extern float atanhf _PARAMS((float));
extern float remainderf _PARAMS((float, float));
extern float gammaf _PARAMS((float));
extern float gammaf_r _PARAMS((float, int *));
extern float lgammaf _PARAMS((float));
extern float lgammaf_r _PARAMS((float, int *));
extern float erff _PARAMS((float));
extern float erfcf _PARAMS((float));
extern float y0f _PARAMS((float));
extern float y1f _PARAMS((float));
extern float ynf _PARAMS((int, float));
extern float j0f _PARAMS((float));
extern float j1f _PARAMS((float));
extern float jnf _PARAMS((int, float));
#define log2f(x) (logf (x) / (float) M_LOG2_E)
extern float hypotf _PARAMS((float, float));

extern float cabsf();
extern float dremf _PARAMS((float, float));

#endif /* ! defined (_REENT_ONLY) */

/* The gamma functions use a global variable, signgam.  */
#ifndef _REENT_ONLY
#define signgam (*__signgam())
extern int *__signgam _PARAMS((void));
#endif /* ! defined (_REENT_ONLY) */

#define __signgam_r(ptr) ((ptr)->_new._reent._gamma_signgam)

/* The exception structure passed to the matherr routine.  */

#ifdef __cplusplus
struct __exception 
#else
struct exception 
#endif
{
  int type;
  char *name;
  double arg1;
  double arg2;
  double retval;
  int err;
};

#ifdef __cplusplus
extern int matherr _PARAMS((struct __exception *e));
#else
extern int matherr _PARAMS((struct exception *e));
#endif

/* Values for the type field of struct exception.  */

#define DOMAIN 1
#define SING 2
#define OVERFLOW 3
#define UNDERFLOW 4
#define TLOSS 5
#define PLOSS 6

/* Useful constants.  */

#define M_E		2.7182818284590452354
#define M_LOG2E		1.4426950408889634074
#define M_LOG10E	0.43429448190325182765
#define M_LN2		0.69314718055994530942
#define M_LN10		2.30258509299404568402
#define M_PI		3.14159265358979323846
#define M_TWOPI         (M_PI * 2.0)
#define M_PI_2		1.57079632679489661923
#define M_PI_4		0.78539816339744830962
#define M_3PI_4		2.3561944901923448370E0
#define M_SQRTPI        1.77245385090551602792981
#define M_1_PI		0.31830988618379067154
#define M_2_PI		0.63661977236758134308
#define M_2_SQRTPI	1.12837916709551257390
#define M_SQRT2		1.41421356237309504880
#define M_SQRT1_2	0.70710678118654752440
#define M_LN2LO         1.9082149292705877000E-10
#define M_LN2HI         6.9314718036912381649E-1
#define M_SQRT3   	1.73205080756887719000
#define M_IVLN10        0.43429448190325182765 /* 1 / log(10) */
#define M_LOG2_E        0.693147180559945309417
#define M_INVLN2        1.4426950408889633870E0  /* 1 / log(2) */

/* Global control over fdlibm error handling.  */

enum __fdlibm_version
{
  __fdlibm_ieee = -1,
  __fdlibm_svid,
  __fdlibm_xopen,
  __fdlibm_posix
};

#define _LIB_VERSION_TYPE enum __fdlibm_version
#define _LIB_VERSION __fdlib_version

extern __IMPORT _CONST _LIB_VERSION_TYPE _LIB_VERSION;

#define _IEEE_  __fdlibm_ieee
#define _SVID_  __fdlibm_svid
#define _XOPEN_ __fdlibm_xopen
#define _POSIX_ __fdlibm_posix

#endif /* ! defined (__STRICT_ANSI__) */

#ifdef __FAST_MATH__
#include <machine/fastmath.h>
#endif

#ifdef __cplusplus
}
#endif
#endif /* _MATH_H_ */
