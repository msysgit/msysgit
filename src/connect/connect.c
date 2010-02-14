/***********************************************************************
 * connect.c -- Make socket connection using SOCKS4/5 and HTTP tunnel.
 *
 * Copyright (c) 2000-2006 Shun-ichi Goto
 * Copyright (c) 2002, J. Grant (English Corrections)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * ---------------------------------------------------------
 * PROJECT:  My Test Program
 * AUTHOR:   Shun-ichi GOTO <gotoh@taiyo.co.jp>
 * CREATE:   Wed Jun 21, 2000
 * REVISION: $Revision: 100 $
 * ---------------------------------------------------------
 *
 * Getting Source
 * ==============
 *
 *   Recent version of 'connect.c' is available from
 *     http://www.taiyo.co.jp/~gotoh/ssh/connect.c
 *
 *   Related tool, ssh-askpass.exe (alternative ssh-askpass on UNIX)
 *   is available:
 *     http://www.taiyo.co.jp/~gotoh/ssh/ssh-askpass.exe.gz
 *
 *   See more detail:
 *     http://www.taiyo.co.jp/~gotoh/ssh/connect.html
 *
 * How To Compile
 * ==============
 *
 *  On UNIX environment:
 *      $ gcc connect.c -o connect
 *
 *  On SOLARIS:
 *      $ gcc -o connect -lresolv -lsocket -lnsl connect.c
 *
 *  on Win32 environment:
 *      $ cl connect.c wsock32.lib advapi32.lib
 *    or
 *      $ bcc32 connect.c wsock32.lib advapi32.lib
 *    or
 *      $ gcc connect.c -o connect
 *
 *  on Mac OS X environment:
 *      $ gcc connect.c -o connect -lresolv
 *    or
 *      $ gcc connect.c -o connect -DBIND_8_COMPAT=1
 *
 * How To Use
 * ==========
 *
 *   You can specify proxy method in an environment variable or in a
 *   command line option.
 *
 *   usage:  connect [-dnhst45] [-R resolve] [-p local-port] [-w sec]
 *                   [-H [user@]proxy-server[:port]]
 *                   [-S [user@]socks-server[:port]]
 *                   [-T proxy-server[:port]]
 *                   [-c telnet proxy command]
 *                   host port
 *
 *   "host" and "port" is for the target hostname and port-number to
 *   connect to.
 *
 *   The -H option specifys a hostname and port number of the http proxy
 *   server to relay. If port is omitted, 80 is used. You can specify this
 *   value in the environment variable HTTP_PROXY and pass the -h option
 *   to use it.
 *
 *   The -S option specifys the hostname and port number of the SOCKS
 *   server to relay.  Like -H, port number can be omitted and the default
 *   is 1080. You can also specify this value pair in the environment
 *   variable SOCKS5_SERVER and give the -s option to use it.
 *
 *   The '-4' and the '-5' options are for specifying SOCKS relaying and
 *   indicates protocol version to use. It is valid only when used with
 *   '-s' or '-S'. Default is '-5' (protocol version 5)
 *
 *   The '-R' option is for specifying method to resolve the
 *   hostname. Three keywords ("local", "remote", "both") or dot-notation
 *   IP address are acceptable.  The keyword "both" means, "Try local
 *   first, then remote". If a dot-notation IP address is specified, use
 *   this host as nameserver. The default is "remote" for SOCKS5 or
 *   "local" for others. On SOCKS4 protocol, remote resolving method
 *   ("remote" and "both") requires protocol 4a supported server.
 *
 *   The '-p' option will forward a local TCP port instead of using the
 *   standard input and output.
 *
 *   The '-P' option is same to '-p' except keep remote session. The
 *   program repeats waiting the port with holding remote session without
 *   disconnecting. To disconnect the remote session, send EOF to stdin or
 *   kill the program.
 *
 *   The '-w' option specifys timeout seconds for making connection with
 *   TARGET host.
 *
 *   The '-d' option is used for debug. If you fail to connect, use this
 *   and check request to and response from server.
 *
 *   You can omit the "port" argument when program name is special format
 *   containing port number itself. For example,
 *     $ ln -s connect connect-25
 *   means this connect-25 command is spcifying port number 25 already
 *   so you need not 2nd argument (and ignored if specified).
 *
 *   To use proxy, this example is for SOCKS5 connection to connect to
 *   'host' at port 25 via SOCKS5 server on 'firewall' host.
 *     $ connect -S firewall  host 25
 *   or
 *     $ SOCKS5_SERVER=firewall; export SOCKS5_SERVER
 *     $ connect -s host 25
 *
 *   For a HTTP-PROXY connection:
 *     $ connect -H proxy-server:8080  host 25
 *   or
 *     $ HTTP_PROXY=proxy-server:8080; export HTTP_PROXY
 *     $ connect -h host 25
 *   To forward a local port, for example to use ssh:
 *     $ connect -p 5550 -H proxy-server:8080  host 22
 *    ($ ssh -l user -p 5550 localhost )
 *
 * TIPS
 * ====
 *
 *   Connect.c doesn't have any configuration to specify the SOCKS server.
 *   If you are a mobile user, this limitation might bother you.  However,
 *   You can compile connect.c and link with other standard SOCKS library
 *   like the NEC SOCKS5 library or Dante. This means connect.c is
 *   socksified and uses a configration file like to other SOCKSified
 *   network commands and you can switch configuration file any time
 *   (ex. when ppp startup) that brings you switching of SOCKS server for
 *   connect.c in same way with other commands. For this case, you can
 *   write ~/.ssh/config like this:
 *
 *     ProxyCommand connect -n %h %p
 *
 * SOCKS5 authentication
 * =====================
 *
 *   Only USER/PASS authentication is supported.
 *
 * Proxy authentication
 * ====================
 *
 *   Only BASIC scheme is supported.
 *
 * Authentication informations
 * ===========================
 *
 *   User name for authentication is specifed by an environment variable
 *   or system login name.  And password is specified from environment
 *   variable or external program (specified in $SSH_ASKPASS) or tty.
 *
 *   Following environment variable is used for specifying user name.
 *     SOCKS: $SOCKS5_USER, $LOGNAME, $USER
 *     HTTP Proxy: $HTTP_PROXY_USER, $LOGNAME, $USER
 *
 * ssh-askpass support
 * ===================
  *
 *   You can use ssh-askpass (came from OpenSSH or else) to specify
 *   password on graphical environment (X-Window or MS Windows). To use
 *   this, set program name to environment variable SSH_ASKPASS. On UNIX,
 *   X-Window must be required, so $DISPLAY environment variable is also
 *   needed.  On Win32 environment, $DISPLAY is not mentioned.
 *
 * Related Informations
 * ====================
 *
 *   SOCKS5 -- RFC 1928, RFC 1929, RFC 1961
 *             NEC SOCKS Reference Implementation is available from:
 *               http://www.socks.nec.com
 *             DeleGate version 5 or earlier can be SOCKS4 server,
 *             and version 6 can be SOCKS5 and SOCKS4 server.
 *             and version 7.7.0 or later can be SOCKS5 and SOCKS4a server.
 *               http://www.delegate.org/delegate/
 *
 *   HTTP-Proxy --
 *             Many http proxy servers supports this, but https should
 *             be allowed as configuration on your host.
 *             For example on DeleGate, you should add "https" to the
 *             "REMITTABLE" parameter to allow HTTP-Proxy like this:
 *               delegated -Pxxxx ...... REMITTABLE="+,https" ...
 *
 *  Hypertext Transfer Protocol -- HTTP/1.1  -- RFC 2616
 *  HTTP Authentication: Basic and Digest Access Authentication -- RFC 2617
 *             For proxy authentication, refer these documents.
 *
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <memory.h>
#include <errno.h>
#include <assert.h>
#include <sys/types.h>
#include <stdarg.h>
#include <fcntl.h>
#include <signal.h>

#ifdef __CYGWIN32__
#undef _WIN32
#endif

#ifdef _WIN32
#include <windows.h>
#include <winsock.h>
#include <sys/stat.h>
#include <io.h>
#include <conio.h>
#else /* !_WIN32 */
#include <unistd.h>
#include <pwd.h>
#include <termios.h>
#include <sys/time.h>
#ifndef __hpux
#include <sys/select.h>
#endif /* __hpux */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#if !defined(_WIN32) && !defined(__CYGWIN32__)
#define WITH_RESOLVER 1
#include <arpa/nameser.h>
#include <resolv.h>
#else  /* not ( not _WIN32 && not __CYGWIN32__) */
#undef WITH_RESOLVER
#endif /* not ( not _WIN32 && not __CYGWIN32__) */
#endif /* !_WIN32 */

#ifdef _WIN32
#define ECONNRESET WSAECONNRESET
#endif /* _WI32 */



#ifndef LINT
static char *vcid = "$Id: connect.c 100 2007-07-03 10:48:26Z gotoh $";
#endif

/* Microsoft Visual C/C++ has _snprintf() and _vsnprintf() */
#ifdef _MSC_VER
#define snprintf _snprintf
#define vsnprintf _vsnprintf
#endif

/* consider Borland C */
#ifdef __BORLANDC__
#define _kbhit kbhit
#define _setmode setmode
#endif

/* help message.
   Win32 environment does not support -R option (vc and cygwin)
   Win32 native compilers does not support -w option, yet (vc)
*/
static char *usage = "usage: %s [-dnhst45] [-p local-port]"
#ifdef _WIN32
#ifdef __CYGWIN32__
"[-w timeout] \n"                               /* cygwin cannot -R */
#else  /* not __CYGWIN32__ */
" \n"                                           /* VC cannot -w nor -R  */
#endif /* not __CYGWIN32__ */
#else  /* not _WIN32 */
/* help message for UNIX */
"[-R resolve] [-w timeout] \n"
#endif /* not _WIN32 */
"          [-H proxy-server[:port]] [-S [user@]socks-server[:port]] \n"
"          [-T proxy-server[:port]]\n"
"          [-c telnet-proxy-command]\n"
"          host port\n";

/* name of this program */
char *progname = NULL;
char *progdesc = "connect --- simple relaying command via proxy.";
char *rcs_revstr = "$Revision: 100 $";
char *revstr = NULL;
int major_version = 1;
int minor_version = 0;

/* set of character for strspn() */
const char *digits    = "0123456789";
const char *dotdigits = "0123456789.";

/* options */
int f_debug = 0;

/* report flag to hide secure information */
int f_report = 1;

int connect_timeout = 0;

/* local input type */
#define LOCAL_STDIO     0
#define LOCAL_SOCKET    1
char *local_type_names[] = { "stdio", "socket" };
int   local_type = LOCAL_STDIO;
u_short local_port = 0;                         /* option 'p' */
int f_hold_session = 0;                         /* option 'P' */

char *telnet_command = "telnet %h %p";

/* utiity types, pair holder of number and string */
typedef struct {
    int num;
    const char *str;
} LOOKUP_ITEM;

/* relay method, server and port */
#define METHOD_UNDECIDED 0
#define METHOD_DIRECT    1
#define METHOD_SOCKS     2
#define METHOD_HTTP      3
#define METHOD_TELNET    4
char *method_names[] = { "UNDECIDED", "DIRECT", "SOCKS", "HTTP", "TELNET" };

int   relay_method = METHOD_UNDECIDED;          /* relaying method */
char *relay_host = NULL;                        /* hostname of relay server */
u_short relay_port = 0;                         /* port of relay server */
char *relay_user = NULL;                        /* user name for auth */

/* destination target host and port */
char *dest_host = NULL;
struct sockaddr_in dest_addr;
u_short dest_port = 0;

