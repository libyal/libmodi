/*
 * Universal Disk Image Format (UDIF) block table functions
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

#include <common.h>
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libmodi_libcerror.h"
#include "libmodi_libcnotify.h"
#include "libmodi_udif_block_table.h"

#include "modi_udif_block_table.h"

const uint8_t modi_udif_block_table_signature[ 4 ] = {
	'm', 'i', 's', 'h' };

/* Creates an UDIF block table
 * Make sure the value udif_block_table is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libmodi_udif_block_table_initialize(
     libmodi_udif_block_table_t **udif_block_table,
     libcerror_error_t **error )
{
	static char *function = "libmodi_udif_block_table_initialize";

	if( udif_block_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UDIF block table.",
		 function );

		return( -1 );
	}
	if( *udif_block_table != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid UDIF block table value already set.",
		 function );

		return( -1 );
	}
	*udif_block_table = memory_allocate_structure(
	                     libmodi_udif_block_table_t );

	if( *udif_block_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create UDIF block table.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *udif_block_table,
	     0,
	     sizeof( libmodi_udif_block_table_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear UDIF block table.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *udif_block_table != NULL )
	{
		memory_free(
		 *udif_block_table );

		*udif_block_table = NULL;
	}
	return( -1 );
}

/* Frees an UDIF block table
 * Returns 1 if successful or -1 on error
 */
int libmodi_udif_block_table_free(
     libmodi_udif_block_table_t **udif_block_table,
     libcerror_error_t **error )
{
	static char *function = "libmodi_udif_block_table_free";

	if( udif_block_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UDIF block table.",
		 function );

		return( -1 );
	}
	if( *udif_block_table != NULL )
	{
		memory_free(
		 *udif_block_table );

		*udif_block_table = NULL;
	}
	return( 1 );
}

/* Reads an UDIF block table
 * Returns 1 if successful or -1 on error
 */
