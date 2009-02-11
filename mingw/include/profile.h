/*	$NetBSD: profile.h,v 1.6 1995/03/28 18:17:08 jtc Exp $	*/

/*
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)profile.h	8.1 (Berkeley) 6/11/93
 */

/*
 * This file is taken from Cygwin distribution. Please keep it in sync.
 * The differences should be within __MINGW32__ guard.
 */
/* If compiler doesn't inline, at least avoid passing args on the stack. */
#define _MCOUNT_CALL __attribute__ ((regparm (2)))
#define _MCOUNT_DECL static __inline__  void _MCOUNT_CALL _mcount

/* FIXME: This works, but it would be cleaner to convert mcount into an
   assembler stub that calls an extern  _mcount. 
   Older versions of GCC (pre-4.1) will still fail with regparm since the
   compiler used %edx to store an unneeded counter variable.  */

#define	MCOUNT \
void									\
mcount()								\
{									\
	u_long selfpc, frompcindex;					\
	/*								\
	 * Save registers, since this may be called from		\
	 * the prologue of a regparm function.				\
	 */								\
	__asm __volatile__ ("pushl %eax\n\t"				\
			    "pushl %ecx\n\t"				\
		 	    "pushl %edx");				\
	/*								\
	 * find the return address for mcount,				\
	 * and the return address for mcount's caller.			\
	 *								\
	 * selfpc = pc pushed by mcount call				\
	 */								\
	/* __asm  ("movl 4(%%ebp),%0" : "=r" (selfpc));	*/		\
	selfpc = (u_long) __builtin_return_address (0);			\
	/*								\
	 * frompcindex = pc pushed by call into self.			\
	 */								\
	/*  __asm ("movl (%%ebp),%0;movl 4(%0),%0" : "=r" (frompcindex)); */  \
	frompcindex = (u_long) __builtin_return_address (1);		\
	_mcount(frompcindex, selfpc);					\
	/*								\
	 * Restore registers.						\
	 */								\
	__asm __volatile__ ("popl %edx\n\t"				\
			    "popl %ecx\n\t"				\
			    "popl %eax");				\
}