/* informations for SOCKS */
#define SOCKS5_REP_SUCCEEDED    0x00    /* succeeded */
#define SOCKS5_REP_FAIL         0x01    /* general SOCKS serer failure */
#define SOCKS5_REP_NALLOWED     0x02    /* connection not allowed by ruleset */
#define SOCKS5_REP_NUNREACH     0x03    /* Network unreachable */
#define SOCKS5_REP_HUNREACH     0x04    /* Host unreachable */
#define SOCKS5_REP_REFUSED      0x05    /* connection refused */
#define SOCKS5_REP_EXPIRED      0x06    /* TTL expired */
#define SOCKS5_REP_CNOTSUP      0x07    /* Command not supported */
#define SOCKS5_REP_ANOTSUP      0x08    /* Address not supported */
#define SOCKS5_REP_INVADDR      0x09    /* Inalid address */

LOOKUP_ITEM socks5_rep_names[] = {
    { SOCKS5_REP_SUCCEEDED, "succeeded"},
    { SOCKS5_REP_FAIL,      "general SOCKS server failure"},
    { SOCKS5_REP_NALLOWED,  "connection not allowed by ruleset"},
    { SOCKS5_REP_NUNREACH,  "Network unreachable"},
    { SOCKS5_REP_HUNREACH,  "Host unreachable"},
    { SOCKS5_REP_REFUSED,   "connection refused"},
    { SOCKS5_REP_EXPIRED,   "TTL expired"},
    { SOCKS5_REP_CNOTSUP,   "Command not supported"},
    { SOCKS5_REP_ANOTSUP,   "Address not supported"},
    { SOCKS5_REP_INVADDR,   "Invalid address"},
    { -1, NULL }
};

/* SOCKS5 authentication methods */
#define SOCKS5_AUTH_REJECT      0xFF    /* No acceptable auth method */
#define SOCKS5_AUTH_NOAUTH      0x00    /* without authentication */
#define SOCKS5_AUTH_GSSAPI      0x01    /* GSSAPI */
#define SOCKS5_AUTH_USERPASS    0x02    /* User/Password */
#define SOCKS5_AUTH_CHAP        0x03    /* Challenge-Handshake Auth Proto. */
#define SOCKS5_AUTH_EAP         0x05    /* Extensible Authentication Proto. */
#define SOCKS5_AUTH_MAF         0x08    /* Multi-Authentication Framework */

#define SOCKS4_REP_SUCCEEDED    90      /* rquest granted (succeeded) */
#define SOCKS4_REP_REJECTED     91      /* request rejected or failed */
#define SOCKS4_REP_IDENT_FAIL   92      /* cannot connect identd */
#define SOCKS4_REP_USERID       93      /* user id not matched */

LOOKUP_ITEM socks4_rep_names[] = {
    { SOCKS4_REP_SUCCEEDED,  "request granted (succeeded)"},
    { SOCKS4_REP_REJECTED,   "request rejected or failed"},
    { SOCKS4_REP_IDENT_FAIL, "cannot connect identd"},
    { SOCKS4_REP_USERID,     "user id not matched"},
    { -1, NULL }
};

#define RESOLVE_UNKNOWN 0
#define RESOLVE_LOCAL   1
#define RESOLVE_REMOTE  2
#define RESOLVE_BOTH    3
char *resolve_names[] = { "UNKNOWN", "LOCAL", "REMOTE", "BOTH" };

int socks_version = 5;                          /* SOCKS protocol version */
int socks_resolve = RESOLVE_UNKNOWN;
struct sockaddr_in socks_ns;
char *socks5_auth = NULL;

/* Environment variable names */
#define ENV_SOCKS_SERVER  "SOCKS_SERVER"        /* SOCKS server */
#define ENV_SOCKS5_SERVER "SOCKS5_SERVER"
#define ENV_SOCKS4_SERVER "SOCKS4_SERVER"

#define ENV_SOCKS_RESOLVE  "SOCKS_RESOLVE"      /* resolve method */
#define ENV_SOCKS5_RESOLVE "SOCKS5_RESOLVE"
#define ENV_SOCKS4_RESOLVE "SOCKS4_RESOLVE"

#define ENV_SOCKS5_USER     "SOCKS5_USER"       /* auth user for SOCKS5 */
#define ENV_SOCKS4_USER     "SOCKS4_USER"       /* auth user for SOCKS4 */
#define ENV_SOCKS_USER      "SOCKS_USER"        /* auth user for SOCKS */
#define ENV_SOCKS5_PASSWD   "SOCKS5_PASSWD"     /* auth password for SOCKS5 */
#define ENV_SOCKS5_PASSWORD "SOCKS5_PASSWORD"   /* old style */

#define ENV_HTTP_PROXY          "HTTP_PROXY"    /* common env var */
#define ENV_HTTP_PROXY_USER     "HTTP_PROXY_USER" /* auth user */
#define ENV_HTTP_PROXY_PASSWORD "HTTP_PROXY_PASSWORD" /* auth password */

#define ENV_TELNET_PROXY          "TELNET_PROXY"    /* common env var */

#define ENV_CONNECT_USER     "CONNECT_USER"     /* default auth user name */
#define ENV_CONNECT_PASSWORD "CONNECT_PASSWORD" /* default auth password */

#define ENV_SOCKS_DIRECT   "SOCKS_DIRECT"       /* addr-list for non-proxy */
#define ENV_SOCKS5_DIRECT  "SOCKS5_DIRECT"
#define ENV_SOCKS4_DIRECT  "SOCKS4_DIRECT"
#define ENV_HTTP_DIRECT    "HTTP_DIRECT"
#define ENV_CONNECT_DIRECT "CONNECT_DIRECT"

#define ENV_SOCKS5_AUTH "SOCKS5_AUTH"
#define ENV_SSH_ASKPASS "SSH_ASKPASS"           /* askpass program */

/* Prefix string of HTTP_PROXY */
#define HTTP_PROXY_PREFIX "http://"
#define PROXY_AUTH_NONE 0
#define PROXY_AUTH_BASIC 1
#define PROXY_AUTH_DIGEST 2
int proxy_auth_type = PROXY_AUTH_NONE;

/* reason of end repeating */
#define REASON_UNK              -2
#define REASON_ERROR            -1
#define REASON_CLOSED_BY_LOCAL  0
#define REASON_CLOSED_BY_REMOTE 1

/* return value of relay start function. */
#define START_ERROR -1
#define START_OK     0
#define START_RETRY  1

/* socket related definitions */
#ifndef _WIN32
#define SOCKET int
#endif
#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif

#ifdef _WIN32
#define socket_errno() WSAGetLastError()
#else /* !_WIN32 */
#define closesocket close
#define socket_errno() (errno)
#endif /* !_WIN32 */

#ifdef _WIN32
#define popen _popen
#endif /* WIN32 */

/* packet operation macro */
#define PUT_BYTE(ptr,data) (*(unsigned char*)ptr = data)

/* debug message output */
void
debug( const char *fmt, ... )
{
    va_list args;
    if ( f_debug ) {
        va_start( args, fmt );
        fprintf(stderr, "DEBUG: ");
        vfprintf( stderr, fmt, args );
        va_end( args );
    }
}

void
debug_( const char *fmt, ... )                  /* without prefix */
{
    va_list args;
    if ( f_debug ) {
        va_start( args, fmt );
        vfprintf( stderr, fmt, args );
        va_end( args );
    }
}

/* error message output */
void
error( const char *fmt, ... )
{
    va_list args;
    va_start( args, fmt );
    fprintf(stderr, "ERROR: ");
    vfprintf( stderr, fmt, args );
    va_end( args );
}

void
fatal( const char *fmt, ... )
{
    va_list args;
    va_start( args, fmt );
    fprintf(stderr, "FATAL: ");
    vfprintf( stderr, fmt, args );
    va_end( args );
    exit (EXIT_FAILURE);
}


void *
xmalloc (size_t size)
{
    void *ret = malloc(size);
    if (ret == NULL)
	fatal("Cannot allocate memory: %d bytes.\n", size);
    return ret;
}

char *
downcase( char *str )
{
    char *buf = str;
    while ( *buf ) {
        if ( isupper(*buf) )
            *buf += 'a'-'A';
        buf++;
    }
    return str;                                 /* return converted arg */
}

char *
expand_host_and_port (const char *fmt, const char *host, int port)
{
    const char *src;
    char *buf, *dst, *ptr;
    size_t len = strlen(fmt) + strlen(host) + 20;
    buf = xmalloc (len);
    dst = buf;
    src = fmt;
    
    while (*src) {
	if (*src == '%') {
	    switch (src[1]) {
	    case 'h':
		strcpy (dst, host);
		src += 2;
		break;
	    case 'p':
		snprintf (dst, len, "%d", port);
		src += 2;
		break;
	    default:
		src ++;
		break;
	    }
	    dst = buf + strlen (buf);
	} else if (*src == '\\') {
	    switch (src[1]) {
	    case 'r':				/* CR */
		*dst++ = '\r';
		src += 2;
		break;
	    case 'n':				/* LF */
		*dst++ = '\n';
		src += 2;
		break;
	    case 't':				/* TAB */
		*dst++ = '\t';
		src += 2;
		break;
	    default:
		src ++;
		break;
	    }
	} else {
	    /* usual */
	    *dst++ = *src++;
	}
	*dst = '\0';
    }
    assert (strlen(buf) < len);
    return buf;
}


int
lookup_resolve( const char *str )
{
    char *buf = strdup( str );
    int ret;

    downcase( buf );
    if ( strcmp( buf, "both" ) == 0 )
        ret = RESOLVE_BOTH;
    else if ( strcmp( buf, "remote" ) == 0 )
        ret = RESOLVE_REMOTE;
    else if ( strcmp( buf, "local" ) == 0 )
        ret = RESOLVE_LOCAL;
    else if ( strspn(buf, dotdigits) == strlen(buf) ) {
#ifndef WITH_RESOLVER
        fatal("Sorry, you can't specify to resolve the hostname with the -R option on Win32 environment.");
#endif /* not WITH_RESOLVER */
        ret = RESOLVE_LOCAL;                    /* this case is also 'local' */
        socks_ns.sin_addr.s_addr = inet_addr(buf);
        socks_ns.sin_family = AF_INET;
    }
    else
        ret = RESOLVE_UNKNOWN;
    free(buf);
    return ret;
}

char *
getusername(void)
{
#ifdef _WIN32
    static char buf[1024];
    DWORD size = sizeof(buf);
    buf[0] = '\0';
    GetUserName( buf, &size);
    return buf;
#else  /* not _WIN32 */
    struct passwd *pw = getpwuid(getuid());
    if ( pw == NULL )
        fatal("getpwuid() failed for uid: %d\n", getuid());
    return pw->pw_name;
#endif /* not _WIN32 */
}

/* expect
   check STR is begin with substr with case-ignored comparison.
   Return 1 if matched, otherwise 0.
*/
int
expect( char *str, char *substr)
{
    int len = strlen(substr);
    while ( 0 < len-- ) {
        if ( toupper(*str) != toupper(*substr) )
            return 0;                           /* not matched */
        str++, substr++;
    }
    return 1;                   /* good, matched */
}


/** PARAMETER operation **/
#define PARAMETER_FILE "/etc/connectrc"
#define PARAMETER_DOTFILE ".connectrc"
typedef struct {
    char* name;
    char* value;
} PARAMETER_ITEM;
PARAMETER_ITEM parameter_table[] = {
    { ENV_SOCKS_SERVER, NULL },
    { ENV_SOCKS5_SERVER, NULL },
    { ENV_SOCKS4_SERVER, NULL },
    { ENV_SOCKS_RESOLVE, NULL },
    { ENV_SOCKS5_RESOLVE, NULL },
    { ENV_SOCKS4_RESOLVE, NULL },
    { ENV_SOCKS5_USER, NULL },
    { ENV_SOCKS5_PASSWD, NULL },
    { ENV_SOCKS5_PASSWORD, NULL },
    { ENV_HTTP_PROXY, NULL },
    { ENV_HTTP_PROXY_USER, NULL },
    { ENV_HTTP_PROXY_PASSWORD, NULL },
    { ENV_CONNECT_USER, NULL },
    { ENV_CONNECT_PASSWORD, NULL },
    { ENV_SSH_ASKPASS, NULL },
    { ENV_SOCKS5_DIRECT, NULL },
    { ENV_SOCKS4_DIRECT, NULL },
    { ENV_SOCKS_DIRECT, NULL },
    { ENV_HTTP_DIRECT, NULL },
    { ENV_CONNECT_DIRECT, NULL },
    { ENV_SOCKS5_AUTH, NULL },
    { NULL, NULL }
};

