/* gsasl-compat.h --- Header file for obsoleted features in GNU SASL Library.
 * Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009  Simon Josefsson
 *
 * This file is part of GNU SASL Library.
 *
 * GNU SASL Library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * GNU SASL Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License License along with GNU SASL Library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#ifndef GSASL_COMPAT_H
# define GSASL_COMPAT_H

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if __GNUC__ < 2 || (__GNUC__ == 2 && __GNUC_MINOR__ < 5)
#  define __attribute__(Spec)	/* empty */
# endif
#endif

/* Old error codes */
enum
{
  GSASL_TOO_SMALL_BUFFER = 4,
  GSASL_FOPEN_ERROR = 5,
  GSASL_FCLOSE_ERROR = 6,
  GSASL_GCRYPT_ERROR = GSASL_CRYPTO_ERROR,
  GSASL_CANNOT_GET_CTX = 32,
  GSASL_NEED_CLIENT_ANONYMOUS_CALLBACK = 11,
  GSASL_NEED_CLIENT_PASSWORD_CALLBACK = 12,
  GSASL_NEED_CLIENT_PASSCODE_CALLBACK = 13,
  GSASL_NEED_CLIENT_PIN_CALLBACK = 14,
  GSASL_NEED_CLIENT_AUTHORIZATION_ID_CALLBACK = 15,
  GSASL_NEED_CLIENT_AUTHENTICATION_ID_CALLBACK = 16,
  GSASL_NEED_CLIENT_SERVICE_CALLBACK = 17,
  GSASL_NEED_SERVER_VALIDATE_CALLBACK = 18,
  GSASL_NEED_SERVER_CRAM_MD5_CALLBACK = 19,
  GSASL_NEED_SERVER_DIGEST_MD5_CALLBACK = 20,
  GSASL_NEED_SERVER_EXTERNAL_CALLBACK = 21,
  GSASL_NEED_SERVER_ANONYMOUS_CALLBACK = 22,
  GSASL_NEED_SERVER_REALM_CALLBACK = 23,
  GSASL_NEED_SERVER_SECURID_CALLBACK = 24,
  GSASL_NEED_SERVER_SERVICE_CALLBACK = 25,
  GSASL_NEED_SERVER_GSSAPI_CALLBACK = 26,
  GSASL_NEED_SERVER_RETRIEVE_CALLBACK = 27,
  GSASL_UNICODE_NORMALIZATION_ERROR = 28,
  GSASL_NO_MORE_REALMS = 34,
  GSASL_INVALID_HANDLE = 50
} __attribute__ ((deprecated));

typedef Gsasl Gsasl_ctx __attribute__ ((deprecated));
typedef Gsasl_session Gsasl_session_ctx __attribute__ ((deprecated));
extern GSASL_API int gsasl_client_listmech (Gsasl * ctx, char *out,
					    size_t * outlen)
  __attribute__ ((deprecated));
extern GSASL_API int gsasl_server_listmech (Gsasl * ctx, char *out,
					    size_t * outlen)
  __attribute__ ((deprecated));
extern GSASL_API int gsasl_client_step (Gsasl_session * sctx,
					const char *input, size_t input_len,
					char *output, size_t * output_len)
  __attribute__ ((deprecated));
extern GSASL_API int gsasl_client_step_base64 (Gsasl_session * sctx,
					       const char *b64input,
					       char *b64output,
					       size_t b64output_len)
  __attribute__ ((deprecated));
extern GSASL_API int gsasl_server_step (Gsasl_session * sctx,
					const char *input, size_t input_len,
					char *output, size_t * output_len)
  __attribute__ ((deprecated));
extern GSASL_API int gsasl_server_step_base64 (Gsasl_session * sctx,
					       const char *b64input,
					       char *b64output,
					       size_t b64output_len)
  __attribute__ ((deprecated));
extern GSASL_API void gsasl_client_finish (Gsasl_session * sctx)
  __attribute__ ((deprecated));
extern GSASL_API void gsasl_server_finish (Gsasl_session * sctx)
  __attribute__ ((deprecated));
extern GSASL_API Gsasl *gsasl_client_ctx_get (Gsasl_session * sctx)
  __attribute__ ((deprecated));
extern GSASL_API Gsasl *gsasl_server_ctx_get (Gsasl_session * sctx)
  __attribute__ ((deprecated));
extern GSASL_API void gsasl_client_application_data_set (Gsasl_session * sctx,
							 void
							 *application_data)
  __attribute__ ((deprecated));
extern GSASL_API void *gsasl_client_application_data_get (Gsasl_session *
							  sctx)
  __attribute__ ((deprecated));
