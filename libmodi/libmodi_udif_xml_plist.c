/*
 * Universal Disk Image Format (UDIF) XML plist functions
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
#include <memory.h>
#include <types.h>

#include "libmodi_libbfio.h"
#include "libmodi_libcerror.h"
#include "libmodi_libcnotify.h"
#include "libmodi_libfplist.h"
#include "libmodi_udif_block_table.h"
#include "libmodi_udif_xml_plist.h"

/* Creates a UDIF XML plist
 * Make sure the value udif_xml_plist is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libmodi_udif_xml_plist_initialize(
     libmodi_udif_xml_plist_t **udif_xml_plist,
     libcerror_error_t **error )
{
	static char *function = "libmodi_udif_xml_plist_initialize";

	if( udif_xml_plist == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UDIF XML plist.",
		 function );

		return( -1 );
	}
	if( *udif_xml_plist != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid UDIF XML plist value already set.",
		 function );

		return( -1 );
	}
	*udif_xml_plist = memory_allocate_structure(
	                   libmodi_udif_xml_plist_t );

	if( *udif_xml_plist == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create UDIF XML plist.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *udif_xml_plist,
	     0,
	     sizeof( libmodi_udif_xml_plist_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear UDIF XML plist.",
		 function );

		memory_free(
		 *udif_xml_plist );

		*udif_xml_plist = NULL;

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( ( *udif_xml_plist )->block_tables_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create block tables array.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *udif_xml_plist != NULL )
	{
		memory_free(
		 *udif_xml_plist );

		*udif_xml_plist = NULL;
	}
	return( -1 );
}

/* Frees a UDIF XML plist
 * Returns 1 if successful or -1 on error
 */
int libmodi_udif_xml_plist_free(
     libmodi_udif_xml_plist_t **udif_xml_plist,
     libcerror_error_t **error )
{
	static char *function = "libmodi_udif_xml_plist_free";
	int result            = 1;

	if( udif_xml_plist == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UDIF XML plist.",
		 function );

		return( -1 );
	}
	if( *udif_xml_plist != NULL )
	{
		if( libcdata_array_free(
		     &( ( *udif_xml_plist )->block_tables_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libmodi_udif_block_table_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free block tables array.",
			 function );

			result = -1;
		}
		memory_free(
		 *udif_xml_plist );

		*udif_xml_plist = NULL;
	}
	return( result );
}

/* Reads an UDIF XML plist blkx array property
 * Returns 1 if successful or -1 on error
 */
