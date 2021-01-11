/*
 * Universal Disk Image Format (UDIF) block table functions
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

#if !defined( _LIBMODI_UDIF_BLOCK_TABLE_H )
#define _LIBMODI_UDIF_BLOCK_TABLE_H

#include <common.h>
#include <types.h>

#include "libmodi_libbfio.h"
#include "libmodi_libcdata.h"
#include "libmodi_libcerror.h"
#include "libmodi_udif_block_table_entry.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libmodi_udif_block_table libmodi_udif_block_table_t;

struct libmodi_udif_block_table
{
	/* The start sector
	 */
	uint64_t start_sector;

	/* The entries array
	 */
	libcdata_array_t *entries_array;
};

int libmodi_udif_block_table_initialize(
     libmodi_udif_block_table_t **block_table,
     libcerror_error_t **error );

int libmodi_udif_block_table_free(
     libmodi_udif_block_table_t **block_table,
     libcerror_error_t **error );

int libmodi_udif_block_table_read_data(
     libmodi_udif_block_table_t *block_table,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libmodi_udif_block_table_get_number_of_entries(
     libmodi_udif_block_table_t *block_table,
     int *number_of_entries,
     libcerror_error_t **error );

int libmodi_udif_block_table_get_entry_by_index(
     libmodi_udif_block_table_t *block_table,
     int entry_index,
     libmodi_udif_block_table_entry_t **block_table_entry,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMODI_UDIF_BLOCK_TABLE_H ) */