PARAMETER_ITEM*
find_parameter_item(const char* name)
{
    int i;
    for( i = 0; parameter_table[i].name != NULL; i++ ){
        if ( strcmp(name, parameter_table[i].name) == 0 )
            return &parameter_table[i];
    }
    return NULL;
}

void
read_parameter_file_1(const char* name)
{
    FILE* f;
    int line;
    char lbuf[1025];
    f = fopen(name, "r");
    if( f ){
        debug("Reading parameter file(%s)\n", name);
        for ( line = 1; fgets(lbuf, 1024, f); line++ ) {
            char *p, *q, *param, *value;
            p = strchr(lbuf, '\n');
            if ( p == NULL )
                fatal("%s:%d: buffer overflow\n", name, line);
            *p = '\0';
            p = strchr(lbuf, '#');
            if ( p )
                *p = '\0';
            for ( p = lbuf; *p; p++ )
                if( *p != ' ' && *p != '\t' ) break;
            if ( *p == '\0' ) continue;
            param = p;
            p = strchr(p, '=');
            if ( p == NULL ) {
                error("%s:%d: missing equal sign\n", name, line);
                continue;
            }
            for ( q = p - 1; q >= lbuf; q-- )
                if ( *q != ' ' && *q != '\t' ) break;
            *++q = '\0';
            for ( ++p; *p; p++ )
                if ( *p != ' ' && *p != '\t' ) break;
            value = p;
            for ( ; *p; p++ );
            for ( p--; p >= lbuf; p-- )
                if ( *p != ' ' && *p != '\t' ) break;
            *++p = '\0';
            if ( param && value ) {
                PARAMETER_ITEM *item;
                item = find_parameter_item(param);
                if ( item == NULL ) {
                    error("%s:%d: unknown parameter `%s'\n", name, line, param);
                    continue;
                }
                item->value = strdup(value);
                debug("Parameter `%s' is set to `%s'\n", param, value);
            }
        }
    }
}

void
read_parameter_file(void)
{
#if !defined(_WIN32) || defined(cygwin)
    char *name;
    struct passwd *pw;
#endif

    read_parameter_file_1(PARAMETER_FILE);
#if !defined(_WIN32) || defined(cygwin)
    pw = getpwuid(getuid());
    if ( pw == NULL )
        fatal("getpwuid() failed for uid: %d\n", getuid());
    name = xmalloc(strlen(pw->pw_dir) + strlen(PARAMETER_DOTFILE) + 2);
    strcpy(name, pw->pw_dir);
    strcat(name, "/" PARAMETER_DOTFILE);
    read_parameter_file_1(name);
    free(name);
#endif /* _WIN32 */
}

char*
getparam(const char* name)
{
    char *value = getenv(name);
    if ( value == NULL ){
        PARAMETER_ITEM *item = find_parameter_item(name);
        if ( item != NULL )
            value = item->value;
    }
    return value;
}


/** DIRECT connection **/
#define MAX_DIRECT_ADDR_LIST 256

struct ADDRPAIR {
    struct in_addr addr;
    struct in_addr mask;
    char *name;
    int negative;
};

struct ADDRPAIR direct_addr_list[MAX_DIRECT_ADDR_LIST];
int n_direct_addr_list = 0;

void
mask_addr (void *addr, void *mask, int addrlen)
{
    char *a, *m;
    a = addr;
    m = mask;
    while ( 0 < addrlen-- )
        *a++ &= *m++;
}

int
add_direct_addr (struct in_addr *addr, struct in_addr *mask, int negative)
{
    struct in_addr iaddr;
    char *s;
    if ( MAX_DIRECT_ADDR_LIST <= n_direct_addr_list ) {
        error("direct address table is full!\n");
        return -1;
    }
    iaddr = *addr;
    mask_addr(&iaddr, mask, sizeof(iaddr));
    s = strdup(inet_ntoa(iaddr));
    debug("adding direct addr entry: %s%s/%s\n",
          negative? "!": "", s, inet_ntoa(*mask));
    free(s);
    memcpy( &direct_addr_list[n_direct_addr_list].addr,
            &iaddr, sizeof(iaddr));
    memcpy( &direct_addr_list[n_direct_addr_list].mask,
            mask, sizeof(*mask));
    direct_addr_list[n_direct_addr_list].name = NULL;
    direct_addr_list[n_direct_addr_list].negative = negative;
    n_direct_addr_list++;
    return 0;
}


/* add domain/host name entry to direct name table */
int
add_direct_host( const char *name, int negative)
{
    if ( MAX_DIRECT_ADDR_LIST <= n_direct_addr_list ) {
        error("direct address table is full!\n");
        return -1;
    }
    if (*name == '*')
        name++;
    if (*name == '.')
        name++;
    debug("adding direct name entry: %s%s\n", negative? "!": "", name);
    direct_addr_list[n_direct_addr_list].name = downcase(strdup(name));
    direct_addr_list[n_direct_addr_list].negative = negative;
    n_direct_addr_list++;
    return 0;
}


int
parse_addr_pair (const char *str, struct in_addr *addr, struct in_addr *mask)
{
    /* NOTE: */
    /* Assume already be splitted by separator
       and formatted as folowing:
       1)  12.34.56.789/255.255.255.0
       2)  12.34.56.789/24
       3)  12.34.56.
       All above generates same addr/mask pair 12.34.56.0 and 255.255.255.0
    */
    const char *ptr;
    u_char *dsta, *dstm;
    int i, n;

    assert( str != NULL );
    addr->s_addr = 0;
    mask->s_addr = 0;
    ptr = str;
    dsta = (u_char*)&addr->s_addr;
    dstm = (u_char*)&mask->s_addr;
    for (i=0; i<4; i++ ) {
        if ( *ptr == '\0' )
            break;              /* case of format #3 */
        if ( !isdigit(*ptr) )
            return -1;          /* format error: */
        *dsta++ = atoi( ptr );
        *dstm++ = 255;          /* automatic mask for format #3 */
        while ( isdigit(*ptr) ) /* skip digits */
            ptr++;
        if ( *ptr == '.' )
            ptr++;
        else
            break;
    }
    /* At this point, *ptr points '/' or EOS ('\0') */
    if ( *ptr == '\0' )
        return 0;                       /* complete as format #3 */
    if ( *ptr != '/' )
        return -1;                      /* format error */
    /* Now parse mask for format #1 or #2 */
    ptr++;
    mask->s_addr = 0;                   /* clear automatic mask */

    if ( strchr( ptr, '.') ) {
        /* case of format #1 */
        dstm = (u_char*)&mask->s_addr;
        for (i=0; i<4; i++) {
            if ( !isdigit(*ptr) )
                return -1;              /* format error: */
            *dstm++ = atoi(ptr);
            while ( isdigit(*ptr) )     /* skip digits */
                ptr++;
            if ( *ptr == '.' )
                ptr++;
            else
                break;                  /* from for loop */
        }
        /* complete as format #1 */
    } else {
        /* case of format #2 */
        if ( !isdigit(*ptr) )
            return -1;                  /* format error: */
        n = atoi(ptr);
        if ( n<0 || 32<n)
            return -1;                  /* format error */
        mask->s_addr = (n==0)? 0: htonl(((u_long)0xFFFFFFFF)<<(32-n));
        /* complete as format #1 */
    }
    return 0;
}

void
initialize_direct_addr (void)
{
    int negative;
    int n_entries;
    char *env = NULL, *beg, *next, *envkey = NULL;
    struct in_addr addr, mask;

    if ( relay_method == METHOD_SOCKS ){
        if ( socks_version == 5 )
            envkey = ENV_SOCKS5_DIRECT;
        else
            envkey = ENV_SOCKS4_DIRECT;
        env = getparam(envkey);
        if ( env == NULL )
            env = getparam(ENV_SOCKS_DIRECT);
    } else if ( relay_method == METHOD_HTTP ){
        env = getparam(ENV_HTTP_DIRECT);
    }

    if ( env == NULL )
        env = getparam(ENV_CONNECT_DIRECT);

    if ( env == NULL )
        return;                 /* no entry */
    debug("making direct addr list from: '%s'\n", env);
    env = strdup( env );        /* reallocate to modify */
    beg = next = env;
    n_entries = 0;
    do {
        if ( MAX_DIRECT_ADDR_LIST <= n_entries ) {
            error("too many entries in %s", envkey);
            break;              /* from do loop */
        }
        next = strchr( beg, ',');
        if ( next != NULL )
            *next++ = '\0';
        addr.s_addr = 0;
        mask.s_addr = 0;
        if (*beg == '!') {
            negative = 1;
            beg++;
        } else
            negative = 0;
        if ( !parse_addr_pair( beg, &addr, &mask ) ) {
            add_direct_addr( &addr, &mask, negative );
        } else {
            add_direct_host( beg, negative );
        }
        if ( next != NULL )
            beg = next;
    } while ( next != NULL );

    free( env );
    return;
}

int
cmp_addr (void *addr1, void *addr2, int addrlen)
{
    return memcmp( addr1, addr2, addrlen );
}

int
is_direct_address (const struct in_addr addr)
{
    int i, neg;
    struct in_addr iaddr;

    /* Note: assume IPV4 address !! */
    for (i=0; i<n_direct_addr_list; i++ ) {
        if (direct_addr_list[i].name != NULL)
            continue;                           /* it's name entry */
        neg = direct_addr_list[i].negative;
        iaddr = addr;
        mask_addr( &iaddr, &direct_addr_list[i].mask,
                   sizeof(struct in_addr));
        if (cmp_addr(&iaddr, &direct_addr_list[i].addr,
                     sizeof(struct in_addr)) == 0) {
            char *a, *m;
            a = strdup(inet_ntoa(direct_addr_list[i].addr));
            m = strdup(inet_ntoa(direct_addr_list[i].mask));
            debug("match with: %s/%s%s\n", a, m, neg? " (negative)": "");
            free(a);
            free(m);
            return !neg? 1: 0;
        }
    }
    debug("not matched, addr to be relayed: %s\n", inet_ntoa(addr));
    return 0;                   /* not direct */
}


/* check s1 is ends with s2.
   return 1 if exact match or domain part match.
   return 0 if s1 is shorter than s2 or partial match.
   For example, 
    ends_with("bar.com", "bar.com")        => 1 (exact match)
    ends_with("foo.bar.com", "bar.com")    => 1 (domain match)
    ends_with("foo.beebar.com", "bar.com") => 0 (partial match)
    ends_with("bar", "bar.com")            => 0 (shorter)
 */
domain_match(const char *s1, const char *s2)
{
    int len1, len2;
    const char *tail1, *tail2;
    len1 = strlen(s1);
    len2 = strlen(s2);
    if (len1 < len2 || len1 == 0 || len2 == 0)
        return 0;                               /* not match */
    tail1 = s1 + len1;
    tail2 = s2 + len2;
    while (0 < len1 && 0 < len2) {
        if (*--tail1 != *--tail2)
            break;                              /* not match */
        len1--, len2--;
    }
    if (len2 != 0)
        return 0;                               /* not match */
    /* Now exact match, domain match or partial match.
       Return true if exact or domain match.
       Or continue checking. */
    if (tail1 == s1 || tail1[-1] == '.')
        return 1;                               /* match! */
    return 0;                                   /* not match */
}

