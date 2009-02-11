/* profil.h: gprof profiling header file

   Copyright 1998, 1999, 2000, 2001, 2002 Red Hat, Inc.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

/*
 * This file is taken from Cygwin distribution. Please keep it in sync.
 * The differences should be within __MINGW32__ guard.
 */

/* profiling frequency.  (No larger than 1000) */
#define PROF_HZ			100

/* convert an addr to an index */
#define PROFIDX(pc, base, scale)	\
  ({									\
    size_t i = (pc - base) / 2;				\
    if (sizeof (unsigned long long int) > sizeof (size_t))		\
      i = (unsigned long long int) i * scale / 65536;			\
    else								\
      i = i / 65536 * scale + i % 65536 * scale / 65536;		\
    i;									\
  })

/* convert an index into an address */
#define PROFADDR(idx, base, scale)		\
  ((base)					\
   + ((((unsigned long long)(idx) << 16)	\
       / (unsigned long long)(scale)) << 1))

/* convert a bin size into a scale */
#define PROFSCALE(range, bins)		(((bins) << 16) / ((range) >> 1))

typedef void *_WINHANDLE;

struct profinfo {
    _WINHANDLE targthr;			/* thread to profile */
    _WINHANDLE profthr;			/* profiling thread */
    u_short *counter;			/* profiling counters */
    u_long lowpc, highpc;		/* range to be profiled */
    u_int scale;			/* scale value of bins */
};

int profile_ctl(struct profinfo *, char *, size_t, u_long, u_int);
int profil(char *, size_t, u_long, u_int);

