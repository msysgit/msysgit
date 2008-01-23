/* Posix dirent.h for WIN32.

   Copyright 2001 Red Hat, Inc.

   This software is a copyrighted work licensed under the terms of the
   Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
   details. */

/* Including this file should not require any Windows headers.  */
   
#ifndef _SYS_DIRENT_H
#define _SYS_DIRENT_H

#include <sys/types.h>

#define __DIRENT_VERSION	1

struct dirent
{
  long d_version; /* Used since Cygwin 1.3.3. */
  long __d_reserved[2];
  long d_fd; /* File descriptor of open directory. Used since Cygwin 1.3.3. */
  ino_t d_ino; /* Just for compatibility, it's junk */
  char d_name[256];		/* FIXME: use NAME_MAX? */
};

#define __DIRENT_COOKIE 0xdede4242

typedef struct
{
  /* This is first to set alignment in non _COMPILING_NEWLIB case.  */
  unsigned long __d_cookie;
  struct dirent *__d_dirent;
  char *__d_dirname;		/* directory name with trailing '*' */
  off_t __d_position;		/* used by telldir/seekdir */
  unsigned long __d_dirhash;	/* hash of directory name for use by
				   readdir */
  union
    {
#ifdef _COMPILING_NEWLIB
      struct
	{
	  void *__handle;
	  char __open_p;
	} __d_data;
#endif
      char __d_filler[16];
    } __d_u;
} DIR;

DIR *opendir (const char *);
struct dirent *readdir (DIR *);
void rewinddir (DIR *);
int closedir (DIR *);

int dirfd (DIR *);

#ifndef _POSIX_SOURCE
off_t telldir (DIR *);
void seekdir (DIR *, off_t loc);

int scandir (const char *__dir,
	     struct dirent ***__namelist,
	     int (*select) (const struct dirent *),
	     int (*compar) (const struct dirent **, const struct dirent **));

int alphasort (const struct dirent **__a, const struct dirent **__b);
#endif /* _POSIX_SOURCE */

#endif
