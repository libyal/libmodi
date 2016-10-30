/*
 * Data band functions
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

#include <common.h>
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libmodi_data_band.h"
#include "libmodi_libbfio.h"
#include "libmodi_libcerror.h"
#include "libmodi_libcnotify.h"

/* Creates a data band
 * Make sure the value data_band is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libmodi_data_band_initialize(
     libmodi_data_band_t **data_band,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libmodi_data_band_initialize";

	if( data_band == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data band.",
		 function );

		return( -1 );
	}
	if( *data_band != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid data band value already set.",
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
	*data_band = memory_allocate_structure(
	              libmodi_data_band_t );

	if( *data_band == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create data band.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *data_band,
	     0,
	     sizeof( libmodi_data_band_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear data band.",
		 function );

		memory_free(
		 *data_band );

		*data_band = NULL;

		return( -1 );
	}
	if( data_size > 0 )
	{
		( *data_band )->data = (uint8_t *) memory_allocate(
		                                    sizeof( uint8_t ) * data_size );

		if( ( *data_band )->data == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create data.",
			 function );

			goto on_error;
		}
		( *data_band )->data_size = data_size;
	}
	return( 1 );

on_error:
	if( *data_band != NULL )
	{
		memory_free(
		 *data_band );

		*data_band = NULL;
	}
	return( -1 );
}

/* Frees a data band
 * Returns 1 if successful or -1 on error
 */
int libmodi_data_band_free(
     libmodi_data_band_t **data_band,
     libcerror_error_t **error )
{
	static char *function = "libmodi_data_band_free";
	int result            = 1;

	if( data_band == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data band.",
		 function );

		return( -1 );
	}
	if( *data_band != NULL )
	{
		if( ( *data_band )->data != NULL )
		{
			if( memory_set(
			     ( *data_band )->data,
			     0,
			     ( *data_band )->data_size ) == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_SET_FAILED,
				 "%s: unable to clear data.",
				 function );

				result = -1;
			}
			memory_free(
			 ( *data_band )->data );
		}
		memory_free(
		 *data_band );

		*data_band = NULL;
	}
	return( result );
}

/* Reads data band
 * Returns 1 if successful or -1 on error
 */
int libmodi_data_band_read(
     libmodi_data_band_t *data_band,
     libbfio_handle_t *file_io_handle,
     off64_t data_band_offset,
     libcerror_error_t **error )
{
	static char *function = "libmodi_data_band_read";
	ssize_t read_count    = 0;

	if( data_band == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data band.",
		 function );

		return( -1 );
	}
	if( data_band->data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data band - missing data.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading data band at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 data_band_offset,
		 data_band_offset );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     data_band_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek data band offset: %" PRIi64 ".",
		 function,
		 data_band_offset );

		return( -1 );
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              data_band->data,
	              data_band->data_size,
	              error );

	if( read_count != (ssize_t) data_band->data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read data band.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data band:\n",
		 function );
		libcnotify_print_data(
		 data_band->data,
		 data_band->data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	return( 1 );
}

