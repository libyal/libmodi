/*
 * Data block functions
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

#if !defined( _LIBMODI_DATA_BLOCK_H )
#define _LIBMODI_DATA_BLOCK_H

#include <common.h>
#include <types.h>

#include "libmodi_io_handle.h"
#include "libmodi_libbfio.h"
#include "libmodi_libcerror.h"
#include "libmodi_libfdata.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libmodi_data_block libmodi_data_block_t;

struct libmodi_data_block
{
	/* The data
	 */
	uint8_t *data;

	/* The data size
	 */
	size_t data_size;
};

int libmodi_data_block_initialize(
     libmodi_data_block_t **data_block,
     size_t data_size,
     libcerror_error_t **error );

int libmodi_data_block_free(
     libmodi_data_block_t **data_block,
     libcerror_error_t **error );

int libmodi_data_block_clear(
     libmodi_data_block_t *data_block,
     libcerror_error_t **error );

int libmodi_data_block_read_file_io_handle(
     libmodi_data_block_t *data_block,
     libbfio_handle_t *file_io_handle,
     off64_t data_offset,
     libcerror_error_t **error );

int libmodi_data_block_read_list_element_data(
     libmodi_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfdata_list_element_t *element,
     libfdata_cache_t *cache,
     int element_data_file_index,
     off64_t element_data_offset,
     size64_t element_data_size,
     uint32_t element_data_flags,
     uint8_t read_flags,
     libcerror_error_t **error );

int libmodi_data_block_read_vector_element_data(
     libmodi_io_handle_t *io_handle,
     intptr_t *file_io_handle,
     libfdata_vector_t *vector,
     libfdata_cache_t *cache,
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

#endif /* !defined( _LIBMODI_DATA_BLOCK_H ) */

