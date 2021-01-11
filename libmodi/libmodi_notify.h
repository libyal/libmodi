/*
 * Notification functions
 *
 * Copyright (C) 2012-2021, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#if !defined( _LIBMODI_NOTIFY_H )
#define _LIBMODI_NOTIFY_H

#include <common.h>
#include <file_stream.h>
#include <types.h>

#include "libmodi_extern.h"
#include "libmodi_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if !defined( HAVE_LOCAL_LIBMODI )

LIBMODI_EXTERN \
void libmodi_notify_set_verbose(
      int verbose );

LIBMODI_EXTERN \
int libmodi_notify_set_stream(
     FILE *stream,
     libcerror_error_t **error );

LIBMODI_EXTERN \
int libmodi_notify_stream_open(
     const char *filename,
     libcerror_error_t **error );

LIBMODI_EXTERN \
int libmodi_notify_stream_close(
     libcerror_error_t **error );

#endif /* !defined( HAVE_LOCAL_LIBMODI ) */

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMODI_NOTIFY_H ) */

