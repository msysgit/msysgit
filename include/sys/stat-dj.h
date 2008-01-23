/* This is file STAT.H */
/*
 * Copyright (C) 1991 DJ Delorie
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms is permitted
 * provided that the above copyright notice and following paragraph are
 * duplicated in all such forms.
 *
 * This file is distributed WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef _STAT_H_
#define _STAT_H_

struct	stat {
	short st_dev;
	short st_ino;
	unsigned short st_mode;
	short st_nlink;
	short st_uid;
	short st_gid;
	short st_rdev;
	short st_align_for_word32;
	long  st_size;
	long  st_atime;
	long  st_mtime;
	long  st_ctime;
	long  st_blksize;
};

#define S_IFMT	0xF000	/* file type mask */
#define S_IFDIR	0x4000	/* directory */
#define S_IFIFO	0x1000	/* FIFO special */
#define S_IFCHR	0x2000	/* character special */
#define S_IFBLK	0x3000	/* block special */
#define S_IFREG	0x8000	/* or just 0x0000, regular */
#define S_IREAD	0x0100	/* owner may read */
#define S_IWRITE 0x0080	/* owner may write */
#define S_IEXEC	0x0040	/* owner may execute <directory search> */

#define	S_ISBLK(m)	(((m) & S_IFMT) == S_IFBLK)
#define	S_ISCHR(m)	(((m) & S_IFMT) == S_IFCHR)
#define	S_ISDIR(m)	(((m) & S_IFMT) == S_IFDIR)
#define	S_ISFIFO(m)	(((m) & S_IFMT) == S_IFIFO)
#define	S_ISREG(m)	(((m) & S_IFMT) == S_IFREG)

#ifdef __cplusplus
extern "C" {
#endif
int stat(const char *, struct stat *);
int fstat(int, struct stat *);
#ifdef __cplusplus
}
#endif

#endif
