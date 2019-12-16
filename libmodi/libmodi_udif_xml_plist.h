/*
 * Universal Disk Image Format (UDIF) XML plist functions
 *
 * Copyright (C) 2012-2019, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBMODI_UDIF_XML_PLIST_H )
#define _LIBMODI_UDIF_XML_PLIST_H

#include <common.h>
#include <types.h>

#include "libmodi_libbfio.h"
#include "libmodi_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libmodi_udif_xml_plist libmodi_udif_xml_plist_t;

struct libmodi_udif_xml_plist
{
	/* Dummy
	 */
	int dummy;
};

int libmodi_udif_xml_plist_initialize(
     libmodi_udif_xml_plist_t **udif_xml_plist,
     libcerror_error_t **error );

int libmodi_udif_xml_plist_free(
     libmodi_udif_xml_plist_t **udif_xml_plist,
     libcerror_error_t **error );

int libmodi_udif_xml_plist_read_data(
     libmodi_udif_xml_plist_t *udif_xml_plist,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libmodi_udif_xml_plist_read_file_io_handle(
     libmodi_udif_xml_plist_t *udif_xml_plist,
     libbfio_handle_t *file_io_handle,
     off64_t offset,
     size64_t size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMODI_UDIF_XML_PLIST_H ) */

