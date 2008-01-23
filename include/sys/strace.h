/* sys/strace.h

   Copyright 1996, 1997, 1998, 1999, 2000, 2001 Red Hat, Inc.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

/* sys/strace.h */

/* This file contains routines for tracing system calls and other internal
   phenomenon.

   When tracing system calls, try to use the same style throughout:

   result = syscall (arg1, arg2, arg3) [optional extra stuff]

   If a system call can block (eg: read, write, wait), print another message
   before hanging so the user will know why the program has stopped.

   Note: __seterrno will also print a trace message.  Have that printed
   *first*.  This will make it easy to always know what __seterrno is
   refering to.  For the same reason, try not to have __seterrno messages
   printed alone.
*/

#ifndef _SYS_STRACE_H
#define _SYS_STRACE_H

#include <stdarg.h>

#ifdef __cplusplus

class strace
{
  int vsprntf (char *buf, const char *func, const char *infmt, va_list ap);
  void write (unsigned category, const char *buf, int count);
public:
  int microseconds ();
  int version;
  int active;
  int lmicrosec;
  int execing;
  strace() : version(1) {}
  void prntf (unsigned, const char *func, const char *, ...) /*__attribute__ ((regparm(3)))*/;
  void vprntf (unsigned, const char *func, const char *, va_list ap) /*__attribute__ ((regparm(3)))*/;
  void wm (int message, int word, int lon) __attribute__ ((regparm(3)));
};

extern strace strace;

#endif /* __cplusplus */

#define _STRACE_INTERFACE_ACTIVATE_ADDR  -1
#define _STRACE_INTERFACE_ACTIVATE_ADDR1 -2

/* Bitmasks of tracing messages to print.  */

#define _STRACE_ALL	 0x00001 // so behaviour of strace=1 is unchanged
#define _STRACE_FLUSH	 0x00002 // flush output buffer after every message
#define _STRACE_INHERIT  0x00004 // children inherit mask from parent
#define _STRACE_UHOH	 0x00008 // unusual or weird phenomenon
#define _STRACE_SYSCALL	 0x00010 // system calls
#define _STRACE_STARTUP	 0x00020 // argc/envp printout at startup
#define _STRACE_DEBUG    0x00040 // info to help debugging
#define _STRACE_PARANOID 0x00080 // paranoid info
#define _STRACE_TERMIOS	 0x00100 // info for debugging termios stuff
#define _STRACE_SELECT	 0x00200 // info on ugly select internals
#define _STRACE_WM	 0x00400 // trace windows messages (enable _strace_wm)
#define _STRACE_SIGP	 0x00800 // trace signal and process handling
#define _STRACE_MINIMAL	 0x01000 // very minimal strace output
#define _STRACE_EXITDUMP 0x04000 // dump strace cache on exit
#define _STRACE_SYSTEM	 0x08000 // cache strace messages
#define _STRACE_NOMUTEX	 0x10000 // don't use mutex for synchronization
#define _STRACE_MALLOC	 0x20000 // trace malloc calls
#define _STRACE_THREAD	 0x40000 // thread-locking calls
#define _STRACE_NOTALL	 0x80000 // don't include if _STRACE_ALL
#if defined (DEBUGGING)
#define _STRACE_ON strace.active = 1;
#define _STRACE_OFF strace.active = 0;
#else
#define _STRACE_ON
#define _STRACE_OFF
#endif

#ifdef __cplusplus
extern "C" {
#endif

void small_printf (const char *, ...);
void strace_printf (unsigned, const char *func, const char *, ...);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

#ifdef NOSTRACE
#define define_strace(c, f)
#define define_strace1(c, f)
#else
#ifdef NEW_MACRO_VARARGS
/* Output message to strace log */

#define define_strace0(c,...) \
  do { \
      if ((c & _STRACE_SYSTEM) || strace.active) \
	strace.prntf (c, __PRETTY_FUNCTION__, __VA_ARGS__); \
    } \
  while (0)

#define define_strace(c, ...) define_strace0 (_STRACE_ ## c, __VA_ARGS__)
#define define_strace1(c, ...) define_strace0 ((_STRACE_ ## c | _STRACE_NOTALL), __VA_ARGS__)

#define debug_printf(...)	define_strace (DEBUG, __VA_ARGS__)
#define paranoid_printf(...)	define_strace (PARANOID, __VA_ARGS__)
#define select_printf(...)	define_strace (SELECT, __VA_ARGS__)
#define sigproc_printf(...)	define_strace (SIGP, __VA_ARGS__)
#define syscall_printf(...)	define_strace (SYSCALL, __VA_ARGS__)
#define system_printf(...)	define_strace (SYSTEM, __VA_ARGS__)
#define termios_printf(...)	define_strace (TERMIOS, __VA_ARGS__)
#define wm_printf(...)		define_strace (WM, __VA_ARGS__)
#define minimal_printf(...)	define_strace1 (MINIMAL, __VA_ARGS__)
#define malloc_printf(...)	define_strace1 (MALLOC, __VA_ARGS__)
#define thread_printf(...)	define_strace1 (THREAD, __VA_ARGS__)
#else
#define strace_printf_wrap(what, fmt, args...) \
   ((void) ({\
	if ((_STRACE_ ## what & _STRACE_SYSTEM) || strace.active) \
	  strace.prntf(_STRACE_ ## what, __PRETTY_FUNCTION__, fmt, ## args); \
	0; \
    }))
#define strace_printf_wrap1(what, fmt, args...) \
    ((void) ({\
	if ((_STRACE_ ## what & _STRACE_SYSTEM) || strace.active) \
	  strace.prntf((_STRACE_ ## what) | _STRACE_NOTALL, __PRETTY_FUNCTION__, fmt, ## args); \
	0; \
    }))

#define debug_printf(fmt, args...) strace_printf_wrap(DEBUG, fmt , ## args)
#if defined (DEBUGGING)
#define mdebug(mdebug_active, mdebug_function, mdebug_string) \
  do { \
      char mdebug_buf[2048]; \
      sprintf (mdebug_buf, "%s [%d]: %s", mdebug_function, mdebug_active, mdebug_string); \
      OutputDebugString (mdebug_buf); \
     } \
  while (0)
#else
#define mdebug(mdebug_active, mdebug_function, mdebug_string)
#endif
#define paranoid_printf(fmt, args...) strace_printf_wrap(PARANOID, fmt , ## args)
#define select_printf(fmt, args...) strace_printf_wrap(SELECT, fmt , ## args)
#define sigproc_printf(fmt, args...) strace_printf_wrap(SIGP, fmt , ## args)
#define syscall_printf(fmt, args...) strace_printf_wrap(SYSCALL, fmt , ## args)
#define system_printf(fmt, args...) strace_printf_wrap(SYSTEM, fmt , ## args)
#define termios_printf(fmt, args...) strace_printf_wrap(TERMIOS, fmt , ## args)
#define wm_printf(fmt, args...) strace_printf_wrap(WM, fmt , ## args)
#define minimal_printf(fmt, args...) strace_printf_wrap1(MINIMAL, fmt , ## args)
#define malloc_printf(fmt, args...) strace_printf_wrap1(MALLOC, fmt , ## args)
#define thread_printf(fmt, args...) strace_printf_wrap1(THREAD, fmt , ## args)
#endif /*NEW_MACRO_VARARGS*/
#endif /*NOSTRACE*/
#endif /* __cplusplus */
#endif /* _SYS_STRACE_H */