/* Check given NAME is ends with one of 
   registered direct name entry.
   Return 1 if matched, or 0.
*/
int
is_direct_name (const char *name)
{
    int len, i;
    const char *tail;
    debug("checking %s is for direct?\n", name);
    name = downcase(strdup(name));
    len = strlen(name);
    if (len < 1)
        return 0;                               /* false */
    tail = &name[len];
    for (i=0; i<n_direct_addr_list; i++ ) {
        int dlen, neg;
        const char *dname;
        const char *n, *d;
        dname = direct_addr_list[i].name;
        if (dname == NULL)
            continue;                           /* it's addr/mask entry */
        neg = direct_addr_list[i].negative;
        if (domain_match(name, dname)) {
            debug("match with: %s%s\n", dname, neg? " (negative)": "");
            if (neg) {
                return 0;       /* not direct */
            } else {
                return 1;       /* direct*/
            }
        }
    }
    return 0;                                   /* not matched */
}

/* check to connect to HOST directyly?
   return 1 if to be direct, 0 for else. */
int
check_direct(const char *host)
{
    struct in_addr addr;
    addr.s_addr = inet_addr(host);
    if (addr.s_addr != INADDR_NONE) {
        /* case of IP address */
        if (is_direct_address(addr)) {
            debug("%s is for direct.\n", host);
            return 1;                           /* true */
        }
    } else {
        /* case of hostname */
        if (is_direct_name(host)) {
            debug("%s is for direct.\n", host);
            return 1;                           /* true */
        }
    }
    debug("%s is for not direct.\n", host);
    return 0;                                    /* false */
}


/** TTY operation **/

int intr_flag = 0;

#ifndef _WIN32
void
intr_handler(int sig)
{
    intr_flag = 1;
}

void
tty_change_echo(int fd, int enable)
{
    static struct termios ntio, otio;           /* new/old termios */
    static sigset_t nset, oset;                 /* new/old sigset */
    static struct sigaction nsa, osa;           /* new/old sigaction */
    static int disabled = 0;

    if ( disabled && enable ) {
        /* enable echo */
        tcsetattr(fd, TCSANOW, &otio);
        disabled = 0;
        /* resotore sigaction */
        sigprocmask(SIG_SETMASK, &oset, NULL);
        sigaction(SIGINT, &osa, NULL);
        if ( intr_flag != 0 ) {
            /* re-generate signal  */
            kill(getpid(), SIGINT);
            sigemptyset(&nset);
            sigsuspend(&nset);
            intr_flag = 0;
        }
    } else if (!disabled && !enable) {
        /* set SIGINTR handler and break syscall on singal */
        sigemptyset(&nset);
        sigaddset(&nset, SIGTSTP);
        sigprocmask(SIG_BLOCK, &nset, &oset);
        intr_flag = 0;
        memset(&nsa, 0, sizeof(nsa));
        nsa.sa_handler = intr_handler;
        sigaction(SIGINT, &nsa, &osa);
        /* disable echo */
        if (tcgetattr(fd, &otio) == 0 && (otio.c_lflag & ECHO)) {
            disabled = 1;
            ntio = otio;
            ntio.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);
            (void) tcsetattr(fd, TCSANOW, &ntio);
        }
    }

    return;
}

#define TTY_NAME "/dev/tty"
int
tty_readpass( const char *prompt, char *buf, size_t size )
{
    int tty, ret = 0;

    tty = open(TTY_NAME, O_RDWR);
    if ( tty < 0 ) {
        error("Unable to open %s\n", TTY_NAME);
        return -1;                              /* can't open tty */
    }
    if ( size <= 0 )
        return -1;                              /* no room */
    write(tty, prompt, strlen(prompt));
    buf[0] = '\0';
    tty_change_echo(tty, 0);                    /* disable echo */
    ret = read(tty,buf, size-1);
    tty_change_echo(tty, 1);                    /* restore */
    write(tty, "\n", 1);                        /* new line */
    close(tty);
    if ( strchr(buf,'\n') == NULL  )
        return -1;
    if ( 0 < ret )
        buf[ret] = '\0';
    return ret;
}

#else  /* _WIN32 */

BOOL __stdcall
w32_intr_handler(DWORD dwCtrlType)
{
    if ( dwCtrlType == CTRL_C_EVENT ) {
        intr_flag = 1;
        return TRUE;
    } else {
        return FALSE;
    }
}

#define tty_readpass w32_tty_readpass
int
w32_tty_readpass( const char *prompt, char *buf, size_t size )
{
    HANDLE in = CreateFile("CONIN$", GENERIC_READ|GENERIC_WRITE,
                           0, NULL, OPEN_EXISTING, 0, NULL);
    HANDLE out = CreateFile("CONOUT$", GENERIC_WRITE,
                            0, NULL, OPEN_EXISTING, 0, NULL);
    DWORD mode;
    DWORD ret, bytes;

    if (in == INVALID_HANDLE_VALUE || out == INVALID_HANDLE_VALUE)
        fatal("Cannot open console. (errno=%d)", GetLastError());

    WriteFile(out, prompt, strlen(prompt), &bytes, 0);
    SetConsoleCtrlHandler(w32_intr_handler, TRUE ); /* add handler */
    GetConsoleMode(in, &mode);
    SetConsoleMode(in, mode&~ENABLE_ECHO_INPUT); /* disable echo */
    ret = ReadFile(in, buf, size, &bytes, 0);
    SetConsoleMode(in, mode);                   /* enable echo */
    SetConsoleCtrlHandler( w32_intr_handler, FALSE ); /* remove handler */
    if ( intr_flag )
        GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0); /* re-signal */
    WriteFile(out,"\n", 1, &bytes, 0);
    CloseHandle(in);
    CloseHandle(out);
    return ret;
}

#endif /* _WIN32 */

/*** User / Password ***/

/* SOCKS5 and HTTP Proxy authentication may requires username and
   password. We ll give it via environment variable or tty.
   Username and password for authentication are decided by
   following rules:

   Username is taken from
     1) server location spec (i.e. user@host:port)
     2) environment variables (see tables.1)
     3) system account name currently logged in.

     Table.1 Order of environment variables for username

        |  SOCKS v5   |  SOCKS v4   |   HTTP proxy    |
      --+-------------+-------------+-----------------+
      1 | SOCKS45_USER | SOCKS4_USER | HTTP_PROXY_USER |
      --+-------------+-------------+                 |
      2 |        SOCKS_USER         |                 |
      --+---------------------------+-----------------+
      3 |              CONNECT_USER                   |
      --+---------------------------------------------+

   Password is taken from
     1) by environment variables (see table.2)
     2) by entering from tty.

     Table.2 Order of environment variables for password

        |    SOCKS v5     |     HTTP proxy      |
      --+-----------------+---------------------+
      1 | SOCKS5_PASSWD   |                     |
      --+-----------------+ HTTP_PROXY_PASSWORD |
      2 | SOCKS5_PASSWORD |                     |
      --+-----------------+---------------------+
      3 |           CONNECT_PASSWORD            |
      --+---------------------------------------+

      Note: SOCKS5_PASSWD which is added in rev. 1.79
            to share value with NEC SOCKS implementation.
 */

char *
determine_relay_user ()
{
    char *user = NULL;
    /* get username from environment variable, or system. */
    if (relay_method == METHOD_SOCKS) {
        if (user == NULL && socks_version == 5)
            user = getparam (ENV_SOCKS5_USER);
        if (user == NULL && socks_version == 4)
            user = getparam (ENV_SOCKS4_USER);
        if (user == NULL)
            user = getparam (ENV_SOCKS_USER);
    } else if (relay_method == METHOD_HTTP) {
        if (user == NULL)
            user = getparam (ENV_HTTP_PROXY_USER);
    }
    if (user == NULL)
        user = getparam (ENV_CONNECT_USER);
    /* determine relay user by system call if not yet. */
    if (user == NULL)
        user = getusername();
    return user;
}

char *
determine_relay_password ()
{
    char *pass = NULL;
    if (pass == NULL && relay_method == METHOD_HTTP)
        pass = getparam(ENV_HTTP_PROXY_PASSWORD);
    if (pass == NULL && relay_method == METHOD_SOCKS)
        pass = getparam(ENV_SOCKS5_PASSWD);
    if (pass == NULL && relay_method == METHOD_SOCKS)
        pass = getparam(ENV_SOCKS5_PASSWORD);
    if (pass == NULL)
        pass = getparam(ENV_CONNECT_PASSWORD);
    return pass;
}


/*** network operations ***/


/* set_relay()
   Determine relay informations:
   method, host, port, and username.
   1st arg, METHOD should be METHOD_xxx.
   2nd arg, SPEC is hostname or hostname:port or user@hostame:port.
   hostname is domain name or dot notation.
   If port is omitted, use 80 for METHOD_HTTP method,
   use 1080 for METHOD_SOCKS method.
   Username is also able to given by 3rd. format.
   2nd argument SPEC can be NULL. if NULL, use environment variable.
 */
int
set_relay( int method, char *spec )
{
    char *buf, *sep, *resolve;

    relay_method = method;

    read_parameter_file();
    initialize_direct_addr();
    if (n_direct_addr_list == 0) {
        debug ("No direct address are specified.\n");
    } else {
        debug ("%d direct address entries.\n", n_direct_addr_list);
    }

    switch ( method ) {
    case METHOD_DIRECT:
        return -1;                              /* nothing to do */

    case METHOD_SOCKS:
        if ( spec == NULL ) {
            switch ( socks_version ) {
            case 5:
                spec = getparam(ENV_SOCKS5_SERVER);
                break;
            case 4:
                spec = getparam(ENV_SOCKS4_SERVER);
                break;
            }
        }
        if ( spec == NULL )
            spec = getparam(ENV_SOCKS_SERVER);

        if ( spec == NULL )
            fatal("Failed to determine SOCKS server.\n");
        relay_port = 1080;                      /* set default first */

        /* determine resolve method */
        if ( socks_resolve == RESOLVE_UNKNOWN ) {
            if ( ((socks_version == 5) &&
                  ((resolve = getparam(ENV_SOCKS5_RESOLVE)) != NULL)) ||
                 ((socks_version == 4) &&
                  ((resolve = getparam(ENV_SOCKS4_RESOLVE)) != NULL)) ||
                 ((resolve = getparam(ENV_SOCKS_RESOLVE)) != NULL) ) {
                socks_resolve = lookup_resolve( resolve );
                if ( socks_resolve == RESOLVE_UNKNOWN )
                    fatal("Invalid resolve method: %s\n", resolve);
            } else {
                /* default */
                if ( socks_version == 5 )
                    socks_resolve = RESOLVE_REMOTE;
                else
                    socks_resolve = RESOLVE_LOCAL;
            }
        }
        break;

    case METHOD_HTTP:
        if ( spec == NULL )
            spec = getparam(ENV_HTTP_PROXY);
        if ( spec == NULL )
            fatal("You must specify http proxy server\n");
        relay_port = 80;                        /* set default first */
        break;
    case METHOD_TELNET:
        if ( spec == NULL )
            spec = getparam(ENV_TELNET_PROXY);
        if ( spec == NULL )
            fatal("You must specify telnet proxy server\n");
        relay_port = 23;                        /* set default first */
    }

    if (expect( spec, HTTP_PROXY_PREFIX)) {
        /* URL format like: "http://server:port/" */
        /* extract server:port part */
        buf = strdup( spec + strlen(HTTP_PROXY_PREFIX));
        buf[strcspn(buf, "/")] = '\0';
    } else {
        /* assume spec is aready "server:port" format */
        buf = strdup( spec );
    }
    spec = buf;

    /* check username in spec */
    sep = strchr( spec, '@' );
    if ( sep != NULL ) {
        *sep = '\0';
        relay_user = strdup( spec );
        spec = sep +1;
    }
    if (relay_user == NULL)
        relay_user = determine_relay_user();

    /* split out hostname and port number from spec */
    sep = strchr(spec,':');
    if ( sep == NULL ) {
        /* hostname only, port is already set as default */
        relay_host = strdup( spec );
    } else {
        /* hostname and port */
        relay_port = atoi(sep+1);
        *sep = '\0';
        relay_host = strdup( spec );
    }
    free(buf);
    return 0;
}


