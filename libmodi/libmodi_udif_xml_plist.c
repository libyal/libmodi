/*
 * Universal Disk Image Format (UDIF) XML plist functions
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
#include <memory.h>
#include <types.h>

#include "libmodi_libbfio.h"
#include "libmodi_libcerror.h"
#include "libmodi_libcnotify.h"
#include "libmodi_libfplist.h"
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
		memory_free(
		 *udif_xml_plist );

		*udif_xml_plist = NULL;
	}
	return( 1 );
}

/* Reads an UDIF XML plist
 * Returns 1 if successful, 0 if the signature does not match or -1 on error
 */
int libmodi_udif_xml_plist_read_data(
     libmodi_udif_xml_plist_t *udif_xml_plist,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libfplist_property_t *root_property  = NULL;
	libfplist_property_t *sub_property   = NULL;
	libfplist_property_list_t *xml_plist = NULL;
	static char *function                = "libmodi_udif_xml_plist_read_data";
	int result                           = 0;

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
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
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
/* TODO implement */

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
	if( sub_property != NULL )
	{
		libfplist_property_free(
		 &sub_property,
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
	if( size > (size64_t) SSIZE_MAX )
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
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek UDIF XML plist offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 offset,
		 offset );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              header_data,
	              5,
	              error );

	if( read_count != (ssize_t) 5 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read XML plist data.",
		 function );

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
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek UDIF XML plist offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 offset,
		 offset );

		goto on_error;
	}
	xml_plist_data = (uint8_t *) memory_allocate(
	                              (size_t) size );

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
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              xml_plist_data,
	              (size_t) size,
	              error );

	if( read_count != (ssize_t) size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read XML plist data.",
		 function );

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

