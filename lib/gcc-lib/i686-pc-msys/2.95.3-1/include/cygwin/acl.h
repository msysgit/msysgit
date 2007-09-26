/* cygwin/acl.h header file for Cygwin.

   Copyright 1999, 2000, 2001 Red Hat, Inc.
   Written by C. Vinschen.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#ifndef _CYGWIN_ACL_H
#ifdef __cplusplus
extern "C" {
#endif
#define _CYGWIN_ACL_H

#include <_ansi.h>

#include <sys/types.h>
#include <sys/stat.h>

/* Values for `cmd' in calls to acl(2) and facl(2) */
#define SETACL          (0x0)
#define GETACL          (0x1)
#define GETACLCNT       (0x2)

#define	MIN_ACL_ENTRIES (4)   
#define	MAX_ACL_ENTRIES	(256) 


#define GRP_ERROR       (0x1)
#define USER_ERROR      (0x2)
#define CLASS_ERROR     (0x3)
#define OTHER_ERROR     (0x4)
#define DUPLICATE_ERROR (0x5)
#define ENTRY_ERROR     (0x6)
#define MISS_ERROR      (0x7)
#define MEM_ERROR       (0x8)


#define USER_OBJ        (0x0001)               
#define USER            (0x0002)               
#define GROUP_OBJ       (0x0004)               
#define GROUP           (0x0008)               
#define CLASS_OBJ       (0x0010)               
#define OTHER_OBJ       (0x0020)               
#define ACL_DEFAULT     (0x1000)               
#define DEF_USER_OBJ    (ACL_DEFAULT|USER_OBJ) 
#define DEF_USER        (ACL_DEFAULT|USER)     
#define DEF_GROUP_OBJ   (ACL_DEFAULT|GROUP_OBJ)
#define DEF_GROUP       (ACL_DEFAULT|GROUP)    
#define DEF_CLASS_OBJ   (ACL_DEFAULT|CLASS_OBJ)
#define DEF_OTHER_OBJ   (ACL_DEFAULT|OTHER_OBJ)

#define USER_OWNER      USER_OBJ
#define GROUP_OWNER     GROUP_OBJ
#define MASK            CLASS_OBJ
#define OTHER           OTHER_OBJ

typedef struct acl {
    int      a_type;    /* entry type */
    uid_t    a_id;      /* UID | GID  */
    mode_t   a_perm;    /* permissions */
} aclent_t;

int _EXFUN(acl,(const char *path, int cmd, int nentries, aclent_t *aclbufp));
int _EXFUN(lacl,(const char *path, int cmd, int nentries, aclent_t *aclbufp));
int _EXFUN(facl,(int fd, int cmd, int nentries, aclent_t *aclbufp));
int _EXFUN(aclcheck,(aclent_t *aclbufp, int nentries, int *which));
int _EXFUN(aclsort,(int nentries, int calclass, aclent_t *aclbufp));
int _EXFUN(acltomode,(aclent_t *aclbufp, int nentries, mode_t *modep));
int _EXFUN(aclfrommode,(aclent_t *aclbufp, int nentries, mode_t *modep));
int _EXFUN(acltopbits,(aclent_t *aclbufp, int nentries, mode_t *pbitsp));
int _EXFUN(aclfrompbits,(aclent_t *aclbufp, int nentries, mode_t *pbitsp));
char *_EXFUN(acltotext,(aclent_t *aclbufp, int aclcnt));
aclent_t *_EXFUN(aclfromtext,(char *acltextp, int *aclcnt));

#ifdef __cplusplus
}
#endif
#endif /* _CYGWIN_ACL_H */
