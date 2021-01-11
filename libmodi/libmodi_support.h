/*
 * Support functions
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

#if !defined( _LIBMODI_SUPPORT_H )
#define _LIBMODI_SUPPORT_H

#include <common.h>
#include <types.h>

#include "libmodi_extern.h"
#include "libmodi_libbfio.h"
#include "libmodi_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if !defined( HAVE_LOCAL_LIBMODI )

LIBMODI_EXTERN \
const char *libmodi_get_version(
             void );

LIBMODI_EXTERN \
int libmodi_get_access_flags_read(
     void );

LIBMODI_EXTERN \
int libmodi_get_access_flags_read_write(
     void );

LIBMODI_EXTERN \
int libmodi_get_access_flags_write(
     void );

LIBMODI_EXTERN \
int libmodi_get_codepage(
     int *codepage,
     libcerror_error_t **error );

LIBMODI_EXTERN \
int libmodi_set_codepage(
     int codepage,
     libcerror_error_t **error );

#endif /* !defined( HAVE_LOCAL_LIBMODI ) */

LIBMODI_EXTERN \
int libmodi_check_file_signature(
     const char *filename,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )
LIBMODI_EXTERN \
int libmodi_check_file_signature_wide(
     const wchar_t *filename,
     libcerror_error_t **error );
#endif

LIBMODI_EXTERN \
int libmodi_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMODI_SUPPORT_H ) */

