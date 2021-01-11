/*
 * Sparse image header functions
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

#include <common.h>
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libmodi_io_handle.h"
#include "libmodi_libbfio.h"
#include "libmodi_libcerror.h"
#include "libmodi_libcnotify.h"
#include "libmodi_sparse_image_header.h"

#include "modi_sparse_image_header.h"

/* Creates a sparse image header
 * Make sure the value sparse_image_header is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libmodi_sparse_image_header_initialize(
     libmodi_sparse_image_header_t **sparse_image_header,
     libcerror_error_t **error )
{
	static char *function = "libmodi_sparse_image_header_initialize";

	if( sparse_image_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sparse image header.",
		 function );

		return( -1 );
	}
	if( *sparse_image_header != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid sparse image header value already set.",
		 function );

		return( -1 );
	}
	*sparse_image_header = memory_allocate_structure(
	                        libmodi_sparse_image_header_t );

	if( *sparse_image_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create sparse image header.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *sparse_image_header,
	     0,
	     sizeof( libmodi_sparse_image_header_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear sparse image header.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *sparse_image_header != NULL )
	{
		memory_free(
		 *sparse_image_header );

		*sparse_image_header = NULL;
	}
	return( -1 );
}

/* Frees a sparse image header
 * Returns 1 if successful or -1 on error
 */
int libmodi_sparse_image_header_free(
     libmodi_sparse_image_header_t **sparse_image_header,
     libcerror_error_t **error )
{
	static char *function = "libmodi_sparse_image_header_free";

	if( sparse_image_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sparse image header.",
		 function );

		return( -1 );
	}
	if( *sparse_image_header != NULL )
	{
		if( ( *sparse_image_header )->band_references != NULL )
		{
			memory_free(
			 ( *sparse_image_header )->band_references );
		}
		memory_free(
		 *sparse_image_header );

		*sparse_image_header = NULL;
	}
	return( 1 );
}

/* Reads a sparse image header
 * Returns 1 if successful, 0 if the signature does not match or -1 on error
 */
int libmodi_sparse_image_header_read_data(
     libmodi_sparse_image_header_t *sparse_image_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function          = "libmodi_sparse_image_header_read_data";
	size_t bands_table_data_size   = 0;
	size_t data_offset             = 0;
	uint32_t bands_table_index     = 0;
	uint32_t bands_table_reference = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit           = 0;
#endif

	if( sparse_image_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sparse image header.",
		 function );

		return( -1 );
	}
	if( sparse_image_header->band_references != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid sparse image header - band references value already set.",
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
	if( ( data_size < sizeof( modi_sparse_image_header_t ) )
	 || ( data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: sparse image header data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( modi_sparse_image_header_t ),
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( memory_compare(
	     ( (modi_sparse_image_header_t *) data )->signature,
	     modi_sparse_image_signature,
	     4 ) != 0 )
	{
		return( 0 );
	}
	byte_stream_copy_to_uint32_big_endian(
	 ( (modi_sparse_image_header_t *) data )->sectors_per_band,
	 sparse_image_header->sectors_per_band );

	byte_stream_copy_to_uint32_big_endian(
	 ( (modi_sparse_image_header_t *) data )->number_of_sectors,
	 sparse_image_header->number_of_sectors );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t: %c%c%c%c\n",
		 function,
		 ( (modi_sparse_image_header_t *) data )->signature[ 0 ],
		 ( (modi_sparse_image_header_t *) data )->signature[ 1 ],
		 ( (modi_sparse_image_header_t *) data )->signature[ 2 ],
		 ( (modi_sparse_image_header_t *) data )->signature[ 3 ] );

		byte_stream_copy_to_uint32_big_endian(
		 ( (modi_sparse_image_header_t *) data )->unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: sectors per band\t\t\t: %" PRIu32 "\n",
		 function,
		 sparse_image_header->sectors_per_band );

		byte_stream_copy_to_uint32_big_endian(
		 ( (modi_sparse_image_header_t *) data )->unknown2,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown2\t\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: number of sectors\t\t: %" PRIu32 "\n",
		 function,
		 sparse_image_header->number_of_sectors );

		libcnotify_printf(
		 "%s: unknown3:\n",
		 function );
		libcnotify_print_data(
		 ( (modi_sparse_image_header_t *) data )->unknown3,
		 12,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );

		byte_stream_copy_to_uint32_big_endian(
		 ( (modi_sparse_image_header_t *) data )->unknown4,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown4\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: unknown5:\n",
		 function );
		libcnotify_print_data(
		 ( (modi_sparse_image_header_t *) data )->unknown5,
		 28,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	data_offset = sizeof( modi_sparse_image_header_t );

	if( sparse_image_header->sectors_per_band == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid sectors per band value out of bounds.",
		 function );

		goto on_error;
	}
	sparse_image_header->number_of_bands = sparse_image_header->number_of_sectors / sparse_image_header->sectors_per_band;

	if( ( sparse_image_header->number_of_sectors % sparse_image_header->sectors_per_band ) != 0 )
	{
		sparse_image_header->number_of_bands += 1;
	}
	if( sparse_image_header->number_of_bands > 0 )
	{
		if( sparse_image_header->number_of_bands > (uint32_t) ( MEMORY_MAXIMUM_ALLOCATION_SIZE / sizeof( uint32_t ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid number of bands value exceeds maximum.",
			 function );

			goto on_error;
		}
		bands_table_data_size = sparse_image_header->number_of_bands * sizeof( uint32_t );

		if( bands_table_data_size > ( data_size - data_offset ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid bands table data size value out of bounds.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: bands table data:\n",
			 function );
			libcnotify_print_data(
			 &( data[ data_offset ] ),
			 bands_table_data_size,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
#endif
		sparse_image_header->band_references = (uint32_t *) memory_allocate(
		                                                     bands_table_data_size );

		if( sparse_image_header->band_references == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create band references.",
			 function );

			goto on_error;
		}
		if( memory_set(
		     sparse_image_header->band_references,
		     0xff,
		     bands_table_data_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear band references.",
			 function );

			goto on_error;
		}
		for( bands_table_index = 0;
		     bands_table_index < sparse_image_header->number_of_bands;
		     bands_table_index++ )
		{
			byte_stream_copy_to_uint32_big_endian(
			 &( data[ data_offset ] ),
			 bands_table_reference );

			data_offset += 4;

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: bands table reference: %03" PRIu32 "\t: 0x%08" PRIx32 " (%" PRIi32 ")\n",
				 function,
				 bands_table_index,
				 bands_table_reference,
				 (int32_t) bands_table_reference );
			}
#endif
			if( bands_table_reference != 0 )
			{
				if( bands_table_reference > sparse_image_header->number_of_bands )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
					 "%s: invalid bands table reference value out of bounds.",
					 function );

					goto on_error;
				}
				( sparse_image_header->band_references )[ bands_table_reference - 1 ] = bands_table_index;
			}
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "\n" );
		}
