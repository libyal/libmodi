/*
 * Bands table functions
 *
 * Copyright (C) 2012-2018, Joachim Metz <joachim.metz@gmail.com>
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

#include <common.h>
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libmodi_bands_table.h"
#include "libmodi_libbfio.h"
#include "libmodi_libcerror.h"
#include "libmodi_libcnotify.h"

/* Creates a bands table
 * Make sure the value bands_table is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libmodi_bands_table_initialize(
     libmodi_bands_table_t **bands_table,
     libcerror_error_t **error )
{
	static char *function = "libmodi_bands_table_initialize";

	if( bands_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid bands table.",
		 function );

		return( -1 );
	}
	if( *bands_table != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid bands table value already set.",
		 function );

		return( -1 );
	}
	*bands_table = memory_allocate_structure(
	                libmodi_bands_table_t );

	if( *bands_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create bands table.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *bands_table,
	     0,
	     sizeof( libmodi_bands_table_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear bands table.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *bands_table != NULL )
	{
		memory_free(
		 *bands_table );

		*bands_table = NULL;
	}
	return( -1 );
}

/* Frees a bands table
 * Returns 1 if successful or -1 on error
 */
int libmodi_bands_table_free(
     libmodi_bands_table_t **bands_table,
     libcerror_error_t **error )
{
	static char *function = "libmodi_bands_table_free";

	if( bands_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid bands table.",
		 function );

		return( -1 );
	}
	if( *bands_table != NULL )
	{
		if( ( *bands_table )->references != NULL )
		{
			memory_free(
			 ( *bands_table )->references );
		}
		memory_free(
		 *bands_table );

		*bands_table = NULL;
	}
	return( 1 );
}

/* Retrieves the number of references in the bands table
 * Returns 1 if successful or -1 on error
 */
int libmodi_bands_table_get_number_of_references(
     libmodi_bands_table_t *bands_table,
     int *number_of_references,
     libcerror_error_t **error )
{
	static char *function = "libmodi_bands_table_get_number_of_references";

	if( bands_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid bands table.",
		 function );

		return( -1 );
	}
	if( number_of_references == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of references.",
		 function );

		return( -1 );
	}
	*number_of_references = bands_table->number_of_references;

	return( 1 );
}

/* Retrieves a specific reference from the bands table
 * Returns 1 if successful or -1 on error
 */
int libmodi_bands_table_get_reference_by_index(
     libmodi_bands_table_t *bands_table,
     int reference_index,
     uint32_t *reference,
     libcerror_error_t **error )
{
	static char *function = "libmodi_bands_table_get_reference_by_index";

	if( bands_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid bands table.",
		 function );

		return( -1 );
	}
	if( bands_table->references == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid bands table - missing references.",
		 function );

		return( -1 );
	}
	if( ( reference_index < 0 )
	 || ( reference_index >= bands_table->number_of_references ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid reference index value out of bounds.",
		 function );

		return( -1 );
	}
	if( reference == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid reference.",
		 function );

		return( -1 );
	}
	*reference = bands_table->references[ reference_index ];

	return( 1 );
}

/* Reads the bands table
 * Returns 1 if successful or -1 on error
 */
int libmodi_bands_table_read_data(
     libmodi_bands_table_t *bands_table,
     const uint8_t *data,
     size_t data_size,
     uint32_t number_of_bands,
     libcerror_error_t **error )
{
	static char *function          = "libmodi_bands_table_read_data";
	size_t data_offset             = 0;
	uint32_t bands_table_reference = 0;
	int bands_table_index          = 0;

	if( bands_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid bands table.",
		 function );

		return( -1 );
	}
	if( bands_table->references != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid bands table - references already set.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( (size_t) number_of_bands > (size_t) ( SSIZE_MAX / 4 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid number of bands value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( number_of_bands == 0 )
	{
		return( 1 );
	}
	bands_table->data_size = number_of_bands * sizeof( uint32_t );

	if( bands_table->data_size > data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid bands table - data size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: bands table data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 bands_table->data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	bands_table->number_of_references = (int) number_of_bands;

	bands_table->references = (uint32_t *) memory_allocate(
	                                        bands_table->data_size );

	if( bands_table->references == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create references.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     bands_table->references,
	     0xff,
	     bands_table->data_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear references.",
		 function );

		goto on_error;
	}
	for( bands_table_index = 0;
	     bands_table_index < bands_table->number_of_references;
	     bands_table_index++ )
	{
		byte_stream_copy_to_uint32_big_endian(
		 &( data[ data_offset ] ),
		 bands_table_reference );

		data_offset += 4;

/* TODO check bounds of reference */

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: bands table reference: %03d\t\t\t: %" PRIu32 "\n",
			 function,
			 bands_table_index,
			 bands_table_reference );
		}
#endif
		if( bands_table_reference != 0 )
		{
			( bands_table->references )[ bands_table_reference - 1 ] = bands_table_index;
		}
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "\n" );
	}
#endif
	return( 1 );

on_error:
	if( bands_table->references != NULL )
	{
		memory_free(
		 bands_table->references );

		bands_table->references = NULL;
	}
	return( -1 );
}

