/* process.h.  This file comes with MSDOS and WIN32 systems.  */

#ifndef __PROCESS_H_
#define __PROCESS_H_

#ifdef __cplusplus
extern "C" {
#endif

int execl(const char *path, const char *argv0, ...);
int execle(const char *path, const char *argv0, ... /*, char * const *envp */);
int execlp(const char *path, const char *argv0, ...);
int execlpe(const char *path, const char *argv0, ... /*, char * const *envp */);

int execv(const char *path, char * const *argv);
int execve(const char *path, char * const *argv, char * const *envp);
int execvp(const char *path, char * const *argv);
int execvpe(const char *path, char * const *argv, char * const *envp);

int spawnl(int mode, const char *path, const char *argv0, ...);
int spawnle(int mode, const char *path, const char *argv0, ... /*, char * const *envp */);
int spawnlp(int mode, const char *path, const char *argv0, ...);
int spawnlpe(int mode, const char *path, const char *argv0, ... /*, char * const *envp */);

int spawnv(int mode, const char *path, const char * const *argv);
int spawnve(int mode, const char *path, char * const *argv, const char * const *envp);
int spawnvp(int mode, const char *path, const char * const *argv);
int spawnvpe(int mode, const char *path, const char * const *argv, const char * const *envp);

#if defined (__CYGWIN__) || defined (__MSYS__)
/* Secure exec() functions family */
/* The first arg should really be a HANDLE which is a void *.  But we
   can't include windows.h here so... */
#include <sys/types.h>
pid_t sexecl(void *, const char *path, const char *argv0, ...);
pid_t sexecle(void *, const char *path, const char *argv0, ... /*, char * const *envp */);
pid_t sexeclp(void *, const char *path, const char *argv0, ...);
pid_t sexeclpe(void *, const char *path, const char *argv0, ... /*, char * const *envp */);

pid_t sexecv(void *, const char *path, const char * const *argv);
pid_t sexecve(void *, const char *path, const char * const *argv, const char * const *envp);
pid_t sexecvp(void *, const char *path, const char * const *argv);
pid_t sexecvpe(void *, const char *path, const char * const *argv, const char * const *envp);
#endif

int cwait(int *, int, int);

#define _P_WAIT		1
#define _P_NOWAIT	2	/* always generates error */
#define _P_OVERLAY	3
#define _P_NOWAITO	4
#define _P_DETACH	5

#define WAIT_CHILD 1

#ifdef __cplusplus
}
#endif

#endif
