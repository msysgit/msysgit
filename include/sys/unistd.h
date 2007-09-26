#ifndef _SYS_UNISTD_H
#define _SYS_UNISTD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <_ansi.h>
#include <sys/types.h>
#include <sys/_types.h>
#define __need_size_t
#define __need_ptrdiff_t
#include <stddef.h>

extern char **environ;

void	_EXFUN(_exit, (int __status ) _ATTRIBUTE ((noreturn)));

int	_EXFUN(access,(const char *__path, int __amode ));
unsigned  _EXFUN(alarm, (unsigned __secs ));
int     _EXFUN(chdir, (const char *__path ));
int     _EXFUN(chmod, (const char *__path, mode_t __mode ));
int     _EXFUN(chown, (const char *__path, uid_t __owner, gid_t __group ));
#if defined (__CYGWIN__) || defined(__rtems__) || defined (__MSYS__)
int     _EXFUN(chroot, (const char *__path ));
#endif
int     _EXFUN(close, (int __fildes ));
char    _EXFUN(*ctermid, (char *__s ));
char    _EXFUN(*cuserid, (char *__s ));
int     _EXFUN(dup, (int __fildes ));
int     _EXFUN(dup2, (int __fildes, int __fildes2 ));
int     _EXFUN(execl, (const char *__path, const char *, ... ));
int     _EXFUN(execle, (const char *__path, const char *, ... ));
int     _EXFUN(execlp, (const char *__file, const char *, ... ));
int     _EXFUN(execv, (const char *__path, char * const __argv[] ));
int     _EXFUN(execve, (const char *__path, char * const __argv[], char * const __envp[] ));
int     _EXFUN(execvp, (const char *__file, char * const __argv[] ));
int     _EXFUN(fchmod, (int __fildes, mode_t __mode ));
int     _EXFUN(fchown, (int __fildes, uid_t __owner, gid_t __group ));
pid_t   _EXFUN(fork, (void ));
long    _EXFUN(fpathconf, (int __fd, int __name ));
int     _EXFUN(fsync, (int __fd));
char    _EXFUN(*getcwd, (char *__buf, size_t __size ));
gid_t   _EXFUN(getegid, (void ));
uid_t   _EXFUN(geteuid, (void ));
gid_t   _EXFUN(getgid, (void ));
int     _EXFUN(getgroups, (int __gidsetsize, gid_t __grouplist[] ));
char    _EXFUN(*getlogin, (void ));
#if defined(_POSIX_THREAD_SAFE_FUNCTIONS)
int _EXFUN(getlogin_r, (char *name, size_t namesize) );
#endif
char 	_EXFUN(*getpass, (__const char *__prompt));
size_t  _EXFUN(getpagesize, (void));
pid_t   _EXFUN(getpgid, (pid_t));
pid_t   _EXFUN(getpgrp, (void ));
pid_t   _EXFUN(getpid, (void ));
pid_t   _EXFUN(getppid, (void ));
uid_t   _EXFUN(getuid, (void ));
#if defined (__CYGWIN__) || defined (__MSYS__)
char    _EXFUN(*getwd, (char *__buf ));
#endif
int     _EXFUN(isatty, (int __fildes ));
int     _EXFUN(lchown, (const char *__path, uid_t __owner, gid_t __group ));
int     _EXFUN(link, (const char *__path1, const char *__path2 ));
int	_EXFUN(nice, (int __nice_value ));
off_t   _EXFUN(lseek, (int __fildes, off_t __offset, int __whence ));
long    _EXFUN(pathconf, (const char *__path, int __name ));
int     _EXFUN(pause, (void ));
#if defined (__CYGWIN__) || defined (__MSYS__)
int	_EXFUN(pthread_atfork, (void (*)(void), void (*)(void), void (*)(void)));
#endif
int     _EXFUN(pipe, (int __fildes[2] ));
_READ_WRITE_RETURN_TYPE _EXFUN(read, (int __fd, void *__buf, size_t __nbyte ));
int     _EXFUN(rmdir, (const char *__path ));
#if defined(__rtems__)
void *  _EXFUN(sbrk,  (ptrdiff_t __incr));
#else
void *  _EXFUN(sbrk,  (size_t __incr));
#endif
#if defined(__CYGWIN__) || defined(__MSYS__)
int     _EXFUN(setegid, (gid_t __gid ));
int     _EXFUN(seteuid, (uid_t __uid ));
#endif
int     _EXFUN(setgid, (gid_t __gid ));
int     _EXFUN(setpgid, (pid_t __pid, pid_t __pgid ));
int     _EXFUN(setpgrp, (void ));
pid_t   _EXFUN(setsid, (void ));
int     _EXFUN(setuid, (uid_t __uid ));
unsigned _EXFUN(sleep, (unsigned int __seconds ));
void    _EXFUN(swab, (const void *, void *, ssize_t));
long    _EXFUN(sysconf, (int __name ));
pid_t   _EXFUN(tcgetpgrp, (int __fildes ));
int     _EXFUN(tcsetpgrp, (int __fildes, pid_t __pgrp_id ));
char    _EXFUN(*ttyname, (int __fildes ));
int     _EXFUN(unlink, (const char *__path ));
int     _EXFUN(vhangup, (void ));
_READ_WRITE_RETURN_TYPE _EXFUN(write, (int __fd, const void *__buf, size_t __nbyte ));

