/*
 * The bands data handle functions
 *
 * Copyright (C) 2010-2021, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBMODI_BANDS_DATA_HANDLE_H )
#define _LIBMODI_BANDS_DATA_HANDLE_H

#include <common.h>
#include <types.h>

#include "libmodi_io_handle.h"
#include "libmodi_libbfio.h"
#include "libmodi_libcerror.h"
#include "libmodi_libfcache.h"
#include "libmodi_libfdata.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libmodi_bands_data_handle libmodi_bands_data_handle_t;

struct libmodi_bands_data_handle
{
	/* The current offset
	 */
	off64_t current_offset;

	/* The data size
	 */
	size64_t data_size;

	/* The bands vector
	 */
	libfdata_vector_t *bands_vector;

	/* The bands cache
	 */
	libfcache_cache_t *bands_cache;
};

int libmodi_bands_data_handle_initialize(
     libmodi_bands_data_handle_t **data_handle,
     libmodi_io_handle_t *io_handle,
     libcerror_error_t **error );

int libmodi_bands_data_handle_free(
     libmodi_bands_data_handle_t **data_handle,
     libcerror_error_t **error );

int libmodi_bands_data_handle_append_segment(
     libmodi_bands_data_handle_t *data_handle,
     int segment_file_index,
     off64_t segment_offset,
     size64_t segment_size,
     uint32_t segment_flags,
     libcerror_error_t **error );

ssize_t libmodi_bands_data_handle_read_segment_data(
         libmodi_bands_data_handle_t *data_handle,
         libbfio_handle_t *file_io_handle,
         int segment_index,
         int segment_file_index,
         uint8_t *segment_data,
         size_t segment_data_size,
         uint32_t segment_flags,
         uint8_t read_flags,
         libcerror_error_t **error );

off64_t libmodi_bands_data_handle_seek_segment_offset(
         libmodi_bands_data_handle_t *data_handle,
         intptr_t *file_io_handle,
         int segment_index,
         int segment_file_index,
         off64_t segment_offset,
         libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMODI_BANDS_DATA_HANDLE_H ) */