int libmodi_udif_block_table_read_data(
     libmodi_udif_block_table_t *udif_block_table,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function      = "libmodi_udif_block_table_read_data";
	size_t data_offset         = 0;
	uint32_t entry_index       = 0;
	uint32_t nubmer_of_entries = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint64_t value_64bit       = 0;
	uint32_t value_32bit       = 0;
#endif

	if( udif_block_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UDIF block table.",
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
	if( ( data_size < sizeof( modi_udif_block_table_header_t ) )
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
		 "%s: UDIF block table data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( memory_compare(
	     ( (modi_udif_block_table_header_t *) data )->signature,
	     modi_udif_block_table_signature,
	     4 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported signature.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint32_big_endian(
	 ( (modi_udif_block_table_header_t *) data )->number_of_entries,
	 nubmer_of_entries );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t: %c%c%c%c\n",
		 function,
		 ( (modi_udif_block_table_header_t *) data )->signature[ 0 ],
		 ( (modi_udif_block_table_header_t *) data )->signature[ 1 ],
		 ( (modi_udif_block_table_header_t *) data )->signature[ 2 ],
		 ( (modi_udif_block_table_header_t *) data )->signature[ 3 ] );

		byte_stream_copy_to_uint32_big_endian(
		 ( (modi_udif_block_table_header_t *) data )->format_version,
		 value_32bit );
		libcnotify_printf(
		 "%s: format version\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint64_big_endian(
		 ( (modi_udif_block_table_header_t *) data )->start_sector,
		 value_64bit );
		libcnotify_printf(
		 "%s: start sector\t\t\t: %" PRIu64 "\n",
		 function,
		 value_64bit );

		byte_stream_copy_to_uint64_big_endian(
		 ( (modi_udif_block_table_header_t *) data )->number_of_sectors,
		 value_64bit );
		libcnotify_printf(
		 "%s: number of sectors\t\t\t: %" PRIu64 "\n",
		 function,
		 value_64bit );

		byte_stream_copy_to_uint64_big_endian(
		 ( (modi_udif_block_table_header_t *) data )->data_offset,
		 value_64bit );
		libcnotify_printf(
		 "%s: data offset\t\t\t\t: %" PRIu64 "\n",
		 function,
		 value_64bit );

		byte_stream_copy_to_uint32_big_endian(
		 ( (modi_udif_block_table_header_t *) data )->unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_big_endian(
		 ( (modi_udif_block_table_header_t *) data )->number_of_descriptors,
		 value_32bit );
		libcnotify_printf(
		 "%s: number of descriptors\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_big_endian(
		 ( (modi_udif_block_table_header_t *) data )->unknown2,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown2\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_big_endian(
		 ( (modi_udif_block_table_header_t *) data )->unknown3,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown3\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_big_endian(
		 ( (modi_udif_block_table_header_t *) data )->unknown4,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown4\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_big_endian(
		 ( (modi_udif_block_table_header_t *) data )->unknown5,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown5\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_big_endian(
		 ( (modi_udif_block_table_header_t *) data )->unknown6,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown6\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_big_endian(
		 ( (modi_udif_block_table_header_t *) data )->unknown7,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown7\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: checksum:\n",
		 function );
		libcnotify_print_data(
		 ( (modi_udif_block_table_header_t *) data )->checksum,
		 136,
		 0 );

		libcnotify_printf(
		 "%s: number of entries\t\t\t: %" PRIu32 "\n",
		 function,
		 nubmer_of_entries );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	data_offset = sizeof( modi_udif_block_table_header_t );

	for( entry_index = 0;
	     entry_index < nubmer_of_entries;
	     entry_index++ )
	{
		if( data_offset > ( data_size - sizeof( modi_udif_block_table_entry_t ) ) )
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
			 "%s: table entry: %" PRIu32 "\n",
			 function,
			 entry_index );
			libcnotify_print_data(
			 &( data[ data_offset ] ),
			 sizeof( modi_udif_block_table_entry_t ),
			 0 );
		}
#endif

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			byte_stream_copy_to_uint32_big_endian(
			 ( (modi_udif_block_table_entry_t *) &( data[ data_offset ] ) )->type,
			 value_32bit );
			libcnotify_printf(
			 "%s: type\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_big_endian(
			 ( (modi_udif_block_table_entry_t *) &( data[ data_offset ] ) )->unknown1,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown1\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint64_big_endian(
			 ( (modi_udif_block_table_entry_t *) &( data[ data_offset ] ) )->start_sector,
			 value_64bit );
			libcnotify_printf(
			 "%s: start sector\t\t\t: %" PRIu64 "\n",
			 function,
			 value_64bit );

			byte_stream_copy_to_uint64_big_endian(
			 ( (modi_udif_block_table_entry_t *) &( data[ data_offset ] ) )->number_of_sectors,
			 value_64bit );
			libcnotify_printf(
			 "%s: number of sectors\t\t\t: %" PRIu64 "\n",
			 function,
			 value_64bit );

			byte_stream_copy_to_uint64_big_endian(
			 ( (modi_udif_block_table_entry_t *) &( data[ data_offset ] ) )->data_offset,
			 value_64bit );
			libcnotify_printf(
			 "%s: data offset\t\t\t\t: %" PRIu64 "\n",
			 function,
			 value_64bit );

			byte_stream_copy_to_uint64_big_endian(
			 ( (modi_udif_block_table_entry_t *) &( data[ data_offset ] ) )->data_size,
			 value_64bit );
			libcnotify_printf(
			 "%s: data size\t\t\t\t: %" PRIu64 "\n",
			 function,
			 value_64bit );

			libcnotify_printf(
			 "\n" );
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

		data_offset += sizeof( modi_udif_block_table_entry_t );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( data_offset < data_size )
		{
			libcnotify_printf(
			 "%s: trailing data:\n",
			 function );
			libcnotify_print_data(
			 &( data[ data_offset ] ),
			 data_size - data_offset,
			 0 );
		}
	}
#endif
	return( 1 );
}

