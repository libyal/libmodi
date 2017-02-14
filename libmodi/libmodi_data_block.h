/*
 * Data block functions
 *
 * Copyright (C) 2012-2017, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBMODI_DATA_BLOCK_H )
#define _LIBMODI_DATA_BLOCK_H

#include <common.h>
#include <types.h>

#include "libmodi_libbfio.h"
#include "libmodi_libcerror.h"

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

int libmodi_data_block_read(
     libmodi_data_block_t *data_block,
     libbfio_handle_t *file_io_handle,
     off64_t data_offset,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMODI_DATA_BLOCK_H ) */