u_short
resolve_port( const char *service )
{
    int port;
    if ( service[strspn (service, digits)] == '\0'  ) {
        /* all digits, port number */
        port = atoi(service);
    } else {
        /* treat as service name */
        struct servent *ent;
        ent = getservbyname( service, NULL );
        if ( ent == NULL ) {
            debug("Unknown service, '%s'\n", service);
            port = 0;
        } else {
            port = ntohs(ent->s_port);
            debug("service: %s => %d\n", service, port);
        }
    }
    return (u_short)port;
}

void
make_revstr(void)
{
    char *ptr;
    size_t len;
    ptr = strstr(rcs_revstr, ": ");
    if (!ptr) {
        revstr = strdup("unknown");
        return;
    }
    ptr += 2;
    /* assume subversion's keyword expansion like "Revision: 96". */
    minor_version = atoi(ptr);
    revstr = xmalloc(20);
    snprintf(revstr, 20, "%d.%d", major_version, minor_version);
}

int
getarg( int argc, char **argv )
{
    int err = 0;
    char *ptr, *server = (char*)NULL;
    int method = METHOD_DIRECT;

    progname = *argv;
    argc--, argv++;

    /* check optinos */
    while ( (0 < argc) && (**argv == '-') ) {
        ptr = *argv + 1;
        while ( *ptr ) {
            switch ( *ptr ) {
            case 's':                           /* use SOCKS */
                method = METHOD_SOCKS;
                break;

            case 'n':                           /* no proxy */
                method = METHOD_DIRECT;
                break;

            case 'h':                           /* use http-proxy */
                method = METHOD_HTTP;
                break;
            case 't':
                method = METHOD_TELNET;
                break;

            case 'S':                           /* specify SOCKS server */
                if ( 1 < argc ) {
                    argv++, argc--;
                    method = METHOD_SOCKS;
                    server = *argv;
                } else {
                    error("option '-%c' needs argument.\n", *ptr);
                    err++;
                }
                break;

            case 'H':                           /* specify http-proxy server */
                if ( 1 < argc ) {
                    argv++, argc--;
                    method = METHOD_HTTP;
                    server = *argv;
                } else {
                    error("option '-%c' needs argument.\n", *ptr);
                    err++;
                }
                break;
            case 'T':                           /* specify telnet proxy server */
                if ( 1 < argc ) {
                    argv++, argc--;
                    method = METHOD_TELNET;
                    server = *argv;
                } else {
                    error("option '-%c' needs argument.\n", *ptr);
                    err++;
                }
                break;

            case 'c':
                 if (1 < argc) {
                      argv++, argc--;
                      telnet_command = *argv;
                 } else {
                      error("option '%c' needs argument.\n", *ptr);
                      err++;
                 }
                 break;

            case 'P':
                f_hold_session = 1;
                /* without break */
            case 'p':                          /* specify port to forward */
                if ( 1 < argc ) {
                    argv++, argc--;
                    local_type = LOCAL_SOCKET;
                    local_port = resolve_port(*argv);
                } else {
                    error("option '-%c' needs argument.\n", *ptr);
                    err++;
                }
                break;

#ifndef _WIN32
            case 'w':
                if ( 1 < argc ) {
                    argv++, argc--;
                    connect_timeout = atoi(*argv);
                } else {
                    error("option '-%c' needs argument.\n", *ptr);
                    err++;
                }
                break;
#endif /* not _WIN32 */

            case '4':
                socks_version = 4;
                break;

            case '5':
                socks_version = 5;
                break;

            case 'a':
                if ( 1 < argc ) {
                    argv++, argc--;
                    socks5_auth = *argv;
                } else {
                    error("option '-%c' needs argument.\n", *ptr);
                    err++;
                }
                break;

            case 'R':                           /* specify resolve method */
                if ( 1 < argc ) {
                    argv++, argc--;
                    socks_resolve = lookup_resolve( *argv );
                } else {
                    error("option '-%c' needs argument.\n", *ptr);
                    err++;
                }
                break;

            case 'V':                           /* print version */
                fprintf(stderr, "%s\nVersion %s\n", progdesc, revstr);
                exit(0);

            case 'd':                           /* debug mode */
                f_debug++;
                break;

            default:
                error("unknown option '-%c'\n", *ptr);
                err++;
            }
            ptr++;
        }
        argc--, argv++;
    }

    /* check error */
    if ( 0 < err )
        goto quit;

    set_relay( method, server );

    /* check destination HOST (MUST) */
    if ( argc == 0  ) {
        fprintf(stderr, "%s\nVersion %s\n", progdesc, revstr);
        fprintf(stderr, usage, progname);
        exit(0);
    }
    dest_host = argv[0];
    /* decide port or service name from programname or argument */
    if ( ((ptr=strrchr( progname, '/' )) != NULL) ||
         ((ptr=strchr( progname, '\\')) != NULL) )
        ptr++;
    else
        ptr = progname;
    if ( dest_port == 0 ) {
        /* accept only if -P is not specified. */
        if ( 1 < argc ) {
            /* get port number from argument (prior to progname) */
            /* NOTE: This way is for cvs ext method. */
            dest_port = resolve_port(argv[1]);
        } else if ( strncmp( ptr, "connect-", 8) == 0 ) {
            /* decide port number from program name */
            char *str = strdup( ptr+8 );
            str[strcspn( str, "." )] = '\0';
            dest_port = resolve_port(str);
            free(str);
        }
    }
    /* check port number */
    if ( dest_port <= 0 ) {
        error( "You must specify the destination port correctly.\n");
        err++;
        goto quit;
    }
    if ( (relay_method != METHOD_DIRECT) && (relay_port <= 0) ) {
        error("Invalid relay port: %d\n", dest_port);
        err++;
        goto quit;
    }

quit:
    /* report for debugging */
    debug("relay_method = %s (%d)\n",
          method_names[relay_method], relay_method);
    if ( relay_method != METHOD_DIRECT ) {
        debug("relay_host=%s\n", relay_host);
        debug("relay_port=%d\n", relay_port);
        debug("relay_user=%s\n", relay_user);
    }
    if ( relay_method == METHOD_SOCKS ) {
        debug("socks_version=%d\n", socks_version);
        debug("socks_resolve=%s (%d)\n",
              resolve_names[socks_resolve], socks_resolve);
    }
    debug("local_type=%s\n", local_type_names[local_type]);
    if ( local_type == LOCAL_SOCKET ) {
        debug("local_port=%d\n", local_port);
        if (f_hold_session)
            debug ("  with holding remote session.\n");
    }
    debug("dest_host=%s\n", dest_host);
    debug("dest_port=%d\n", dest_port);
    if ( 0 < err ) {
        fprintf(stderr, usage, progname);
        exit(1);
    }
    return 0;
}

#ifndef _WIN32
/* Time-out feature is not allowed for Win32 native compilers. */
/* MSVC and Borland C cannot but Cygwin and UNIXes can. */

/* timeout signal hander */
void
sig_timeout(void)
{
    signal( SIGALRM, SIG_IGN );
    alarm( 0 );
    error( "timed out\n" );
    exit(1);
}

/* set timeout param = seconds, 0 clears */
void
set_timeout(int timeout)
{
    /* This feature is allowed for UNIX or cygwin environments, currently */
    if ( timeout == 0 ) {
        debug( "clearing timeout\n" );
        signal( SIGALRM, SIG_IGN );
        alarm( 0 );
    } else {
        debug( "setting timeout: %d seconds\n", timeout );
        signal(SIGALRM, (void *)sig_timeout);
        alarm( timeout );
    }
}
#endif

#if !defined(_WIN32) && !defined(__CYGWIN32__)
void
switch_ns (struct sockaddr_in *ns)
{
    res_init();
    memcpy (&_res.nsaddr_list[0], ns, sizeof(*ns));
    _res.nscount = 1;
    debug("Using nameserver at %s\n", inet_ntoa(ns->sin_addr));
}
#endif /* !_WIN32 && !__CYGWIN32__ */

/* TODO: IPv6
   TODO: fallback if askpass execution failed.
 */

int
local_resolve (const char *host, struct sockaddr_in *addr)
{
    struct hostent *ent;
    if ( strspn(host, dotdigits) == strlen(host) ) {
        /* given by IPv4 address */
        addr->sin_family = AF_INET;
        addr->sin_addr.s_addr = inet_addr(host);
    } else {
        debug("resolving host by name: %s\n", host);
        ent = gethostbyname (host);
        if ( ent ) {
            memcpy (&addr->sin_addr, ent->h_addr, ent->h_length);
            addr->sin_family = ent->h_addrtype;
            debug("resolved: %s (%s)\n",
                  host, inet_ntoa(addr->sin_addr));
        } else {
            debug("failed to resolve locally.\n");
            return -1;                          /* failed */
        }
    }
    return 0;                                   /* good */
}

int
open_connection( const char *host, u_short port )
{
    SOCKET s;
    struct sockaddr_in saddr;

    /* resolve address of proxy or direct target */
    if (local_resolve (host, &saddr) < 0) {
        error("can't resolve hostname: %s\n", host);
        return SOCKET_ERROR;
    }
    saddr.sin_port = htons(port);

    debug("connecting to %s:%u\n", inet_ntoa(saddr.sin_addr), port);
    s = socket( AF_INET, SOCK_STREAM, 0 );
    if ( connect( s, (struct sockaddr *)&saddr, sizeof(saddr))
         == SOCKET_ERROR) {
        debug( "connect() failed.\n");
        return SOCKET_ERROR;
    }
    return s;
}

void
report_text( char *prefix, char *buf )
{
    static char work[1024];
    char *tmp;

    if ( !f_debug )
        return;
    if ( !f_report )
        return;                                 /* don't report */
    debug("%s \"", prefix);
    while ( *buf ) {
        memset( work, 0, sizeof(work));
        tmp = work;
        while ( *buf && ((tmp-work) < (int)sizeof(work)-5) ) {
            switch ( *buf ) {
            case '\t': *tmp++ = '\\'; *tmp++ = 't'; break;
            case '\r': *tmp++ = '\\'; *tmp++ = 'r'; break;
            case '\n': *tmp++ = '\\'; *tmp++ = 'n'; break;
            case '\\': *tmp++ = '\\'; *tmp++ = '\\'; break;
            default:
                if ( isprint(*buf) ) {
                    *tmp++ = *buf;
                } else {
		    int consumed = tmp - work;
                    snprintf( tmp, sizeof(work)-consumed,
			      "\\x%02X", (unsigned char)*buf);
                    tmp += strlen(tmp);
                }
            }
            buf++;
            *tmp = '\0';
        }
        debug_("%s", work);
    }

    debug_("\"\n");
}


void
report_bytes( char *prefix, char *buf, int len )
{
    if ( ! f_debug )
        return;
    debug( "%s", prefix );
    while ( 0 < len ) {
        fprintf( stderr, " %02x", *(unsigned char *)buf);
        buf++;
        len--;
    }
    fprintf(stderr, "\n");
    return;
}

int
atomic_out( SOCKET s, char *buf, int size )
{
    int ret, len;

    assert( buf != NULL );
    assert( 0<=size );
    /* do atomic out */
    ret = 0;
    while ( 0 < size ) {
        len = send( s, buf+ret, size, 0 );
        if ( len == -1 )
            fatal("atomic_out() failed to send(), %d\n", socket_errno());
        ret += len;
        size -= len;
    }
    if (!f_report) {
        debug("atomic_out()  [some bytes]\n");
        debug(">>> xx xx xx xx ...\n");
    } else {
        debug("atomic_out()  [%d bytes]\n", ret);
        report_bytes(">>>", buf, ret);
    }
    return ret;
}

