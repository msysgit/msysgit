/* 
   Internationalization of neon
   Copyright (C) 1999-2002, Joe Orton <joe@manyfish.co.uk>

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

#ifndef NEON_I18N_H
#define NEON_I18N_H

#undef _
#ifdef ENABLE_NLS
#include <libintl.h>
#define _(str) gettext(str)
#else
#define _(str) (str)
#endif /* ENABLE_NLS */
#define N_(str) (str)

/* Initialize i18n in neon */
void neon_i18n_init(void);

#endif /* NEON_I18N_H */
