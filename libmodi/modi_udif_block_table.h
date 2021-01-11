/*
 * The block table of the Mac OS Universal Disk Image Format (UDIF)
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

#if !defined( _MODI_UDIF_BLOCK_TABLE_H )
#define _MODI_UDIF_BLOCK_TABLE_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct modi_udif_block_table_header modi_udif_block_table_header_t;

struct modi_udif_block_table_header
{
	/* The signature
	 * Consists of 4 bytes
	 * Consists of: mish
	 */
	uint8_t signature[ 4 ];

	/* The format version
	 * Consists of 4 bytes
	 */
	uint8_t format_version[ 4 ];

	/* The start sector
	 * Consists of 8 bytes
	 */
	uint8_t start_sector[ 8 ];

	/* The number of sectors
	 * Consists of 8 bytes
	 */
	uint8_t number_of_sectors[ 8 ];

	/* The data offset
	 * Consists of 8 bytes
	 */
	uint8_t data_offset[ 8 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* The number of descriptors
	 * Consists of 4 bytes
	 */
	uint8_t number_of_descriptors[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown2[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown3[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown4[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown5[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown6[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown7[ 4 ];

	/* The checksum
	 * Consists of 136 bytes
	 */
	uint8_t checksum[ 136 ];

	/* The number of entries
	 * Consists of 4 bytes
	 */
	uint8_t number_of_entries[ 4 ];
};

typedef struct modi_udif_block_table_entry modi_udif_block_table_entry_t;

struct modi_udif_block_table_entry
{
	/* The entry type
	 * Consists of 4 bytes
	 */
	uint8_t type[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* The start sector
	 * Consists of 8 bytes
	 */
	uint8_t start_sector[ 8 ];

	/* The number of sectors
	 * Consists of 8 bytes
	 */
	uint8_t number_of_sectors[ 8 ];

	/* The data offset
	 * Consists of 8 bytes
	 */
	uint8_t data_offset[ 8 ];

	/* The data size
	 * Consists of 8 bytes
	 */
	uint8_t data_size[ 8 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _MODI_UDIF_BLOCK_TABLE_H ) */