extern GSASL_API void gsasl_server_application_data_set (Gsasl_session * sctx,
							 void
							 *application_data)
  __attribute__ ((deprecated));
extern GSASL_API void *gsasl_server_application_data_get (Gsasl_session *
							  sctx)
  __attribute__ ((deprecated));
extern GSASL_API int gsasl_randomize (int strong, char *data, size_t datalen)
  __attribute__ ((deprecated));
extern GSASL_API Gsasl *gsasl_ctx_get (Gsasl_session * sctx)
  __attribute__ ((deprecated));
extern GSASL_API int gsasl_encode_inline (Gsasl_session * sctx,
					  const char *input, size_t input_len,
					  char *output, size_t * output_len)
  __attribute__ ((deprecated));
extern GSASL_API int gsasl_decode_inline (Gsasl_session * sctx,
					  const char *input, size_t input_len,
					  char *output, size_t * output_len)
  __attribute__ ((deprecated));
extern GSASL_API void gsasl_application_data_set (Gsasl * ctx, void *appdata)
  __attribute__ ((deprecated));
extern GSASL_API void *gsasl_application_data_get (Gsasl * ctx)
  __attribute__ ((deprecated));
extern GSASL_API void gsasl_appinfo_set (Gsasl_session * sctx, void *appdata)
  __attribute__ ((deprecated));
extern GSASL_API void *gsasl_appinfo_get (Gsasl_session * sctx)
  __attribute__ ((deprecated));
extern GSASL_API const char *gsasl_server_suggest_mechanism (Gsasl * ctx,
							     const char
							     *mechlist)
  __attribute__ ((deprecated));

extern GSASL_API int gsasl_base64_encode (char const *src, size_t srclength,
					  char *target, size_t targsize)
  __attribute__ ((deprecated));
extern GSASL_API int gsasl_base64_decode (char const *src,
					  char *target, size_t targsize)
  __attribute__ ((deprecated));

extern GSASL_API char *gsasl_stringprep_nfkc (const char *in, ssize_t len)
  __attribute__ ((deprecated));
extern GSASL_API char *gsasl_stringprep_saslprep (const char *in,
						  int *stringprep_rc)
  __attribute__ ((deprecated));
extern GSASL_API char *gsasl_stringprep_trace (const char *in,
					       int *stringprep_rc)
  __attribute__ ((deprecated));

extern GSASL_API int gsasl_md5pwd_get_password (const char *filename,
						const char *username,
						char *key, size_t * keylen)
  __attribute__ ((deprecated));

/* Callback prototypes */
typedef int (*Gsasl_client_callback_anonymous) (Gsasl_session * sctx,
						char *out, size_t * outlen);
typedef int (*Gsasl_client_callback_authentication_id) (Gsasl_session * sctx,
							char *out,
							size_t * outlen);
typedef int (*Gsasl_client_callback_authorization_id) (Gsasl_session * sctx,
						       char *out,
						       size_t * outlen);
typedef int (*Gsasl_client_callback_password) (Gsasl_session * sctx,
					       char *out, size_t * outlen);
typedef int (*Gsasl_client_callback_passcode) (Gsasl_session * sctx,
					       char *out, size_t * outlen);
typedef int (*Gsasl_client_callback_pin) (Gsasl_session * sctx,
					  char *suggestion, char *out,
					  size_t * outlen);
typedef int (*Gsasl_client_callback_service) (Gsasl_session * sctx,
					      char *service,
					      size_t * servicelen,
					      char *hostname,
					      size_t * hostnamelen,
					      char *servicename,
					      size_t * servicenamelen);
typedef Gsasl_qop (*Gsasl_client_callback_qop) (Gsasl_session * sctx,
						Gsasl_qop serverqops);
typedef size_t (*Gsasl_client_callback_maxbuf) (Gsasl_session * sctx,
						size_t servermaxbuf);
typedef int (*Gsasl_client_callback_realm) (Gsasl_session * sctx, char *out,
					    size_t * outlen);
typedef int (*Gsasl_server_callback_retrieve) (Gsasl_session * sctx,
					       const char *authentication_id,
					       const char *authorization_id,
					       const char *realm, char *key,
					       size_t * keylen);
typedef int (*Gsasl_server_callback_validate) (Gsasl_session * sctx,
					       const char *authorization_id,
					       const char *authentication_id,
					       const char *password);
typedef int (*Gsasl_server_callback_gssapi) (Gsasl_session * sctx,
					     const char *clientname,
					     const char *authentication_id);
