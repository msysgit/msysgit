/* 
   HTTP authentication routines
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

#ifndef NE_AUTH_H
#define NE_AUTH_H

#include "ne_session.h" /* for ne_session */

BEGIN_NEON_DECLS

/* Size of username/password buffers passed to ne_auth_creds
 * callback. */
#define NE_ABUFSIZ (256)

/* The callback used to request the username and password in the given
 * realm. The username and password must be copied into the buffers
 * which are both of size NE_ABUFSIZ.  The 'attempt' parameter is zero
 * on the first call to the callback, and increases by one each time
 * an attempt to authenticate fails.
 *
 * The callback must return zero to indicate that authentication
 * should be attempted with the username/password, or non-zero to
 * cancel the request. (if non-zero, username and password are
 * ignored.)  */
typedef int (*ne_auth_creds)(void *userdata, const char *realm, int attempt,
			     char *username, char *password);

/* TOP TIP: if you just wish to try authenticating once (even if the
 * user gets the username/password wrong), have your implementation of
 * the callback return the 'attempt' value.  */

/* Set callbacks to provide credentials for server and proxy
 * authentication.  userdata is passed as the first argument to the
 * callback.  The callback is called *indefinitely* until either it
 * returns non-zero, or authentication is successful.  */
void ne_set_server_auth(ne_session *sess, ne_auth_creds creds, void *userdata);
void ne_set_proxy_auth(ne_session *sess, ne_auth_creds creds, void *userdata);

/* Clear any stored authentication details for the given session. */
void ne_forget_auth(ne_session *sess);

END_NEON_DECLS

#endif /* NE_AUTH_H */