int libmodi_udif_xml_plist_read_blkx_array_property(
     libmodi_udif_xml_plist_t *udif_xml_plist,
     libfplist_property_t *array_property,
     libcerror_error_t **error )
{
	libfplist_property_t *array_entry_property = NULL;
	static char *function                      = "libmodi_udif_xml_plist_read_blkx_array_property";
	int entry_index                            = 0;
	int number_of_entries                      = 0;

	if( udif_xml_plist == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UDIF XML plist.",
		 function );

		return( -1 );
	}
	if( libfplist_property_get_array_number_of_entries(
	     array_property,
	     &number_of_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries in array property.",
		 function );

		goto on_error;
	}
	for( entry_index = 0;
	     entry_index < number_of_entries;
	     entry_index++ )
	{
		if( libfplist_property_get_array_entry_by_index(
		     array_property,
		     entry_index,
		     &array_entry_property,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve entry: %d from array property.",
			 function,
			 entry_index );

			goto on_error;
		}
		if( libmodi_udif_xml_plist_read_blkx_array_entry_property(
		     udif_xml_plist,
		     array_entry_property,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read array entry: %d property.",
			 function,
			 entry_index );

			goto on_error;
		}
		if( libfplist_property_free(
		     &array_entry_property,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free array entry: %d property.",
			 function,
			 entry_index );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( array_entry_property != NULL )
	{
		libfplist_property_free(
		 &array_entry_property,
		 NULL );
	}
	return( -1 );
}

/* Reads an UDIF XML plist blkx array entry property
 * Returns 1 if successful or -1 on error
 */
int libmodi_udif_xml_plist_read_blkx_array_entry_property(
     libmodi_udif_xml_plist_t *udif_xml_plist,
     libfplist_property_t *array_entry_property,
     libcerror_error_t **error )
{
	libfplist_property_t *data_property     = NULL;
	libmodi_udif_block_table_t *block_table = NULL;
	uint8_t *data                           = NULL;
	static char *function                   = "libmodi_udif_xml_plist_read_blkx_array_entry_property";
	size_t data_size                        = 0;
	int entry_index                         = 0;
	int result                              = 0;

	if( udif_xml_plist == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UDIF XML plist.",
		 function );

		return( -1 );
	}
	result = libfplist_property_get_sub_property_by_utf8_name(
	          array_entry_property,
	          (uint8_t *) "Data",
	          4,
	          &data_property,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data property.",
		 function );

		goto on_error;
	}
	else if( result != 0 )
	{
		if( libfplist_property_get_value_data_size(
		     data_property,
		     &data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve value data size of data from data property.",
			 function );

			goto on_error;
		}
		if( ( data_size == 0 )
		 || ( data_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid data property - value data size value out of bounds.",
			 function );

			goto on_error;
		}
		data = (uint8_t *) memory_allocate(
		                    sizeof( uint8_t ) * data_size );

		if( data == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create data.",
			 function );

			goto on_error;
		}
		if( libfplist_property_get_value_data(
		     data_property,
		     data,
		     data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve value data from data property.",
			 function );

			goto on_error;
		}
		if( libmodi_udif_block_table_initialize(
		     &block_table,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create block table.",
			 function );

			goto on_error;
		}
		if( libmodi_udif_block_table_read_data(
		     block_table,
		     data,
		     data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read block table.",
			 function );

			goto on_error;
		}
		/* block_table->entries_array takes over management of block_table_entry
		 */
		if( libcdata_array_append_entry(
		     udif_xml_plist->block_tables_array,
		     &entry_index,
		     (intptr_t *) block_table,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append block table to array.",
			 function );

			goto on_error;
		}
		block_table = NULL;

		memory_free(
		 data );

		data = NULL;

		if( libfplist_property_free(
		     &data_property,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free data property.",
			 function );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( block_table != NULL )
	{
		libmodi_udif_block_table_free(
		 &block_table,
		 NULL );
	}
	if( data != NULL )
	{
		memory_free(
		 data );
	}
	if( data_property != NULL )
	{
		libfplist_property_free(
		 &data_property,
		 NULL );
	}
	return( -1 );
}

/* Reads an UDIF XML plist
 * Returns 1 if successful or -1 on error
 */
int libmodi_udif_xml_plist_read_data(
     libmodi_udif_xml_plist_t *udif_xml_plist,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libfplist_property_t *blkx_array_property    = NULL;
	libfplist_property_t *resource_fork_property = NULL;
	libfplist_property_t *root_property          = NULL;
	libfplist_property_list_t *xml_plist         = NULL;
	static char *function                        = "libmodi_udif_xml_plist_read_data";
	int result                                   = 0;

	if( udif_xml_plist == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UDIF XML plist.",
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
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( libfplist_property_list_initialize(
	     &xml_plist,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create property list.",
		 function );

		goto on_error;
	}
	result = libfplist_property_list_copy_from_byte_stream(
	          xml_plist,
	          data,
	          data_size,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy property list from byte stream.",
		 function );

		goto on_error;
	}
	else if( result != 0 )
	{
		if( libfplist_property_list_get_root_property(
		     xml_plist,
		     &root_property,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve root property.",
			 function );

			goto on_error;
		}
		result = libfplist_property_get_sub_property_by_utf8_name(
		          root_property,
		          (uint8_t *) "resource-fork",
		          13,
		          &resource_fork_property,
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve resource-fork property.",
			 function );

			goto on_error;
		}
		else if( result != 0 )
		{
			result = libfplist_property_get_sub_property_by_utf8_name(
			          resource_fork_property,
			          (uint8_t *) "blkx",
			          4,
			          &blkx_array_property,
			          error );

			if( result == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve blkx array property.",
				 function );

				goto on_error;
			}
			else if( result != 0 )
			{
				if( libmodi_udif_xml_plist_read_blkx_array_property(
				     udif_xml_plist,
				     blkx_array_property,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_IO,
					 LIBCERROR_IO_ERROR_READ_FAILED,
					 "%s: unable to read blkx array property.",
					 function );

					goto on_error;
				}
				if( libfplist_property_free(
				     &blkx_array_property,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable to free blkx property.",
					 function );

					goto on_error;
				}
			}
			if( libfplist_property_free(
			     &resource_fork_property,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free resource-fork property.",
				 function );

				goto on_error;
			}
		}
		if( libfplist_property_free(
		     &root_property,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free root property.",
			 function );

			goto on_error;
		}
	}
	if( libfplist_property_list_free(
	     &xml_plist,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free property list.",
		 function );

		goto on_error;
	}
	return( result );