typedef int (*Gsasl_server_callback_securid) (Gsasl_session * sctx,
					      const char *authentication_id,
					      const char *authorization_id,
					      const char *passcode, char *pin,
					      char *suggestpin,
					      size_t * suggestpinlen);
typedef int (*Gsasl_server_callback_cram_md5) (Gsasl_session * sctx,
					       char *username,
					       char *challenge,
					       char *response);
typedef int (*Gsasl_server_callback_digest_md5) (Gsasl_session * sctx,
						 char *username, char *realm,
						 char *secrethash);
typedef int (*Gsasl_server_callback_service) (Gsasl_session * sctx,
					      char *service,
					      size_t * servicelen,
					      char *hostname,
					      size_t * hostnamelen);
typedef int (*Gsasl_server_callback_external) (Gsasl_session * sctx);
typedef int (*Gsasl_server_callback_anonymous) (Gsasl_session * sctx,
						const char *token);
typedef int (*Gsasl_server_callback_realm) (Gsasl_session * sctx, char *out,
					    size_t * outlen, size_t nth);
typedef Gsasl_qop (*Gsasl_server_callback_qop) (Gsasl_session * sctx);
typedef size_t (*Gsasl_server_callback_maxbuf) (Gsasl_session * sctx);
typedef Gsasl_cipher (*Gsasl_server_callback_cipher) (Gsasl_session * sctx);

/* Obsolete client callbacks: callback-c.c */
extern GSASL_API void
  gsasl_client_callback_authorization_id_set
  (Gsasl * ctx, Gsasl_client_callback_authorization_id cb)
  __attribute__ ((deprecated));
extern GSASL_API Gsasl_client_callback_authorization_id
gsasl_client_callback_authorization_id_get (Gsasl * ctx)
__attribute__ ((deprecated));

extern GSASL_API void
  gsasl_client_callback_authentication_id_set
  (Gsasl * ctx, Gsasl_client_callback_authentication_id cb)
  __attribute__ ((deprecated));
extern GSASL_API Gsasl_client_callback_authentication_id
gsasl_client_callback_authentication_id_get (Gsasl * ctx)
__attribute__ ((deprecated));

extern GSASL_API void
gsasl_client_callback_anonymous_set (Gsasl * ctx,
				     Gsasl_client_callback_anonymous cb)
__attribute__ ((deprecated));
extern GSASL_API Gsasl_client_callback_anonymous
gsasl_client_callback_anonymous_get (Gsasl * ctx)
__attribute__ ((deprecated));

extern GSASL_API void
gsasl_client_callback_password_set (Gsasl * ctx,
				    Gsasl_client_callback_password cb)
__attribute__ ((deprecated));
extern GSASL_API Gsasl_client_callback_password
gsasl_client_callback_password_get (Gsasl * ctx) __attribute__ ((deprecated));

extern GSASL_API void
gsasl_client_callback_passcode_set (Gsasl * ctx,
				    Gsasl_client_callback_passcode cb)
__attribute__ ((deprecated));
extern GSASL_API Gsasl_client_callback_passcode
gsasl_client_callback_passcode_get (Gsasl * ctx) __attribute__ ((deprecated));

extern GSASL_API void
gsasl_client_callback_pin_set (Gsasl * ctx, Gsasl_client_callback_pin cb)
__attribute__ ((deprecated));
extern GSASL_API Gsasl_client_callback_pin
gsasl_client_callback_pin_get (Gsasl * ctx) __attribute__ ((deprecated));

extern GSASL_API void
gsasl_client_callback_service_set (Gsasl * ctx,
				   Gsasl_client_callback_service cb)
__attribute__ ((deprecated));
extern GSASL_API Gsasl_client_callback_service
gsasl_client_callback_service_get (Gsasl * ctx) __attribute__ ((deprecated));

extern GSASL_API void
gsasl_client_callback_qop_set (Gsasl * ctx, Gsasl_client_callback_qop cb)
__attribute__ ((deprecated));
extern GSASL_API Gsasl_client_callback_qop
gsasl_client_callback_qop_get (Gsasl * ctx) __attribute__ ((deprecated));

extern GSASL_API void
gsasl_client_callback_maxbuf_set (Gsasl * ctx,
				  Gsasl_client_callback_maxbuf cb)
__attribute__ ((deprecated));
extern GSASL_API Gsasl_client_callback_maxbuf
gsasl_client_callback_maxbuf_get (Gsasl * ctx) __attribute__ ((deprecated));
extern GSASL_API
void gsasl_client_callback_realm_set (Gsasl * ctx,
				      Gsasl_client_callback_realm cb)
  __attribute__ ((deprecated));
