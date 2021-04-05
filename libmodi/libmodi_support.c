/*
 * Support functions
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
#include <narrow_string.h>
#include <types.h>
#include <wide_string.h>

#include "libmodi_definitions.h"
#include "libmodi_io_handle.h"
#include "libmodi_libbfio.h"
#include "libmodi_libcdirectory.h"
#include "libmodi_libcerror.h"
#include "libmodi_libclocale.h"
#include "libmodi_libcpath.h"
#include "libmodi_support.h"

#include "modi_sparse_image_header.h"
#include "modi_udif_resource_file.h"

#if !defined( HAVE_LOCAL_LIBMODI )

/* Returns the library version
 */
const char *libmodi_get_version(
             void )
{
	return( (const char *) LIBMODI_VERSION_STRING );
}

/* Returns the access flags for reading
 */
int libmodi_get_access_flags_read(
     void )
{
	return( (int) LIBMODI_ACCESS_FLAG_READ );
}

/* Returns the access flags for reading and writing
 */
int libmodi_get_access_flags_read_write(
     void )
{
	return( (int) ( LIBMODI_ACCESS_FLAG_READ | LIBMODI_ACCESS_FLAG_WRITE ) );
}

/* Returns the access flags for writing
 */
int libmodi_get_access_flags_write(
     void )
{
	return( (int) LIBMODI_ACCESS_FLAG_WRITE );
}

/* Retrieves the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
int libmodi_get_codepage(
     int *codepage,
     libcerror_error_t **error )
{
	static char *function = "libmodi_get_codepage";

	if( libclocale_codepage_get(
	     codepage,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve codepage.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Sets the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
int libmodi_set_codepage(
     int codepage,
     libcerror_error_t **error )
{
	static char *function = "libmodi_set_codepage";

	if( libclocale_codepage_set(
	     codepage,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set codepage.",
		 function );

		return( -1 );
	}
	return( 1 );
}

#endif /* !defined( HAVE_LOCAL_LIBMODI ) */

/* Determines if a file contains a Mac OS disk image file signature
 * Returns 1 if true, 0 if not or -1 on error
 */
