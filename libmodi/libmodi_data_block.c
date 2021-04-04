/*
 * Data block functions
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

#include "libmodi_compression.h"
#include "libmodi_data_block.h"
#include "libmodi_definitions.h"
#include "libmodi_io_handle.h"
#include "libmodi_libbfio.h"
#include "libmodi_libcerror.h"
#include "libmodi_libcnotify.h"
#include "libmodi_libfdata.h"
#include "libmodi_unused.h"

/* Creates a data block
 * Make sure the value data_block is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libmodi_data_block_initialize(
     libmodi_data_block_t **data_block,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libmodi_data_block_initialize";

	if( data_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data block.",
		 function );

		return( -1 );
	}
	if( *data_block != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid data block value already set.",
		 function );

		return( -1 );
	}
	if( ( data_size == 0 )
	 || ( data_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
	*data_block = memory_allocate_structure(
	               libmodi_data_block_t );

	if( *data_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create data block.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *data_block,
	     0,
	     sizeof( libmodi_data_block_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear data block.",
		 function );

		memory_free(
		 *data_block );

		*data_block = NULL;

		return( -1 );
	}
	( *data_block )->data = (uint8_t *) memory_allocate(
	                                     sizeof( uint8_t ) * data_size );

	if( ( *data_block )->data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create data.",
		 function );

		goto on_error;
	}
	( *data_block )->data_size = data_size;

	return( 1 );

on_error:
	if( *data_block != NULL )
	{
		memory_free(
		 *data_block );

		*data_block = NULL;
	}
	return( -1 );
}

/* Frees a data block
 * Returns 1 if successful or -1 on error
 */
int libmodi_data_block_free(
     libmodi_data_block_t **data_block,
     libcerror_error_t **error )
{
	static char *function = "libmodi_data_block_free";
	int result            = 1;

	if( data_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data block.",
		 function );

		return( -1 );
	}
	if( *data_block != NULL )
	{
		memory_free(
		 ( *data_block )->data );

		memory_free(
		 *data_block );

		*data_block = NULL;
	}
	return( result );
}

/* Clears a data block
 * Returns 1 if successful or -1 on error
 */
