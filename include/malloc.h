/* malloc.h -- header file for memory routines.  */

#ifndef _INCLUDE_MALLOC_H_
#define _INCLUDE_MALLOC_H_

#include <_ansi.h>
#include <sys/reent.h>

#define __need_size_t
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* This version of struct mallinfo must match the one in
   libc/stdlib/mallocr.c.  */

struct mallinfo {
  int arena;    /* total space allocated from system */
  int ordblks;  /* number of non-inuse chunks */
  int smblks;   /* unused -- always zero */
  int hblks;    /* number of mmapped regions */
  int hblkhd;   /* total space in mmapped regions */
  int usmblks;  /* unused -- always zero */
  int fsmblks;  /* unused -- always zero */
  int uordblks; /* total allocated space */
  int fordblks; /* total non-inuse space */
  int keepcost; /* top-most, releasable (via malloc_trim) space */
};	

/* The routines.  */

extern _PTR malloc _PARAMS ((size_t));
extern _PTR _malloc_r _PARAMS ((struct _reent *, size_t));

extern _VOID free _PARAMS ((_PTR));
extern _VOID _free_r _PARAMS ((struct _reent *, _PTR));

extern _PTR realloc _PARAMS ((_PTR, size_t));
extern _PTR _realloc_r _PARAMS ((struct _reent *, _PTR, size_t));

extern _PTR calloc _PARAMS ((size_t, size_t));
extern _PTR _calloc_r _PARAMS ((struct _reent *, size_t, size_t));

extern _PTR memalign _PARAMS ((size_t, size_t));
extern _PTR _memalign_r _PARAMS ((struct _reent *, size_t, size_t));

extern struct mallinfo mallinfo _PARAMS ((void));
extern struct mallinfo _mallinfo_r _PARAMS ((struct _reent *));

extern void malloc_stats _PARAMS ((void));
extern void _malloc_stats_r _PARAMS ((struct _reent *));

extern int mallopt _PARAMS ((int, int));
extern int _mallopt_r _PARAMS ((struct _reent *, int, int));

extern size_t malloc_usable_size _PARAMS ((_PTR));
extern size_t _malloc_usable_size_r _PARAMS ((struct _reent *, _PTR));

/* These aren't too useful on an embedded system, but we define them
   anyhow.  */

extern _PTR valloc _PARAMS ((size_t));
extern _PTR _valloc_r _PARAMS ((struct _reent *, size_t));

extern _PTR pvalloc _PARAMS ((size_t));
extern _PTR _pvalloc_r _PARAMS ((struct _reent *, size_t));

extern int malloc_trim _PARAMS ((size_t));
extern int _malloc_trim_r _PARAMS ((struct _reent *, size_t));

/* A compatibility routine for an earlier version of the allocator.  */

extern _VOID mstats _PARAMS ((char *));
extern _VOID _mstats_r _PARAMS ((struct _reent *, char *));

/* SVID2/XPG mallopt options */

#define M_MXFAST  1    /* UNUSED in this malloc */
#define M_NLBLKS  2    /* UNUSED in this malloc */
#define M_GRAIN   3    /* UNUSED in this malloc */
#define M_KEEP    4    /* UNUSED in this malloc */

/* mallopt options that actually do something */
  
#define M_TRIM_THRESHOLD    -1
#define M_TOP_PAD           -2
#define M_MMAP_THRESHOLD    -3 
#define M_MMAP_MAX          -4

#if !defined (__CYGWIN__) && !defined (__MSYS__)
/* Some systems provide this, so do too for compatibility.  */
extern void cfree _PARAMS ((_PTR));
#endif /* not __CYGWIN__ and not __MSYS__ */

#ifdef __cplusplus
}
#endif

#endif /* _INCLUDE_MALLOC_H_ */
