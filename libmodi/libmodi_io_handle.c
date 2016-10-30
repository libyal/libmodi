/*
 * Input/Output (IO) handle functions
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

#include "libmodi_bands_table.h"
#include "libmodi_data_band.h"
#include "libmodi_definitions.h"
#include "libmodi_io_handle.h"
#include "libmodi_libbfio.h"
#include "libmodi_libcerror.h"
#include "libmodi_libcnotify.h"
#include "libmodi_libfcache.h"
#include "libmodi_libfdata.h"
#include "libmodi_libuna.h"
#include "libmodi_unused.h"

#include "modi_sparse_image_header.h"

const uint8_t *modi_sparse_image_signature = (uint8_t *) "sprs";

/* Creates an IO handle
 * Make sure the value io_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libmodi_io_handle_initialize(
     libmodi_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libmodi_io_handle_initialize";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( *io_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid IO handle value already set.",
		 function );

		return( -1 );
	}
	*io_handle = memory_allocate_structure(
	              libmodi_io_handle_t );

	if( *io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create IO handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *io_handle,
	     0,
	     sizeof( libmodi_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		memory_free(
		 *io_handle );

		*io_handle = NULL;

		return( -1 );
	}
	( *io_handle )->image_type = LIBMODI_IMAGE_TYPE_DMG;

	return( 1 );

on_error:
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( -1 );
}

/* Frees an IO handle
 * Returns 1 if successful or -1 on error
 */
int libmodi_io_handle_free(
     libmodi_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libmodi_io_handle_free";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( 1 );
}

/* Clears the IO handle
 * Returns 1 if successful or -1 on error
 */
