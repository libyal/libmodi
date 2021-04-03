/*
 * Universal Disk Image Format (UDIF) block table entry functions
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

#include "libmodi_debug.h"
#include "libmodi_libcerror.h"
#include "libmodi_libcnotify.h"
#include "libmodi_udif_block_table_entry.h"

#include "modi_udif_block_table.h"

/* Creates a block table entry entry
 * Make sure the value block_table_entry is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libmodi_udif_block_table_entry_initialize(
     libmodi_udif_block_table_entry_t **block_table_entry,
     libcerror_error_t **error )
{
	static char *function = "libmodi_udif_block_table_entry_initialize";

	if( block_table_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block table entry.",
		 function );

		return( -1 );
	}
	if( *block_table_entry != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid block table entry value already set.",
		 function );

		return( -1 );
	}
	*block_table_entry = memory_allocate_structure(
	                      libmodi_udif_block_table_entry_t );

	if( *block_table_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create block table entry.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *block_table_entry,
	     0,
	     sizeof( libmodi_udif_block_table_entry_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear block table entry.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *block_table_entry != NULL )
	{
		memory_free(
		 *block_table_entry );

		*block_table_entry = NULL;
	}
	return( -1 );
}

/* Frees a block table entry
 * Returns 1 if successful or -1 on error
 */
int libmodi_udif_block_table_entry_free(
     libmodi_udif_block_table_entry_t **block_table_entry,
     libcerror_error_t **error )
{
	static char *function = "libmodi_udif_block_table_entry_free";

	if( block_table_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block table entry.",
		 function );

		return( -1 );
	}
	if( *block_table_entry != NULL )
	{
		memory_free(
		 *block_table_entry );

		*block_table_entry = NULL;
	}
	return( 1 );
}

/* Reads a block table entry
 * Returns 1 if successful or -1 on error
 */
int libmodi_udif_block_table_entry_read_data(
     libmodi_udif_block_table_entry_t *block_table_entry,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libmodi_udif_block_table_entry_read_data";

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit  = 0;
#endif

	if( block_table_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block table entry.",
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
	if( ( data_size < sizeof( modi_udif_block_table_entry_t ) )
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
		 "%s: block table entry data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 data_size,
		 0 );
	}
#endif
	byte_stream_copy_to_uint32_big_endian(
	 ( (modi_udif_block_table_entry_t *) data )->type,
	 block_table_entry->type );

	byte_stream_copy_to_uint64_big_endian(
	 ( (modi_udif_block_table_entry_t *) data )->start_sector,
	 block_table_entry->start_sector );

	byte_stream_copy_to_uint64_big_endian(
	 ( (modi_udif_block_table_entry_t *) data )->number_of_sectors,
	 block_table_entry->number_of_sectors );

	byte_stream_copy_to_uint64_big_endian(
	 ( (modi_udif_block_table_entry_t *) data )->data_offset,
	 block_table_entry->data_offset );

	byte_stream_copy_to_uint64_big_endian(
	 ( (modi_udif_block_table_entry_t *) data )->data_size,
	 block_table_entry->data_size );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: type\t\t\t\t: 0x%08" PRIx32 " (%s)\n",
		 function,
		 block_table_entry->type,
		 libmodi_debug_get_udif_block_table_entry_type(
		  block_table_entry->type ) );

		byte_stream_copy_to_uint32_big_endian(
		 ( (modi_udif_block_table_entry_t *) data )->unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: start sector\t\t\t: %" PRIu64 "\n",
		 function,
		 block_table_entry->start_sector );

		libcnotify_printf(
		 "%s: number of sectors\t\t: %" PRIu64 "\n",
		 function,
		 block_table_entry->number_of_sectors );

		libcnotify_printf(
		 "%s: data offset\t\t\t: %" PRIu64 "\n",
		 function,
		 block_table_entry->data_offset );

		libcnotify_printf(
		 "%s: data size\t\t\t: %" PRIu64 "\n",
		 function,
		 block_table_entry->data_size );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );
}

