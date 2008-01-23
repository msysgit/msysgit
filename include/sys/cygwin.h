/* sys/cygwin.h

   Copyright 1997, 1998, 2000, 2001 Red Hat, Inc.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#ifndef _SYS_CYGWIN_H
#define _SYS_CYGWIN_H

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

extern pid_t cygwin32_winpid_to_pid (int);
extern void cygwin32_win32_to_posix_path_list (const char *, char *);
extern int cygwin32_win32_to_posix_path_list_buf_size (const char *);
extern void cygwin32_posix_to_win32_path_list (const char *, char *);
extern int cygwin32_posix_to_win32_path_list_buf_size (const char *);
extern int cygwin32_conv_to_win32_path (const char *, char *);
extern int cygwin32_conv_to_full_win32_path (const char *, char *);
extern void cygwin32_conv_to_posix_path (const char *, char *);
extern void cygwin32_conv_to_full_posix_path (const char *, char *);
extern int cygwin32_posix_path_list_p (const char *);
extern void cygwin32_split_path (const char *, char *, char *);

extern pid_t cygwin_winpid_to_pid (int);
extern int cygwin_win32_to_posix_path_list (const char *, char *);
extern int cygwin_win32_to_posix_path_list_buf_size (const char *);
extern int cygwin_posix_to_win32_path_list (const char *, char *);
extern int cygwin_posix_to_win32_path_list_buf_size (const char *);
extern int cygwin_conv_to_win32_path (const char *, char *);
extern int cygwin_conv_to_full_win32_path (const char *, char *);
extern int cygwin_conv_to_posix_path (const char *, char *);
extern int cygwin_conv_to_full_posix_path (const char *, char *);
extern int cygwin_posix_path_list_p (const char *);
extern void cygwin_split_path (const char *, char *, char *);

struct __cygwin_perfile
{
  const char *name;
  unsigned flags;
};

/* External interface stuff */

typedef enum
  {
    CW_LOCK_PINFO,
    CW_UNLOCK_PINFO,
    CW_GETTHREADNAME,
    CW_GETPINFO,
    CW_SETPINFO,
    CW_SETTHREADNAME,
    CW_GETVERSIONINFO,
    CW_READ_V1_MOUNT_TABLES,
    CW_USER_DATA,
    CW_PERFILE,
    CW_GET_CYGDRIVE_PREFIXES,
    CW_GETPINFO_FULL,
    CW_INIT_EXCEPTIONS,
    CW_GET_CYGDRIVE_INFO
  } cygwin_getinfo_types;

#define CW_NEXTPID	0x80000000	// or with pid to get next one

/* Flags associated with process_state */
enum
{
  PID_IN_USE	       = 0x0001, // Entry in use.
  PID_ZOMBIE	       = 0x0002, // Child exited: no parent wait.
  PID_STOPPED	       = 0x0004, // Waiting for SIGCONT.
  PID_TTYIN	       = 0x0008, // Waiting for terminal input.
  PID_TTYOU	       = 0x0010, // Waiting for terminal output.
  PID_ORPHANED	       = 0x0020, // Member of an orphaned process group.
  PID_ACTIVE	       = 0x0040, // Pid accepts signals.
  PID_CYGPARENT	       = 0x0080, // Set if parent was a cygwin app.
  PID_SPLIT_HEAP       = 0x0100, // Set if the heap has been split,
				 //  which means we can't fork again.
  PID_UNUSED	       = 0x0200, // Flag that pid should be cleared from parent's
				 //  wait list
  PID_UNUSED1	       = 0x0400, // Set if process uses Winsock.
  PID_INITIALIZING     = 0x0800, // Set until ready to receive signals.
  PID_USETTY	       = 0x1000, // Setting this enables or disables cygwin's
				 //  tty support.  This is inherited by
				 //  all execed or forked processes.
  PID_UNUSED2	       = 0x2000, // child has execed
  PID_EXECED	       = 0x4000, // redirect to original pid info block
  PID_NOREDIR	       = 0x8000, // don't redirect if execed
  PID_EXITED	       = 0x80000000 // Free entry.
};

#ifdef WINVER
#ifdef _PATH_PASSWD
extern HANDLE cygwin_logon_user (const struct passwd *, const char *);
#endif

