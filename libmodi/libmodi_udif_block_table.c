/*
 * Universal Disk Image Format (UDIF) block table functions
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

#include "libmodi_definitions.h"
#include "libmodi_libcdata.h"
#include "libmodi_libcerror.h"
#include "libmodi_libcnotify.h"
#include "libmodi_udif_block_table.h"
#include "libmodi_udif_block_table_entry.h"

#include "modi_udif_block_table.h"

const uint8_t modi_udif_block_table_signature[ 4 ] = {
	'm', 'i', 's', 'h' };

/* Creates a block table
 * Make sure the value udif_block_table is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libmodi_udif_block_table_initialize(
     libmodi_udif_block_table_t **block_table,
     libcerror_error_t **error )
{
	static char *function = "libmodi_udif_block_table_initialize";

	if( block_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block table.",
		 function );

		return( -1 );
	}
	if( *block_table != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid block table value already set.",
		 function );

		return( -1 );
	}
	*block_table = memory_allocate_structure(
	                libmodi_udif_block_table_t );

	if( *block_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create block table.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *block_table,
	     0,
	     sizeof( libmodi_udif_block_table_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear block table.",
		 function );

		memory_free(
		 *block_table );

		*block_table = NULL;

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( ( *block_table )->entries_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create entries array.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *block_table != NULL )
	{
		memory_free(
		 *block_table );

		*block_table = NULL;
	}
	return( -1 );
}

/* Frees a block table
 * Returns 1 if successful or -1 on error
 */
int libmodi_udif_block_table_free(
     libmodi_udif_block_table_t **block_table,
     libcerror_error_t **error )
{
	static char *function = "libmodi_udif_block_table_free";
	int result            = 1;

	if( block_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block table.",
		 function );

		return( -1 );
	}
	if( *block_table != NULL )
	{
		if( libcdata_array_free(
		     &( ( *block_table )->entries_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libmodi_udif_block_table_entry_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free entries array.",
			 function );

			result = -1;
		}
		memory_free(
		 *block_table );

		*block_table = NULL;
	}
	return( result );
}

/* Reads a block table
 * Returns 1 if successful or -1 on error
 */
int libmodi_udif_block_table_read_data(
     libmodi_udif_block_table_t *block_table,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libmodi_udif_block_table_entry_t *block_table_entry = NULL;
	static char *function                               = "libmodi_udif_block_table_read_data";
	size_t data_offset                                  = 0;
	uint64_t calculated_number_of_sectors               = 0;
	uint64_t number_of_sectors                          = 0;
	uint32_t block_table_entry_index                    = 0;
	uint32_t format_version                             = 0;
	uint32_t number_of_entries                          = 0;
	int entry_index                                     = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint64_t value_64bit                                = 0;
	uint32_t value_32bit                                = 0;
#endif

	if( block_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block table.",
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
		 "%s: block table data:\n",
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

		goto on_error;
	}
	byte_stream_copy_to_uint32_big_endian(
	 ( (modi_udif_block_table_header_t *) data )->format_version,
	 format_version );

	byte_stream_copy_to_uint64_big_endian(
	 ( (modi_udif_block_table_header_t *) data )->start_sector,
	 block_table->start_sector );

	byte_stream_copy_to_uint64_big_endian(
	 ( (modi_udif_block_table_header_t *) data )->number_of_sectors,
	 number_of_sectors );

	byte_stream_copy_to_uint32_big_endian(
	 ( (modi_udif_block_table_header_t *) data )->number_of_entries,
	 number_of_entries );

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

		libcnotify_printf(
		 "%s: format version\t\t\t: %" PRIu32 "\n",
		 function,
		 format_version );

		libcnotify_printf(
		 "%s: start sector\t\t\t: %" PRIu64 "\n",
		 function,
		 block_table->start_sector );

		libcnotify_printf(
		 "%s: number of sectors\t\t\t: %" PRIu64 "\n",
		 function,
		 number_of_sectors );

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
		 number_of_entries );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( format_version != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported format version.",
		 function );

		goto on_error;
	}
	data_offset = sizeof( modi_udif_block_table_header_t );

	for( block_table_entry_index = 0;
	     block_table_entry_index < number_of_entries;
	     block_table_entry_index++ )
	{
		if( data_offset > ( data_size - sizeof( modi_udif_block_table_entry_t ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid data size value out of bounds.",
			 function );

			goto on_error;
		}
		if( libmodi_udif_block_table_entry_initialize(
		     &block_table_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create block table entry.",
			 function );

			goto on_error;
		}
		if( libmodi_udif_block_table_entry_read_data(
		     block_table_entry,
		     &( data[ data_offset ] ),
		     sizeof( modi_udif_block_table_entry_t ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read block table entry.",
			 function );

			goto on_error;
		}
		if( ( block_table_entry_index + 1 ) == number_of_entries )
		{
			if( block_table_entry->type != LIBMODI_UDIF_BLOCK_TABLE_ENTRY_TYPE_TERMINATOR )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
				 "%s: unsupported last block table entry type.",
				 function );

				goto on_error;
			}
		}
		if( block_table_entry->start_sector != calculated_number_of_sectors )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: mismatch between start sector and number of sectors.",
			 function );

			goto on_error;
		}
		if( block_table_entry->type != LIBMODI_UDIF_BLOCK_TABLE_ENTRY_TYPE_TERMINATOR )
		{
			calculated_number_of_sectors += block_table_entry->number_of_sectors;

			/* block_table->entries_array takes over management of block_table_entry
			 */
			if( libcdata_array_append_entry(
			     block_table->entries_array,
			     &entry_index,
			     (intptr_t *) block_table_entry,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to append entry to array.",
				 function );

				goto on_error;
			}
			block_table_entry = NULL;
		}
		else
		{
			if( libmodi_udif_block_table_entry_free(
			     &block_table_entry,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free block table entry.",
				 function );

				goto on_error;
			}
		}
		data_offset += sizeof( modi_udif_block_table_entry_t );
	}
	if( number_of_sectors != calculated_number_of_sectors )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: mismatch between number of sectors in header and in table.",
		 function );

		goto on_error;
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

on_error:
	if( block_table_entry != NULL )
	{
		libmodi_udif_block_table_entry_free(
		 &block_table_entry,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the number of entries
 * Returns 1 if successful or -1 on error
 */
int libmodi_udif_block_table_get_number_of_entries(
     libmodi_udif_block_table_t *block_table,
     int *number_of_entries,
     libcerror_error_t **error )
{
	static char *function = "libmodi_udif_block_table_get_number_of_entries";

	if( block_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block table.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     block_table->entries_array,
	     number_of_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries from entries array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific entry
 * Returns 1 if successful or -1 on error
 */
int libmodi_udif_block_table_get_entry_by_index(
     libmodi_udif_block_table_t *block_table,
     int entry_index,
     libmodi_udif_block_table_entry_t **block_table_entry,
     libcerror_error_t **error )
{
	static char *function = "libmodi_udif_block_table_get_entry_by_index";

	if( block_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block table.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     block_table->entries_array,
	     entry_index,
	     (intptr_t **) block_table_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry: %d from entries array.",
		 function,
		 entry_index );

		return( -1 );
	}
	return( 1 );
}

