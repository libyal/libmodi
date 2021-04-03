/*
 * Universal Disk Image Format (UDIF) resource file functions
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
#include "libmodi_udif_resource_file.h"

#include "modi_udif_resource_file.h"

/* Creates a resource file
 * Make sure the value resource_file is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libmodi_udif_resource_file_initialize(
     libmodi_udif_resource_file_t **resource_file,
     libcerror_error_t **error )
{
	static char *function = "libmodi_udif_resource_file_initialize";

	if( resource_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource file.",
		 function );

		return( -1 );
	}
	if( *resource_file != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid resource file value already set.",
		 function );

		return( -1 );
	}
	*resource_file = memory_allocate_structure(
	                  libmodi_udif_resource_file_t );

	if( *resource_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create resource file.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *resource_file,
	     0,
	     sizeof( libmodi_udif_resource_file_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear resource file.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *resource_file != NULL )
	{
		memory_free(
		 *resource_file );

		*resource_file = NULL;
	}
	return( -1 );
}

/* Frees a resource file
 * Returns 1 if successful or -1 on error
 */
int libmodi_udif_resource_file_free(
     libmodi_udif_resource_file_t **resource_file,
     libcerror_error_t **error )
{
	static char *function = "libmodi_udif_resource_file_free";

	if( resource_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource file.",
		 function );

		return( -1 );
	}
	if( *resource_file != NULL )
	{
		memory_free(
		 *resource_file );

		*resource_file = NULL;
	}
	return( 1 );
}

/* Reads a resource file
 * Returns 1 if successful, 0 if the signature does not match or -1 on error
 */
