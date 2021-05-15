/*
 * The block chunks data handle functions
 *
 * Copyright (C) 2010-2021, Joachim Metz <joachim.metz@gmail.com>
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
#include <memory.h>
#include <types.h>

#include "libmodi_block_chunks_data_handle.h"
#include "libmodi_data_block.h"
#include "libmodi_definitions.h"
#include "libmodi_io_handle.h"
#include "libmodi_libbfio.h"
#include "libmodi_libcerror.h"
#include "libmodi_libcnotify.h"
#include "libmodi_libfdata.h"
#include "libmodi_libfcache.h"
#include "libmodi_unused.h"

/* Creates block chunks data handle
 * Make sure the value data_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libmodi_block_chunks_data_handle_initialize(
     libmodi_block_chunks_data_handle_t **data_handle,
     libmodi_io_handle_t *io_handle,
     libcerror_error_t **error )
{
	static char *function = "libmodi_block_chunks_data_handle_initialize";

	if( data_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data handle.",
		 function );

		return( -1 );
	}
	if( *data_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid data handle value already set.",
		 function );

		return( -1 );
	}
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
	*data_handle = memory_allocate_structure(
	                libmodi_block_chunks_data_handle_t );

	if( *data_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create data handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *data_handle,
	     0,
	     sizeof( libmodi_block_chunks_data_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear data handle.",
		 function );

		memory_free(
		 *data_handle );

		*data_handle = NULL;

		return( -1 );
	}
	if( libfdata_list_initialize(
	     &( ( *data_handle )->block_chunks_list ),
	     (intptr_t *) io_handle,
	     NULL,
	     NULL,
	     (int (*)(intptr_t *, intptr_t *, libfdata_list_element_t *, libfdata_cache_t *, int, off64_t, size64_t, uint32_t, uint8_t, libcerror_error_t **)) &libmodi_data_block_read_list_element_data,
	     NULL,
	     LIBFDATA_DATA_HANDLE_FLAG_NON_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create block chunks list.",
		 function );

		goto on_error;
	}
	if( libfcache_cache_initialize(
	     &( ( *data_handle )->block_chunks_cache ),
	     LIBMODI_MAXIMUM_CACHE_ENTRIES_DATA_BLOCK_CHUNKS,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create block chunks cache.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *data_handle != NULL )
	{
		if( ( *data_handle )->block_chunks_list != NULL )
		{
			libfdata_list_free(
			 &( ( *data_handle )->block_chunks_list ),
			 NULL );
		}
		memory_free(
		 *data_handle );

		*data_handle = NULL;
	}
	return( -1 );
}

/* Frees a data handle
 * Returns 1 if successful or -1 on error
 */