int
atomic_in( SOCKET s, char *buf, int size )
{
    int ret, len;

    assert( buf != NULL );
    assert( 0<=size );

    /* do atomic in */
    ret = 0;
    while ( 0 < size ) {
        len = recv( s, buf+ret, size, 0 );
        if ( len == -1 ) {
            fatal("atomic_in() failed to recv(), %d\n", socket_errno());
        } else if ( len == 0 ) {
            fatal( "Connection closed by peer.\n");
        }
        ret += len;
        size -= len;
    }
    if (!f_report) {
        debug("atomic_in()  [some bytes]\n");
        debug("<<< xx xx xx xx ...\n");
    } else {
        debug("atomic_in() [%d bytes]\n", ret);
        report_bytes("<<<", buf, ret);
    }
    return ret;
}

int
line_input( SOCKET s, char *buf, int size )
{
    char *dst = buf;
    if ( size == 0 )
        return 0;                               /* no error */
    size--;
    while ( 0 < size ) {
        switch ( recv( s, dst, 1, 0) ) {        /* recv one-by-one */
        case SOCKET_ERROR:
            error("recv() error\n");
            return -1;                          /* error */
        case 0:
            size = 0;                           /* end of stream */
            break;
        default:
            /* continue reading until last 1 char is EOL? */
            if ( *dst == '\n' ) {
                /* finished */
                size = 0;
            } else {
                /* more... */
                size--;
            }
            dst++;
        }
    }
    *dst = '\0';
    report_text( "<<<", buf);
    return 0;
}

/* cut_token()
   Span token in given string STR until char in DELIM is appeared.
   Then replace contiguous DELIMS with '\0' for string termination
   and returns next pointer.
   If no next token, return NULL.
*/
char *
cut_token( char *str, char *delim)
{
    char *ptr = str + strcspn(str, delim);
    char *end = ptr + strspn(ptr, delim);
    if ( ptr == str )
        return NULL;
    while ( ptr < end )
        *ptr++ = '\0';
    return ptr;
}

const char *
lookup(int num, LOOKUP_ITEM *items)
{
    int i = 0;
    while (0 <= items[i].num) {
        if (items[i].num == num)
            return items[i].str;
        i++;
    }
    return "(unknown)";
}

/* readpass()
   password input routine
   Use ssh-askpass (same mechanism to OpenSSH)
*/
char *
readpass( const char* prompt, ...)
{
    static char buf[1000];                      /* XXX, don't be fix length */
    va_list args;
    va_start(args, prompt);
    vsnprintf(buf, sizeof(buf), prompt, args);
    va_end(args);

    if ( getparam(ENV_SSH_ASKPASS)
#if !defined(_WIN32) && !defined(__CYGWIN32__)
         && getenv("DISPLAY")
#endif /* not _WIN32 && not __CYGWIN32__ */
        ) {
        /* use ssh-askpass to get password */
        FILE *fp;
        char *askpass = getparam(ENV_SSH_ASKPASS), *cmd;
	int cmd_size = strlen(askpass) +1 +1 +strlen(buf) +1 +1;
        cmd = xmalloc(cmd_size);
        snprintf(cmd, cmd_size, "%s \"%s\"", askpass, buf);
        fp = popen(cmd, "r");
        free(cmd);
        if ( fp == NULL )
            return NULL;                        /* fail */
        buf[0] = '\0';
        if (fgets(buf, sizeof(buf), fp) == NULL)
            return NULL;                        /* fail */
        fclose(fp);
    } else {
        tty_readpass( buf, buf, sizeof(buf));
    }
    buf[strcspn(buf, "\r\n")] = '\0';
    return buf;
}

static int
socks5_do_auth_userpass( int s )
{
    unsigned char buf[1024], *ptr;
    char *pass = NULL;
    int len;

    /* do User/Password authentication. */
    /* This feature requires username and password from
       command line argument or environment variable,
       or terminal. */
    if (relay_user == NULL)
        fatal("cannot determine user name.\n");

    /* get password from environment variable if exists. */
    if ((pass=determine_relay_password()) == NULL &&
        (pass=readpass("Enter SOCKS5 password for %s@%s: ",
                       relay_user, relay_host)) == NULL)
        fatal("Cannot get password for user: %s\n", relay_user);

    /* make authentication packet */
    ptr = buf;
    PUT_BYTE( ptr++, 1 );                       /* subnegotiation ver.: 1 */
    len = strlen( relay_user );                 /* ULEN and UNAME */
    PUT_BYTE( ptr++, len );
    strcpy( ptr, relay_user );
    ptr += len;
    len = strlen( pass );                       /* PLEN and PASSWD */
    PUT_BYTE( ptr++, strlen(pass));
    strcpy( ptr, pass );
    ptr += len;
    memset (pass, 0, strlen(pass));             /* erase password */

    /* send it and get answer */
    f_report = 0;
    atomic_out( s, buf, ptr-buf );
    f_report = 1;
    atomic_in( s, buf, 2 );

    /* check status */
    if ( buf[1] == 0 )
        return 0;                               /* success */
    else
        return -1;                              /* fail */
}

static const char *
socks5_getauthname( int auth )
{
    switch ( auth ) {
    case SOCKS5_AUTH_REJECT: return "REJECTED";
    case SOCKS5_AUTH_NOAUTH: return "NO-AUTH";
    case SOCKS5_AUTH_GSSAPI: return "GSSAPI";
    case SOCKS5_AUTH_USERPASS: return "USERPASS";
    case SOCKS5_AUTH_CHAP: return "CHAP";
    case SOCKS5_AUTH_EAP: return "EAP";
    case SOCKS5_AUTH_MAF: return "MAF";
    default: return "(unknown)";
    }
}

typedef struct {
    char* name;
    unsigned char auth;
} AUTH_METHOD_ITEM;

AUTH_METHOD_ITEM socks5_auth_table[] = {
    { "none", SOCKS5_AUTH_NOAUTH },
    { "gssapi", SOCKS5_AUTH_GSSAPI },
    { "userpass", SOCKS5_AUTH_USERPASS },
    { "chap", SOCKS5_AUTH_CHAP },
    { NULL, -1 },
};

int
socks5_auth_parse_1(char *start, char *end){
    int i, len;
    for ( ; *start; start++ )
        if ( *start != ' ' && *start != '\t') break;
    for ( end--; end >= start; end-- ) {
        if ( *end != ' ' && *end != '\t'){
            end++;
            break;
        }
    }
    len = end - start;
    for ( i = 0; socks5_auth_table[i].name != NULL; i++ ){
        if ( strncmp(start, socks5_auth_table[i].name, len) == 0) {
            return socks5_auth_table[i].auth;
        }
    }
    fatal("Unknown auth method: %s\n", start);
    return -1;
}

int
socks5_auth_parse(char *start, unsigned char *auth_list, int max_auth){
    char *end;
    int i = 0;
    while ( i < max_auth ) {
        end = strchr(start, ',');
        if (*start && end) {
            auth_list[i++] = socks5_auth_parse_1(start, end);
            start = ++end;
        } else {
            break;
        }
    }
    if ( *start && ( i < max_auth ) ){
        for( end = start; *end; end++ );
        auth_list[i++] = socks5_auth_parse_1(start, end);
    } else {
        fatal("Too much auth method.\n");
    }
    return i;
}

/* begin SOCKS5 relaying
   And no authentication is supported.
 */
int
begin_socks5_relay( SOCKET s )
{
    unsigned char buf[256], *ptr, *env = socks5_auth;
    unsigned char n_auth = 0; unsigned char auth_list[10], auth_method;
    int len, auth_result, i;

    debug( "begin_socks_relay()\n");

    /* request authentication */
    ptr = buf;
    PUT_BYTE( ptr++, 5);                        /* SOCKS version (5) */

    if ( env == NULL )
        env = getparam(ENV_SOCKS5_AUTH);
    if ( env == NULL ) {
        /* add no-auth authentication */
        auth_list[n_auth++] = SOCKS5_AUTH_NOAUTH;
        /* add user/pass authentication */
        auth_list[n_auth++] = SOCKS5_AUTH_USERPASS;
    } else {
        n_auth = socks5_auth_parse(env, auth_list, 10);
    }
    PUT_BYTE( ptr++, n_auth);                   /* num auth */
    for (i=0; i<n_auth; i++) {
        debug("available auth method[%d] = %s (0x%02x)\n",
              i, socks5_getauthname(auth_list[i]), auth_list[i]);
        PUT_BYTE( ptr++, auth_list[i]);         /* authentications */
    }
    atomic_out( s, buf, ptr-buf );              /* send requst */
    atomic_in( s, buf, 2 );                     /* recv response */
    if ( (buf[0] != 5) ||                       /* ver5 response */
         (buf[1] == 0xFF) ) {                   /* check auth method */
        error("No auth method accepted.\n");
        return -1;
    }
    auth_method = buf[1];

    debug("auth method: %s\n", socks5_getauthname(auth_method));

    switch ( auth_method ) {
    case SOCKS5_AUTH_REJECT:
        error("No acceptable authentication method\n");
        return -1;                              /* fail */

    case SOCKS5_AUTH_NOAUTH:
        /* nothing to do */
        auth_result = 0;
        break;

    case SOCKS5_AUTH_USERPASS:
        auth_result = socks5_do_auth_userpass(s);
        break;

    default:
        error("Unsupported authentication method: %s\n",
              socks5_getauthname( auth_method ));
        return -1;                              /* fail */
    }
    if ( auth_result != 0 ) {
        error("Authentication failed.\n");
        return -1;
    }
    /* request to connect */
    ptr = buf;
    PUT_BYTE( ptr++, 5);                        /* SOCKS version (5) */
    PUT_BYTE( ptr++, 1);                        /* CMD: CONNECT */
    PUT_BYTE( ptr++, 0);                        /* FLG: 0 */
    if ( dest_addr.sin_addr.s_addr == 0 ) {
        /* resolved by SOCKS server */
        PUT_BYTE( ptr++, 3);                    /* ATYP: DOMAINNAME */
        len = strlen(dest_host);
        PUT_BYTE( ptr++, len);                  /* DST.ADDR (len) */
        memcpy( ptr, dest_host, len );          /* (hostname) */
        ptr += len;
    } else {
        /* resolved localy */
        PUT_BYTE( ptr++, 1 );                   /* ATYP: IPv4 */
        memcpy( ptr, &dest_addr.sin_addr.s_addr, sizeof(dest_addr.sin_addr));
        ptr += sizeof(dest_addr.sin_addr);
    }
    PUT_BYTE( ptr++, dest_port>>8);     /* DST.PORT */
    PUT_BYTE( ptr++, dest_port&0xFF);
    atomic_out( s, buf, ptr-buf);               /* send request */
    atomic_in( s, buf, 4 );                     /* recv response */
    if ( (buf[1] != SOCKS5_REP_SUCCEEDED) ) {   /* check reply code */
        error("Got error response from SOCKS server: %d (%s).\n",
              buf[1], lookup(buf[1], socks5_rep_names));
        return -1;
    }
    ptr = buf + 4;
    switch ( buf[3] ) {                         /* case by ATYP */
    case 1:                                     /* IP v4 ADDR*/
        atomic_in( s, ptr, 4+2 );               /* recv IPv4 addr and port */
        break;
    case 3:                                     /* DOMAINNAME */
        atomic_in( s, ptr, 1 );                 /* recv name and port */
        atomic_in( s, ptr+1, *(unsigned char*)ptr + 2);
        break;
    case 4:                                     /* IP v6 ADDR */
        atomic_in( s, ptr, 16+2 );              /* recv IPv6 addr and port */
        break;
    }

    /* Conguraturation, connected via SOCKS5 server! */
    return 0;
}

