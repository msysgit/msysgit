/* 
   HTTP session handling
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

#ifndef NE_SESSION_H
#define NE_SESSION_H 1

#include <sys/types.h>

#include "ne_ssl.h"
#include "ne_uri.h" /* for ne_uri */
#include "ne_defs.h"
#include "ne_socket.h"

BEGIN_NEON_DECLS

typedef struct ne_session_s ne_session;

/* Create a session to the given server, using the given scheme.  If
 * "https" is passed as the scheme, SSL will be used to connect to the
 * server. */
ne_session *ne_session_create(const char *scheme,
			      const char *hostname, unsigned int port);

/* Finish an HTTP session */
void ne_session_destroy(ne_session *sess);

/* Prematurely force the connection to be closed for the given
 * session. */
void ne_close_connection(ne_session *sess);

/* Set the proxy server to be used for the session. */
void ne_session_proxy(ne_session *sess,
		      const char *hostname, unsigned int port);

/* Disable use of persistent connection if 'flag' is non-zero, else
 * enable (the default). */
void ne_set_persist(ne_session *sess, int flag);

/* Bypass the normal name resolution; force the use of specific set of
 * addresses for this session, addrs[0]...addrs[n-1].  The addrs array
 * must remain valid until the session is destroyed. */
void ne_set_addrlist(ne_session *sess, const ne_inet_addr **addrs, size_t n);

/* Progress callback. */
typedef void (*ne_progress)(void *userdata, off_t progress, off_t total);

/* Set a progress callback for the session. */
void ne_set_progress(ne_session *sess, 
		     ne_progress progress, void *userdata);

/* Store an opaque context for the session, 'priv' is returned by a
 * call to ne_session_get_private with the same ID. */
void ne_set_session_private(ne_session *sess, const char *id, void *priv);
void *ne_get_session_private(ne_session *sess, const char *id);

typedef enum {
    ne_conn_namelookup, /* lookup up hostname (info = hostname) */
    ne_conn_connecting, /* connecting to host (info = hostname) */
    ne_conn_connected, /* connected to host (info = hostname) */
    ne_conn_secure /* connection now secure (info = crypto level) */
} ne_conn_status;

typedef void (*ne_notify_status)(void *userdata, 
				 ne_conn_status status,
				 const char *info);


/* Set a status notification callback for the session, to report
 * connection status. */
void ne_set_status(ne_session *sess,
		   ne_notify_status status, void *userdata);

/* Certificate verification failures.
 * The certificate is not yet valid: */
#define NE_SSL_NOTYETVALID (0x01)
/* The certificate has expired: */
#define NE_SSL_EXPIRED (0x02)
/* The hostname for which the certificate was issued does not
 * match the hostname of the server; this could mean that the
 * connection is being intercepted: */
#define NE_SSL_IDMISMATCH (0x04)
/* The certificate authority which signed the server certificate is
 * not trusted: there is no indicatation the server is who they claim
 * to be: */
#define NE_SSL_UNTRUSTED (0x08)

/* The bitmask of known failure bits: if (failures & ~NE_SSL_FAILMASK)
 * is non-zero, an unrecognized failure is given, and the verification
 * should be failed. */
#define NE_SSL_FAILMASK (0x0f)

/* A callback which is used when server certificate verification is
 * needed.  The reasons for verification failure are given in the
 * 'failures' parameter, which is a binary OR of one or more of the
 * above NE_SSL_* values. failures is guaranteed to be non-zero.  The
 * callback must return zero to accept the certificate: a non-zero
 * return value will fail the SSL negotiation. */
typedef int (*ne_ssl_verify_fn)(void *userdata, int failures,
				const ne_ssl_certificate *cert);

/* Install a callback to handle server certificate verification.  This
 * is required when the CA certificate is not known for the server
 * certificate, or the server cert has other verification problems. */
void ne_ssl_set_verify(ne_session *sess, ne_ssl_verify_fn fn, void *userdata);

/* Use the given client certificate for the session.  The client cert
 * MUST be in the decrypted state, otherwise behaviour is undefined. */
void ne_ssl_set_clicert(ne_session *sess, const ne_ssl_client_cert *clicert);

/* Indicate that the certificate 'cert' is trusted; 'cert' is
 * duplicated internally and may be destroyed at will. */
void ne_ssl_trust_cert(ne_session *sess, const ne_ssl_certificate *cert);

/* If the SSL library provided a default set of CA certificates, trust
 * this set of CAs. */
void ne_ssl_trust_default_ca(ne_session *sess);

/* Callback used to load a client certificate on demand.  If dncount
 * is > 0, the 'dnames' array dnames[0] through dnames[dncount-1]
 * gives the list of CA names which the server indicated were
 * acceptable.  The callback should load an appropriate client
 * certificate and then pass it to 'ne_ssl_set_clicert'. */
typedef void (*ne_ssl_provide_fn)(void *userdata, ne_session *sess,
				  const ne_ssl_dname *const *dnames,
                                  int dncount);

/* Register a function to be called when the server requests a client
 * certificate. */
void ne_ssl_provide_clicert(ne_session *sess, 
                            ne_ssl_provide_fn fn, void *userdata);

/* Set the timeout (in seconds) used when reading from a socket.  The
 * timeout value must be greater than zero. */
void ne_set_read_timeout(ne_session *sess, int timeout);

/* Sets the user-agent string. neon/VERSION will be appended, to make
 * the full header "User-Agent: product neon/VERSION".
 * If this function is not called, the User-Agent header is not sent.
 * The product string must follow the RFC2616 format, i.e.
 *       product         = token ["/" product-version]
 *       product-version = token
 * where token is any alpha-numeric-y string [a-zA-Z0-9]* */
void ne_set_useragent(ne_session *sess, const char *product);

/* Returns non-zero if next-hop server does not claim compliance to
 * HTTP/1.1 or later. */
int ne_version_pre_http11(ne_session *sess);

/* Returns the 'hostport' URI segment for the end-server, e.g.
 * "my.server.com:8080". */
const char *ne_get_server_hostport(ne_session *sess);

/* Returns the URL scheme being used for the current session, omitting
 * the trailing ':'; e.g. "http" or "https". */
const char *ne_get_scheme(ne_session *sess);

/* Sets the host, scheme, and port fields (and no others) of the given
 * URI structure; host and scheme are malloc-allocated. */
void ne_fill_server_uri(ne_session *sess, ne_uri *uri);

/* Set the error string for the session; takes printf-like format
 * string. */
void ne_set_error(ne_session *sess, const char *format, ...)
    ne_attribute((format (printf, 2, 3)));

/* Retrieve the error string for the session */
const char *ne_get_error(ne_session *sess);

END_NEON_DECLS

#endif /* NE_SESSION_H */