int libmodi_data_block_clear(
     libmodi_data_block_t *data_block,
     libcerror_error_t **error )
{
	static char *function = "libmodi_data_block_clear";

	if( data_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
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
	if( memory_set(
	     data_block->data,
	     0,
	     data_block->data_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear data block data.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Reads data block
 * Returns 1 if successful or -1 on error
 */
int libmodi_data_block_read_file_io_handle(
     libmodi_data_block_t *data_block,
     libbfio_handle_t *file_io_handle,
     off64_t data_block_offset,
     libcerror_error_t **error )
{
	static char *function = "libmodi_data_block_read_file_io_handle";
	ssize_t read_count    = 0;

	if( data_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data block.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading data block at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 data_block_offset,
		 data_block_offset );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              data_block->data,
	              data_block->data_size,
	              data_block_offset,
	              error );

	if( read_count != (ssize_t) data_block->data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read data block at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 data_block_offset,
		 data_block_offset );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data block:\n",
		 function );
		libcnotify_print_data(
		 data_block->data,
		 data_block->data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	return( 1 );
}

/* Reads a data block
 * Callback function for the block chunks list
 * Returns 1 if successful or -1 on error
 */
int libmodi_data_block_read_list_element_data(
     libmodi_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfdata_list_element_t *element,
     libfdata_cache_t *cache,
     int element_data_file_index LIBMODI_ATTRIBUTE_UNUSED,
     off64_t element_data_offset,
     size64_t element_data_size,
     uint32_t element_data_flags,
     uint8_t read_flags LIBMODI_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	libmodi_data_block_t *data_block = NULL;
	static char *function            = "libmodi_data_block_read_list_element_data";
	uint8_t *compressed_data         = NULL;
	size64_t mapped_size             = 0;
	size_t uncompressed_data_size    = 0;
	ssize_t read_count               = 0;

	LIBMODI_UNREFERENCED_PARAMETER( element_data_file_index )
	LIBMODI_UNREFERENCED_PARAMETER( read_flags )

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
	if( ( element_data_flags & LIBFDATA_RANGE_FLAG_IS_COMPRESSED ) != 0 )
	{
		if( ( element_data_size == 0 )
		 || ( element_data_size > (size64_t) SSIZE_MAX ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid element data size value out of bounds.",
			 function );

			return( -1 );
		}
	}
	if( libfdata_list_element_get_mapped_size(
	     element,
	     &mapped_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve mapped size from element.",
		 function );

		goto on_error;
	}
	if( ( mapped_size == 0 )
	 || ( mapped_size > (size64_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid block chunk data size value out of bounds.",
		 function );

		goto on_error;
	}
	if( libmodi_data_block_initialize(
	     &data_block,
	     (size_t) mapped_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create data block.",
		 function );

		goto on_error;
	}
	if( ( element_data_flags & LIBFDATA_RANGE_FLAG_IS_SPARSE ) != 0 )
	{
		if( memory_set(
		     data_block->data,
		     0,
		     data_block->data_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear data block.",
			 function );

			goto on_error;
		}
	}
	else if( ( element_data_flags & LIBFDATA_RANGE_FLAG_IS_COMPRESSED ) != 0 )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: reading compressed block chunk at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
			 function,
			 element_data_offset,
			 element_data_offset );
		}
#endif
		compressed_data = (uint8_t *) memory_allocate(
		                               sizeof( uint8_t ) * element_data_size );

		if( compressed_data == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create compressed data.",
			 function );

			goto on_error;
		}
		read_count = libbfio_handle_read_buffer_at_offset(
		              file_io_handle,
		              compressed_data,
		              element_data_size,
		              element_data_offset,
		              error );

		if( read_count != (ssize_t) element_data_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read compressed block chunk at offset: %" PRIi64 " (0x%08" PRIx64 ").",
			 function,
			 element_data_offset,
			 element_data_offset );

			goto on_error;
		}
		uncompressed_data_size = data_block->data_size;

		if( libmodi_decompress_data(
		     compressed_data,
		     (size_t) read_count,
		     io_handle->compression_method,
		     data_block->data,
		     &uncompressed_data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ENCRYPTION,
			 LIBCERROR_ENCRYPTION_ERROR_GENERIC,
			 "%s: unable to decompress block chunk at offset: %" PRIi64 " (0x%08" PRIx64 ").",
			 function,
			 element_data_offset,
			 element_data_offset );

			goto on_error;
		}
		memory_free(
		 compressed_data );

		compressed_data = NULL;
	}
	else
	{
		if( libmodi_data_block_read_file_io_handle(
		     data_block,
		     file_io_handle,
		     element_data_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read data block at offset: %" PRIi64 " (0x%08" PRIx64 ").",
			 function,
			 element_data_offset,
			 element_data_offset );

			goto on_error;
		}
	}
	if( libfdata_list_element_set_element_value(
	     element,
	     (intptr_t *) file_io_handle,
	     cache,
	     (intptr_t *) data_block,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libmodi_data_block_free,
	     LIBFDATA_LIST_ELEMENT_VALUE_FLAG_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set data block as element value.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( compressed_data != NULL )
	{
		memory_free(
		 compressed_data );
	}
	if( data_block != NULL )
	{
		libmodi_data_block_free(
		 &data_block,
		 NULL );
	}
	return( -1 );
}

/* Reads a data block
 * Callback function for the data block vector
 * Returns 1 if successful or -1 on error
 */
int libmodi_data_block_read_vector_element_data(
     libmodi_io_handle_t *io_handle,
     intptr_t *file_io_handle,
     libfdata_vector_t *vector,
     libfdata_cache_t *cache,
     int element_index,
     int element_data_file_index,
     off64_t element_data_offset,
     size64_t element_data_size,
     uint32_t element_data_flags,
     uint8_t read_flags LIBMODI_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	libbfio_handle_t *bfio_handle    = NULL;
	libmodi_data_block_t *data_block = NULL;
	static char *function            = "libmodi_data_block_read_vector_element_data";

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
	if( ( io_handle->image_type != LIBMODI_IMAGE_TYPE_SPARSE_BUNDLE )
	 && ( element_data_file_index != 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid element data file index value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( element_data_size == 0 )
	 || ( element_data_size > (size64_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid element data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( libmodi_data_block_initialize(
	     &data_block,
	     (size_t) element_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create data block.",
		 function );

		goto on_error;
	}
	if( ( element_data_flags & LIBFDATA_RANGE_FLAG_IS_SPARSE ) != 0 )
	{
		if( memory_set(
		     data_block->data,
		     0,
		     data_block->data_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear data block.",
			 function );

			goto on_error;
		}
	}
	else
	{
		if( io_handle->image_type != LIBMODI_IMAGE_TYPE_SPARSE_BUNDLE )
		{
			bfio_handle = (libbfio_handle_t *) file_io_handle;
		}
		else if( libbfio_pool_get_handle(
		          (libbfio_pool_t *) file_io_handle,
		          element_data_file_index,
		          &bfio_handle,
		          error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve handle: %d from file IO pool.",
			 function,
			 element_data_file_index );

			goto on_error;
		}
		if( libmodi_data_block_read_file_io_handle(
		     data_block,
		     bfio_handle,
		     element_data_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read data block at offset: %" PRIi64 " (0x%08" PRIx64 ").",
			 function,
			 element_data_offset,
			 element_data_offset );

			goto on_error;
		}
	}
	if( libfdata_vector_set_element_value_by_index(
	     vector,
	     (intptr_t *) file_io_handle,
	     cache,
	     element_index,
	     (intptr_t *) data_block,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libmodi_data_block_free,
	     LIBFDATA_LIST_ELEMENT_VALUE_FLAG_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set data block as element value.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( data_block != NULL )
	{
		libmodi_data_block_free(
		 &data_block,
		 NULL );
	}
	return( -1 );
}