/* begin SOCKS protocol 4 relaying
   And no authentication is supported.

   There's SOCKS protocol version 4 and 4a. Protocol version
   4a has capability to resolve hostname by SOCKS server, so
   we don't need resolving IP address of destination host on
   local machine.

   Environment variable SOCKS_RESOLVE directs how to resolve
   IP addess. There's 3 keywords allowed; "local", "remote"
   and "both" (case insensitive). Keyword "local" means taht
   target host name is resolved by localhost resolver
   (usualy with gethostbyname()), "remote" means by remote
   SOCKS server, "both" means to try resolving by localhost
   then remote.

   SOCKS4 protocol and authentication of SOCKS5 protocol
   requires user name on connect request.
   User name is determined by following method.

   1. If server spec has user@hostname:port format then
      user part is used for this SOCKS server.

   2. Get user name from environment variable LOGNAME, USER
      (in this order).

*/
int
begin_socks4_relay( SOCKET s )
{
    unsigned char buf[256], *ptr;

    debug( "begin_socks_relay()\n");

    /* make connect request packet
       protocol v4:
         VN:1, CD:1, PORT:2, ADDR:4, USER:n, NULL:1
       protocol v4a:
         VN:1, CD:1, PORT:2, DUMMY:4, USER:n, NULL:1, HOSTNAME:n, NULL:1
    */
    ptr = buf;
    PUT_BYTE( ptr++, 4);                        /* protocol version (4) */
    PUT_BYTE( ptr++, 1);                        /* CONNECT command */
    PUT_BYTE( ptr++, dest_port>>8);     /* destination Port */
    PUT_BYTE( ptr++, dest_port&0xFF);
    /* destination IP */
    memcpy(ptr, &dest_addr.sin_addr, sizeof(dest_addr.sin_addr));
    ptr += sizeof(dest_addr.sin_addr);
    if ( dest_addr.sin_addr.s_addr == 0 )
        *(ptr-1) = 1;                           /* fake, protocol 4a */
    /* username */
    if (relay_user == NULL)
        fatal( "Cannot determine user name.\n");
    strcpy( ptr, relay_user );
    ptr += strlen( relay_user ) +1;
    /* destination host name (for protocol 4a) */
    if ( (socks_version == 4) && (dest_addr.sin_addr.s_addr == 0)) {
        strcpy( ptr, dest_host );
        ptr += strlen( dest_host ) +1;
    }
    /* send command and get response
       response is: VN:1, CD:1, PORT:2, ADDR:4 */
    atomic_out( s, buf, ptr-buf);               /* send request */
    atomic_in( s, buf, 8 );                     /* recv response */
    if ( (buf[1] != SOCKS4_REP_SUCCEEDED) ) {   /* check reply code */
        error("Got error response: %d: '%s'.\n",
              buf[1], lookup(buf[1], socks4_rep_names));
        return -1;                              /* failed */
    }

    /* Conguraturation, connected via SOCKS4 server! */
    return 0;
}

int
sendf(SOCKET s, const char *fmt,...)
{
    static char buf[10240];                     /* xxx, enough? */

    va_list args;
    va_start( args, fmt );
    vsnprintf( buf, sizeof(buf), fmt, args );
    va_end( args );

    report_text(">>>", buf);
    if ( send(s, buf, strlen(buf), 0) == SOCKET_ERROR ) {
        debug("failed to send http request. errno=%d\n", socket_errno());
        return -1;
    }
    return 0;
}

const char *base64_table =
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char *
make_base64_string(const char *str)
{
    static char *buf;
    unsigned char *src;
    char *dst;
    int bits, data, src_len, dst_len;
    /* make base64 string */
    src_len = strlen(str);
    dst_len = (src_len+2)/3*4;
    buf = xmalloc(dst_len+1);
    bits = data = 0;
    src = (unsigned char *)str;
    dst = (unsigned char *)buf;
    while ( dst_len-- ) {
        if ( bits < 6 ) {
            data = (data << 8) | *src;
            bits += 8;
            if ( *src != 0 )
                src++;
        }
        *dst++ = base64_table[0x3F & (data >> (bits-6))];
        bits -= 6;
    }
    *dst = '\0';
    /* fix-up tail padding */
    switch ( src_len%3 ) {
    case 1:
        *--dst = '=';
    case 2:
        *--dst = '=';
    }
    return buf;
}


int
basic_auth (SOCKET s)
{
    char *userpass;
    char *cred;
    const char *user = relay_user;
    char *pass = NULL;
    int len, ret;

    /* Get username/password for authentication */
    if (user == NULL)
        fatal("Cannot decide username for proxy authentication.");
    if ((pass = determine_relay_password ()) == NULL &&
        (pass = readpass("Enter proxy authentication password for %s@%s: ",
                         relay_user, relay_host)) == NULL)
        fatal("Cannot decide password for proxy authentication.");

    len = strlen(user)+strlen(pass)+1;
    userpass = xmalloc(len+1);
    snprintf(userpass, len+1, "%s:%s", user, pass);
    memset (pass, 0, strlen(pass));
    cred = make_base64_string(userpass);
    memset (userpass, 0, len);

    f_report = 0;                               /* don't report for security */
    ret = sendf(s, "Proxy-Authorization: Basic %s\r\n", cred);
    f_report = 1;
    report_text(">>>", "Proxy-Authorization: Basic xxxxx\r\n");

    memset(cred, 0, strlen(cred));
    free(cred);

    return ret;
}

/* begin relaying via HTTP proxy
   Directs CONNECT method to proxy server to connect to
   destination host (and port). It may not be allowed on your
   proxy server.
 */
int
begin_http_relay( SOCKET s )
{
    char buf[1024];
    int result;
    char *auth_what;

    debug("begin_http_relay()\n");

    if (sendf(s,"CONNECT %s:%d HTTP/1.0\r\n", dest_host, dest_port) < 0)
        return START_ERROR;
    if (proxy_auth_type == PROXY_AUTH_BASIC && basic_auth (s) < 0)
        return START_ERROR;
    if (sendf(s,"\r\n") < 0)
        return START_ERROR;

    /* get response */
    if ( line_input(s, buf, sizeof(buf)) < 0 ) {
        debug("failed to read http response.\n");
        return START_ERROR;
    }

    /* check status */
    if (!strchr(buf, ' ')) {
	error ("Unexpected http response: '%s'.\n", buf);
	return START_ERROR;
    }
    result = atoi(strchr(buf,' '));

    switch ( result ) {
    case 200:
        /* Conguraturation, connected via http proxy server! */
        debug("connected, start user session.\n");
        break;
    case 302:                                   /* redirect */
        do {
            if (line_input(s, buf, sizeof(buf)))
                break;
            downcase(buf);
            if (expect(buf, "Location: ")) {
                relay_host = cut_token(buf, "//");
                cut_token(buf, "/");
                relay_port = atoi(cut_token(buf, ":"));
            }
        } while (strcmp(buf,"\r\n") != 0);
        return START_RETRY;

    /* We handle both 401 and 407 codes here: 401 is WWW-Authenticate, which
     * not strictly the correct response, but some proxies do send this (e.g.
     * Symantec's Raptor firewall) */
    case 401:                                   /* WWW-Auth required */
    case 407:                                   /* Proxy-Auth required */
        /** NOTE: As easy implementation, we support only BASIC scheme
            and ignore realm. */
        /* If proxy_auth_type is PROXY_AUTH_BASIC and get
         this result code, authentication was failed. */
        if (proxy_auth_type != PROXY_AUTH_NONE) {
            error("Authentication failed.\n");
            return START_ERROR;
        }
        auth_what = (result == 401) ? "WWW-Authenticate:" : "Proxy-Authenticate:";
        do {
            if ( line_input(s, buf, sizeof(buf)) ) {
                break;
            }
            downcase(buf);
            if (expect(buf, auth_what)) {
                /* parse type and realm */
                char *scheme, *realm;
                scheme = cut_token(buf, " ");
                realm = cut_token(scheme, " ");
                if ( scheme == NULL || realm == NULL ) {
                    debug("Invalid format of %s field.", auth_what);
                    return START_ERROR;         /* fail */
                }
                /* check supported auth type */
                if (expect(scheme, "basic")) {
                    proxy_auth_type = PROXY_AUTH_BASIC;
                } else {
                    debug("Unsupported authentication type: %s", scheme);
                }
            }
        } while (strcmp(buf,"\r\n") != 0);
        if ( proxy_auth_type == PROXY_AUTH_NONE ) {
            debug("Can't find %s in response header.", auth_what);
            return START_ERROR;
        } else {
            return START_RETRY;
        }

    default:
        /* Not allowed */
        debug("http proxy is not allowed.\n");
        return START_ERROR;
    }
    /* skip to end of response header */
    do {
        if ( line_input(s, buf, sizeof(buf) ) ) {
            debug("Can't skip response headers\n");
            return START_ERROR;
        }
    } while ( strcmp(buf,"\r\n") != 0 );

    return START_OK;
}

/* begin relaying via TELNET proxy.
   Sends string specified by telnet_command (-c option) with
   replacing host name and port number to the socket.  */
int
begin_telnet_relay( SOCKET s )
{
    char buf[1024];
    char *cmd;
    char *good_phrase = "connected to";
    char *bad_phrase_list[] = {
	" failed", " refused", " rejected", " closed"
    };
    char sep = ' ';
    int i;

    debug("begin_telnet_relay()\n");

    /* report phrase */
    debug("good phrase: '%s'\n", good_phrase);
    debug("bad phrases");
    sep = ':';
    for (i=0; i< (sizeof(bad_phrase_list) / sizeof(char*)); i++) {
	debug_("%c '%s'", sep, bad_phrase_list[i]);
	sep = ',';
    }
    debug_("\n");

    /* make request string with replacing %h by destination hostname
       and %p by port number, etc. */
    cmd = expand_host_and_port(telnet_command, dest_host, dest_port);
    
    /* Sorry, we send request string now without waiting a prompt. */
    if (sendf(s, "%s\r\n", cmd) < 0) {
	free(cmd);
        return START_ERROR;
    }
    free(cmd);

    /* Process answer from proxy until good or bad phrase is detected.  We
       assume that the good phrase should be appeared only in the final
       line of proxy responses. Bad keywods in the line causes operation
       fail. First checks a good phrase, then checks bad phrases.
       If no match, continue reading line from proxy. */
    while (!line_input(s, buf, sizeof(buf)) && buf[0] != '\0') {
	downcase(buf);
	/* first, check good phrase */
        if (strstr(buf, good_phrase)) {
	    debug("good phrase is detected: '%s'\n", good_phrase);
            return START_OK;
        }
	/* then, check bad phrase */
	for (i=0; i<(sizeof(bad_phrase_list)/sizeof(char*)); i++) {
	    if (strstr(buf, bad_phrase_list[i]) != NULL) {
		debug("bad phrase is detected: '%s'\n", bad_phrase_list[i]);
		return START_ERROR;
	    }
        }
    }
    debug("error reading from telnet proxy\n");

    return START_ERROR;
}


#ifdef _WIN32
/* ddatalen()
   Returns 1 if data is available, otherwise return 0
 */
int
stdindatalen (void)
{
    DWORD len = 0;
    struct stat st;
    fstat( 0, &st );
    if ( st.st_mode & _S_IFIFO ) {
        /* in case of PIPE */
        if ( !PeekNamedPipe( GetStdHandle(STD_INPUT_HANDLE),
                             NULL, 0, NULL, &len, NULL) ) {
            if ( GetLastError() == ERROR_BROKEN_PIPE ) {
                /* PIPE source is closed */
                /* read() will detects EOF */
                len = 1;
            } else {
                fatal("PeekNamedPipe() failed, errno=%d\n",
                      GetLastError());
            }
        }
    } else if ( st.st_mode & _S_IFREG ) {
        /* in case of regular file (redirected) */
        len = 1;                        /* always data ready */
    } else if ( _kbhit() ) {
        /* in case of console */
        len = 1;
    }
    return len;
}
#endif /* _WIN32 */

/* relay byte from stdin to socket and fro socket to stdout.
   returns reason of termination */
