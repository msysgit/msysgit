/* exceptions.h

   Copyright 1996, 1997, 1998, 2001 Red Hat, Inc.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#ifndef _EXCEPTIONS_H
#define _EXCEPTIONS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Documentation on the innards of exception handling (i.e. from the
   perspective of a compiler implementor) apparently doesn't exist.  Sigh.
   However, the following came from Onno Hovers <onno@stack.urc.tue.nl>

The first pointer to the chain of handlers is in the thread environment block
at FS:[0].  This chain has the following format:

typedef struct __EXCEPTION_FRAME
{
   struct __EXCEPTION_FRAME	*Prev;    /-* pointer to the previous frame *-/
   PEXCEPTION_HANDLER		Handler; /-* handler function *-/
}

You register an exception handler in your compiler with this simple ASM
sequence:
   PUSH _MyExceptionHandler
   PUSH FS:[0]
   MOV  FS:[0],ESP
An exception frame MUST be on the stack! The frame may have more fields and
both Visual C++ and Borland C++ use more fields for themselves.

When an exception occurs the system calls all handlers starting with the
handler at FS:0, and then the previous etc. until one handler returns
ExceptionContinueExecution, which is 0. If a handler does not want to handle
the exception it should just return ExceptionContinueSearch, which is 1.

The handler has the following parameters:
ehandler (
	   PEXCEPTION_RECORD erecord,
	   PEXCEPTION_FRAME myframe,
	   PCONTEXT context,		/-* context before and after *-/
	   PVOID dispatch)		/-* something *-/

When a handler wants to handle the exception, it has some alternatives:

-one is to do do something about the exception condition, like emulating
an invalid instruction, mapping memory where there was a page fault, etc.
If the handler wants to have the context of the thread that causes the
exception changed, it should make that change in the context passed to the
handler.

-the second alternative is to call all exception handlers again, indicating
that you want them to clean up. This way all the __finally blocks get
executed. After doing that you change the context passed to the handler so
the code starts executing in the except block. For this purpose you could
call RtlUnwind. This (undocumented) function calls all exception handlers
up to but not including the exception frame passed to it. If NULL is passed
as exception frame RtlUnwind calls all exception handlers and then exits the
process. The parameters to RtlUnwind are:

RtlUnwind (
   PEXCEPTION_FRAME	endframe,
   PVOID		unusedEip,
   PEXCEPTION_RECORD	erecord,
   DWORD		returnEax)

You should set unusedEip to the address where RtlUnwind should return like
this:
	  PUSH 0
	  PUSH OFFSET ReturnUnwind
	  PUSH 0
	  PUSH 0
	  CALL RtlUnwind
ReturnUnwind:
	  .....

If no EXCEPTION_RECORD is passed, RtlUnwind makes a default exception
record. In any case, the ExceptionFlags part of this record has the
EH_UNWINDING (=2),  flag set. (and EH_EXIT_UNWIND (=4), when NULL is passed as the end
frame.).

The handler for a exception as well as a for unwinds may be executed in the
thread causing the exception, but may also be executed in another (special
exception) thread. So it is not wise to make any assumptions about that!

As an alternative you may consider the SetUnhandledExceptionFilter API
to install your own exception filter. This one is documented.
*/

/* The January 1994 MSJ has an article entitled "Clearer, More Comprehensive
   Error Processing with Win32 Structured Exception Handling".  It goes into
   a teensy bit of detail of the innards of exception handling (i.e. what we
   have to do).  */

typedef int (exception_handler)
     (EXCEPTION_RECORD *, void *, CONTEXT *, void *);

typedef struct _exception_list
{
  struct _exception_list *prev;
  exception_handler *handler;

  /* We're apparently free to add more stuff here.
     At present we don't need any.  */
} exception_list;

void init_exceptions (exception_list *);

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* _EXCEPTIONS_H */