/* This lives in the app and is initialized before jumping into the DLL.
   It should only contain stuff which the user's process needs to see, or
   which is needed before the user pointer is initialized, or is needed to
   carry inheritance information from parent to child.  Note that it cannot
   be used to carry inheritance information across exec!

   Remember, this structure is linked into the application's executable.
   Changes to this can invalidate existing executables, so we go to extra
   lengths to avoid having to do it.

   When adding/deleting members, remember to adjust {public,internal}_reserved.
   The size of the class shouldn't change [unless you really are prepared to
   invalidate all existing executables].  The program does a check (using
   SIZEOF_PER_PROCESS) to make sure you remember to make the adjustment.
*/

#ifdef __cplusplus
class ResourceLocks;
class MTinterface;
#endif

struct per_process
{
  char *initial_sp;

  /* The offset of these 3 values can never change. */
  /* magic_biscuit is the size of this class and should never change. */
  unsigned long magic_biscuit;
  unsigned long dll_major;
  unsigned long dll_minor;

  struct _reent **impure_ptr_ptr;
  char ***envptr;

  /* Used to point to the memory machine we should use.  Usually these
     point back into the dll, but they can be overridden by the user. */
  void *(*malloc)(size_t);
  void (*free)(void *);
  void *(*realloc)(void *, size_t);

  int *fmode_ptr;

  int (*main)(int, char **, char **);
  void (**ctors)(void);
  void (**dtors)(void);

  /* For fork */
  void *data_start;
  void *data_end;
  void *bss_start;
  void *bss_end;

  void *(*calloc)(size_t, size_t);
  /* For future expansion of values set by the app. */
  void (*premain[4]) (int, char **, struct per_process *);

  /* The rest are *internal* to cygwin.dll.
     Those that are here because we want the child to inherit the value from
     the parent (which happens when bss is copied) are marked as such. */

  /* non-zero of ctors have been run.  Inherited from parent. */
  int run_ctors_p;

  DWORD unused[7];

  /* Non-zero means the task was forked.  The value is the pid.
     Inherited from parent. */
  int forkee;

  HMODULE hmodule;

  DWORD api_major;		/* API version that this program was */
  DWORD api_minor;		/*  linked with */
  /* For future expansion, so apps won't have to be relinked if we
     add an item. */
  DWORD unused2[5];

#if defined (__INSIDE_CYGWIN__) || defined (__INSIDE_MSYS__)
  ResourceLocks *resourcelocks;
  MTinterface *threadinterface;
#else
  void *resourcelocks;
  void *threadinterface;
#endif
  struct _reent *impure_ptr;
};
#define per_process_overwrite ((unsigned) &(((struct per_process *) NULL)->resourcelocks))

extern void cygwin_premain0 (int argc, char **argv, struct per_process *);
extern void cygwin_premain1 (int argc, char **argv, struct per_process *);
extern void cygwin_premain2 (int argc, char **argv, struct per_process *);
extern void cygwin_premain3 (int argc, char **argv, struct per_process *);

extern void cygwin_set_impersonation_token (const HANDLE);

/* included if <windows.h> is included */
extern int cygwin32_attach_handle_to_fd (char *, int, HANDLE, mode_t, DWORD);
extern int cygwin_attach_handle_to_fd (char *, int, HANDLE, mode_t, DWORD);

#include <sys/resource.h>

#define TTY_CONSOLE	0x40000000

struct external_pinfo
  {
  pid_t pid;
  pid_t ppid;
  HANDLE hProcess;
  DWORD dwProcessId, dwSpawnedProcessId;
  uid_t uid;
  gid_t gid;
  pid_t pgid;
  pid_t sid;
  int ctty;
  mode_t umask;

  long start_time;
  struct rusage rusage_self;
  struct rusage rusage_children;

  char progname[MAX_PATH];

  DWORD strace_mask;
  HANDLE strace_file;

  DWORD process_state;
};

DWORD cygwin_internal (cygwin_getinfo_types, ...);
#endif /*WINVER*/

#ifdef __cplusplus
};
#endif

#endif /* _SYS_CYGWIN_H */
