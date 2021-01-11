/*
 * Sparse bundle XML plist functions
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

#if !defined( _LIBMODI_SPARSE_BUNDLE_XML_PLIST_H )
#define _LIBMODI_SPARSE_BUNDLE_XML_PLIST_H

#include <common.h>
#include <types.h>

#include "libmodi_libbfio.h"
#include "libmodi_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libmodi_sparse_bundle_xml_plist libmodi_sparse_bundle_xml_plist_t;

struct libmodi_sparse_bundle_xml_plist
{
	/* The band data size
	 */
	uint64_t band_data_size;

	/* The number of bands
	 */
	uint64_t number_of_bands;

	/* The media size
	 */
	uint64_t media_size;
};

int libmodi_sparse_bundle_xml_plist_initialize(
     libmodi_sparse_bundle_xml_plist_t **sparse_bundle_xml_plist,
     libcerror_error_t **error );

int libmodi_sparse_bundle_xml_plist_free(
     libmodi_sparse_bundle_xml_plist_t **sparse_bundle_xml_plist,
     libcerror_error_t **error );

int libmodi_sparse_bundle_xml_plist_read_data(
     libmodi_sparse_bundle_xml_plist_t *sparse_bundle_xml_plist,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libmodi_sparse_bundle_xml_plist_read_file_io_handle(
     libmodi_sparse_bundle_xml_plist_t *sparse_bundle_xml_plist,
     libbfio_handle_t *file_io_handle,
     off64_t offset,
     size64_t size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMODI_SPARSE_BUNDLE_XML_PLIST_H ) */

