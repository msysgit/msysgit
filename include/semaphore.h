/* semaphore.h: POSIX semaphore interface

   Copyright 2001 Red Hat, Inc.

   Written by Robert Collins <rbtcollins@hotmail.com>

   This file is part of Cygwin.

   This software is a copyrighted work licensed under the terms of the
   Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
   details. */

#include <sys/types.h>

#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H

#ifdef __cplusplus
extern "C"
{
#endif

#if !(defined (__INSIDE_CYGWIN__) || defined (__INSIDE_MSYS__))
  typedef void *sem_t;
#endif

#define SEM_FAILED 0
#define SEM_VALUE_MAX 1147483648

/* Semaphores */
  int sem_init (sem_t * sem, int pshared, unsigned int value);
  int sem_destroy (sem_t * sem);
  int sem_wait (sem_t * sem);
  int sem_trywait (sem_t * sem);
  int sem_post (sem_t * sem);

#ifdef __cplusplus
}
#endif

#endif				/* _SEMAPHORE_H */