#ifndef        _POSIX_SOURCE
pid_t   _EXFUN(vfork, (void ));
#endif /* _POSIX_SOURCE */

/* Provide prototypes for most of the _<systemcall> names that are
   provided in newlib for some compilers.  */
int     _EXFUN(_close, (int __fildes ));
pid_t   _EXFUN(_fork, (void ));
pid_t   _EXFUN(_getpid, (void ));
int     _EXFUN(_link, (const char *__path1, const char *__path2 ));
off_t   _EXFUN(_lseek, (int __fildes, off_t __offset, int __whence ));
_READ_WRITE_RETURN_TYPE _EXFUN(_read, (int __fd, void *__buf, size_t __nbyte ));
void *  _EXFUN(_sbrk,  (size_t __incr));
int     _EXFUN(_unlink, (const char *__path ));
_READ_WRITE_RETURN_TYPE _EXFUN(_write, (int __fd, const void *__buf, size_t __nbyte ));
int     _EXFUN(_execve, (const char *__path, char * const __argv[], char * const __envp[] ));

#if defined(__CYGWIN__) || defined(__rtems__) || defined(__MSYS__)
int	_EXFUN(getdtablesize, (void));
int	_EXFUN(setdtablesize, (int));
unsigned _EXFUN(usleep, (unsigned int __useconds));
int     _EXFUN(ftruncate, (int __fd, off_t __length));
int     _EXFUN(truncate, (const char *, off_t __length));
#if !(defined  (_WINSOCK_H) || defined (__USE_W32_SOCKETS))
/* winsock[2].h defines as __stdcall, and with int as 2nd arg */
 int	_EXFUN(gethostname, (char *__name, size_t __len));
#endif
char *	_EXFUN(mktemp, (char *));
int     _EXFUN(sync, (void));
int     _EXFUN(readlink, (const char *__path, char *__buf, int __buflen));
int     _EXFUN(symlink, (const char *__name1, const char *__name2));
#endif

#define	F_OK	0
#define	R_OK	4
#define	W_OK	2
#define	X_OK	1

# define	SEEK_SET	0
# define	SEEK_CUR	1
# define	SEEK_END	2

#include <sys/features.h>

#define STDIN_FILENO    0       /* standard input file descriptor */
#define STDOUT_FILENO   1       /* standard output file descriptor */
#define STDERR_FILENO   2       /* standard error file descriptor */

/*
 *  4.8.1 Get Configurable System Variables, P1003.1b-1993, p. 96
 *
 *  NOTE: Table 4-2, Configurable System Variables, p. 96
 */

#define _SC_ARG_MAX                 0
#define _SC_CHILD_MAX               1
#define _SC_CLK_TCK                 2
#define _SC_NGROUPS_MAX             3
#define _SC_OPEN_MAX                4
  /* no _SC_STREAM_MAX */
