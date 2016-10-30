/*
 * Input/Output (IO) handle functions
 *
 * Copyright (C) 2012-2016, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined( _LIBMODI_IO_HANDLE_H )
#define _LIBMODI_IO_HANDLE_H

#include <common.h>
#include <types.h>

#include "libmodi_bands_table.h"
#include "libmodi_libbfio.h"
#include "libmodi_libcerror.h"
#include "libmodi_libfcache.h"
#include "libmodi_libfdata.h"
#include "libmodi_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

extern const uint8_t *modi_sparse_image_signature;

typedef struct libmodi_io_handle libmodi_io_handle_t;

struct libmodi_io_handle
{
	/* The (storage) media size
	 */
	size64_t media_size;

	/* The image type
	 */
	int image_type;

	/* The bands data offset
	 */
	off64_t bands_data_offset;

	/* The bands data size
	 */
	size64_t bands_data_size;

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

int libmodi_io_handle_read_sparse_image_header(
     libmodi_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libmodi_bands_table_t *data_bands_table,
     libcerror_error_t **error );

int libmodi_io_handle_read_data_band(
     libmodi_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfdata_vector_t *vector,
     libfcache_cache_t *cache,
     int element_index,
     int element_data_file_index,
     off64_t element_data_offset,
     size64_t element_data_size,
     uint32_t element_data_flags,
     uint8_t read_flags,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMODI_IO_HANDLE_H ) */