int
do_repeater( SOCKET local_in, SOCKET local_out, SOCKET remote )
{
    /** vars for local input data **/
    char lbuf[1024];                            /* local input buffer */
    int lbuf_len;                               /* available data in lbuf */
    int f_local;                                /* read local input more? */
    /** vars for remote input data **/
    char rbuf[1024];                            /* remote input buffer */
    int rbuf_len;                               /* available data in rbuf */
    int f_remote;                               /* read remote input more? */
    int close_reason = REASON_UNK;              /* reason of end repeating */
    /** other variables **/
    int nfds, len;
    fd_set ifds, ofds;
    struct timeval *tmo;
#ifdef _WIN32
    struct timeval win32_tmo;
#endif /* _WIN32 */

    /* repeater between stdin/out and socket  */
    nfds = ((local_in<remote)? remote: local_in) +1;
    f_local = 1;                                /* yes, read from local */
    f_remote = 1;                               /* yes, read from remote */
    lbuf_len = 0;
    rbuf_len = 0;

    while ( f_local || f_remote ) {
        FD_ZERO(&ifds );
        FD_ZERO(&ofds );
        tmo = NULL;

        /** prepare for reading local input **/
        if ( f_local && (lbuf_len < (int)sizeof(lbuf)) ) {
#ifdef _WIN32
            if ( local_type != LOCAL_SOCKET ) {
                /* select() on Winsock is not accept standard handle.
                   So use select() with short timeout and checking data
                   in stdin by another method. */
                win32_tmo.tv_sec = 0;
                win32_tmo.tv_usec = 10*1000;    /* 10 ms */
                tmo = &win32_tmo;
            } else
#endif /* !_WIN32 */
            FD_SET( local_in, &ifds );
        }

        /** prepare for reading remote input **/
        if ( f_remote && (rbuf_len < (int)sizeof(rbuf)) ) {
            FD_SET( remote, &ifds );
        }

        /* FD_SET( local_out, ofds ); */
        /* FD_SET( remote, ofds ); */

        if ( select( nfds, &ifds, &ofds, (fd_set*)NULL, tmo ) == -1 ) {
            /* some error */
            error( "select() failed, %d\n", socket_errno());
            return REASON_ERROR;
        }
#ifdef _WIN32
        /* fake ifds if local is stdio handle because
           select() of Winsock does not accept stdio
           handle. */
        if (f_local && (local_type!=LOCAL_SOCKET) && (0<stdindatalen()))
            FD_SET(0,&ifds);            /* data ready */
#endif

        /* remote => local */
        if ( FD_ISSET(remote, &ifds) && (rbuf_len < (int)sizeof(rbuf)) ) {
            len = recv( remote, rbuf + rbuf_len, sizeof(rbuf)-rbuf_len, 0);
            if ( len == 0 || (len == -1 && socket_errno() == ECONNRESET)) {
                debug("connection %s by peer\n",
                      (len==0)? "closed": "reset");
                close_reason = REASON_CLOSED_BY_REMOTE;
                f_remote = 0;                   /* no more read from socket */
                f_local = 0;
            } else if ( len == -1 ) {
                /* error */
                fatal("recv() failed, %d\n", socket_errno());
            } else {
                debug("recv %d bytes\n", len);
                if ( 1 < f_debug )              /* more verbose */
                    report_bytes( "<<<", rbuf+rbuf_len, len);
                rbuf_len += len;
            }
        }

        /* local => remote */
        if ( FD_ISSET(local_in, &ifds) && (lbuf_len < (int)sizeof(lbuf)) ) {
            if (local_type == LOCAL_SOCKET)
                len = recv(local_in, lbuf + lbuf_len,
                           sizeof(lbuf)-lbuf_len, 0);
            else
                len = read(local_in, lbuf + lbuf_len, sizeof(lbuf)-lbuf_len);
            if ( len == 0 ) {
                /* stdin is EOF */
                debug("local input is EOF\n");
                if (!f_hold_session)
                    shutdown(remote, 1);        /* no-more writing */
                f_local = 0;
                close_reason = REASON_CLOSED_BY_LOCAL;
            } else if ( len == -1 ) {
                /* error on reading from stdin */
                if (f_hold_session) {
                    debug ("failed to read from local\n");
                    f_local = 0;
                    close_reason = REASON_CLOSED_BY_LOCAL;
                } else
                    fatal("recv() failed, errno = %d\n", errno);
            } else {
                /* repeat */
                lbuf_len += len;
            }
        }

        /* flush data in buffer to socket */
        if ( 0 < lbuf_len ) {
            len = send(remote, lbuf, lbuf_len, 0);
            if ( len == -1 ) {
                fatal("send() failed, %d\n", socket_errno());
            } else if ( 0 < len ) {
                if ( 1 < f_debug )              /* more verbose */
                    report_bytes( ">>>", lbuf, len);
                /* move data on to top of buffer */
                debug("sent %d bytes\n", len);
                lbuf_len -= len;
                if ( 0 < lbuf_len )
                    memcpy( lbuf, lbuf+len, lbuf_len );
                assert( 0 <= lbuf_len );
            }
        }

        /* flush data in buffer to local output */
        if ( 0 < rbuf_len ) {
            if (local_type == LOCAL_SOCKET)
                len = send( local_out, rbuf, rbuf_len, 0);
            else
                len = write( local_out, rbuf, rbuf_len);
            if ( len == -1 ) {
                fatal("output (local) failed, errno=%d\n", errno);
            }
            rbuf_len -= len;
            if ( len < rbuf_len )
                memcpy( rbuf, rbuf+len, rbuf_len );
            assert( 0 <= rbuf_len );
        }
        if (f_local == 0 && f_hold_session) {
            debug ("closing local port without disconnecting from remote\n");
            f_remote = 0;
            shutdown (local_out, 2);
            close (local_out);
            break;
        }
    }

    return close_reason;
}

int
accept_connection (u_short port)
{
    static int sock = -1;
    int connection;
    struct sockaddr_in name;
    struct sockaddr client;
    int socklen;
    fd_set ifds;
    int nfds;
    int sockopt;

    /* Create the socket. */
    debug("Creating source port to forward.\n");
    sock = socket (PF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        fatal("socket() failed, errno=%d\n", socket_errno());
    sockopt = 1;
    setsockopt (sock, SOL_SOCKET, SO_REUSEADDR,
                (void*)&sockopt, sizeof(sockopt));

    /* Give the socket a name. */
    name.sin_family = AF_INET;
    name.sin_port = htons (port);
    name.sin_addr.s_addr = htonl (INADDR_ANY);
    if (bind (sock, (struct sockaddr *) &name, sizeof (name)) < 0)
        fatal ("bind() failed, errno=%d\n", socket_errno());

    if (listen( sock, 1) < 0)
        fatal ("listen() failed, errno=%d\n", socket_errno());

    /* wait for new connection with watching EOF of stdin. */
    debug ("waiting new connection at port %d (socket=%d)\n", port, sock);
    nfds = sock + 1;
    do {
        int n;
        struct timeval *ptmo = NULL;
#ifdef _WIN32
        struct timeval tmo;
        tmo.tv_sec = 0;
        tmo.tv_usec = 100*1000;                 /* On Windows, 100ms timeout */
        ptmo = &tmo;
#endif /* _WIN32 */
        FD_ZERO (&ifds);
        FD_SET ((SOCKET)sock, &ifds);
#ifndef _WIN32
        FD_SET (0, &ifds);                      /* watch stdin */
#endif
        n = select (nfds, &ifds, NULL, NULL, ptmo);
        if (n == -1) {
            fatal ("select() failed, %d\n", socket_errno());
            exit (1);
        }
#ifdef _WIN32
        if (0 < stdindatalen()) {
            FD_SET (0, &ifds);          /* fake */
            n++;
        }
#endif
        if (0 < n) {
            if (FD_ISSET(0, &ifds) && (getchar() <= 0)) {
                /* EOF */
                debug ("Give-up waiting port because stdin is closed.");
                exit(0);
            }
            if (FD_ISSET(sock, &ifds))
                break;                          /* socket is stimulated */
        }
    } while (1);
    socklen = sizeof(client);
    connection = accept( sock, &client, &socklen);
    if ( connection < 0 )
        fatal ("accept() failed, errno=%d\n", socket_errno());
    return connection;
}



/** Main of program **/
int
main( int argc, char **argv )
{
    int ret;
    int remote;                                 /* socket */
    int local_in;                               /* Local input */
    int local_out;                              /* Local output */
    int reason;
#ifdef _WIN32
    WSADATA wsadata;
    WSAStartup( 0x101, &wsadata);
#endif /* _WIN32 */

    /* initialization */
    make_revstr();
    getarg( argc, argv );
    debug("Program is $Revision: 100 $\n");

    /* Open local_in and local_out if forwarding a port */
    if ( local_type == LOCAL_SOCKET ) {
        /* Relay between local port and destination */
        local_in = local_out = accept_connection( local_port );
    } else {
        /* Relay between stdin/stdout and desteination */
        local_in = 0;
        local_out = 1;
#ifdef _WIN32
        _setmode(local_in, O_BINARY);
        _setmode(local_out, O_BINARY);
#endif
    }

retry:
#ifndef _WIN32
    if (0 < connect_timeout)
        set_timeout (connect_timeout);
#endif /* not _WIN32 */

    if (check_direct(dest_host))
        relay_method = METHOD_DIRECT;
    /* make connection */
    if ( relay_method == METHOD_DIRECT ) {
        remote = open_connection (dest_host, dest_port);
        if ( remote == SOCKET_ERROR )
            fatal( "Unable to connect to destination host, errno=%d\n",
                   socket_errno());
    } else {
        remote = open_connection (relay_host, relay_port);
        if ( remote == SOCKET_ERROR )
            fatal( "Unable to connect to relay host, errno=%d\n",
                   socket_errno());
    }

    /** resolve destination host (SOCKS) **/
#if !defined(_WIN32) && !defined(__CYGWIN32__)
    if (socks_ns.sin_addr.s_addr != 0)
        switch_ns (&socks_ns);
#endif /* not _WIN32 && not __CYGWIN32__ */
    if (relay_method == METHOD_SOCKS &&
        socks_resolve == RESOLVE_LOCAL &&
        local_resolve (dest_host, &dest_addr) < 0) {
        fatal("Unknown host: %s", dest_host);
    }

    /** relay negociation **/
    switch ( relay_method ) {
    case METHOD_SOCKS:
        if ( ((socks_version == 5) && (begin_socks5_relay(remote) < 0)) ||
             ((socks_version == 4) && (begin_socks4_relay(remote) < 0)) )
            fatal( "failed to begin relaying via SOCKS.\n");
        break;

    case METHOD_HTTP:
        ret = begin_http_relay(remote);
        switch (ret) {
        case START_ERROR:
            close (remote);
            fatal("failed to begin relaying via HTTP.\n");
        case START_OK:
            break;
        case START_RETRY:
            /* retry with authentication */
            close (remote);
            goto retry;
        }
        break;
    case METHOD_TELNET:
        if (begin_telnet_relay(remote) < 0)
             fatal("failed to begin relaying via telnet.\n");
        break;
    }
    debug("connected\n");

#ifndef _WIN32
    if (0 < connect_timeout)
        set_timeout (0);
#endif /* not _WIN32 */

    /* main loop */
    debug ("start relaying.\n");
do_repeater:
    reason = do_repeater(local_in, local_out, remote);
    debug ("relaying done.\n");
    if (local_type == LOCAL_SOCKET &&
        reason == REASON_CLOSED_BY_LOCAL &&
        f_hold_session) {
        /* re-wait at local port without closing remote session */
        debug ("re-waiting at local port %d\n", local_port);
        local_in = local_out = accept_connection( local_port );
        debug ("re-start relaying\n");
        goto do_repeater;
    }
    closesocket(remote);
    if ( local_type == LOCAL_SOCKET)
        closesocket(local_in);
#ifdef _WIN32
    WSACleanup();
#endif /* _WIN32 */
    debug ("that's all, bye.\n");

    return 0;
}

/* ------------------------------------------------------------
   Local Variables:
   compile-command: "cc connect.c -o connect"
   tab-width: 8
   fill-column: 74
   comment-column: 48
   End:
   ------------------------------------------------------------ */

/*** end of connect.c ***/
