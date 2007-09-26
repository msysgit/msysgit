/* pthread.h: POSIX pthread interface

   Copyright 1996, 1997, 1998, 1999, 20000, 2001 Red Hat, Inc.

   Written by Marco Fuykschot <marco@ddi.nl>

   This file is part of Cygwin.

   This software is a copyrighted work licensed under the terms of the
   Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
   details. */

#include <sys/types.h>
#include <signal.h>
#include <sched.h>

#ifndef _PTHREAD_H
#define _PTHREAD_H

#ifdef __cplusplus
extern "C"
{
#endif


/* Defines. (These are correctly defined here as per
   http://www.opengroup.org/onlinepubs/7908799/xsh/pthread.h.html */

/* FIXME: this should allocate a new cond variable, and return the value  that
 would normally be written to the passed parameter of pthread_cond_init(lvalue, NULL); */
/* #define PTHREAD_COND_INITIALIZER 0 */

#define PTHREAD_DESTRUCTOR_ITERATIONS 1
/* Tls has 64 items for pre win2000 - and we don't want to use them all :]
 * Before committing discuss this with the list
 */
#define PTHREAD_KEYS_MAX 32
/* the default : joinable */

#define PTHREAD_CANCEL_ASYNCHRONOUS 1
/* defaults are enable, deferred */
#define PTHREAD_CANCEL_ENABLE 0
#define PTHREAD_CANCEL_DEFERRED 0
#define PTHREAD_CANCEL_DISABLE 1
#define PTHREAD_CANCELED
#define PTHREAD_COND_INITIALIZER
#define PTHREAD_CREATE_DETACHED 1
/* the default : joinable */
#define PTHREAD_CREATE_JOINABLE 0
#define PTHREAD_EXPLICIT_SCHED 1
#define PTHREAD_INHERIT_SCHED 0
#define PTHREAD_MUTEX_DEFAULT 0
#define PTHREAD_MUTEX_ERRORCHECK 1
#define PTHREAD_MUTEX_NORMAL 2
/* this should be too low to ever be a valid address */
#define PTHREAD_MUTEX_INITIALIZER (void *)20
#define PTHREAD_MUTEX_RECURSIVE 0
#define PTHREAD_ONCE_INIT { PTHREAD_MUTEX_INITIALIZER, 0 }
#define PTHREAD_PRIO_INHERIT
#define PTHREAD_PRIO_NONE
#define PTHREAD_PRIO_PROTECT
#define PTHREAD_PROCESS_SHARED 1
#define PTHREAD_PROCESS_PRIVATE 0
#define PTHREAD_RWLOCK_INITIALIZER
/* process is the default */
#define PTHREAD_SCOPE_PROCESS 0
#define PTHREAD_SCOPE_SYSTEM 1


/* Attributes */
int pthread_attr_destroy (pthread_attr_t *);
int pthread_attr_getdetachstate (const pthread_attr_t *, int *);
int pthread_attr_getinheritsched (const pthread_attr_t *, int *);
int pthread_attr_getschedparam (const pthread_attr_t *, struct sched_param *);
int pthread_attr_getschedpolicy (const pthread_attr_t *, int *);
int pthread_attr_getscope (const pthread_attr_t *, int *);
int pthread_attr_init (pthread_attr_t *);
int pthread_attr_setdetachstate (pthread_attr_t *, int);
int pthread_attr_setinheritsched (pthread_attr_t *, int);
int pthread_attr_setschedparam (pthread_attr_t *, const struct sched_param *);
int pthread_attr_setschedpolicy (pthread_attr_t *, int);
int pthread_attr_setscope (pthread_attr_t *, int);

#ifdef _POSIX_THREAD_ATTR_STACKADDR
/* These functions may be implementable via some low level trickery. For now they are
 * Not supported or implemented. The prototypes are here so if someone greps the 
 * source they will see these comments
 */
int pthread_attr_getstackaddr (const pthread_attr_t *, void **);
int pthread_attr_setstackaddr (pthread_attr_t *, void *);
#endif

#ifdef _POSIX_THREAD_ATTR_STACKSIZE
int pthread_attr_getstacksize (const pthread_attr_t *, size_t *);
int pthread_attr_setstacksize (pthread_attr_t *, size_t);
#endif

int pthread_cancel (pthread_t);
/* Macros for cleanup_push and pop; 
 * The function definitions are
void pthread_cleanup_push (void (*routine)(void*), void *arg);
void pthread_cleanup_pop (int execute);
*/
typedef void __cleanup_routine_type (void *);

#define pthread_cleanup_push(fn, arg) { __cleanup_routine_type __cleanup_routine=fn; \
void *__cleanup_param=arg;
#define pthread_cleanup_pop(execute) if (execute) __cleanup_routine(__cleanup_param); }

/* Condition variables */
int pthread_cond_broadcast (pthread_cond_t *);
int pthread_cond_destroy (pthread_cond_t *);
int pthread_cond_init (pthread_cond_t *, const pthread_condattr_t *);
int pthread_cond_signal (pthread_cond_t *);
int pthread_cond_timedwait (pthread_cond_t *,
			    pthread_mutex_t *, const struct timespec *);
int pthread_cond_wait (pthread_cond_t *, pthread_mutex_t *);
int pthread_condattr_destroy (pthread_condattr_t *);
int pthread_condattr_getpshared (const pthread_condattr_t *, int *);
int pthread_condattr_init (pthread_condattr_t *);
int pthread_condattr_setpshared (pthread_condattr_t *, int);

int pthread_create (pthread_t *, const pthread_attr_t *,
		    void *(*)(void *), void *);
int pthread_detach (pthread_t);
int pthread_equal (pthread_t, pthread_t);
void pthread_exit (void *);
int pthread_getschedparam (pthread_t, int *, struct sched_param *);
void *pthread_getspecific (pthread_key_t);
int pthread_join (pthread_t, void **);
int pthread_key_create (pthread_key_t *, void (*)(void *));
int pthread_key_delete (pthread_key_t);

/* Mutex's */
int pthread_mutex_destroy (pthread_mutex_t *);
int pthread_mutex_getprioceiling (const pthread_mutex_t *, int *);
int pthread_mutex_init (pthread_mutex_t *, const pthread_mutexattr_t *);
int pthread_mutex_lock (pthread_mutex_t *);
int pthread_mutex_setprioceiling (pthread_mutex_t *, int, int *);
int pthread_mutex_trylock (pthread_mutex_t *);
int pthread_mutex_unlock (pthread_mutex_t *);
int pthread_mutexattr_destroy (pthread_mutexattr_t *);
int pthread_mutexattr_getprioceiling (const pthread_mutexattr_t *, int *);
int pthread_mutexattr_getprotocol (const pthread_mutexattr_t *, int *);
int pthread_mutexattr_getpshared (const pthread_mutexattr_t *, int *);
int pthread_mutexattr_gettype (const pthread_mutexattr_t *, int *);
int pthread_mutexattr_init (pthread_mutexattr_t *);
int pthread_mutexattr_setprioceiling (pthread_mutexattr_t *, int);
int pthread_mutexattr_setprotocol (pthread_mutexattr_t *, int);
int pthread_mutexattr_setpshared (pthread_mutexattr_t *, int);
int pthread_mutexattr_settype (pthread_mutexattr_t *, int);

int pthread_once (pthread_once_t *, void (*)(void));

/* Concurrency levels - X/Open interface */
int pthread_getconcurrency (void);
int pthread_setconcurrency (int);


pthread_t pthread_self (void);
int pthread_setcancelstate (int, int *);
int pthread_setcanceltype (int, int *);
int pthread_setschedparam (pthread_t, int, const struct sched_param *);
int pthread_setspecific (pthread_key_t, const void *);
void pthread_testcancel (void);

/* Non posix calls */

int pthread_suspend (pthread_t);
int pthread_continue (pthread_t);

#ifdef __cplusplus
}
#endif

#endif /* _PTHREAD_H */
