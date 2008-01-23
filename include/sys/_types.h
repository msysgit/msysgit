/* ANSI C namespace clean utility typedefs */

/* This file defines various typedefs needed by the system calls that support
   the C library.  Basically, they're just the POSIX versions with an '_'
   prepended.  This file lives in the `sys' directory so targets can provide
   their own if desired (or they can put target dependant conditionals here).
*/

#ifndef	_SYS__TYPES_H
#define _SYS__TYPES_H

typedef long _off_t;
typedef long _ssize_t;

#endif	/* _SYS__TYPES_H */