on_error:
	if( blkx_array_property != NULL )
	{
		libfplist_property_free(
		 &blkx_array_property,
		 NULL );
	}
	if( resource_fork_property != NULL )
	{
		libfplist_property_free(
		 &resource_fork_property,
		 NULL );
	}
	if( root_property != NULL )
	{
		libfplist_property_free(
		 &root_property,
		 NULL );
	}
	if( xml_plist != NULL )
	{
		libfplist_property_list_free(
		 &xml_plist,
		 NULL );
	}
	return( -1 );
}

/* Reads an UDIF XML plist
 * Returns 1 if successful, 0 if the signature does not match or -1 on error
 */
int libmodi_udif_xml_plist_read_file_io_handle(
     libmodi_udif_xml_plist_t *udif_xml_plist,
     libbfio_handle_t *file_io_handle,
     off64_t offset,
     size64_t size,
     libcerror_error_t **error )
{
	uint8_t header_data[ 5 ];

	uint8_t *xml_plist_data = NULL;
	static char *function   = "libmodi_udif_xml_plist_read_file_io_handle";
	ssize_t read_count      = 0;
	int result              = 0;

	if( udif_xml_plist == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UDIF XML plist.",
		 function );

		return( -1 );
	}
	if( ( size == 0 )
	 || ( size > (size64_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
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
		 "%s: reading UDIF XML plist at offset: %" PRIi64 " (0x%08" PRIx64 ").\n",
		 function,
		 offset,
		 offset );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              header_data,
	              5,
	              offset,
	              error );

	if( read_count != (ssize_t) 5 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read UDIF XML plist data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 offset,
		 offset );

		goto on_error;
	}
	if( ( header_data[ 0 ] != '<' )
	 || ( header_data[ 1 ] != '?' )
	 || ( header_data[ 2 ] != 'x' )
	 || ( header_data[ 3 ] != 'm' )
	 || ( header_data[ 4 ] != 'l' ) )
	{
		return( 0 );
	}
	xml_plist_data = (uint8_t *) memory_allocate(
	                              sizeof( uint8_t ) * (size_t) size );

	if( xml_plist_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create XML plist data.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              xml_plist_data,
	              (size_t) size,
	              offset,
	              error );

	if( read_count != (ssize_t) size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read UDIF XML plist data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 offset,
		 offset );

		goto on_error;
	}
	result = libmodi_udif_xml_plist_read_data(
	          udif_xml_plist,
	          xml_plist_data,
	          (size_t) size,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read UDIF XML plist.",
		 function );

		goto on_error;
	}
	memory_free(
	 xml_plist_data );

	xml_plist_data = NULL;

	return( result );

on_error:
	if( xml_plist_data != NULL )
	{
		memory_free(
		 xml_plist_data );
	}
	return( -1 );
}

/* Retrieves the number of block tables
 * Returns 1 if successful or -1 on error
 */
int libmodi_udif_xml_plist_get_number_of_block_tables(
     libmodi_udif_xml_plist_t *xml_plist,
     int *number_of_block_tables,
     libcerror_error_t **error )
{
	static char *function = "libmodi_udif_xml_plist_get_number_of_block_tables";

	if( xml_plist == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UDIF XML plist.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     xml_plist->block_tables_array,
	     number_of_block_tables,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries from block tables array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific block table
 * Returns 1 if successful or -1 on error
 */
int libmodi_udif_xml_plist_get_block_table_by_index(
     libmodi_udif_xml_plist_t *xml_plist,
     int block_table_index,
     libmodi_udif_block_table_t **block_table,
     libcerror_error_t **error )
{
	static char *function = "libmodi_udif_xml_plist_get_block_table_by_index";

	if( xml_plist == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UDIF XML plist.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     xml_plist->block_tables_array,
	     block_table_index,
	     (intptr_t **) block_table,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry: %d from block tables array.",
		 function,
		 block_table_index );

		return( -1 );
	}
	return( 1 );
}