int libmodi_udif_resource_file_read_data(
     libmodi_udif_resource_file_t *resource_file,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function       = "libmodi_udif_resource_file_read_data";
	uint32_t number_of_segments = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint64_t value_64bit        = 0;
	uint32_t value_32bit        = 0;
#endif

	if( resource_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource file.",
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
	if( ( data_size < sizeof( modi_udif_resource_file_t ) )
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
		 "%s: resource file data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( modi_udif_resource_file_t ),
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( memory_compare(
	     ( (modi_udif_resource_file_t *) data )->signature,
	     modi_udif_resource_file_signature,
	     4 ) != 0 )
	{
		return( 0 );
	}
	byte_stream_copy_to_uint64_big_endian(
	 ( (modi_udif_resource_file_t *) data )->data_fork_offset,
	 resource_file->data_fork_offset );

	byte_stream_copy_to_uint64_big_endian(
	 ( (modi_udif_resource_file_t *) data )->data_fork_size,
	 resource_file->data_fork_size );

	byte_stream_copy_to_uint64_big_endian(
	 ( (modi_udif_resource_file_t *) data )->resource_fork_offset,
	 resource_file->resource_fork_offset );

	byte_stream_copy_to_uint64_big_endian(
	 ( (modi_udif_resource_file_t *) data )->resource_fork_size,
	 resource_file->resource_fork_size );

	byte_stream_copy_to_uint32_big_endian(
	 ( (modi_udif_resource_file_t *) data )->number_of_segments,
	 number_of_segments );

	byte_stream_copy_to_uint64_big_endian(
	 ( (modi_udif_resource_file_t *) data )->xml_plist_offset,
	 resource_file->xml_plist_offset );

	byte_stream_copy_to_uint64_big_endian(
	 ( (modi_udif_resource_file_t *) data )->xml_plist_size,
	 resource_file->xml_plist_size );

	byte_stream_copy_to_uint32_big_endian(
	 ( (modi_udif_resource_file_t *) data )->number_of_sectors,
	 resource_file->number_of_sectors );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t: %c%c%c%c\n",
		 function,
		 ( (modi_udif_resource_file_t *) data )->signature[ 0 ],
		 ( (modi_udif_resource_file_t *) data )->signature[ 1 ],
		 ( (modi_udif_resource_file_t *) data )->signature[ 2 ],
		 ( (modi_udif_resource_file_t *) data )->signature[ 3 ] );

		byte_stream_copy_to_uint32_big_endian(
		 ( (modi_udif_resource_file_t *) data )->format_version,
		 value_32bit );
		libcnotify_printf(
		 "%s: format version\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_big_endian(
		 ( (modi_udif_resource_file_t *) data )->size,
		 value_32bit );
		libcnotify_printf(
		 "%s: size\t\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_big_endian(
		 ( (modi_udif_resource_file_t *) data )->flags,
		 value_32bit );
		libcnotify_printf(
		 "%s: flags\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint64_big_endian(
		 ( (modi_udif_resource_file_t *) data )->unknown1,
		 value_64bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 value_64bit );

		libcnotify_printf(
		 "%s: data fork offset\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 resource_file->data_fork_offset );

		libcnotify_printf(
		 "%s: data fork size\t\t\t: %" PRIu64 "\n",
		 function,
		 resource_file->data_fork_size );

		libcnotify_printf(
		 "%s: resource fork offset\t\t: 0x%08" PRIx64 "\n",
		 function,
		 resource_file->resource_fork_offset );

		libcnotify_printf(
		 "%s: resource fork size\t\t: %" PRIu64 "\n",
		 function,
		 resource_file->resource_fork_size );

		byte_stream_copy_to_uint32_big_endian(
		 ( (modi_udif_resource_file_t *) data )->unknown2,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown2\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: number of segments\t\t: %" PRIu32 "\n",
		 function,
		 number_of_segments );

		libcnotify_printf(
		 "%s: segment identifier:\n",
		 function );
		libcnotify_print_data(
		 ( (modi_udif_resource_file_t *) data )->segment_identifier,
		 16,
		 0 );

		byte_stream_copy_to_uint32_big_endian(
		 ( (modi_udif_resource_file_t *) data )->data_checksum_type,
		 value_32bit );
		libcnotify_printf(
		 "%s: data checksum type\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_big_endian(
		 ( (modi_udif_resource_file_t *) data )->data_checksum_size,
		 value_32bit );
		libcnotify_printf(
		 "%s: data checksum size\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: data checksum:\n",
		 function );
		libcnotify_print_data(
		 ( (modi_udif_resource_file_t *) data )->data_checksum,
		 128,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );

		libcnotify_printf(
		 "%s: XML plist offset\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 resource_file->xml_plist_offset );

		libcnotify_printf(
		 "%s: XML plist size\t\t\t: %" PRIu64 "\n",
		 function,
		 resource_file->xml_plist_size );

		libcnotify_printf(
		 "%s: unknown3:\n",
		 function );
		libcnotify_print_data(
		 ( (modi_udif_resource_file_t *) data )->unknown3,
		 120,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );

		byte_stream_copy_to_uint32_big_endian(
		 ( (modi_udif_resource_file_t *) data )->master_checksum_type,
		 value_32bit );
		libcnotify_printf(
		 "%s: master checksum type\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_big_endian(
		 ( (modi_udif_resource_file_t *) data )->master_checksum_size,
		 value_32bit );
		libcnotify_printf(
		 "%s: master checksum size\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: master checksum data:\n",
		 function );
		libcnotify_print_data(
		 ( (modi_udif_resource_file_t *) data )->master_checksum,
		 128,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );

		byte_stream_copy_to_uint32_big_endian(
		 ( (modi_udif_resource_file_t *) data )->image_type,
		 value_32bit );
		libcnotify_printf(
		 "%s: image type\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: number of sectors\t\t\t: %" PRIu32 "\n",
		 function,
		 resource_file->number_of_sectors );

		byte_stream_copy_to_uint32_big_endian(
		 ( (modi_udif_resource_file_t *) data )->unknown5,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown5\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_big_endian(
		 ( (modi_udif_resource_file_t *) data )->unknown6,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown6\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_big_endian(
		 ( (modi_udif_resource_file_t *) data )->unknown7,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown7\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( number_of_segments > 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported number of segments.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Reads a resource file
 * Returns 1 if successful, 0 if the signature does not match or -1 on error
 */
int libmodi_udif_resource_file_read_file_io_handle(
     libmodi_udif_resource_file_t *resource_file,
     libbfio_handle_t *file_io_handle,
     off64_t offset,
     libcerror_error_t **error )
{
	uint8_t *resource_file_data = NULL;
	static char *function       = "libmodi_udif_resource_file_read_file_io_handle";
	size_t read_size            = 512;
	ssize_t read_count          = 0;
	int result                  = 0;

	if( resource_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource file.",
		 function );

		return( -1 );
	}
	resource_file_data = (uint8_t *) memory_allocate(
	                                  read_size );

	if( resource_file_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create resource file data.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading resource file at offset: %" PRIi64 " (0x%08" PRIx64 ").\n",
		 function,
		 offset,
		 offset );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              resource_file_data,
	              read_size,
	              offset,
	              error );

	if( read_count != (ssize_t) read_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read resource file data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 offset,
		 offset );

		goto on_error;
	}
	result = libmodi_udif_resource_file_read_data(
	          resource_file,
	          resource_file_data,
	          read_size,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read resource file.",
		 function );

		goto on_error;
	}
	memory_free(
	 resource_file_data );

	resource_file_data = NULL;

	return( result );

on_error:
	if( resource_file_data != NULL )
	{
		memory_free(
		 resource_file_data );
	}
	return( -1 );
}