int libmodi_check_file_signature(
     const char *filename,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle     = NULL;
	libcdirectory_directory_t *directory = NULL;
	static char *function                = "libmodi_check_file_signature";
	char *info_plist_path                = NULL;
	size_t filename_length               = 0;
	size_t info_plist_path_size          = 0;
	int is_directory                     = 0;
	int result                           = 0;

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( libcdirectory_directory_initialize(
	     &directory,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create directory.",
		 function );

		goto on_error;
	}
	is_directory = libcdirectory_directory_open(
	                directory,
	                filename,
	                NULL );

	if( libcdirectory_directory_free(
	     &directory,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free directory.",
		 function );

		goto on_error;
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
	if( is_directory == 1 )
	{
		filename_length = narrow_string_length(
		                   filename );

		if( libcpath_path_join(
		     &info_plist_path,
		     &info_plist_path_size,
		     filename,
		     filename_length,
		     "Info.plist",
		     10,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create info.plist path.",
			 function );

			goto on_error;
		}
		if( libbfio_file_set_name(
		     file_io_handle,
		     info_plist_path,
		     info_plist_path_size - 1,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set filename in file IO handle.",
			 function );

			goto on_error;
		}
		filename        = info_plist_path;
		filename_length = info_plist_path_size - 1;
	}
	else
	{
		filename_length = narrow_string_length(
		                   filename );

		if( libbfio_file_set_name(
		     file_io_handle,
		     filename,
		     filename_length,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set filename in file IO handle.",
			 function );

			goto on_error;
		}
	}
	result = libmodi_check_file_signature_file_io_handle(
	          file_io_handle,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to check file signature using a file handle.",
		 function );

		goto on_error;
	}
	if( libbfio_handle_free(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to free file IO handle.",
		 function );

		goto on_error;
	}
	if( info_plist_path != NULL )
	{
		memory_free(
		 info_plist_path );

		info_plist_path = NULL;
	}
	return( result );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	if( info_plist_path != NULL )
	{
		memory_free(
		 info_plist_path );
	}
	if( directory != NULL )
	{
		libcdirectory_directory_free(
		 &directory,
		 NULL );
	}
	return( -1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Determines if a file contains a Mac OS disk image file signature
 * Returns 1 if true, 0 if not or -1 on error
 */
int libmodi_check_file_signature_wide(
     const wchar_t *filename,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle     = NULL;
	libcdirectory_directory_t *directory = NULL;
	static char *function                = "libmodi_check_file_signature_wide";
	wchar_t *info_plist_path             = NULL;
	size_t filename_length               = 0;
	size_t info_plist_path_size          = 0;
	int is_directory                     = 0;
	int result                           = 0;

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( libcdirectory_directory_initialize(
	     &directory,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create directory.",
		 function );

		goto on_error;
	}
	is_directory = libcdirectory_directory_open_wide(
	                directory,
	                filename,
	                NULL );

	if( libcdirectory_directory_free(
	     &directory,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free directory.",
		 function );

		goto on_error;
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
	if( is_directory == 1 )
	{
		filename_length = wide_string_length(
		                   filename );

		if( libcpath_path_join_wide(
		     &info_plist_path,
		     &info_plist_path_size,
		     filename,
		     filename_length,
		     L"Info.plist",
		     10,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create info.plist path.",
			 function );

			goto on_error;
		}
		if( libbfio_file_set_name_wide(
		     file_io_handle,
		     info_plist_path,
		     info_plist_path_size - 1,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set filename in file IO handle.",
			 function );

			goto on_error;
		}
	}
	else
	{
		filename_length = wide_string_length(
		                   filename );

		if( libbfio_file_set_name_wide(
		     file_io_handle,
		     filename,
		     filename_length,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set filename in file IO handle.",
			 function );

			goto on_error;
		}
	}
	result = libmodi_check_file_signature_file_io_handle(
	          file_io_handle,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to check file signature using a file handle.",
		 function );

		goto on_error;
	}
	if( libbfio_handle_free(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to free file IO handle.",
		 function );

		goto on_error;
	}
	if( info_plist_path != NULL )
	{
		memory_free(
		 info_plist_path );

		info_plist_path = NULL;
	}
	return( result );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	if( info_plist_path != NULL )
	{
		memory_free(
		 info_plist_path );
	}
	if( directory != NULL )
	{
		libcdirectory_directory_free(
		 &directory,
		 NULL );
	}
	return( -1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Determines if a file contains a Mac OS disk image file signature using a Basic File IO (bfio) handle
 * Returns 1 if true, 0 if not or -1 on error
 */
int libmodi_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	uint8_t header_signature[ 5 ];
	uint8_t resource_file_signature[ 4 ];

	static char *function      = "libmodi_check_file_signature_file_io_handle";
	size64_t file_size         = 0;
	ssize_t read_count         = 0;
	int file_io_handle_is_open = 1;

	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	file_io_handle_is_open = libbfio_handle_is_open(
	                          file_io_handle,
	                          error );

	if( file_io_handle_is_open == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file.",
		 function );

		goto on_error;
	}
	else if( file_io_handle_is_open == 0 )
	{
		if( libbfio_handle_open(
		     file_io_handle,
		     LIBBFIO_OPEN_READ,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open file.",
			 function );

			goto on_error;
		}
	}
	if( libbfio_handle_get_size(
	     file_io_handle,
	     &file_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve file size.",
		 function );

		goto on_error;
	}
	if( file_size < 5 )
	{
		return( 0 );
	}
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              header_signature,
	              5,
	              0,
	              error );

	if( read_count != 5 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read header signature at offset: 0 (0x00000000).",
		 function );

		goto on_error;
	}
	if( file_size >= 512 )
	{
		read_count = libbfio_handle_read_buffer_at_offset(
		              file_io_handle,
		              resource_file_signature,
		              4,
		              file_size - 512,
		              error );

		if( read_count != 4 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read footer signature at offset: %" PRIi64 " (0x%08" PRIx64 ").",
			 function,
			 file_size - 512,
			 file_size - 512 );

			goto on_error;
		}
	}
	if( file_io_handle_is_open == 0 )
	{
		file_io_handle_is_open = 1;

		if( libbfio_handle_close(
		     file_io_handle,
		     error ) != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close file.",
			 function );

			goto on_error;
		}
	}
	if( file_size >= 4096 )
	{
		if( memory_compare(
		     header_signature,
		     modi_sparse_image_signature,
		     4 ) == 0 )
		{
			return( 1 );
		}
	}
	if( file_size >= 512 )
	{
		if( memory_compare(
		     resource_file_signature,
		     modi_udif_resource_file_signature,
		     4 ) == 0 )
		{
			return( 1 );
		}
	}
/* TODO improve check for sparse bundles and uncompressed UDIF */
	if( memory_compare(
	     header_signature,
	     "<?xml",
	     5 ) == 0 )
	{
		return( 1 );
	}
	return( 0 );

on_error:
	if( file_io_handle_is_open == 0 )
	{
		libbfio_handle_close(
		 file_io_handle,
		 error );
	}
	return( -1 );
}

