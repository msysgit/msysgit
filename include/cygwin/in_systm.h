/* System specific type definitions for networking code.
 *
 * Version:     @(#)in_systm.h        1.0.0   06/07/00
 *
 * Authors:     Original taken from the GNU Project <netinet/in_systm.h> file.
 *              Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *
 *              This program is free software; you can redistribute it and/or
 *              modify it under the terms of the GNU General Public License
 *              as published by the Free Software Foundation; either version
 *              2 of the License, or (at your option) any later version.
 */
#ifndef _CYGWIN_IN_SYSTM_H
#define _CYGWIN_IN_SYSTM_H

#include <sys/cdefs.h>
#include <sys/types.h>

__BEGIN_DECLS

/*
 * Network order versions of various data types. Unfortunately, BSD
 * assumes specific sizes for shorts (16 bit) and longs (32 bit) which
 * don't hold in general. As a consequence, the network order versions
 * may not reflect the actual size of the native data types.
 */

typedef u_int16_t n_short;      /* short as received from the net */
typedef u_int32_t n_long;       /* long as received from the net  */
typedef u_int32_t n_time;       /* ms since 00:00 GMT, byte rev   */

__END_DECLS

#endif /* _CYGWIN_IN_SYSTM_H */
