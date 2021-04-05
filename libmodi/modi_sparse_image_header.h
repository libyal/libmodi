/*
 * The file header definition of the Mac OS sparse disk image format
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

#if !defined( _MODI_SPARSE_IMAGE_HEADER_H )
#define _MODI_SPARSE_IMAGE_HEADER_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

static uint8_t modi_sparse_image_signature[ 4 ] = {
	's', 'p', 'r', 's' };

typedef struct modi_sparse_image_header modi_sparse_image_header_t;

struct modi_sparse_image_header
{
	/* The signature
	 * Consists of 4 bytes
	 * Consists of: sprs
	 */
	uint8_t signature[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* The sectors per band
	 * Consists of 4 bytes
	 */
	uint8_t sectors_per_band[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown2[ 4 ];

	/* The total number of sectors
	 * Consists of 4 bytes
	 */
	uint8_t number_of_sectors[ 4 ];

	/* Unknown
	 * Consists of 12 bytes
	 */
	uint8_t unknown3[ 12 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown4[ 4 ];

	/* Unknown
	 * Consists of 28 bytes
	 */
	uint8_t unknown5[ 28 ];

	/* Array of band indexes
	 */
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _MODI_SPARSE_IMAGE_HEADER_H ) */

