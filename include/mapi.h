/* mapi.h

   Copyright 1997, 1998, 1999, 2000, 2001 Red Hat, Inc.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#ifndef _MAPI_H
#define _MAPI_H

/* Currently this doesn't include all the definitions.  It does cover
   the parts of Simple MAPI required to send mail.  */

#ifdef __cplusplus
extern "C"
{
#endif

  /* FIXME: should this be elsewhere?  */
typedef unsigned long FLAGS;

  /* FIXME: should this be elsewhere?  */
#define SUCCESS_SUCCESS 0

  /* FIXME: should this be elsewhere?  */
typedef unsigned long LHANDLE, FAR *LPLHANDLE;


#define MAPI_E_AMBIGUOUS_RECIPIENT 0x15
#define MAPI_E_ATTACHMENT_NOT_FOUND 0xb
#define MAPI_E_ATTACHMENT_OPEN_FAILURE 0xc
#define MAPI_E_BAD_RECIPTYPE 0xf
#define MAPI_E_FAILURE 0x2
#define MAPI_E_INSUFFICIENT_MEMORY 0x5
#define MAPI_E_INVALID_RECIPS 0x19
#define MAPI_E_LOGIN_FAILURE 0x3
#define MAPI_E_TEXT_TOO_LARGE 0x12
#define MAPI_E_TOO_MANY_FILES 0x9
#define MAPI_E_TOO_MANY_RECIPIENTS 0xa
#define MAPI_E_UNKNOWN_RECIPIENT 0xe
#define MAPI_E_USER_ABORT 0x1
#define MAPI_E_TEXT_TOO_LARGE 0x12
#define MAPI_DIALOG 0x8
#define MAPI_NEW_SESSION 0x2
#define MAPI_LOGON_UI 0x1
#define MAPI_RECEIPT_REQUESTED 0x2
#define MAPI_SENT 0x4
#define MAPI_UNREAD 0x1
#define MAPI_OLE 0x1
#define MAPI_OLE_STATIC 0x2

#define MAPI_ORIG 0
#define MAPI_TO   1
#define MAPI_CC   2
#define MAPI_BCC  3

typedef struct
{
  ULONG ulReserved;
  ULONG flFlags;
  ULONG nPosition;
  LPTSTR lpszPathName;
  LPTSTR lpszFileName;
  LPVOID lpFileType;
} MapiFileDesc, FAR *lpMapiFileDesc;

typedef struct
{
  ULONG ulReserved;
  ULONG ulRecipClass;
  LPTSTR lpszName;
  LPTSTR lpszAddress;
  ULONG ulEIDSize;
  LPVOID lpEntryID;
} MapiRecipDesc, FAR *lpMapiRecipDesc;

typedef struct
{
  ULONG ulReserved;
  LPTSTR lpszSubject;
  LPTSTR lpszNoteText;
  LPTSTR lpszMessageType;
  LPTSTR lpszDateReceived;
  LPTSTR lpszConversationID;
  FLAGS flFlags;
  lpMapiRecipDesc lpOriginator;
  ULONG nRecipCount;
  lpMapiRecipDesc lpRecips;
  ULONG nFileCount;
  lpMapiFileDesc lpFiles;
} MapiMessage, FAR *lpMapiMessage;

ULONG FAR PASCAL MAPISendMail (LHANDLE, ULONG, lpMapiMessage, FLAGS, ULONG);

#ifdef __cplusplus
}
#endif

#endif /* _MAPI_H */
