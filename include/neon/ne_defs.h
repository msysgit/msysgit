/* 
   Standard definitions for neon headers
   Copyright (C) 2003-2005, Joe Orton <joe@manyfish.co.uk>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with this library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
   MA 02111-1307, USA

*/

#undef BEGIN_NEON_DECLS
#undef END_NEON_DECLS
#ifdef __cplusplus
# define BEGIN_NEON_DECLS extern "C" {
# define END_NEON_DECLS }
#else
# define BEGIN_NEON_DECLS /* empty */
# define END_NEON_DECLS /* empty */
#endif

/* define ssize_t for Win32 */
#if defined(WIN32) && !defined(ssize_t)
#define ssize_t int
#endif

#ifdef __GNUC__
#if __GNUC__ >= 3
#define ne_attribute_malloc __attribute__((malloc))
#else
#define ne_attribute_malloc
#endif
#define ne_attribute(x) __attribute__(x)
#else
#define ne_attribute(x)
#define ne_attribute_malloc
#endif

#ifndef NE_BUFSIZ
#define NE_BUFSIZ 8192
#endif
