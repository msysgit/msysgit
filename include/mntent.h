/* mntent.h

   Copyright 1996, 1998, 1999, 2000, 2001 Red Hat, Inc.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#ifndef _MNTENT_H
#define _MNTENT_H

#ifdef __cplusplus
extern "C" {
#endif

struct mntent
{
  char *mnt_fsname;
  char *mnt_dir;
  char *mnt_type;
  char *mnt_opts;
  int mnt_freq;
  int mnt_passno;
};

#ifndef _NOMNTENT_FUNCS
FILE *setmntent (const char *__filep, const char *__type);
struct mntent *getmntent (FILE *__filep);
int addmntent (FILE *__filep, const struct mntent *__mnt);
int endmntent (FILE *__filep);
char *hasmntopt (const struct mntent *__mnt, const char *__opt);
#endif

/* This next file doesn't exist, it is in the registry,
   however applications need the define to pass to
   the above calls.
*/
#ifndef MOUNTED
#define MOUNTED "/etc/mtab"
#endif
#ifdef __cplusplus
};
#endif

#endif /* _MNTENT_H */
