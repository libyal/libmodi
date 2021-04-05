/*
 * The resource file definition of the Mac OS Universal Disk Image Format (UDIF)
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

#if !defined( _MODI_UDIF_RESOURCE_FILE_H )
#define _MODI_UDIF_RESOURCE_FILE_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

static uint8_t modi_udif_resource_file_signature[ 4 ] = {
	'k', 'o', 'l', 'y' };

typedef struct modi_udif_resource_file modi_udif_resource_file_t;

struct modi_udif_resource_file
{
	/* The signature
	 * Consists of 4 bytes
	 * Consists of: koly
	 */
	uint8_t signature[ 4 ];

	/* The format version
	 * Consists of 4 bytes
	 */
	uint8_t format_version[ 4 ];

	/* The size
	 * Consists of 4 bytes
	 */
	uint8_t size[ 4 ];

	/* The flags
	 * Consists of 4 bytes
	 */
	uint8_t flags[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown1[ 8 ];

	/* The data fork offset
	 * Consists of 8 bytes
	 */
	uint8_t data_fork_offset[ 8 ];

	/* The data fork size
	 * Consists of 8 bytes
	 */
	uint8_t data_fork_size[ 8 ];

	/* The resource fork offset
	 * Consists of 8 bytes
	 */
	uint8_t resource_fork_offset[ 8 ];

	/* The resource fork size
	 * Consists of 8 bytes
	 */
	uint8_t resource_fork_size[ 8 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown2[ 4 ];

	/* The number of segments
	 * Consists of 4 bytes
	 */
	uint8_t number_of_segments[ 4 ];

	/* The segment identifier
	 * Consists of 16 bytes
	 * Contains an UUID
	 */
	uint8_t segment_identifier[ 16 ];

	/* The data checkum type
	 * Consists of 4 bytes
	 */
	uint8_t data_checksum_type[ 4 ];

	/* The data checkum size
	 * Consists of 4 bytes
	 */
	uint8_t data_checksum_size[ 4 ];

	/* The data checkum
	 * Consists of 128 bytes
	 */
	uint8_t data_checksum[ 128 ];

	/* The XML plist offset
	 * Consists of 8 bytes
	 */
	uint8_t xml_plist_offset[ 8 ];

	/* The XML plist size
	 * Consists of 8 bytes
	 */
	uint8_t xml_plist_size[ 8 ];

	/* Unknown
	 * Consists of 120 bytes
	 */
	uint8_t unknown3[ 120 ];

	/* The master checkum type
	 * Consists of 4 bytes
	 */
	uint8_t master_checksum_type[ 4 ];

	/* The master checkum size
	 * Consists of 4 bytes
	 */
	uint8_t master_checksum_size[ 4 ];

	/* The master checkum
	 * Consists of 128 bytes
	 */
	uint8_t master_checksum[ 128 ];

	/* The image type
	 * Consists of 4 bytes
	 */
	uint8_t image_type[ 4 ];

	/* The number of sectors
	 * Consists of 8 bytes
	 */
	uint8_t number_of_sectors[ 8 ];

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
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _MODI_UDIF_RESOURCE_FILE_H ) */

