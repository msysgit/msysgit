/* core_dump.h

   Copyright 1999, 2000, 2001 Red Hat, Inc.

   Written by Egor Duda <deo@logos-m.ru>

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#ifndef _CYGWIN_CORE_DUMP_H
#define _CYGWIN_CORE_DUMP_H

#include <windows.h>

#define	NOTE_INFO_PROCESS	1
#define	NOTE_INFO_THREAD	2
#define	NOTE_INFO_MODULE	3

struct win32_core_process_info
{
  DWORD pid;
  int signal;
  int command_line_size;
  char command_line[1];
}
#ifdef __GNUC__
  __attribute__ ((packed))
#endif
;

struct win32_core_thread_info
{
  DWORD tid;
  BOOL is_active_thread;
  CONTEXT thread_context;
}
#ifdef __GNUC__
  __attribute__ ((packed))
#endif
;

struct win32_core_module_info
{
  void* base_address;
  int module_name_size;
  char module_name[1];
}
#ifdef __GNUC__
  __attribute__ ((packed))
#endif
;

struct win32_pstatus
{
  unsigned long data_type;
  union
    {
      struct win32_core_process_info process_info;
      struct win32_core_thread_info thread_info;
      struct win32_core_module_info module_info;
    } data ;
}
#ifdef __GNUC__
  __attribute__ ((packed))
#endif
;

typedef struct win32_pstatus win32_pstatus_t ;

#endif /* _CYGWIN_CORE_DUMP_H */
