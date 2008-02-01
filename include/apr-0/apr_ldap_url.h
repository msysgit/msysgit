/* Copyright 2000-2005 The Apache Software Foundation or its licensors, as
 * applicable.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef APR_LDAP_URL_H
#define APR_LDAP_URL_H

#include "apr_ldap.h"

#if APR_HAS_LDAP
#if APR_HAS_LDAP_URL_PARSE

#define apr_ldap_url_desc_t             LDAPURLDesc
#define apr_ldap_is_ldap_url(url)       ldap_is_ldap_url(url)
#define apr_ldap_is_ldaps_url(url)      ldap_is_ldaps_url(url)
#define apr_ldap_is_ldapi_url(url)      ldap_is_ldapi_url(url)
#define apr_ldap_url_parse(url, ludpp)  ldap_url_parse(url, ludpp)
#define apr_ldap_free_urldesc(ludp)     ldap_free_urldesc(ludp)

#else /* ! APR_HAS_LDAP_URL_PARSE */

/*
 * types for ldap URL handling
 */
typedef struct apr_ldap_url_desc_t {
    struct  apr_ldap_url_desc_t  *lud_next;
    char    *lud_scheme;
    char    *lud_host;
    int     lud_port;
    char    *lud_dn;
    char    **lud_attrs;
    int     lud_scope;
    char    *lud_filter;
    char    **lud_exts;
    int     lud_crit_exts;
} apr_ldap_url_desc_t;

#ifndef LDAP_URL_SUCCESS
#define LDAP_URL_SUCCESS          0x00    /* Success */
#define LDAP_URL_ERR_MEM          0x01    /* can't allocate memory space */
#define LDAP_URL_ERR_PARAM        0x02    /* parameter is bad */
#define LDAP_URL_ERR_BADSCHEME    0x03    /* URL doesn't begin with "ldap[si]://" */
#define LDAP_URL_ERR_BADENCLOSURE 0x04    /* URL is missing trailing ">" */
#define LDAP_URL_ERR_BADURL       0x05    /* URL is bad */
#define LDAP_URL_ERR_BADHOST      0x06    /* host port is bad */
#define LDAP_URL_ERR_BADATTRS     0x07    /* bad (or missing) attributes */
#define LDAP_URL_ERR_BADSCOPE     0x08    /* scope string is invalid (or missing) */
#define LDAP_URL_ERR_BADFILTER    0x09    /* bad or missing filter */
#define LDAP_URL_ERR_BADEXTS      0x0a    /* bad or missing extensions */
#endif

/*
 * in url.c
 *
 * need _ext varients
 */
APU_DECLARE(int) apr_ldap_is_ldap_url(const char *url);

APU_DECLARE(int) apr_ldap_is_ldaps_url(const char *url);

APU_DECLARE(int) apr_ldap_is_ldapi_url(const char *url);

APU_DECLARE(int) apr_ldap_url_parse(const char *url, 
                                    apr_ldap_url_desc_t **ludpp);

APU_DECLARE(void) apr_ldap_free_urldesc(apr_ldap_url_desc_t *ludp);

#endif /* ! APR_HAS_LDAP_URL_PARSE */

#endif /* APR_HAS_LDAP */

#endif /* APR_LDAP_URL_H */
