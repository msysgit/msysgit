/* sched.h: scheduler interface for Cygwin

   Copyright 2001  Red Hat, Inc.

   Written by Robert Collins <rbtcollins@hotmail.com>

   This file is part of Cygwin.

   This software is a copyrighted work licensed under the terms of the
   Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
   details. */

/* Written from the opengroup specifications */

#ifndef _SCHED_H
#define _SCHED_H
#include <time.h>

/* we return -1 and set errno on failure */
#define SCHED_FIFO  1
#define SCHED_RR    2
#define SCHED_OTHER 3

struct sched_param
{
  int sched_priority;
};

#ifdef __cplusplus
extern "C" {
#endif

/* max priority for policy */
int sched_get_priority_max (int);
/* min priority for policy */
int sched_get_priority_min (int);
/* get sched params for process */
int sched_getparam (pid_t, struct sched_param *);
/* get the scheduler for pid */
int sched_getscheduler (pid_t);
/* get the time quantum for pid */
int sched_rr_get_interval (pid_t, struct timespec *);
/* set the scheduling parameters */
int sched_setparam (pid_t, const struct sched_param *);
/* set the scheduler */
int sched_setscheduler (pid_t, int, const struct sched_param *);
/* yield the cpu */
int sched_yield (void);

#if defined(__INSIDE_CYGWIN__) || defined(__INSIDE_MSYS__)
/* These are private helper functions used to calculate scheduler settings and
 * validate parameters */

/* check parameters for validity */
int valid_sched_parameters(const struct sched_param *);
/* set a single thread's priority */
int sched_set_thread_priority(HANDLE thread, int priority);

#endif /* __INSIDE_CYGWIN__ || __INSIDE_MSYS__*/

#ifdef __cplusplus
}
#endif
#endif				/* _SCHED_H */
