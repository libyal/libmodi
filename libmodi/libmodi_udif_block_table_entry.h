/*
 * Universal Disk Image Format (UDIF) block table entry functions
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

#if !defined( _LIBMODI_UDIF_BLOCK_TABLE_ENTRY_H )
#define _LIBMODI_UDIF_BLOCK_TABLE_ENTRY_H

#include <common.h>
#include <types.h>

#include "libmodi_libbfio.h"
#include "libmodi_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libmodi_udif_block_table_entry libmodi_udif_block_table_entry_t;

struct libmodi_udif_block_table_entry
{
	/* The entry type
	 */
	uint32_t type;

	/* The start sector
	 */
	uint64_t start_sector;

	/* The number of sectors
	 */
	uint64_t number_of_sectors;

	/* The data offset
	 */
	uint64_t data_offset;

	/* The data size
	 */
	uint64_t data_size;
};

int libmodi_udif_block_table_entry_initialize(
     libmodi_udif_block_table_entry_t **block_table_entry,
     libcerror_error_t **error );

int libmodi_udif_block_table_entry_free(
     libmodi_udif_block_table_entry_t **block_table_entry,
     libcerror_error_t **error );

int libmodi_udif_block_table_entry_read_data(
     libmodi_udif_block_table_entry_t *block_table_entry,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMODI_UDIF_BLOCK_TABLE_ENTRY_H ) */

