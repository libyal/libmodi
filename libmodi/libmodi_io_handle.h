/*
 * Input/Output (IO) handle functions
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

#if !defined( _LIBMODI_IO_HANDLE_H )
#define _LIBMODI_IO_HANDLE_H

#include <common.h>
#include <types.h>

#include "libmodi_extern.h"
#include "libmodi_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libmodi_io_handle libmodi_io_handle_t;

struct libmodi_io_handle
{
	/* The (storage) media size
	 */
	size64_t media_size;

	/* The image type
	 */
	int image_type;

	/* The data offset
	 */
	off64_t data_offset;

	/* The band data size
	 */
	size64_t band_data_size;

	/* The number of bands
	 */
	int number_of_bands;

	/* The compression method
	 */
	int compression_method;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

int libmodi_io_handle_initialize(
     libmodi_io_handle_t **io_handle,
     libcerror_error_t **error );

int libmodi_io_handle_free(
     libmodi_io_handle_t **io_handle,
     libcerror_error_t **error );

int libmodi_io_handle_clear(
     libmodi_io_handle_t *io_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMODI_IO_HANDLE_H ) */