int libmodi_io_handle_clear(
     libmodi_io_handle_t *io_handle,
     libcerror_error_t **error )
{
	static char *function = "libmodi_io_handle_clear";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( memory_set(
	     io_handle,
	     0,
	     sizeof( libmodi_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Reads the sparse image header
 * Returns 1 if successful or -1 on error
 */
int libmodi_io_handle_read_sparse_image_header(
     libmodi_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libmodi_bands_table_t *data_bands_table,
     libcerror_error_t **error )
{
	uint8_t *file_header_data   = NULL;
	static char *function       = "libmodi_io_handle_read_sparse_image_header";
	size_t band_array_data_size = 0;
	size_t file_header_offset   = 0;
	size_t file_header_size     = 4096;
	ssize_t read_count          = 0;
	uint32_t number_of_bands    = 0;
	uint32_t number_of_sectors  = 0;
	uint32_t sectors_per_band   = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	size_t trailing_data_size   = 0;
	uint32_t value_32bit        = 0;
#endif

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading file header at offset: 0.\n",
		 function );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     0,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek file header offset: 0.",
		 function );

		goto on_error;
	}
	file_header_data = (uint8_t *) memory_allocate(
	                                file_header_size );

	if( file_header_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create file header data.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              file_header_data,
	              file_header_size,
	              error );

	if( read_count != (ssize_t) file_header_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file header.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: file header data:\n",
		 function );
		libcnotify_print_data(
		 file_header_data,
		 sizeof( modi_sparse_image_header_t ),
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( memory_compare(
	     ( (modi_sparse_image_header_t *) file_header_data )->signature,
	     modi_sparse_image_signature,
	     4 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported file signature.",
		 function );

		goto on_error;
	}
	io_handle->image_type = LIBMODI_IMAGE_TYPE_SPARSE_IMAGE;

	byte_stream_copy_to_uint32_big_endian(
	 ( (modi_sparse_image_header_t *) file_header_data )->sectors_per_band,
	 sectors_per_band );

	byte_stream_copy_to_uint32_big_endian(
	 ( (modi_sparse_image_header_t *) file_header_data )->number_of_sectors,
	 number_of_sectors );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t: %c%c%c%c\n",
		 function,
		 ( (modi_sparse_image_header_t *) file_header_data )->signature[ 0 ],
		 ( (modi_sparse_image_header_t *) file_header_data )->signature[ 1 ],
		 ( (modi_sparse_image_header_t *) file_header_data )->signature[ 2 ],
		 ( (modi_sparse_image_header_t *) file_header_data )->signature[ 3 ] );

		byte_stream_copy_to_uint32_big_endian(
		 ( (modi_sparse_image_header_t *) file_header_data )->unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: sectors per band\t\t: %" PRIu32 "\n",
		 function,
		 sectors_per_band );

		byte_stream_copy_to_uint32_big_endian(
		 ( (modi_sparse_image_header_t *) file_header_data )->unknown2,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown2\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: number of sectors\t\t: %" PRIu32 "\n",
		 function,
		 number_of_sectors );

		libcnotify_printf(
		 "%s: unknown3:\n",
		 function );
		libcnotify_print_data(
		 ( (modi_sparse_image_header_t *) file_header_data )->unknown3,
		 12,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );

		byte_stream_copy_to_uint32_big_endian(
		 ( (modi_sparse_image_header_t *) file_header_data )->unknown4,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown4\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: unknown5:\n",
		 function );
		libcnotify_print_data(
		 ( (modi_sparse_image_header_t *) file_header_data )->unknown5,
		 28,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	file_header_offset = sizeof( modi_sparse_image_header_t );

	if( sectors_per_band == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid sectors per band value out of bounds.",
		 function );

		goto on_error;
	}
	io_handle->media_size        = (size64_t) number_of_sectors * 512;
	io_handle->bands_data_offset = (off64_t) file_header_size;
	io_handle->bands_data_size   = (size64_t) sectors_per_band * 512;

	number_of_bands = number_of_sectors / sectors_per_band;

	if( ( number_of_sectors % sectors_per_band ) != 0 )
	{
		number_of_bands++;
	}
/* TODO check bounds number of bands */
/* TODO check if file size matches 4096 + media_size */

	if( number_of_bands > 0 )
	{
		if( libmodi_bands_table_read(
		     data_bands_table,
		     &( file_header_data[ file_header_offset ] ),
		     band_array_data_size,
		     number_of_bands,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read data bands table.",
			 function );

			goto on_error;
		}
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		trailing_data_size = file_header_size - file_header_offset;

		if( trailing_data_size > 0 )
		{
			libcnotify_printf(
			 "%s: trailing data:\n",
			 function );
			libcnotify_print_data(
			 &( file_header_data[ file_header_offset ] ),
			 trailing_data_size,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
	}
#endif
	memory_free(
	 file_header_data );

	file_header_data = NULL;

	return( 1 );

on_error:
	if( file_header_data != NULL )
	{
		memory_free(
		 file_header_data );
	}
	return( -1 );
}

/* Reads a data band
 * Callback function for the data band vector
 * Returns 1 if successful or -1 on error
 */
int libmodi_io_handle_read_data_band(
     libmodi_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfdata_vector_t *vector,
     libfcache_cache_t *cache,
     int element_index,
     int element_data_file_index,
     off64_t element_data_offset,
     size64_t element_data_size,
     uint32_t element_data_flags LIBMODI_ATTRIBUTE_UNUSED,
     uint8_t read_flags LIBMODI_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	libmodi_data_band_t *data_band = NULL;
	static char *function          = "libmodi_io_handle_read_data_band";

	LIBMODI_UNREFERENCED_PARAMETER( element_data_flags );
	LIBMODI_UNREFERENCED_PARAMETER( read_flags );

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( element_data_file_index != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid element data file index value out of bounds.",
		 function );

		goto on_error;
	}
	if( element_data_size > (size64_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid element data size value exceeds maximum.",
		 function );

		goto on_error;
	}
	if( libmodi_data_band_initialize(
	     &data_band,
	     (size_t) element_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create data band.",
		 function );

		goto on_error;
	}
	if( libmodi_data_band_read(
	     data_band,
	     file_io_handle,
             element_data_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read data band.",
		 function );

		goto on_error;
	}
	if( libfdata_vector_set_element_value_by_index(
	     vector,
	     (intptr_t *) file_io_handle,
	     cache,
	     element_index,
	     (intptr_t *) data_band,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libmodi_data_band_free,
	     LIBFDATA_LIST_ELEMENT_VALUE_FLAG_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set data band as element value.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( data_band != NULL )
	{
		libmodi_data_band_free(
		 &data_band,
		 NULL );
	}
	return( -1 );
}