#endif
	}
	data_offset += bands_table_data_size;

#if defined( HAVE_DEBUG_OUTPUT )
	if( ( libcnotify_verbose != 0 )
	 && ( data_offset < data_size ) )
	{
		libcnotify_printf(
		 "%s: trailing data:\n",
		 function );
		libcnotify_print_data(
		 &( data[ data_offset ] ),
		 data_size - data_offset,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	return( 1 );

on_error:
	if( sparse_image_header->band_references != NULL )
	{
		memory_free(
		 sparse_image_header->band_references );

		sparse_image_header->band_references = 0;
	}
	return( -1 );
}

/* Reads a sparse image header
 * Returns 1 if successful, 0 if the signature does not match or -1 on error
 */
int libmodi_sparse_image_header_read_file_io_handle(
     libmodi_sparse_image_header_t *sparse_image_header,
     libbfio_handle_t *file_io_handle,
     off64_t offset,
     libcerror_error_t **error )
{
	uint8_t *sparse_image_header_data = NULL;
	static char *function             = "libmodi_sparse_image_header_read_file_io_handle";
	size_t read_size                  = 4096;
	ssize_t read_count                = 0;
	int result                        = 0;

	if( sparse_image_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sparse image header.",
		 function );

		return( -1 );
	}
	sparse_image_header_data = (uint8_t *) memory_allocate(
	                                        read_size );

	if( sparse_image_header_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create sparse image header data.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading sparse image header at offset: %" PRIi64 " (0x%08" PRIx64 ").\n",
		 function,
		 offset,
		 offset );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              sparse_image_header_data,
	              read_size,
	              offset,
	              error );

	if( read_count != (ssize_t) read_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read sparse image header data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 offset,
		 offset );

		goto on_error;
	}
	result = libmodi_sparse_image_header_read_data(
	          sparse_image_header,
	          sparse_image_header_data,
	          read_size,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read sparse image header.",
		 function );

		goto on_error;
	}
	memory_free(
	 sparse_image_header_data );

	sparse_image_header_data = NULL;

	return( result );

on_error:
	if( sparse_image_header_data != NULL )
	{
		memory_free(
		 sparse_image_header_data );
	}
	return( -1 );
}

