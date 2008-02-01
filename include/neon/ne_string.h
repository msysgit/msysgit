/* 
   String utility functions
   Copyright (C) 1999-2005, Joe Orton <joe@manyfish.co.uk>

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

#ifndef NE_STRING_H
#define NE_STRING_H

#include "ne_defs.h"
#include "ne_alloc.h"

#include <stdarg.h>

BEGIN_NEON_DECLS

/* ne_token and ne_qtoken return the next token in *str between *str
 * and separator character 'sep' or the NUL terminator. ne_qtoken
 * skips over any parts quoted using a pair of any one of the
 * characters given in 'quotes'.  After returning, *str will point to
 * the next character after the separator, or NULL if no more
 * separator characters were found.
 * 
 * ne_qtoken may return NULL if unterminated quotes are found. */
char *ne_token(char **str, char sep);
char *ne_qtoken(char **str, char sep, const char *quotes);

/* Return portion of 'str' with any characters in 'whitespace' shaved
 * off the beginning and end.  Modifies str. */
char *ne_shave(char *str, const char *whitespace);

/* Cleanse 'str' of non-printable characters.  'str' is modified
 * in-place, and returned. */
char *ne_strclean(char *str);

/* A base64 encoder: converts 'len' bytes of 'text' to base64.
 * Returns malloc-allocated buffer; caller must free(). */
char *ne_base64(const unsigned char *text, size_t len);

/* Base64 decoder; decodes NUL-terminated base64-encoded string
 * 'data', places malloc-allocated raw data in '*out', returns length,
 * or zero on decode error (in which case *out is undefined). */
size_t ne_unbase64(const char *data, unsigned char **out);

/* String buffer handling. (Strings are zero-terminated still).  A
 * string buffer ne_buffer * which grows dynamically with the
 * string. */

typedef struct {
    char *data; /* contents: null-terminated string. */
    size_t used; /* used bytes in buffer */
    size_t length; /* length of buffer */
} ne_buffer;

/* Returns size of data in buffer, equiv to strlen(ne_buffer_data(buf)) */
#define ne_buffer_size(buf) ((buf)->used - 1)

/* Concatenate all given strings onto the end of the buffer.  The
 * strings must all be NUL-terminated, and MUST be followed by a NULL
 * argument marking the end of the list.  */
void ne_buffer_concat(ne_buffer *buf, ...);

/* Create a new ne_buffer. */
ne_buffer *ne_buffer_create(void);

/* Create a new ne_buffer of given minimum size. */
ne_buffer *ne_buffer_ncreate(size_t size);

/* Destroys (deallocates) a buffer */
void ne_buffer_destroy(ne_buffer *buf);

/* Append a NUL-terminated string 'str' to buf. */
void ne_buffer_zappend(ne_buffer *buf, const char *str);

/* Append 'len' bytes of 'data' to buf.  'data' does not need to be
 * NUL-terminated. The resultant string will have a NUL-terminator,
 * either way.  */
void ne_buffer_append(ne_buffer *buf, const char *data, size_t len);

/* Append a literal constant string 'str' to buffer 'buf'. */
#define ne_buffer_czappend(buf, str) \
ne_buffer_append((buf), (str), sizeof((str)) - 1)

/* Empties the contents of buf; makes the buffer zero-length. */
void ne_buffer_clear(ne_buffer *buf);

/* Grows the ne_buffer to a minimum size. */
void ne_buffer_grow(ne_buffer *buf, size_t size);

void ne_buffer_altered(ne_buffer *buf);

/* Destroys a buffer, WITHOUT freeing the data, and returns the
 * data. */
char *ne_buffer_finish(ne_buffer *buf);

/* Thread-safe strerror() wrapper; place system error for errno value
 * 'errnum' in 'buffer', which is of length 'buflen'.  Returns
 * 'buffer'. */
char *ne_strerror(int errnum, char *buffer, size_t buflen);

/* ne_strnzcpy copies at most 'n'-1 bytes of 'src' to 'dest', and
 * ensures that 'dest' is subsequently NUL-terminated. */
#define ne_strnzcpy(dest, src, n) do { \
strncpy(dest, src, n-1); dest[n-1] = '\0'; } while (0)

/* Return malloc-allocated concatenation of all NUL-terminated string
 * arguments, up to a terminating NULL. */
char *ne_concat(const char *str, ...);

#define NE_ASC2HEX(x) (((x) <= '9') ? ((x) - '0') : (tolower((x)) + 10 - 'a'))
#define NE_HEX2ASC(x) ((char) ((x) > 9 ? ((x) - 10 + 'a') : ((x) + '0')))

/* Wrapper for snprintf: always NUL-terminates returned buffer, and
 * returns strlen(str). */
size_t ne_snprintf(char *str, size_t size, const char *fmt, ...)
    ne_attribute((format(printf, 3, 4)));

/* Wrapper for vsnprintf. */
size_t ne_vsnprintf(char *str, size_t size, const char *fmt, va_list ap)
    ne_attribute((format(printf, 3, 0)));

END_NEON_DECLS

#endif /* NE_STRING_H */
