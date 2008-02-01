/* Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef APR_NETWORK_IO_H
#define APR_NETWORK_IO_H
/**
 * @file apr_network_io.h
 * @brief APR Network library
 */

#include "apr.h"
#include "apr_pools.h"
#include "apr_file_io.h"
#include "apr_errno.h"
#include "apr_inherit.h" 

#if APR_HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup apr_network_io Network Routines
 * @ingroup APR 
 * @{
 */

#ifndef APR_MAX_SECS_TO_LINGER
/** Maximum seconds to linger */
#define APR_MAX_SECS_TO_LINGER 30
#endif

#ifndef MAX_SECS_TO_LINGER
/** @deprecated @see APR_MAX_SECS_TO_LINGER */
#define MAX_SECS_TO_LINGER APR_MAX_SECS_TO_LINGER
#endif

#ifndef APRMAXHOSTLEN
/** Maximum hostname length */
#define APRMAXHOSTLEN 256
#endif

#ifndef APR_ANYADDR
/** Default 'any' address */
#define APR_ANYADDR "0.0.0.0"
#endif

/**
 * @defgroup apr_sockopt Socket option definitions
 * @{
 */
#define APR_SO_LINGER        1    /**< Linger */
#define APR_SO_KEEPALIVE     2    /**< Keepalive */
#define APR_SO_DEBUG         4    /**< Debug */
#define APR_SO_NONBLOCK      8    /**< Non-blocking IO */
#define APR_SO_REUSEADDR     16   /**< Reuse addresses */
#define APR_SO_TIMEOUT       32   /**< Timeout */
#define APR_SO_SNDBUF        64   /**< Send buffer */
#define APR_SO_RCVBUF        128  /**< Receive buffer */
#define APR_SO_DISCONNECTED  256  /**< Disconnected */
#define APR_TCP_NODELAY      512  /**< For SCTP sockets, this is mapped
                                   * to STCP_NODELAY internally.
                                   */
#define APR_TCP_NOPUSH       1024 /**< No push */
#define APR_RESET_NODELAY    2048 /**< This flag is ONLY set internally
                                   * when we set APR_TCP_NOPUSH with
                                   * APR_TCP_NODELAY set to tell us that
                                   * APR_TCP_NODELAY should be turned on
                                   * again when NOPUSH is turned off
                                   */
#define APR_INCOMPLETE_READ 4096  /**< Set on non-blocking sockets
				   * (timeout != 0) on which the
				   * previous read() did not fill a buffer
				   * completely.  the next apr_socket_recv() 
                                   * will first call select()/poll() rather than
				   * going straight into read().  (Can also
				   * be set by an application to force a
				   * select()/poll() call before the next
				   * read, in cases where the app expects
				   * that an immediate read would fail.)
				   */
#define APR_INCOMPLETE_WRITE 8192 /**< like APR_INCOMPLETE_READ, but for write
                                   * @see APR_INCOMPLETE_READ
                                   */
#define APR_IPV6_V6ONLY     16384 /**< Don't accept IPv4 connections on an
                                   * IPv6 listening socket.
                                   */

/** @} */

/** Define what type of socket shutdown should occur. */
typedef enum {
    APR_SHUTDOWN_READ,          /**< no longer allow read request */
    APR_SHUTDOWN_WRITE,         /**< no longer allow write requests */
    APR_SHUTDOWN_READWRITE      /**< no longer allow read or write requests */
} apr_shutdown_how_e;

#define APR_IPV4_ADDR_OK  0x01  /**< @see apr_sockaddr_info_get() */
#define APR_IPV6_ADDR_OK  0x02  /**< @see apr_sockaddr_info_get() */

#if (!APR_HAVE_IN_ADDR)
/**
 * We need to make sure we always have an in_addr type, so APR will just
 * define it ourselves, if the platform doesn't provide it.
 */
struct in_addr {
    apr_uint32_t  s_addr; /**< storage to hold the IP# */
};
#endif

/**
 * @def APR_INET
 * Not all platforms have these defined, so we'll define them here
 * The default values come from FreeBSD 4.1.1
 */
#define APR_INET     AF_INET
/** @def APR_UNSPEC
 * Let the system decide which address family to use
 */
#ifdef AF_UNSPEC
#define APR_UNSPEC   AF_UNSPEC
#else
#define APR_UNSPEC   0
#endif
#if APR_HAVE_IPV6
#define APR_INET6    AF_INET6
#endif

/**
 * @defgroup IP_Proto IP Protocol Definitions for use when creating sockets
 * @{
 */
#define APR_PROTO_TCP       6   /**< TCP  */
#define APR_PROTO_UDP      17   /**< UDP  */
#define APR_PROTO_SCTP    132   /**< SCTP */
/** @} */

/**
 * Enum to tell us if we're interested in remote or local socket
 */
typedef enum {
    APR_LOCAL,
    APR_REMOTE
} apr_interface_e;

/**
 * The specific declaration of inet_addr's ... some platforms fall back
 * inet_network (this is not good, but necessary)
 */

#if APR_HAVE_INET_ADDR
#define apr_inet_addr    inet_addr
#elif APR_HAVE_INET_NETWORK        /* only DGUX, as far as I know */
/**
 * @warning
 * not generally safe... inet_network() and inet_addr() perform
 * different functions */
#define apr_inet_addr    inet_network
#endif

/** A structure to represent sockets */
typedef struct apr_socket_t     apr_socket_t;
/**
 * A structure to encapsulate headers and trailers for apr_socket_sendfile
 */
typedef struct apr_hdtr_t       apr_hdtr_t;
/** A structure to represent in_addr */
typedef struct in_addr          apr_in_addr_t;
/** A structure to represent an IP subnet */
typedef struct apr_ipsubnet_t apr_ipsubnet_t;

/** @remark use apr_uint16_t just in case some system has a short that isn't 16 bits... */
typedef apr_uint16_t            apr_port_t;

/** @remark It's defined here as I think it should all be platform safe...
 * @see apr_sockaddr_t
 */
typedef struct apr_sockaddr_t apr_sockaddr_t;
/**
 * APRs socket address type, used to ensure protocol independence
 */
struct apr_sockaddr_t {
    /** The pool to use... */
    apr_pool_t *pool;
    /** The hostname */
    char *hostname;
    /** Either a string of the port number or the service name for the port */
    char *servname;
    /** The numeric port */
    apr_port_t port;
    /** The family */
    apr_int32_t family;
    /** Union of either IPv4 or IPv6 sockaddr. */
    union {
        /** IPv4 sockaddr structure */
        struct sockaddr_in sin;
#if APR_HAVE_IPV6
        /** IPv6 sockaddr structure */
        struct sockaddr_in6 sin6;
#endif
    } sa;
    /** How big is the sockaddr we're using? */
    apr_socklen_t salen;
    /** How big is the ip address structure we're using? */
    int ipaddr_len;
    /** How big should the address buffer be?  16 for v4 or 46 for v6
     *  used in inet_ntop... */
    int addr_str_len;
    /** This points to the IP address structure within the appropriate
     *  sockaddr structure.  */
    void *ipaddr_ptr;
    /** If multiple addresses were found by apr_sockaddr_info_get(), this 
     *  points to a representation of the next address. */
    apr_sockaddr_t *next;
};

#if APR_HAS_SENDFILE
/** 
 * Support reusing the socket on platforms which support it (from disconnect,
 * specifically Win32.
 * @remark Optional flag passed into apr_socket_sendfile() 
 */
#define APR_SENDFILE_DISCONNECT_SOCKET      1
#endif

/** A structure to encapsulate headers and trailers for apr_socket_sendfile */
struct apr_hdtr_t {
    /** An iovec to store the headers sent before the file. */
    struct iovec* headers;
    /** number of headers in the iovec */
    int numheaders;
    /** An iovec to store the trailers sent after the file. */
    struct iovec* trailers;
    /** number of trailers in the iovec */
    int numtrailers;
};

/* function definitions */

/**
 * Create a socket.
 * @remark With APR 1.0, this function follows the prototype 
 * of apr_socket_create_ex.
 * @param new_sock The new socket that has been set up.
 * @param family The address family of the socket (e.g., APR_INET).
 * @param type The type of the socket (e.g., SOCK_STREAM).
 * @param cont The pool to use
 */
APR_DECLARE(apr_status_t) apr_socket_create(apr_socket_t **new_sock, 
                                            int family, int type,
                                            apr_pool_t *cont);

/**
 * Create a socket.
 * @remark With APR 1.0, this function is deprecated and apr_socket_create 
 * follows this prototype.
 * @param new_sock The new socket that has been set up.
 * @param family The address family of the socket (e.g., APR_INET).
 * @param type The type of the socket (e.g., SOCK_STREAM).
 * @param protocol The protocol of the socket (e.g., APR_PROTO_TCP).
 * @param cont The pool to use
 */
APR_DECLARE(apr_status_t) apr_socket_create_ex(apr_socket_t **new_sock, 
                                               int family, int type,
                                               int protocol,
                                               apr_pool_t *cont);

/**
 * Shutdown either reading, writing, or both sides of a socket.
 * @param thesocket The socket to close 
 * @param how How to shutdown the socket.  One of:
 * <PRE>
 *            APR_SHUTDOWN_READ         no longer allow read requests
 *            APR_SHUTDOWN_WRITE        no longer allow write requests
 *            APR_SHUTDOWN_READWRITE    no longer allow read or write requests 
 * </PRE>
 * @see apr_shutdown_how_e
 * @remark This does not actually close the socket descriptor, it just
 *      controls which calls are still valid on the socket.
 */
APR_DECLARE(apr_status_t) apr_socket_shutdown(apr_socket_t *thesocket,
                                              apr_shutdown_how_e how);

/** @deprecated @see apr_socket_shutdown */
APR_DECLARE(apr_status_t) apr_shutdown(apr_socket_t *thesocket,
                                       apr_shutdown_how_e how);

/**
 * Close a socket.
 * @param thesocket The socket to close 
 */
APR_DECLARE(apr_status_t) apr_socket_close(apr_socket_t *thesocket);

/**
 * Bind the socket to its associated port
 * @param sock The socket to bind 
 * @param sa The socket address to bind to
 * @remark This may be where we will find out if there is any other process
 *      using the selected port.
 */
APR_DECLARE(apr_status_t) apr_socket_bind(apr_socket_t *sock, 
                                          apr_sockaddr_t *sa);

/** @deprecated @see apr_socket_bind */
APR_DECLARE(apr_status_t) apr_bind(apr_socket_t *sock, apr_sockaddr_t *sa);

/**
 * Listen to a bound socket for connections.
 * @param sock The socket to listen on 
 * @param backlog The number of outstanding connections allowed in the sockets
 *                listen queue.  If this value is less than zero, the listen
 *                queue size is set to zero.  
 */
APR_DECLARE(apr_status_t) apr_socket_listen(apr_socket_t *sock, 
                                            apr_int32_t backlog);

/** @deprecated @see apr_socket_listen */
APR_DECLARE(apr_status_t) apr_listen(apr_socket_t *sock, apr_int32_t backlog);

/**
 * Accept a new connection request
 * @param new_sock A copy of the socket that is connected to the socket that
 *                 made the connection request.  This is the socket which should
 *                 be used for all future communication.
 * @param sock The socket we are listening on.
 * @param connection_pool The pool for the new socket.
 */
APR_DECLARE(apr_status_t) apr_socket_accept(apr_socket_t **new_sock, 
                                            apr_socket_t *sock,
                                            apr_pool_t *connection_pool);

/** @deprecated @see apr_socket_accept */
APR_DECLARE(apr_status_t) apr_accept(apr_socket_t **new_sock, 
                                     apr_socket_t *sock,
                                     apr_pool_t *connection_pool);

/**
 * Issue a connection request to a socket either on the same machine 
 * or a different one.
 * @param sock The socket we wish to use for our side of the connection 
 * @param sa The address of the machine we wish to connect to.  If NULL,
 *           APR assumes that the sockaddr_in in the apr_socket is 
 *           completely filled out.
 */
APR_DECLARE(apr_status_t) apr_socket_connect(apr_socket_t *sock,
                                             apr_sockaddr_t *sa);

/** @deprecated @see apr_socket_connect */
APR_DECLARE(apr_status_t) apr_connect(apr_socket_t *sock, apr_sockaddr_t *sa);

/**
 * Create apr_sockaddr_t from hostname, address family, and port.
 * @param sa The new apr_sockaddr_t.
 * @param hostname The hostname or numeric address string to resolve/parse, or
 *               NULL to build an address that corresponds to 0.0.0.0 or ::
 * @param family The address family to use, or APR_UNSPEC if the system should 
 *               decide.
 * @param port The port number.
 * @param flags Special processing flags:
 * <PRE>
 *       APR_IPV4_ADDR_OK          first query for IPv4 addresses; only look
 *                                 for IPv6 addresses if the first query failed;
 *                                 only valid if family is APR_UNSPEC and hostname
 *                                 isn't NULL; mutually exclusive with
 *                                 APR_IPV6_ADDR_OK
 *       APR_IPV6_ADDR_OK          first query for IPv6 addresses; only look
 *                                 for IPv4 addresses if the first query failed;
 *                                 only valid if family is APR_UNSPEC and hostname
 *                                 isn't NULL and APR_HAVE_IPV6; mutually exclusive
 *                                 with APR_IPV4_ADDR_OK
 * </PRE>
 * @param p The pool for the apr_sockaddr_t and associated storage.
 */
APR_DECLARE(apr_status_t) apr_sockaddr_info_get(apr_sockaddr_t **sa,
                                          const char *hostname,
                                          apr_int32_t family,
                                          apr_port_t port,
                                          apr_int32_t flags,
                                          apr_pool_t *p);

/**
 * Look up the host name from an apr_sockaddr_t.
 * @param hostname The hostname.
 * @param sa The apr_sockaddr_t.
 * @param flags Special processing flags.
 */
APR_DECLARE(apr_status_t) apr_getnameinfo(char **hostname,
                                          apr_sockaddr_t *sa,
                                          apr_int32_t flags);

/**
 * Parse hostname/IP address with scope id and port.
 *
 * Any of the following strings are accepted:
 *   8080                  (just the port number)
 *   www.apache.org        (just the hostname)
 *   www.apache.org:8080   (hostname and port number)
 *   [fe80::1]:80          (IPv6 numeric address string only)
 *   [fe80::1%eth0]        (IPv6 numeric address string and scope id)
 *
 * Invalid strings:
 *                         (empty string)
 *   [abc]                 (not valid IPv6 numeric address string)
 *   abc:65536             (invalid port number)
 *
 * @param addr The new buffer containing just the hostname.  On output, *addr 
 *             will be NULL if no hostname/IP address was specfied.
 * @param scope_id The new buffer containing just the scope id.  On output, 
 *                 *scope_id will be NULL if no scope id was specified.
 * @param port The port number.  On output, *port will be 0 if no port was 
 *             specified.
 *             ### FIXME: 0 is a legal port (per RFC 1700). this should
 *             ### return something besides zero if the port is missing.
 * @param str The input string to be parsed.
 * @param p The pool from which *addr and *scope_id are allocated.
 * @remark If scope id shouldn't be allowed, check for scope_id != NULL in 
 *         addition to checking the return code.  If addr/hostname should be 
 *         required, check for addr == NULL in addition to checking the 
 *         return code.
 */
APR_DECLARE(apr_status_t) apr_parse_addr_port(char **addr,
                                              char **scope_id,
                                              apr_port_t *port,
                                              const char *str,
                                              apr_pool_t *p);

/**
 * Get name of the current machine
 * @param buf A buffer to store the hostname in.
 * @param len The maximum length of the hostname that can be stored in the
 *            buffer provided.  The suggested length is APRMAXHOSTLEN + 1.
 * @param cont The pool to use.
 * @remark If the buffer was not large enough, an error will be returned.
 */
APR_DECLARE(apr_status_t) apr_gethostname(char *buf, int len, apr_pool_t *cont);

/**
 * Return the data associated with the current socket
 * @param data The user data associated with the socket.
 * @param key The key to associate with the user data.
 * @param sock The currently open socket.
 */
APR_DECLARE(apr_status_t) apr_socket_data_get(void **data, const char *key,
                                              apr_socket_t *sock);

/**
 * Set the data associated with the current socket.
 * @param sock The currently open socket.
 * @param data The user data to associate with the socket.
 * @param key The key to associate with the data.
 * @param cleanup The cleanup to call when the socket is destroyed.
 */
APR_DECLARE(apr_status_t) apr_socket_data_set(apr_socket_t *sock, void *data,
                                              const char *key,
                                              apr_status_t (*cleanup)(void*));

/**
 * Send data over a network.
 * @param sock The socket to send the data over.
 * @param buf The buffer which contains the data to be sent. 
 * @param len On entry, the number of bytes to send; on exit, the number
 *            of bytes sent.
 * @remark
 * <PRE>
 * This functions acts like a blocking write by default.  To change 
 * this behavior, use apr_socket_timeout_set().
 *
 * It is possible for both bytes to be sent and an error to be returned.
 *
 * APR_EINTR is never returned.
 * </PRE>
 */
APR_DECLARE(apr_status_t) apr_socket_send(apr_socket_t *sock, const char *buf, 
                                          apr_size_t *len);

/** @deprecated @see apr_socket_send */
APR_DECLARE(apr_status_t) apr_send(apr_socket_t *sock, const char *buf, 
                                   apr_size_t *len);

/**
 * Send multiple packets of data over a network.
 * @param sock The socket to send the data over.
 * @param vec The array of iovec structs containing the data to send 
 * @param nvec The number of iovec structs in the array
 * @param len Receives the number of bytes actually written
 * @remark
 * <PRE>
 * This functions acts like a blocking write by default.  To change 
 * this behavior, use apr_socket_timeout_set().
 * The number of bytes actually sent is stored in argument 3.
 *
 * It is possible for both bytes to be sent and an error to be returned.
 *
 * APR_EINTR is never returned.
 * </PRE>
 */
APR_DECLARE(apr_status_t) apr_socket_sendv(apr_socket_t *sock, 
                                           const struct iovec *vec,
                                           apr_int32_t nvec, apr_size_t *len);

/** @deprecated @see apr_socket_sendv */
APR_DECLARE(apr_status_t) apr_sendv(apr_socket_t *sock, 
                                    const struct iovec *vec,
                                    apr_int32_t nvec, apr_size_t *len);

/**
 * @param sock The socket to send from
 * @param where The apr_sockaddr_t describing where to send the data
 * @param flags The flags to use
 * @param buf  The data to send
 * @param len  The length of the data to send
 */
APR_DECLARE(apr_status_t) apr_socket_sendto(apr_socket_t *sock, 
                                            apr_sockaddr_t *where,
                                            apr_int32_t flags, const char *buf, 
                                            apr_size_t *len);

/** @deprecated @see apr_socket_sendto */
APR_DECLARE(apr_status_t) apr_sendto(apr_socket_t *sock, apr_sockaddr_t *where,
                                     apr_int32_t flags, const char *buf, 
                                     apr_size_t *len);

/**
 * @param from The apr_sockaddr_t to fill in the recipient info
 * @param sock The socket to use
 * @param flags The flags to use
 * @param buf  The buffer to use
 * @param len  The length of the available buffer
 */

APR_DECLARE(apr_status_t) apr_socket_recvfrom(apr_sockaddr_t *from, 
                                              apr_socket_t *sock,
                                              apr_int32_t flags, char *buf, 
                                              apr_size_t *len);
 
/** @deprecated @see apr_socket_recvfrom */
APR_DECLARE(apr_status_t) apr_recvfrom(apr_sockaddr_t *from, apr_socket_t *sock,
                                       apr_int32_t flags, char *buf, 
                                       apr_size_t *len);

#if APR_HAS_SENDFILE || defined(DOXYGEN)

/**
 * Send a file from an open file descriptor to a socket, along with 
 * optional headers and trailers
 * @param sock The socket to which we're writing
 * @param file The open file from which to read
 * @param hdtr A structure containing the headers and trailers to send
 * @param offset Offset into the file where we should begin writing
 * @param len (input)  - Number of bytes to send from the file 
 *            (output) - Number of bytes actually sent, 
 *                       including headers, file, and trailers
 * @param flags APR flags that are mapped to OS specific flags
 * @remark This functions acts like a blocking write by default.  To change 
 *         this behavior, use apr_socket_timeout_set().
 *         The number of bytes actually sent is stored in argument 5.
 */
APR_DECLARE(apr_status_t) apr_socket_sendfile(apr_socket_t *sock, 
                                              apr_file_t *file,
                                              apr_hdtr_t *hdtr,
                                              apr_off_t *offset,
                                              apr_size_t *len,
                                              apr_int32_t flags);

/** @deprecated @see apr_socket_sendfile */
APR_DECLARE(apr_status_t) apr_sendfile(apr_socket_t *sock, apr_file_t *file,
                                       apr_hdtr_t *hdtr, apr_off_t *offset,
                                       apr_size_t *len, apr_int32_t flags);

#endif /* APR_HAS_SENDFILE */

/**
 * Read data from a network.
 * @param sock The socket to read the data from.
 * @param buf The buffer to store the data in. 
 * @param len On entry, the number of bytes to receive; on exit, the number
 *            of bytes received.
 * @remark
 * <PRE>
 * This functions acts like a blocking read by default.  To change 
 * this behavior, use apr_socket_timeout_set().
 * The number of bytes actually sent is stored in argument 3.
 *
 * It is possible for both bytes to be received and an APR_EOF or
 * other error to be returned.
 *
 * APR_EINTR is never returned.
 * </PRE>
 */
APR_DECLARE(apr_status_t) apr_socket_recv(apr_socket_t *sock, 
                                   char *buf, apr_size_t *len);

/** @deprecated @see apr_socket_recv */
APR_DECLARE(apr_status_t) apr_recv(apr_socket_t *sock, 
                                   char *buf, apr_size_t *len);

/**
 * Setup socket options for the specified socket
 * @param sock The socket to set up.
 * @param opt The option we would like to configure.  One of:
 * <PRE>
 *            APR_SO_DEBUG      --  turn on debugging information 
 *            APR_SO_KEEPALIVE  --  keep connections active
 *            APR_SO_LINGER     --  lingers on close if data is present
 *            APR_SO_NONBLOCK   --  Turns blocking on/off for socket
 *            APR_SO_REUSEADDR  --  The rules used in validating addresses
 *                                  supplied to bind should allow reuse
 *                                  of local addresses.
 *            APR_SO_SNDBUF     --  Set the SendBufferSize
 *            APR_SO_RCVBUF     --  Set the ReceiveBufferSize
 * </PRE>
 * @param on Value for the option.
 */
APR_DECLARE(apr_status_t) apr_socket_opt_set(apr_socket_t *sock,
                                             apr_int32_t opt, apr_int32_t on);

/** @deprecated @see apr_socket_opt_set */
APR_DECLARE(apr_status_t) apr_setsocketopt(apr_socket_t *sock,
                                           apr_int32_t opt, apr_int32_t on);

/**
 * Setup socket timeout for the specified socket
 * @param sock The socket to set up.
 * @param t Value for the timeout.
 * <PRE>
 *   t > 0  -- read and write calls return APR_TIMEUP if specified time
 *             elapsess with no data read or written
 *   t == 0 -- read and write calls never block
 *   t < 0  -- read and write calls block
 * </PRE>
 */
APR_DECLARE(apr_status_t) apr_socket_timeout_set(apr_socket_t *sock,
                                                 apr_interval_time_t t);

/**
 * Query socket options for the specified socket
 * @param sock The socket to query
 * @param opt The option we would like to query.  One of:
 * <PRE>
 *            APR_SO_DEBUG      --  turn on debugging information 
 *            APR_SO_KEEPALIVE  --  keep connections active
 *            APR_SO_LINGER     --  lingers on close if data is present
 *            APR_SO_NONBLOCK   --  Turns blocking on/off for socket
 *            APR_SO_REUSEADDR  --  The rules used in validating addresses
 *                                  supplied to bind should allow reuse
 *                                  of local addresses.
 *            APR_SO_SNDBUF     --  Set the SendBufferSize
 *            APR_SO_RCVBUF     --  Set the ReceiveBufferSize
 *            APR_SO_DISCONNECTED -- Query the disconnected state of the socket.
 *                                  (Currently only used on Windows)
 * </PRE>
 * @param on Socket option returned on the call.
 */
APR_DECLARE(apr_status_t) apr_socket_opt_get(apr_socket_t *sock, 
                                             apr_int32_t opt, apr_int32_t *on);

/** @deprecated @see apr_socket_opt_set */
APR_DECLARE(apr_status_t) apr_getsocketopt(apr_socket_t *sock, 
                                           apr_int32_t opt, apr_int32_t *on);

/**
 * Query socket timeout for the specified socket
 * @param sock The socket to query
 * @param t Socket timeout returned from the query.
 */
APR_DECLARE(apr_status_t) apr_socket_timeout_get(apr_socket_t *sock, 
                                                 apr_interval_time_t *t);

/**
 * Query the specified socket if at the OOB/Urgent data mark
 * @param sock The socket to query
 * @param atmark Is set to true if socket is at the OOB/urgent mark,
 *               otherwise is set to false.
 */
APR_DECLARE(apr_status_t) apr_socket_atmark(apr_socket_t *sock, 
                                            int *atmark);

/**
 * Return an apr_sockaddr_t from an apr_socket_t
 * @param sa The returned apr_sockaddr_t.
 * @param which Which interface do we want the apr_sockaddr_t for?
 * @param sock The socket to use
 */
APR_DECLARE(apr_status_t) apr_socket_addr_get(apr_sockaddr_t **sa,
                                              apr_interface_e which,
                                              apr_socket_t *sock);
 
/**
 * Set the port in an APR socket address.
 * @param sockaddr The socket address to set.
 * @param port The port to be stored in the socket address.
 * @deprecated @see apr_sockaddr_info_get
 */
APR_DECLARE(apr_status_t) apr_sockaddr_port_set(apr_sockaddr_t *sockaddr,
                                                apr_port_t port);

/**
 * Return the port in an APR socket address.
 * @param port The port from the socket address.
 * @param sockaddr The socket address to reference.
 * @deprecated Access port field directly.
 */
APR_DECLARE(apr_status_t) apr_sockaddr_port_get(apr_port_t *port,
                                                apr_sockaddr_t *sockaddr);

/**
 * Set the IP address in an APR socket address.
 * @param sockaddr The socket address to use 
 * @param addr The IP address to attach to the socket.
 *             Use APR_ANYADDR to use any IP addr on the machine.
 * @deprecated @see apr_sockaddr_info_get
 */
APR_DECLARE(apr_status_t) apr_sockaddr_ip_set(apr_sockaddr_t *sockaddr,
                                              const char *addr);

/**
 * Return the IP address (in numeric address string format) in
 * an APR socket address.  APR will allocate storage for the IP address 
 * string from the pool of the apr_sockaddr_t.
 * @param addr The IP address.
 * @param sockaddr The socket address to reference.
 */
APR_DECLARE(apr_status_t) apr_sockaddr_ip_get(char **addr, 
                                              apr_sockaddr_t *sockaddr);

/**
 * See if the IP addresses in two APR socket addresses are
 * equivalent.  Appropriate logic is present for comparing
 * IPv4-mapped IPv6 addresses with IPv4 addresses.
 *
 * @param addr1 One of the APR socket addresses.
 * @param addr2 The other APR socket address.
 * @remark The return value will be non-zero if the addresses
 * are equivalent.
 */
APR_DECLARE(int) apr_sockaddr_equal(const apr_sockaddr_t *addr1,
                                    const apr_sockaddr_t *addr2);


#if APR_FILES_AS_SOCKETS || defined(DOXYGEN)

/**
 * Convert a File type to a socket so that it can be used in a poll operation.
 * @param newsock the newly created socket which represents a file.
 * @param file the file to mask as a socket.
 * @warning This is not available on all platforms.  Platforms that have the
 *      ability to poll files for data to be read/written/exceptions will
 *      have the APR_FILES_AS_SOCKETS macro defined as true.
 * @deprecated This function has been deprecated, because of the new poll
 *             implementation.
 */
APR_DECLARE(apr_status_t) apr_socket_from_file(apr_socket_t **newsock,
                                               apr_file_t *file);

#endif /* APR_FILES_AS_SOCKETS */

/**
 * Given an apr_sockaddr_t and a service name, set the port for the service
 * @param sockaddr The apr_sockaddr_t that will have its port set
 * @param servname The name of the service you wish to use
 */
APR_DECLARE(apr_status_t) apr_getservbyname(apr_sockaddr_t *sockaddr, 
                                            const char *servname);
/**
 * Build an ip-subnet representation from an IP address and optional netmask or
 * number-of-bits.
 * @param ipsub The new ip-subnet representation
 * @param ipstr The input IP address string
 * @param mask_or_numbits The input netmask or number-of-bits string, or NULL
 * @param p The pool to allocate from
 */
APR_DECLARE(apr_status_t) apr_ipsubnet_create(apr_ipsubnet_t **ipsub, 
                                              const char *ipstr, 
                                              const char *mask_or_numbits, 
                                              apr_pool_t *p);

/**
 * Test the IP address in an apr_sockaddr_t against a pre-built ip-subnet
 * representation.
 * @param ipsub The ip-subnet representation
 * @param sa The socket address to test
 * @return non-zero if the socket address is within the subnet, 0 otherwise
 */
APR_DECLARE(int) apr_ipsubnet_test(apr_ipsubnet_t *ipsub, apr_sockaddr_t *sa);

#if APR_HAS_SO_ACCEPTFILTER || defined(DOXYGEN)
/**
 * Set an OS level accept filter.
 * @param sock The socket to put the accept filter on.
 * @param name The accept filter
 * @param args Any extra args to the accept filter.  Passing NULL here removes
 *             the accept filter. 
 */
apr_status_t apr_socket_accept_filter(apr_socket_t *sock, char *name,
                                      char *args);
#endif

/**
 * Return the protocol of the socket.
 * @param sock The socket to query.
 * @param protocol The returned protocol (e.g., APR_PROTO_TCP).
 */
APR_DECLARE(apr_status_t) apr_socket_protocol_get(apr_socket_t *sock,
                                                  int *protocol);

/**
 * Set a socket to be inherited by child processes.
 */
APR_DECLARE_INHERIT_SET(socket);

/** @deprecated @see apr_socket_inherit_set */
APR_DECLARE(void) apr_socket_set_inherit(apr_socket_t *skt);

/**
 * Unset a socket from being inherited by child processes.
 */
APR_DECLARE_INHERIT_UNSET(socket);

/** @deprecated @see apr_socket_inherit_unset */
APR_DECLARE(void) apr_socket_unset_inherit(apr_socket_t *skt);

/** @} */

#ifdef __cplusplus
}
#endif

#endif  /* ! APR_NETWORK_IO_H */