extern GSASL_API Gsasl_client_callback_realm
gsasl_client_callback_realm_get (Gsasl * ctx) __attribute__ ((deprecated));

/* Obsolete server callbacks: callback-s.c */
extern GSASL_API void
gsasl_server_callback_validate_set (Gsasl * ctx,
				    Gsasl_server_callback_validate cb)
__attribute__ ((deprecated));
extern GSASL_API Gsasl_server_callback_validate
gsasl_server_callback_validate_get (Gsasl * ctx) __attribute__ ((deprecated));

extern GSASL_API void
gsasl_server_callback_retrieve_set (Gsasl * ctx,
				    Gsasl_server_callback_retrieve cb)
__attribute__ ((deprecated));
extern GSASL_API Gsasl_server_callback_retrieve
gsasl_server_callback_retrieve_get (Gsasl * ctx) __attribute__ ((deprecated));

extern GSASL_API void
gsasl_server_callback_cram_md5_set (Gsasl * ctx,
				    Gsasl_server_callback_cram_md5 cb)
__attribute__ ((deprecated));
extern GSASL_API Gsasl_server_callback_cram_md5
gsasl_server_callback_cram_md5_get (Gsasl * ctx) __attribute__ ((deprecated));

extern GSASL_API void
gsasl_server_callback_digest_md5_set (Gsasl * ctx,
				      Gsasl_server_callback_digest_md5 cb)
__attribute__ ((deprecated));
extern GSASL_API Gsasl_server_callback_digest_md5
gsasl_server_callback_digest_md5_get (Gsasl * ctx)
__attribute__ ((deprecated));

extern GSASL_API void
gsasl_server_callback_external_set (Gsasl * ctx,
				    Gsasl_server_callback_external cb)
__attribute__ ((deprecated));
extern GSASL_API Gsasl_server_callback_external
gsasl_server_callback_external_get (Gsasl * ctx) __attribute__ ((deprecated));

extern GSASL_API void
gsasl_server_callback_anonymous_set (Gsasl * ctx,
				     Gsasl_server_callback_anonymous cb)
__attribute__ ((deprecated));
extern GSASL_API Gsasl_server_callback_anonymous
gsasl_server_callback_anonymous_get (Gsasl * ctx)
__attribute__ ((deprecated));

extern GSASL_API void
gsasl_server_callback_realm_set (Gsasl * ctx, Gsasl_server_callback_realm cb)
__attribute__ ((deprecated));
extern GSASL_API Gsasl_server_callback_realm
gsasl_server_callback_realm_get (Gsasl * ctx) __attribute__ ((deprecated));

extern GSASL_API void
gsasl_server_callback_qop_set (Gsasl * ctx, Gsasl_server_callback_qop cb)
__attribute__ ((deprecated));
extern GSASL_API Gsasl_server_callback_qop
gsasl_server_callback_qop_get (Gsasl * ctx) __attribute__ ((deprecated));

extern GSASL_API void
gsasl_server_callback_maxbuf_set (Gsasl * ctx,
				  Gsasl_server_callback_maxbuf cb)
__attribute__ ((deprecated));
extern GSASL_API Gsasl_server_callback_maxbuf
gsasl_server_callback_maxbuf_get (Gsasl * ctx) __attribute__ ((deprecated));

extern GSASL_API void
gsasl_server_callback_cipher_set (Gsasl * ctx,
				  Gsasl_server_callback_cipher cb)
__attribute__ ((deprecated));
extern GSASL_API Gsasl_server_callback_cipher
gsasl_server_callback_cipher_get (Gsasl * ctx) __attribute__ ((deprecated));

extern GSASL_API void
gsasl_server_callback_securid_set (Gsasl * ctx,
				   Gsasl_server_callback_securid cb)
__attribute__ ((deprecated));
extern GSASL_API Gsasl_server_callback_securid
gsasl_server_callback_securid_get (Gsasl * ctx) __attribute__ ((deprecated));

extern GSASL_API void
gsasl_server_callback_gssapi_set (Gsasl * ctx,
				  Gsasl_server_callback_gssapi cb)
__attribute__ ((deprecated));
extern GSASL_API Gsasl_server_callback_gssapi
gsasl_server_callback_gssapi_get (Gsasl * ctx) __attribute__ ((deprecated));

extern GSASL_API void
gsasl_server_callback_service_set (Gsasl * ctx,
				   Gsasl_server_callback_service cb)
__attribute__ ((deprecated));
extern GSASL_API Gsasl_server_callback_service
gsasl_server_callback_service_get (Gsasl * ctx) __attribute__ ((deprecated));

#endif /* GSASL_COMPAT_H */