#define _SC_JOB_CONTROL             5
#define _SC_SAVED_IDS               6
#define _SC_VERSION                 7
#define _SC_PAGESIZE                8
/* CYGWIN and MSYS-specific values .. do not touch */
#define _SC_NPROCESSORS_CONF        9
#define _SC_NPROCESSORS_ONLN       10
#define _SC_PHYS_PAGES             11
#define _SC_AVPHYS_PAGES           12
/* end of CYGWIN and MSYS-specific values */
#define _SC_MQ_OPEN_MAX            13
#define _SC_MQ_PRIO_MAX            14
#define _SC_RTSIG_MAX              15
#define _SC_SEM_NSEMS_MAX          16
#define _SC_SEM_VALUE_MAX          17
#define _SC_SIGQUEUE_MAX           18
#define _SC_TIMER_MAX              19
#define _SC_TZNAME_MAX             20

#define _SC_ASYNCHRONOUS_IO        21
#define _SC_FSYNC                  22
#define _SC_MAPPED_FILES           23
#define _SC_MEMLOCK                24
#define _SC_MEMLOCK_RANGE          25
#define _SC_MEMORY_PROTECTION      26
#define _SC_MESSAGE_PASSING        27
#define _SC_PRIORITIZED_IO         28
#define _SC_REALTIME_SIGNALS       29
#define _SC_SEMAPHORES             30
#define _SC_SHARED_MEMORY_OBJECTS  31
#define _SC_SYNCHRONIZED_IO        32
#define _SC_TIMERS                 33
#define _SC_AIO_LISTIO_MAX         34
#define _SC_AIO_MAX                35
#define _SC_AIO_PRIO_DELTA_MAX     36
#define _SC_DELAYTIMER_MAX         37

/*
 *  P1003.1c/D10, p. 52 adds the following.
 */

#define _SC_THREAD_KEYS_MAX              38
#define _SC_THREAD_STACK_MIN             39
#define _SC_THREAD_THREADS_MAX           40
#define _SC_TTY_NAME_MAX                 41

#define _SC_THREADS                      42
#define _SC_THREAD_ATTR_STACKADDR        43
#define _SC_THREAD_ATTR_STACKSIZE        44
#define _SC_THREAD_PRIORITY_SCHEDULING   45
#define _SC_THREAD_PRIO_INHERIT          46
/* _SC_THREAD_PRIO_PROTECT was _SC_THREAD_PRIO_CEILING in early drafts */
#define _SC_THREAD_PRIO_PROTECT          47
#define _SC_THREAD_PRIO_CEILING          _SC_THREAD_PRIO_PROTECT
#define _SC_THREAD_PROCESS_SHARED        48
#define _SC_THREAD_SAFE_FUNCTIONS        49
#define _SC_GETGR_R_SIZE_MAX             50
#define _SC_GETPW_R_SIZE_MAX             51
#define _SC_LOGIN_NAME_MAX               52
#define _SC_THREAD_DESTRUCTOR_ITERATIONS 53
  
# define	_PC_LINK_MAX	        0
# define	_PC_MAX_CANON	        1
# define	_PC_MAX_INPUT	        2
# define	_PC_NAME_MAX	        3
# define	_PC_PATH_MAX	        4
# define	_PC_PIPE_BUF	        5
# define	_PC_CHOWN_RESTRICTED   	6
# define	_PC_NO_TRUNC	        7
# define	_PC_VDISABLE	        8
# define	_PC_ASYNC_IO            9
# define	_PC_PRIO_IO            10
# define	_PC_SYNC_IO            11
#if defined(__CYGWIN__) || defined(__MSYS__)
/* Ask for POSIX permission bits support. */
# define	_PC_POSIX_PERMISSIONS   90
/* Ask for full POSIX permission support including uid/gid settings. */
# define	_PC_POSIX_SECURITY     91
#endif

/* FIXME: This is temporary until winsup gets sorted out.  */
#if defined(__CYGWIN__) || defined(__MSYS__)
#define MAXPATHLEN (260 - 1 /* NUL */)
#else
# define	MAXPATHLEN	1024
#endif

#ifdef __cplusplus
}
#endif
#endif /* _SYS_UNISTD_H */
