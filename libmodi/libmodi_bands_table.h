/*
 * Bands table functions
 *
 * Copyright (C) 2012-2016, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBMODI_BANDS_TABLE_H )
#define _LIBMODI_BANDS_TABLE_H

#include <common.h>
#include <types.h>

#include "libmodi_libbfio.h"
#include "libmodi_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libmodi_bands_table libmodi_bands_table_t;

struct libmodi_bands_table
{
	/* The number of references
 	 */
	int number_of_references;

	/* The references
	 */
	uint32_t *references;

	/* The size
	 */
	size_t size;
};

int libmodi_bands_table_initialize(
     libmodi_bands_table_t **bands_table,
     libcerror_error_t **error );

int libmodi_bands_table_free(
     libmodi_bands_table_t **bands_table,
     libcerror_error_t **error );

int libmodi_bands_table_get_number_of_references(
     libmodi_bands_table_t *bands_table,
     int *number_of_references,
     libcerror_error_t **error );

int libmodi_bands_table_get_reference_by_index(
     libmodi_bands_table_t *bands_table,
     int reference_index,
     uint32_t *reference,
     libcerror_error_t **error );

int libmodi_bands_table_read(
     libmodi_bands_table_t *bands_table,
     const uint8_t *data,
     size_t data_size,
     uint32_t number_of_bands,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMODI_BANDS_TABLE_H ) */