int libmodi_block_chunks_data_handle_free(
     libmodi_block_chunks_data_handle_t **data_handle,
     libcerror_error_t **error )
{
	static char *function = "libmodi_block_chunks_data_handle_free";
	int result            = 1;

	if( data_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data handle.",
		 function );

		return( -1 );
	}
	if( *data_handle != NULL )
	{
		if( libfcache_cache_free(
		     &( ( *data_handle )->block_chunks_cache ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free block chunks cache.",
			 function );

			result = -1;
		}
		if( libfdata_list_free(
		     &( ( *data_handle )->block_chunks_list ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free block chunks list.",
			 function );

			result = -1;
		}
		memory_free(
		 *data_handle );

		*data_handle = NULL;
	}
	return( result );
}

/* Appends a segment
 * Returns 1 if successful or -1 on error
 */
int libmodi_block_chunks_data_handle_append_segment(
     libmodi_block_chunks_data_handle_t *data_handle,
     int segment_file_index,
     off64_t segment_offset,
     size64_t segment_size,
     uint32_t segment_flags,
     size64_t mapped_size,
     libcerror_error_t **error )
{
	static char *function = "libmodi_block_chunks_data_handle_append_segment";
	int element_index     = 0;

	if( data_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data handle.",
		 function );

		return( -1 );
	}
	if( libfdata_list_append_element_with_mapped_size(
	     data_handle->block_chunks_list,
	     &element_index,
	     segment_file_index,
	     segment_offset,
	     segment_size,
	     segment_flags,
	     mapped_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append element to block chunks list.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Reads data from the current offset into a compressed
 * Callback for the data stream
 * Returns the number of bytes read or -1 on error
 */
ssize_t libmodi_block_chunks_data_handle_read_segment_data(
         libmodi_block_chunks_data_handle_t *data_handle,
         libbfio_handle_t *file_io_handle,
         int segment_index,
         int segment_file_index LIBMODI_ATTRIBUTE_UNUSED,
         uint8_t *segment_data,
         size_t segment_data_size,
         uint32_t segment_flags,
         uint8_t read_flags LIBMODI_ATTRIBUTE_UNUSED,
         libcerror_error_t **error )
{
	libmodi_data_block_t *data_block = NULL;
	static char *function            = "libmodi_block_chunks_data_handle_read_segment_data";
	size_t read_size                 = 0;
	size_t segment_data_offset       = 0;
	off64_t element_data_offset      = 0;
	int element_index                = 0;

	LIBMODI_UNREFERENCED_PARAMETER( segment_file_index )
	LIBMODI_UNREFERENCED_PARAMETER( read_flags )

	if( data_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data handle.",
		 function );

		return( -1 );
	}
	if( data_handle->current_offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data handle - current offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( segment_index < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid segment index value out of bounds.",
		 function );

		return( -1 );
	}
	if( segment_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid segment data.",
		 function );

		return( -1 );
	}
	if( segment_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid segment data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( data_handle->data_size == 0 )
	{
		if( libfdata_list_get_size(
		     data_handle->block_chunks_list,
		     &( data_handle->data_size ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve size of block chunks list.",
			 function );

			return( -1 );
		}
	}
	if( (size64_t) data_handle->current_offset >= data_handle->data_size )
	{
		return( 0 );
	}
	if( ( segment_flags & LIBFDATA_RANGE_FLAG_IS_SPARSE ) != 0 )
	{
		if( memory_set(
		     segment_data,
		     0,
		     segment_data_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear segment data.",
			 function );

			return( -1 );
		}
		segment_data_offset = (size_t) segment_data_size;
	}
	else while( segment_data_size > 0 )
	{
		if( libfdata_list_get_element_value_at_offset(
		     data_handle->block_chunks_list,
		     (intptr_t *) file_io_handle,
		     (libfdata_cache_t *) data_handle->block_chunks_cache,
		     data_handle->current_offset,
		     &element_index,
		     &element_data_offset,
		     (intptr_t **) &data_block,
		     0,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data block at offset: %" PRIi64 " (0x%08" PRIx64 ").",
			 function,
			 data_handle->current_offset,
			 data_handle->current_offset );

			return( -1 );
		}
		if( data_block == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid data block.",
			 function );

			return( -1 );
		}
		if( data_block->data == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid data block - missing data.",
			 function );

			return( -1 );
		}
		if( ( element_data_offset < 0 )
		 || ( (size64_t) element_data_offset >= data_block->data_size ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid element data offset value out of bounds.",
			 function );

			return( -1 );
		}
		read_size = data_block->data_size - element_data_offset;

		if( read_size > segment_data_size )
		{
			read_size = segment_data_size;
		}
		if( memory_copy(
		     &( segment_data[ segment_data_offset ] ),
		     &( ( data_block->data )[ element_data_offset ] ),
		     read_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy block data.",
			 function );

			return( -1 );
		}
		segment_data_offset += read_size;
		segment_data_size   -= read_size;

		data_handle->current_offset += read_size;

		if( (size64_t) data_handle->current_offset >= data_handle->data_size )
		{
			break;
		}
	}
	return( (ssize_t) segment_data_offset );
}

/* Seeks a certain offset of the data
 * Callback for the data stream
 * Returns the offset if seek is successful or -1 on error
 */
off64_t libmodi_block_chunks_data_handle_seek_segment_offset(
         libmodi_block_chunks_data_handle_t *data_handle,
         intptr_t *file_io_handle LIBMODI_ATTRIBUTE_UNUSED,
         int segment_index LIBMODI_ATTRIBUTE_UNUSED,
         int segment_file_index LIBMODI_ATTRIBUTE_UNUSED,
         off64_t segment_offset,
         libcerror_error_t **error )
{
	static char *function = "libmodi_block_chunks_data_handle_seek_segment_offset";

	LIBMODI_UNREFERENCED_PARAMETER( file_io_handle )
	LIBMODI_UNREFERENCED_PARAMETER( segment_index )
	LIBMODI_UNREFERENCED_PARAMETER( segment_file_index )

	if( data_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data handle.",
		 function );

		return( -1 );
	}
	if( segment_offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid segment offset value out of bounds.",
		 function );

		return( -1 );
	}
	data_handle->current_offset = segment_offset;

	return( segment_offset );
}

