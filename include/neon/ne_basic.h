/* 
   HTTP/1.1 methods
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

#ifndef NE_BASIC_H
#define NE_BASIC_H

#include <sys/types.h> /* for time_t */

#include "ne_request.h"

BEGIN_NEON_DECLS

/* Perform a GET request on resource at 'path', writing the entity
 * body which is returned to 'fd'. */
int ne_get(ne_session *sess, const char *path, int fd);

/* Perform a PUT request on resource at 'path', reading the entity
 * body to submit from 'fd'. */
int ne_put(ne_session *sess, const char *path, int fd);

#define NE_DEPTH_ZERO (0)
#define NE_DEPTH_ONE (1)
#define NE_DEPTH_INFINITE (2)

/* For ne_copy and ne_move:
 * 
 * If a resource exists at "dest" and overwrite is zero, the operation
 * will fail; if overwrite is non-zero, any existing resource will
 * be over-written.
 */

/* Copy resource from 'src to 'dest' paths. If 'src' identifies a
 * collection resource, depth may be NE_DEPTH_ZERO to request that the
 * collection and its properties are to be copied, or
 * NE_DEPTH_INFINITE to request that the collection and its contents
 * are to be copied.  */
int ne_copy(ne_session *sess, int overwrite, int depth,
	    const char *src, const char *dest);

/* Move resource from 'src' to dest 'path'. */
int ne_move(ne_session *sess, int overwrite,
	    const char *src, const char *dest);

/* Delete resource at 'path'. */
int ne_delete(ne_session *sess, const char *path);
/* Create a collection at 'path', which MUST have a trailing slash. */
int ne_mkcol(ne_session *sess, const char *path);

/* Adds a Depth: header to a request */
void ne_add_depth_header(ne_request *req, int depth);

/* Retrieve modification time of resource at location 'path', place in
 * *modtime.  (uses HEAD) */
int ne_getmodtime(ne_session *sess, const char *path, time_t *modtime);

typedef struct {
    const char *type, *subtype;
    const char *charset;
    char *value;
} ne_content_type;

/* Retrieve the content-type of the response; returns zero if response
 * had valid content-type, in which case all fields in *ctype are set
 * (and never NULL); the caller must free(ctype->value) after use.
 * Returns non-zero on error, in which case *ctype is not altered. */
int ne_get_content_type(ne_request *req, ne_content_type *ctype);

/* Server capabilities: */
typedef struct {
    unsigned int dav_class1; /* True if Class 1 WebDAV server */
    unsigned int dav_class2; /* True if Class 2 WebDAV server */
    unsigned int dav_executable; /* True if supports the 'executable'
				  * property a. la. mod_dav */
} ne_server_capabilities;

/* Determines server capabilities (using OPTIONS).  Pass 'path' as "*"
 * to determine proxy server capabilities if using a proxy server. */
int ne_options(ne_session *sess, const char *path,
	       ne_server_capabilities *caps);

/* Defines a range of bytes, starting at 'start' and ending
 * at 'end'.  'total' is the number of bytes in the range.
 */
typedef struct {
    off_t start, end, total;
} ne_content_range;

/* Partial GET. range->start must be >= 0. range->total is ignored.
 *
 * If range->end is -1, then the rest of the resource from start is
 * requested, and range->total and end are filled in on success.
 *
 * Otherwise, bytes from range->start to range->end are requested.
 *
 * This will write to the CURRENT position of f; so if you want
 * to do a resume download, use:
 *      struct ne_content_range range;
 *      range.start = resume_from; 
 *      range.end = range.start + 999;  (= 1000 bytes)
 *      fseek(myfile, resume_from, SEEK_SET);
 *      ne_get_range(sess, path, &range, myfile); */
int ne_get_range(ne_session *sess, const char *path, 
		 ne_content_range *range, int fd);

/* Post using buffer as request-body: stream response into f */
int ne_post(ne_session *sess, const char *path, int fd, const char *buffer);

END_NEON_DECLS

#endif /* NE_BASIC_H */
