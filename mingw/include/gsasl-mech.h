/* gsasl-mech.h --- Header file for mechanism handling in GNU SASL Library.
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

#ifndef GSASL_MECH_H
# define GSASL_MECH_H

/* Mechanism function prototypes. */
typedef int (*Gsasl_init_function) (Gsasl * ctx);
typedef void (*Gsasl_done_function) (Gsasl * ctx);
typedef int (*Gsasl_start_function) (Gsasl_session * sctx, void **mech_data);
typedef int (*Gsasl_step_function) (Gsasl_session * sctx, void *mech_data,
				    const char *input, size_t input_len,
				    char **output, size_t * output_len);
typedef void (*Gsasl_finish_function) (Gsasl_session * sctx, void *mech_data);
typedef int (*Gsasl_code_function) (Gsasl_session * sctx, void *mech_data,
				    const char *input, size_t input_len,
				    char **output, size_t * output_len);

/* Collection of mechanism functions for either client or server. */
struct Gsasl_mechanism_functions
{
  Gsasl_init_function init;
  Gsasl_done_function done;
  Gsasl_start_function start;
  Gsasl_step_function step;
  Gsasl_finish_function finish;
  Gsasl_code_function encode;
  Gsasl_code_function decode;
};
typedef struct Gsasl_mechanism_functions Gsasl_mechanism_functions;

/* Information about a mechanism. */
struct Gsasl_mechanism
{
  const char *name;

  struct Gsasl_mechanism_functions client;
  struct Gsasl_mechanism_functions server;
};
typedef struct Gsasl_mechanism Gsasl_mechanism;

/* Register new mechanism: register.c. */
extern GSASL_API int gsasl_register (Gsasl * ctx,
				     const Gsasl_mechanism * mech);

#endif /* GSASL_MECH_H */
