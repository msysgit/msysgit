/* types.h

   Copyright 2001 Red Hat Inc. 
   Written by Robert Collins <rbtcollins@hotmail.com>

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef _CYGWIN_TYPES_H
#define _CYGWIN_TYPES_H

#if !(defined(__INSIDE_CYGWIN__) || defined (__INSIDE_MSYS__)) || !defined(__cplusplus)

typedef void *pthread_t;
typedef void *pthread_mutex_t;

typedef void *pthread_key_t;
typedef void *pthread_attr_t;
typedef void *pthread_mutexattr_t;
typedef void *pthread_condattr_t;
typedef void *pthread_cond_t;

  /* These variables are not user alterable. This means you!. */
typedef struct
{
  pthread_mutex_t mutex;
  int state;
}
pthread_once_t;
typedef void *pthread_rwlock_t;
typedef void *pthread_rwlockattr_t;

#else

/* pthreads types */

typedef class pthread *pthread_t;
typedef class pthread_mutex *pthread_mutex_t;
typedef class pthread_key *pthread_key_t;
typedef class pthread_attr *pthread_attr_t;
typedef class pthread_mutexattr *pthread_mutexattr_t;
typedef class pthread_condattr *pthread_condattr_t;
typedef class pthread_cond *pthread_cond_t;
typedef class pthread_once pthread_once_t;
typedef class pthread_rwlock *pthread_rwlock_t;
typedef class pthread_rwlockattr *pthread_rwlockattr_t;

/* semaphores types */
typedef class semaphore *sem_t;
#endif /* __INSIDE_CYGWIN__ */
#endif /* _CYGWIN_TYPES_H */

#ifdef __cplusplus
}
#endif
