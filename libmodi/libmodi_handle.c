/*
 * Handle functions
 *
 * Copyright (C) 2012-2019, Joachim Metz <joachim.metz@gmail.com>
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
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "libmodi_data_block.h"
#include "libmodi_debug.h"
#include "libmodi_definitions.h"
#include "libmodi_i18n.h"
#include "libmodi_io_handle.h"
#include "libmodi_handle.h"
#include "libmodi_libbfio.h"
#include "libmodi_libcdirectory.h"
#include "libmodi_libcerror.h"
#include "libmodi_libcfile.h"
#include "libmodi_libcnotify.h"
#include "libmodi_libcpath.h"
#include "libmodi_libcthreads.h"
#include "libmodi_libfcache.h"
#include "libmodi_libfdata.h"
#include "libmodi_libfvalue.h"
#include "libmodi_sparse_bundle_xml_plist.h"
#include "libmodi_sparse_image_header.h"
#include "libmodi_system_string.h"
#include "libmodi_udif_resource_file.h"
#include "libmodi_udif_xml_plist.h"

/* Creates a handle
 * Make sure the value handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libmodi_handle_initialize(
     libmodi_handle_t **handle,
     libcerror_error_t **error )
{
	libmodi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libmodi_handle_initialize";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( *handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid handle value already set.",
		 function );

		return( -1 );
	}
	internal_handle = memory_allocate_structure(
	                   libmodi_internal_handle_t );

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_handle,
	     0,
	     sizeof( libmodi_internal_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear handle.",
		 function );

		memory_free(
		 internal_handle );

		return( -1 );
	}
	if( libmodi_io_handle_initialize(
	     &( internal_handle->io_handle ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create IO handle.",
		 function );

		goto on_error;
	}
	if( libmodi_i18n_initialize(
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initalize internationalization (i18n).",
		 function );

		goto on_error;
	}
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_initialize(
	     &( internal_handle->read_write_lock ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize read/write lock.",
		 function );

		goto on_error;
	}
#endif
	internal_handle->maximum_number_of_open_handles = LIBBFIO_POOL_UNLIMITED_NUMBER_OF_OPEN_HANDLES;

	*handle = (libmodi_handle_t *) internal_handle;

	return( 1 );

on_error:
	if( internal_handle != NULL )
	{
		if( internal_handle->io_handle != NULL )
		{
			libmodi_io_handle_free(
			 &( internal_handle->io_handle ),
			 NULL );
		}
		memory_free(
		 internal_handle );
	}
	return( -1 );
}

/* Frees a handle
 * Returns 1 if successful or -1 on error
 */
int libmodi_handle_free(
     libmodi_handle_t **handle,
     libcerror_error_t **error )
{
	libmodi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libmodi_handle_free";
	int result                                 = 1;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( *handle != NULL )
	{
		internal_handle = (libmodi_internal_handle_t *) *handle;

		if( internal_handle->file_io_handle != NULL )
		{
			if( libmodi_handle_close(
			     *handle,
			     error ) != 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_CLOSE_FAILED,
				 "%s: unable to close handle.",
				 function );

				result = -1;
			}
		}
		*handle = NULL;

#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
		if( libcthreads_read_write_lock_free(
		     &( internal_handle->read_write_lock ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free read/write lock.",
			 function );

			result = -1;
		}
#endif
		if( internal_handle->bands_directory_path != NULL )
		{
			memory_free(
			 internal_handle->bands_directory_path );
		}
		if( libmodi_io_handle_free(
		     &( internal_handle->io_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free IO handle.",
			 function );

			result = -1;
		}
		memory_free(
		 internal_handle );
	}
	return( result );
}

/* Signals a handle to abort its current activity
 * Returns 1 if successful or -1 on error
 */
int libmodi_handle_signal_abort(
     libmodi_handle_t *handle,
     libcerror_error_t **error )
{
	libmodi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libmodi_handle_signal_abort";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libmodi_internal_handle_t *) handle;

	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	internal_handle->io_handle->abort = 1;

	return( 1 );
}

/* Sets the bands directory path
 * Returns 1 if successful or -1 on error
 */
int libmodi_internal_handle_set_bands_directory_path(
     libmodi_internal_handle_t *internal_handle,
     const char *path,
     size_t path_length,
     libcerror_error_t **error )
{
	char *bands_directory_path       = NULL;
	static char *function            = "libmodi_internal_handle_set_bands_directory_path";
	size_t bands_directory_path_size = 0;

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path.",
		 function );

		goto on_error;
	}
	if( internal_handle->bands_directory_path != NULL )
	{
		memory_free(
		 internal_handle->bands_directory_path );

		internal_handle->bands_directory_path      = NULL;
		internal_handle->bands_directory_path_size = 0;
	}
	if( libcpath_path_join(
	     &bands_directory_path,
	     &bands_directory_path_size,
	     path,
	     path_length,
	     "bands",
	     5,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create bands directory path.",
		 function );

		goto on_error;
	}
	if( libmodi_system_string_size_from_narrow_string(
	     bands_directory_path,
	     bands_directory_path_size,
	     &( internal_handle->bands_directory_path_size ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine bands directory  size.",
		 function );

		goto on_error;
	}
	internal_handle->bands_directory_path = system_string_allocate(
	                                         internal_handle->bands_directory_path_size );

	if( internal_handle->bands_directory_path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create bands directory path.",
		 function );

		goto on_error;
	}
	if( libmodi_system_string_copy_from_narrow_string(
	     internal_handle->bands_directory_path,
	     internal_handle->bands_directory_path_size,
	     bands_directory_path,
	     bands_directory_path_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set bands directory path.",
		 function );

		goto on_error;
	}
	memory_free(
	 bands_directory_path );

	return( 1 );

on_error:
	if( bands_directory_path != NULL )
	{
		memory_free(
		 bands_directory_path );
	}
	if( internal_handle->bands_directory_path != NULL )
	{
		memory_free(
		 internal_handle->bands_directory_path );

		internal_handle->bands_directory_path = NULL;
	}
	internal_handle->bands_directory_path_size = 0;

	return( -1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Sets the bands directory path
 * Returns 1 if successful or -1 on error
 */
int libmodi_internal_handle_set_bands_directory_path_wide(
     libmodi_internal_handle_t *internal_handle,
     const wchar_t *path,
     size_t path_length,
     libcerror_error_t **error )
{
	wchar_t *bands_directory_path    = NULL;
	static char *function            = "libmodi_internal_handle_set_bands_directory_path_wide";
	size_t bands_directory_path_size = 0;

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path.",
		 function );

		goto on_error;
	}
	if( internal_handle->bands_directory_path != NULL )
	{
		memory_free(
		 internal_handle->bands_directory_path );

		internal_handle->bands_directory_path      = NULL;
		internal_handle->bands_directory_path_size = 0;
	}
	if( libcpath_path_join_wide(
	     &bands_directory_path,
	     &bands_directory_path_size,
	     path,
	     path_length,
	     L"bands",
	     5,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create bands directory path.",
		 function );

		goto on_error;
	}
	if( libmodi_system_string_size_from_wide_string(
	     bands_directory_path,
	     bands_directory_path_size,
	     &( internal_handle->bands_directory_path_size ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine bands directory  size.",
		 function );

		goto on_error;
	}
	internal_handle->bands_directory_path = system_string_allocate(
	                                         internal_handle->bands_directory_path_size );

	if( internal_handle->bands_directory_path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create bands directory path.",
		 function );

		goto on_error;
	}
	if( libmodi_system_string_copy_from_wide_string(
	     internal_handle->bands_directory_path,
	     internal_handle->bands_directory_path_size,
	     bands_directory_path,
	     bands_directory_path_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set bands directory path.",
		 function );

		goto on_error;
	}
	memory_free(
	 bands_directory_path );

	return( 1 );

on_error:
	if( bands_directory_path != NULL )
	{
		memory_free(
		 bands_directory_path );
	}
	if( internal_handle->bands_directory_path != NULL )
	{
		memory_free(
		 internal_handle->bands_directory_path );

		internal_handle->bands_directory_path = NULL;
	}
	internal_handle->bands_directory_path_size = 0;

	return( -1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Opens a handle
 * Returns 1 if successful or -1 on error
 */
int libmodi_handle_open(
     libmodi_handle_t *handle,
     const char *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle           = NULL;
	libcdirectory_directory_t *directory       = NULL;
	libmodi_internal_handle_t *internal_handle = NULL;
	char *basename_end                         = NULL;
	static char *function                      = "libmodi_handle_open";
	char *info_plist_path                      = NULL;
	size_t basename_length                     = 0;
	size_t filename_length                     = 0;
	size_t info_plist_path_size                = 0;
	int is_directory                           = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libmodi_internal_handle_t *) handle;

	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
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
	if( ( ( access_flags & LIBMODI_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBMODI_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBMODI_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
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
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set track offsets read in file IO handle.",
		 function );

		goto on_error;
	}
#endif
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
	if( libmodi_handle_open_file_io_handle(
	     handle,
	     file_io_handle,
	     access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open handle from file: %s.",
		 function,
		 filename );

		goto on_error;
	}
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	if( internal_handle->io_handle->image_type == LIBMODI_IMAGE_TYPE_SPARSE_BUNDLE )
	{
		filename_length = narrow_string_length(
		                   filename );

		basename_end = narrow_string_search_character_reverse(
		                filename,
		                (int) LIBCPATH_SEPARATOR,
		                filename_length + 1 );

		if( basename_end != NULL )
		{
			basename_length = (size_t) ( basename_end - filename );
		}
		if( basename_length > 0 )
		{
			if( libmodi_internal_handle_set_bands_directory_path(
			     internal_handle,
			     filename,
			     basename_length,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set bands directory path.",
				 function );

				goto on_error;
			}
		}
	}
	internal_handle->file_io_handle_created_in_library = 1;

#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	if( info_plist_path != NULL )
	{
		memory_free(
		 info_plist_path );

		info_plist_path = NULL;
	}
	return( 1 );

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

/* Opens a handle
 * Returns 1 if successful or -1 on error
 */
int libmodi_handle_open_wide(
     libmodi_handle_t *handle,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle           = NULL;
	libcdirectory_directory_t *directory       = NULL;
	libmodi_internal_handle_t *internal_handle = NULL;
	wchar_t *basename_end                      = NULL;
	wchar_t *info_plist_path                   = NULL;
	static char *function                      = "libmodi_handle_open_wide";
	size_t basename_length                     = 0;
	size_t filename_length                     = 0;
	size_t info_plist_path_size                = 0;
	int is_directory                           = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libmodi_internal_handle_t *) handle;

	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
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
	if( ( ( access_flags & LIBMODI_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBMODI_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBMODI_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
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
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set track offsets read in file IO handle.",
		 function );

		goto on_error;
	}
#endif
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
	if( libmodi_handle_open_file_io_handle(
	     handle,
	     file_io_handle,
	     access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open handle: %ls.",
		 function,
		 filename );

		goto on_error;
	}
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	if( internal_handle->io_handle->image_type == LIBMODI_IMAGE_TYPE_SPARSE_BUNDLE )
	{
		filename_length = wide_string_length(
		                   filename );

/* TODO does this work for UTF-16 ? */
		basename_end = wide_string_search_character_reverse(
		                filename,
		                (int) LIBCPATH_SEPARATOR,
		                filename_length + 1 );

		if( basename_end != NULL )
		{
			basename_length = (size_t) ( basename_end - filename );
		}
		if( basename_length > 0 )
		{
			if( libmodi_internal_handle_set_bands_directory_path_wide(
			     internal_handle,
			     filename,
			     basename_length,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set bands directory path.",
				 function );

				goto on_error;
			}
		}
	}
	internal_handle->file_io_handle_created_in_library = 1;

#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	if( info_plist_path != NULL )
	{
		memory_free(
		 info_plist_path );

		info_plist_path = NULL;
	}
	return( 1 );

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

/* Opens a handle using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
int libmodi_handle_open_file_io_handle(
     libmodi_handle_t *handle,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error )
{
	libmodi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libmodi_handle_open_file_io_handle";
	int bfio_access_flags                      = 0;
	int file_io_handle_is_open                 = 0;
	int file_io_handle_opened_in_library       = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libmodi_internal_handle_t *) handle;

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
	if( ( ( access_flags & LIBMODI_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBMODI_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBMODI_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBMODI_ACCESS_FLAG_READ ) != 0 )
	{
		bfio_access_flags = LIBBFIO_ACCESS_FLAG_READ;
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
		 "%s: unable to determine if file IO handle is open.",
		 function );

		goto on_error;
	}
	else if( file_io_handle_is_open == 0 )
	{
		if( libbfio_handle_open(
		     file_io_handle,
		     bfio_access_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open file IO handle.",
			 function );

			goto on_error;
		}
		file_io_handle_opened_in_library = 1;
	}
	if( libmodi_internal_handle_open_read(
	     internal_handle,
	     file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read from file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	internal_handle->file_io_handle                   = file_io_handle;
	internal_handle->file_io_handle_opened_in_library = file_io_handle_opened_in_library;
	internal_handle->access_flags                     = access_flags;

#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );

on_error:
	if( file_io_handle_opened_in_library != 0 )
	{
		libbfio_handle_close(
		 file_io_handle,
		 error );
	}
	return( -1 );
}

/* Opens the band data files
 * If the band data filenames were not set explicitly this function assumes the band data files
 * are in the sub directory band in the same location as the Info.plist file
 * Returns 1 if successful or -1 on error
 */
int libmodi_handle_open_band_data_files(
     libmodi_handle_t *handle,
     libcerror_error_t **error )
{
        libbfio_pool_t *file_io_pool               = NULL;
	libmodi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libmodi_handle_open_band_data_files";
	int band_index                             = 0;
	int result                                 = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libmodi_internal_handle_t *) handle;

	if( ( ( internal_handle->access_flags & LIBMODI_ACCESS_FLAG_READ ) == 0 )
	 && ( ( internal_handle->access_flags & LIBMODI_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( internal_handle->access_flags & LIBMODI_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	if( ( internal_handle->io_handle->image_type == LIBMODI_IMAGE_TYPE_SPARSE_BUNDLE )
	 && ( internal_handle->io_handle->number_of_bands <= 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - invalid IO handle - missing number of bands.",
		 function );

		return( -1 );
	}
	if( internal_handle->band_data_file_io_pool != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid handle - band data file IO pool already exists.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	if( internal_handle->io_handle->image_type == LIBMODI_IMAGE_TYPE_SPARSE_BUNDLE )
	{
		if( libbfio_pool_initialize(
		     &file_io_pool,
		     internal_handle->io_handle->number_of_bands,
		     internal_handle->maximum_number_of_open_handles,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create file IO pool.",
			 function );

			goto on_error;
		}
		for( band_index = 0;
		     band_index < internal_handle->io_handle->number_of_bands;
		     band_index++ )
		{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libmodi_internal_handle_open_band_data_file_wide(
				  internal_handle,
				  file_io_pool,
				  band_index,
				  error );
#else
			result = libmodi_internal_handle_open_band_data_file(
				  internal_handle,
				  file_io_pool,
				  band_index,
				  error );
#endif
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_OPEN_FAILED,
				 "%s: unable to open band data file: %x.",
				 function,
				 band_index );

				goto on_error;
			}
		}
		if( libmodi_internal_handle_open_band_data_files_file_io_pool(
		     internal_handle,
		     file_io_pool,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open band data files from file IO pool.",
			 function );

			goto on_error;
		}
		internal_handle->band_data_file_io_pool_created_in_library = 1;
	}
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );

on_error:
	if( file_io_pool != NULL )
	{
		libbfio_pool_close_all(
		 file_io_pool,
		 NULL );
		libbfio_pool_free(
		 &file_io_pool,
		 NULL );
	}
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	libcthreads_read_write_lock_release_for_write(
	 internal_handle->read_write_lock,
	 NULL );
#endif
	return( -1 );
}

/* Opens the band data files using a Basic File IO (bfio) pool
 * This function assumes the band data files are in order and
 * non-existing band data files are set to NULL
 * Returns 1 if successful or -1 on error
 */
int libmodi_handle_open_band_data_files_file_io_pool(
     libmodi_handle_t *handle,
     libbfio_pool_t *file_io_pool,
     libcerror_error_t **error )
{
	libmodi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libmodi_handle_open_band_data_files_file_io_pool";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libmodi_internal_handle_t *) handle;

	if( ( ( internal_handle->access_flags & LIBMODI_ACCESS_FLAG_READ ) == 0 )
	 && ( ( internal_handle->access_flags & LIBMODI_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( internal_handle->access_flags & LIBMODI_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->band_data_file_io_pool != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid handle - band data file IO pool already exists.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	if( internal_handle->io_handle->image_type == LIBMODI_IMAGE_TYPE_SPARSE_BUNDLE )
	{
		if( libmodi_internal_handle_open_band_data_files_file_io_pool(
		     internal_handle,
		     file_io_pool,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open band data files from file IO pool.",
			 function );

			goto on_error;
		}
	}
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );

on_error:
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	libcthreads_read_write_lock_release_for_write(
	 internal_handle->read_write_lock,
	 NULL );
#endif
	return( -1 );
}

/* Opens the band data files using a Basic File IO (bfio) pool
 * This function assumes the band data files are in order and
 * non-existing band data files are set to NULL
 * Returns 1 if successful or -1 on error
 */
int libmodi_internal_handle_open_band_data_files_file_io_pool(
     libmodi_internal_handle_t *internal_handle,
     libbfio_pool_t *file_io_pool,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle = NULL;
	static char *function            = "libmodi_internal_handle_open_band_data_files_file_io_pool";
	size64_t band_data_size          = 0;
	size64_t file_size               = 0;
	size64_t media_size              = 0;
	size64_t sparse_band_data_size   = 0;
	int file_io_handle_index         = 0;
	int number_of_file_io_handles    = 0;
	int segment_index                = 0;

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->band_data_file_io_pool != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid handle - band data file IO pool already exists.",
		 function );

		return( -1 );
	}
	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->io_handle->band_data_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - invalid IO handle - missing band data size.",
		 function );

		return( -1 );
	}
	if( libbfio_pool_get_number_of_handles(
	     file_io_pool,
	     &number_of_file_io_handles,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of handles in file IO pool.",
		 function );

		return( -1 );
	}
	if( number_of_file_io_handles != internal_handle->io_handle->number_of_bands )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid number of handles in file IO pool value does not match number of bands.",
		 function );

		return( -1 );
	}
	media_size = internal_handle->io_handle->media_size;

	for( file_io_handle_index = 0;
	     file_io_handle_index < number_of_file_io_handles;
	     file_io_handle_index++ )
	{
		if( libbfio_pool_get_handle(
		     file_io_pool,
		     file_io_handle_index,
		     &file_io_handle,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve handle: %d from file IO pool.",
			 function,
			 file_io_handle_index );

			return( -1 );
		}
		if( file_io_handle == NULL )
		{
			band_data_size        = 0;
			sparse_band_data_size = internal_handle->io_handle->band_data_size;
		}
		else
		{
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

				return( -1 );
			}
			if( internal_handle->io_handle->band_data_size < media_size )
			{
				sparse_band_data_size = internal_handle->io_handle->band_data_size;
			}
			else
			{
				sparse_band_data_size = media_size;
			}
			if( file_size > sparse_band_data_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid band data file: %d size value out of bounds.",
				 function,
				 file_io_handle_index );

				return( -1 );
			}
			band_data_size         = file_size;
			sparse_band_data_size -= file_size;
		}
		if( band_data_size > 0 )
		{
			if( libfdata_vector_append_segment(
			     internal_handle->bands_vector,
			     &segment_index,
			     file_io_handle_index,
			     0,
			     band_data_size,
			     0,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to append band data file: %d as segment to bands vector.",
				 function,
				 file_io_handle_index );

				return( -1 );
			}
		}
		if( sparse_band_data_size > 0 )
		{
			if( libfdata_vector_append_segment(
			     internal_handle->bands_vector,
			     &segment_index,
			     file_io_handle_index,
			     0,
			     sparse_band_data_size,
			     LIBFDATA_RANGE_FLAG_IS_SPARSE,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to append band data file: %d as sparse segment to bands vector.",
				 function,
				 file_io_handle_index );

				return( -1 );
			}
		}
		media_size -= internal_handle->io_handle->band_data_size;
	}
	internal_handle->band_data_file_io_pool = file_io_pool;

	return( 1 );
}

/* Opens a specific band data file
 * Returns 1 if successful or -1 on error
 */
int libmodi_internal_handle_open_band_data_file(
     libmodi_internal_handle_t *internal_handle,
     libbfio_pool_t *file_io_pool,
     int band_index,
     libcerror_error_t **error )
{
	char filename[ 16 ];

	libbfio_handle_t *file_io_handle = NULL;
	char *bands_file_path            = NULL;
	static char *function            = "libmodi_internal_handle_open_band_data_file";
	size_t bands_file_path_size      = 0;
	size_t filename_length           = 0;
	int bfio_access_flags            = 0;
	int result                       = 0;

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( libfvalue_utf8_string_copy_from_integer(
	     (uint8_t *) filename,
	     16,
	     band_index,
	     SIZEOF_INT * 8,
	     LIBFVALUE_INTEGER_FORMAT_FLAG_NO_BASE_INDICATOR | LIBFVALUE_INTEGER_FORMAT_TYPE_HEXADECIMAL,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to copy band index to string.",
		 function );

		goto on_error;
	}
	filename_length = narrow_string_length(
	                   filename );

	if( libcpath_path_join(
	     &bands_file_path,
	     &bands_file_path_size,
	     (char *) internal_handle->bands_directory_path,
	     internal_handle->bands_directory_path_size - 1,
	     filename,
	     filename_length,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create bands file: %d path.",
		 function,
		 band_index );

		goto on_error;
	}
	result = libcfile_file_exists(
	          bands_file_path,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_GENERIC,
		 "%s: unable to determine if band data file exists.",
		 function );
	}
	else if( result != 0 )
	{
		if( ( internal_handle->access_flags & LIBMODI_ACCESS_FLAG_READ ) != 0 )
		{
			bfio_access_flags = LIBBFIO_ACCESS_FLAG_READ;
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
#if defined( HAVE_DEBUG_OUTPUT )
		if( libbfio_handle_set_track_offsets_read(
		     file_io_handle,
		     1,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set track offsets read in file IO handle.",
			 function );

			goto on_error;
		}
#endif
		if( libbfio_file_set_name(
		     file_io_handle,
		     bands_file_path,
		     bands_file_path_size,
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
		if( libbfio_handle_open(
		     file_io_handle,
		     bfio_access_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open file IO handle.",
			 function );

			goto on_error;
		}
		if( libbfio_pool_set_handle(
		     file_io_pool,
		     band_index,
		     file_io_handle,
		     bfio_access_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set file IO handle: %d in pool.",
			 function,
			 band_index );

			goto on_error;
		}
	}
	memory_free(
	 bands_file_path );

	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	if( bands_file_path != NULL )
	{
		memory_free(
		 bands_file_path );
	}
	return( -1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Opens a specific band data file
 * Returns 1 if successful or -1 on error
 */
int libmodi_internal_handle_open_band_data_file_wide(
     libmodi_internal_handle_t *internal_handle,
     libbfio_pool_t *file_io_pool,
     int band_index,
     libcerror_error_t **error )
{
	wchar_t filename[ 16 ];

	libbfio_handle_t *file_io_handle = NULL;
	wchar_t *bands_file_path         = NULL;
	static char *function            = "libmodi_internal_handle_open_band_data_file_wide";
	size_t bands_file_path_size      = 0;
	size_t filename_length           = 0;
	int bfio_access_flags            = 0;
	int result                       = 0;

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
#if ( SIZEOF_WCHAR_T == 4 )
	result = libfvalue_utf32_string_copy_from_integer(
	          (uint32_t *) filename,
	          16,
	          band_index,
	          SIZEOF_INT * 8,
	          LIBFVALUE_INTEGER_FORMAT_FLAG_NO_BASE_INDICATOR | LIBFVALUE_INTEGER_FORMAT_TYPE_HEXADECIMAL,
	          error );
#else
	result = libfvalue_utf16_string_copy_from_integer(
	          (uint16_t *) filename,
	          16,
	          band_index,
	          SIZEOF_INT * 8,
	          LIBFVALUE_INTEGER_FORMAT_FLAG_NO_BASE_INDICATOR | LIBFVALUE_INTEGER_FORMAT_TYPE_HEXADECIMAL,
	          error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to copy band index to string.",
		 function );

		goto on_error;
	}
	filename_length = wide_string_length(
	                   filename );

	if( libcpath_path_join_wide(
	     &bands_file_path,
	     &bands_file_path_size,
	     (wchar_t *) internal_handle->bands_directory_path,
	     internal_handle->bands_directory_path_size - 1,
	     filename,
	     filename_length,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create bands file path.",
		 function );

		goto on_error;
	}
	result = libcfile_file_exists_wide(
	          bands_file_path,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_GENERIC,
		 "%s: unable to determine if band data file exists.",
		 function );
	}
	else if( result != 0 )
	{
		if( ( internal_handle->access_flags & LIBMODI_ACCESS_FLAG_READ ) != 0 )
		{
			bfio_access_flags = LIBBFIO_ACCESS_FLAG_READ;
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
#if defined( HAVE_DEBUG_OUTPUT )
		if( libbfio_handle_set_track_offsets_read(
		     file_io_handle,
		     1,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set track offsets read in file IO handle.",
			 function );

			goto on_error;
		}
#endif
		if( libbfio_file_set_name_wide(
		     file_io_handle,
		     bands_file_path,
		     bands_file_path_size,
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
		if( libbfio_handle_open(
		     file_io_handle,
		     bfio_access_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open file IO handle.",
			 function );

			goto on_error;
		}
		if( libbfio_pool_set_handle(
		     file_io_pool,
		     band_index,
		     file_io_handle,
		     bfio_access_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set file IO handle: %d in pool.",
			 function,
			 band_index );

			goto on_error;
		}
	}
	memory_free(
	 bands_file_path );

	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	if( bands_file_path != NULL )
	{
		memory_free(
		 bands_file_path );
	}
	return( -1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Closes a handle
 * Returns 0 if successful or -1 on error
 */
int libmodi_handle_close(
     libmodi_handle_t *handle,
     libcerror_error_t **error )
{
	libmodi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libmodi_handle_close";
	int result                                 = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libmodi_internal_handle_t *) handle;

	if( internal_handle->file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing file IO handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( internal_handle->file_io_handle_created_in_library != 0 )
		{
			if( libmodi_debug_print_read_offsets(
			     internal_handle->file_io_handle,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print the read offsets.",
				 function );

				result = -1;
			}
		}
	}
#endif
	if( internal_handle->band_data_file_io_pool_created_in_library != 0 )
	{
		if( libbfio_pool_close_all(
		     internal_handle->band_data_file_io_pool,
		     error ) != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close all files in band data file IO pool.",
			 function );

			result = -1;
		}
		if( libbfio_pool_free(
		     &( internal_handle->band_data_file_io_pool ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free band data file IO pool.",
			 function );

			result = -1;
		}
		internal_handle->band_data_file_io_pool_created_in_library = 0;
	}
	internal_handle->band_data_file_io_pool = NULL;

	if( internal_handle->file_io_handle_opened_in_library != 0 )
	{
		if( libbfio_handle_close(
		     internal_handle->file_io_handle,
		     error ) != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close file IO handle.",
			 function );

			result = -1;
		}
		internal_handle->file_io_handle_opened_in_library = 0;
	}
	if( internal_handle->file_io_handle_created_in_library != 0 )
	{
		if( libbfio_handle_free(
		     &( internal_handle->file_io_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free file IO handle.",
			 function );

			result = -1;
		}
		internal_handle->file_io_handle_created_in_library = 0;
	}
	internal_handle->file_io_handle = NULL;
	internal_handle->current_offset = 0;

	if( libmodi_io_handle_clear(
	     internal_handle->io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		result = -1;
	}
	if( libfdata_vector_free(
	     &( internal_handle->bands_vector ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free bands vector.",
		 function );

		result = -1;
	}
	if( libfcache_cache_free(
	     &( internal_handle->bands_cache ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free bands cache.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Opens a handle for reading
 * Returns 1 if successful or -1 on error
 */
int libmodi_internal_handle_open_read(
     libmodi_internal_handle_t *internal_handle,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	libmodi_sparse_bundle_xml_plist_t *sparse_bundle_xml_plist = NULL;
	libmodi_sparse_image_header_t *sparse_image_header         = NULL;
	libmodi_udif_resource_file_t *udif_resource_file           = NULL;
	libmodi_udif_xml_plist_t *udif_xml_plist                   = NULL;
	static char *function                                      = "libmodi_internal_handle_open_read";
	size64_t band_data_size                                    = 0;
	size64_t file_size                                         = 0;
	off64_t band_data_offset                                   = 0;
	uint32_t band_data_range_flags                             = 0;
	uint32_t band_reference                                    = 0;
	uint32_t band_reference_index                              = 0;
	int result                                                 = 0;
	int segment_index                                          = 0;

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->bands_vector != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - bands vector already set.",
		 function );

		return( -1 );
	}
	if( internal_handle->bands_cache != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - bands cache already set.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
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
/* TODO clone function ? */
	if( libfdata_vector_initialize(
	     &( internal_handle->bands_vector ),
	     (size64_t) 512,
	     (intptr_t *) internal_handle->io_handle,
	     NULL,
	     NULL,
	     (int (*)(intptr_t *, intptr_t *, libfdata_vector_t *, libfdata_cache_t *, int, int, off64_t, size64_t, uint32_t, uint8_t, libcerror_error_t **)) &libmodi_io_handle_read_data_block,
	     NULL,
	     LIBFDATA_DATA_HANDLE_FLAG_NON_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create bands vector.",
		 function );

		goto on_error;
	}
	if( ( internal_handle->io_handle->image_type == LIBMODI_IMAGE_TYPE_UNKNOWN )
	 && ( file_size >= 512 ) )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "Reading Universal Disk Image Format (UDIF) resource file:\n" );
		}
#endif
		if( libmodi_udif_resource_file_initialize(
		     &udif_resource_file,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create UDIF resource file.",
			 function );

			goto on_error;
		}
		result = libmodi_udif_resource_file_read_file_io_handle(
		          udif_resource_file,
		          file_io_handle,
		          file_size - 512,
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read UDIF resource file at offset: %" PRIi64 " (0x%08" PRIx64 ").",
			 function,
			 file_size - 512,
			 file_size - 512 );

			goto on_error;
		}
		else if( result != 0 )
		{
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "Reading Universal Disk Image Format (UDIF) XML plist:\n" );
			}
#endif
			if( libmodi_udif_xml_plist_initialize(
			     &udif_xml_plist,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create UDIF XML plist.",
				 function );

				goto on_error;
			}
			result = libmodi_udif_xml_plist_read_file_io_handle(
			          udif_xml_plist,
			          file_io_handle,
			          udif_resource_file->xml_plist_offset,
			          udif_resource_file->xml_plist_size,
			          error );

			if( result == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read UDIF XML plist at offset: %" PRIi64 " (0x%08" PRIx64 ").",
				 function,
				 udif_resource_file->xml_plist_offset,
				 udif_resource_file->xml_plist_offset );

				goto on_error;
			}
			if( libmodi_udif_xml_plist_free(
			     &udif_xml_plist,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to free UDIF resource file.",
				 function );

				goto on_error;
			}
			internal_handle->io_handle->image_type = LIBMODI_IMAGE_TYPE_UDIF_COMPRESSED;
			internal_handle->io_handle->media_size = 0;

			if( libfdata_vector_append_segment(
			     internal_handle->bands_vector,
			     &segment_index,
			     0,
			     udif_resource_file->data_fork_offset,
			     udif_resource_file->data_fork_size,
			     0,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to append data fork as segment to bands vector.",
				 function );

				goto on_error;
			}
		}
		if( libmodi_udif_resource_file_free(
		     &udif_resource_file,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to free UDIF resource file.",
			 function );

			goto on_error;
		}
	}
	if( ( internal_handle->io_handle->image_type == LIBMODI_IMAGE_TYPE_UNKNOWN )
	 && ( file_size >= 4096 ) )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "Reading sparse image header:\n" );
		}
#endif
		if( libmodi_sparse_image_header_initialize(
		     &sparse_image_header,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create sparse image header.",
			 function );

			goto on_error;
		}
		result = libmodi_sparse_image_header_read_file_io_handle(
		          sparse_image_header,
		          file_io_handle,
		          0,
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read sparse image header at offset: 0 (0x00000000).",
			 function );

			goto on_error;
		}
		else if( result != 0 )
		{
			internal_handle->io_handle->image_type = LIBMODI_IMAGE_TYPE_SPARSE_IMAGE;
			internal_handle->io_handle->media_size = (size64_t) sparse_image_header->number_of_sectors * 512;

			band_data_size = (size64_t) sparse_image_header->sectors_per_band * 512;

			for( band_reference_index = 0;
			     band_reference_index < sparse_image_header->number_of_bands;
			     band_reference_index++ )
			{
				band_reference = sparse_image_header->band_references[ band_reference_index ];

#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: band reference: %03" PRIu32 "\t\t: 0x%08" PRIx32 "",
					 function,
					 band_reference_index,
					 band_reference );

					if( band_reference == 0xffffffffUL )
					{
						libcnotify_printf(
						 " (sparse)\n" );
					}
					else
					{
						libcnotify_printf(
						 " (data offset: 0x%08" PRIx64 ")\n",
						 4096 + ( band_reference * band_data_size ) );
					}
				}
#endif
				if( band_reference == 0xffffffffUL )
				{
					band_data_offset      = 0;
					band_data_range_flags = LIBFDATA_RANGE_FLAG_IS_SPARSE;
				}
				else
				{
					band_data_offset      = 4096 + ( band_reference * band_data_size );
					band_data_range_flags = 0;
				}
				if( libfdata_vector_append_segment(
				     internal_handle->bands_vector,
				     &segment_index,
				     0,
				     band_data_offset,
				     band_data_size,
				     band_data_range_flags,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
					 "%s: unable to append band reference: %" PRIu32 " as segment to bands vector.",
					 function,
					 band_reference_index );

					goto on_error;
				}
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "\n" );
			}
#endif
		}
		if( libmodi_sparse_image_header_free(
		     &sparse_image_header,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to free sparse image header.",
			 function );

			goto on_error;
		}
	}
	if( internal_handle->io_handle->image_type == LIBMODI_IMAGE_TYPE_UNKNOWN )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "Reading info.plist:\n" );
		}
#endif
		if( libmodi_sparse_bundle_xml_plist_initialize(
		     &sparse_bundle_xml_plist,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create sparse bundle XML plist",
			 function );

			goto on_error;
		}
		result = libmodi_sparse_bundle_xml_plist_read_file_io_handle(
		          sparse_bundle_xml_plist,
		          file_io_handle,
		          0,
		          file_size,
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read sparse bundle info.plist.",
			 function );

			goto on_error;
		}
		else if( result != 0 )
		{
			internal_handle->io_handle->image_type      = LIBMODI_IMAGE_TYPE_SPARSE_BUNDLE;
			internal_handle->io_handle->band_data_size  = (size64_t) sparse_bundle_xml_plist->band_data_size;
			internal_handle->io_handle->number_of_bands = (int) sparse_bundle_xml_plist->number_of_bands;
			internal_handle->io_handle->media_size      = (size64_t) sparse_bundle_xml_plist->media_size;
		}
		if( libmodi_sparse_bundle_xml_plist_free(
		     &sparse_bundle_xml_plist,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free sparse bundle XML plist",
			 function );

			goto on_error;
		}
	}
	if( internal_handle->io_handle->image_type == LIBMODI_IMAGE_TYPE_UNKNOWN )
	{
/* TODO check MBR boot and HFS+/HFSX signatures */
		internal_handle->io_handle->image_type = LIBMODI_IMAGE_TYPE_UDIF_UNCOMPRESSED;
		internal_handle->io_handle->media_size = file_size;

		if( libfdata_vector_append_segment(
		     internal_handle->bands_vector,
		     &segment_index,
		     0,
		     0,
		     file_size,
		     0,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append segment to bands vector.",
			 function );

			goto on_error;
		}
	}
	if( libfcache_cache_initialize(
	     &( internal_handle->bands_cache ),
	     LIBMODI_MAXIMUM_CACHE_ENTRIES_DATA_BANDS,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create bands cache.",
		 function );

		goto on_error;
	}
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );

on_error:
	if( internal_handle->bands_cache != NULL )
	{
		libfcache_cache_free(
		 &( internal_handle->bands_cache ),
		 NULL );
	}
	if( sparse_bundle_xml_plist != NULL )
	{
		libmodi_sparse_bundle_xml_plist_free(
		 &sparse_bundle_xml_plist,
		 NULL );
	}
	if( sparse_image_header != NULL )
	{
		libmodi_sparse_image_header_free(
		 &sparse_image_header,
		 NULL );
	}
	if( udif_xml_plist != NULL )
	{
		libmodi_udif_xml_plist_free(
		 &udif_xml_plist,
		 NULL );
	}
	if( udif_resource_file != NULL )
	{
		libmodi_udif_resource_file_free(
		 &udif_resource_file,
		 NULL );
	}
	if( internal_handle->bands_vector != NULL )
	{
		libfdata_vector_free(
		 &( internal_handle->bands_vector ),
		 NULL );
	}
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	libcthreads_read_write_lock_release_for_write(
	 internal_handle->read_write_lock,
	 NULL );
#endif
	return( -1 );
}

/* Reads (media) data from the current offset into a buffer using a Basic File IO (bfio) handle
 * This function is not multi-thread safe acquire write lock before call
 * Returns the number of bytes read or -1 on error
 */
ssize_t libmodi_internal_handle_read_buffer_from_file_io_handle(
         libmodi_internal_handle_t *internal_handle,
         intptr_t *file_io_handle,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error )
{
	libmodi_data_block_t *data_block = NULL;
	static char *function            = "libmodi_internal_handle_read_buffer_from_file_io_handle";
	off64_t element_data_offset      = 0;
	size_t available_block_size      = 0;
	size_t buffer_offset             = 0;
	size_t read_size                 = 0;

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->current_offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid handle - invalid IO handle - current offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer.",
		 function );

		return( -1 );
	}
	if( buffer_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid element data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( (size64_t) internal_handle->current_offset >= internal_handle->io_handle->media_size )
	{
		return( 0 );
	}
	while( buffer_offset < buffer_size )
	{
		if( libfdata_vector_get_element_value_at_offset(
		     internal_handle->bands_vector,
		     file_io_handle,
		     (libfdata_cache_t *) internal_handle->bands_cache,
		     internal_handle->current_offset,
		     &element_data_offset,
		     (intptr_t **) &data_block,
		     0,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve band at offset: %" PRIi64 " (0x%08" PRIx64 ").",
			 function,
			 internal_handle->current_offset,
			 internal_handle->current_offset );

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
		if( element_data_offset > (off64_t) data_block->data_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid element data offset value out of bounds.",
			 function );

			return( -1 );
		}
		available_block_size = data_block->data_size - (size_t) element_data_offset;

		if( buffer_size < available_block_size )
		{
			read_size = buffer_size;
		}
		else
		{
			read_size = available_block_size;
		}
		if( read_size > ( internal_handle->io_handle->media_size - internal_handle->current_offset ) )
		{
			read_size = (size_t) ( internal_handle->io_handle->media_size - internal_handle->current_offset );
		}
		if( memory_copy(
		     &( ( (uint8_t *) buffer )[ buffer_offset ] ),
		     &( data_block->data[ element_data_offset ] ),
		     read_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy block data to buffer.",
			 function );

			return( -1 );
		}
		buffer_offset += read_size;

		internal_handle->current_offset += read_size;

		if( (size64_t) internal_handle->current_offset >= internal_handle->io_handle->media_size )
		{
			break;
		}
	}
	return( (ssize_t) buffer_offset );
}

/* Reads (media) data from the current offset into a buffer
 * Returns the number of bytes read or -1 on error
 */
ssize_t libmodi_handle_read_buffer(
         libmodi_handle_t *handle,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error )
{
	libmodi_internal_handle_t *internal_handle = NULL;
	intptr_t *file_io_handle                   = NULL;
	static char *function                      = "libmodi_handle_read_buffer";
	ssize_t read_count                         = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libmodi_internal_handle_t *) handle;

	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing file IO handle.",
		 function );

		return( -1 );
	}
	if( ( internal_handle->io_handle->image_type == LIBMODI_IMAGE_TYPE_SPARSE_BUNDLE )
	 && ( internal_handle->band_data_file_io_pool == NULL ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing band data file IO pool.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	if( internal_handle->io_handle->image_type == LIBMODI_IMAGE_TYPE_SPARSE_BUNDLE )
	{
		file_io_handle = (intptr_t *) internal_handle->band_data_file_io_pool;
	}
	else
	{
		file_io_handle = (intptr_t *) internal_handle->file_io_handle;
	}
	read_count = libmodi_internal_handle_read_buffer_from_file_io_handle(
		      internal_handle,
		      file_io_handle,
		      buffer,
		      buffer_size,
		      error );

	if( read_count == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read buffer.",
		 function );

		read_count = -1;
	}
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( read_count );
}

/* Reads (media) data at a specific offset
 * Returns the number of bytes read or -1 on error
 */
ssize_t libmodi_handle_read_buffer_at_offset(
         libmodi_handle_t *handle,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libcerror_error_t **error )
{
	libmodi_internal_handle_t *internal_handle = NULL;
	intptr_t *file_io_handle                   = NULL;
	static char *function                      = "libmodi_handle_read_buffer_at_offset";
	ssize_t read_count                         = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libmodi_internal_handle_t *) handle;

	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing file IO handle.",
		 function );

		return( -1 );
	}
	if( ( internal_handle->io_handle->image_type == LIBMODI_IMAGE_TYPE_SPARSE_BUNDLE )
	 && ( internal_handle->band_data_file_io_pool == NULL ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing band data file IO pool.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	if( libmodi_internal_handle_seek_offset(
	     internal_handle,
	     offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset.",
		 function );

		goto on_error;
	}
	if( internal_handle->io_handle->image_type == LIBMODI_IMAGE_TYPE_SPARSE_BUNDLE )
	{
		file_io_handle = (intptr_t *) internal_handle->band_data_file_io_pool;
	}
	else
	{
		file_io_handle = (intptr_t *) internal_handle->file_io_handle;
	}
	read_count = libmodi_internal_handle_read_buffer_from_file_io_handle(
		      internal_handle,
		      file_io_handle,
		      buffer,
		      buffer_size,
		      error );

	if( read_count == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read buffer.",
		 function );

		goto on_error;
	}
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( read_count );

on_error:
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	libcthreads_read_write_lock_release_for_write(
	 internal_handle->read_write_lock,
	 NULL );
#endif
	return( -1 );
}

#ifdef TODO_WRITE_SUPPORT

/* Writes (media) data at the current offset from a buffer using a Basic File IO (bfio) handle
 * the necessary settings of the write values must have been made
 * Will initialize write if necessary
 * This function is not multi-thread safe acquire write lock before call
 * Returns the number of input bytes written, 0 when no longer bytes can be written or -1 on error
 */
ssize_t libmodi_internal_handle_write_buffer_to_file_io_handle(
         libmodi_internal_handle_t *internal_handle,
         libbfio_handle_t *file_io_handle,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error )
{
/* TODO implement */
	return( -1 );
}

/* Writes (media) data at the current offset
 * the necessary settings of the write values must have been made
 * Will initialize write if necessary
 * Returns the number of input bytes written, 0 when no longer bytes can be written or -1 on error
 */
ssize_t libmodi_handle_write_buffer(
         libmodi_handle_t *handle,
         const void *buffer,
         size_t buffer_size,
         libcerror_error_t **error )
{
	libmodi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libmodi_handle_write_buffer";
	ssize_t write_count                        = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libmodi_internal_handle_t *) handle;

	if( internal_handle->file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing file IO handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	write_count = libmodi_internal_handle_write_buffer_to_file_io_handle(
	               internal_handle,
	               internal_handle->file_io_handle,
	               buffer,
	               buffer_size,
	               error );

	if( write_count == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to write buffer.",
		 function );

		write_count = -1;
	}
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( write_count );
}

/* Writes (media) data at a specific offset,
 * the necessary settings of the write values must have been made
 * Will initialize write if necessary
 * Returns the number of input bytes written, 0 when no longer bytes can be written or -1 on error
 */
ssize_t libmodi_handle_write_buffer_at_offset(
         libmodi_handle_t *handle,
         const void *buffer,
         size_t buffer_size,
         off64_t offset,
         libcerror_error_t **error )
{
	libmodi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libmodi_handle_write_buffer_at_offset";
	ssize_t write_count                        = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libmodi_internal_handle_t *) handle;

	if( internal_handle->file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing file IO handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	if( libmodi_internal_handle_seek_offset(
	     internal_handle,
	     offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset.",
		 function );

		goto on_error;
	}
	write_count = libmodi_internal_handle_write_buffer_to_file_io_handle(
	               internal_handle,
	               internal_handle->file_io_handle,
	               buffer,
	               buffer_size,
	               error );

	if( write_count == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to write buffer.",
		 function );

		goto on_error;
	}
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( write_count );

on_error:
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	libcthreads_read_write_lock_release_for_write(
	 internal_handle->read_write_lock,
	 NULL );
#endif
	return( -1 );
}

#endif /* TODO_WRITE_SUPPORT */

/* Seeks a certain offset of the (media) data
 * This function is not multi-thread safe acquire write lock before call
 * Returns the offset if seek is successful or -1 on error
 */
off64_t libmodi_internal_handle_seek_offset(
         libmodi_internal_handle_t *internal_handle,
         off64_t offset,
         int whence,
         libcerror_error_t **error )
{
	static char *function = "libmodi_internal_handle_seek_offset";

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	if( ( whence != SEEK_CUR )
	 && ( whence != SEEK_END )
	 && ( whence != SEEK_SET ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported whence.",
		 function );

		return( -1 );
	}
	if( whence == SEEK_CUR )
	{
		offset += internal_handle->current_offset;
	}
	else if( whence == SEEK_END )
	{
		offset += (off64_t) internal_handle->io_handle->media_size;
	}
	if( offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid offset value out of bounds.",
		 function );

		return( -1 );
	}
	internal_handle->current_offset = offset;

	return( offset );
}

/* Seeks a certain offset of the (media) data
 * Returns the offset if seek is successful or -1 on error
 */
off64_t libmodi_handle_seek_offset(
         libmodi_handle_t *handle,
         off64_t offset,
         int whence,
         libcerror_error_t **error )
{
	libmodi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libmodi_handle_seek_offset";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libmodi_internal_handle_t *) handle;

	if( internal_handle->file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing file IO handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	offset = libmodi_internal_handle_seek_offset(
	          internal_handle,
	          offset,
	          whence,
	          error );

	if( offset == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset.",
		 function );

		offset = -1;
	}
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( offset );
}

/* Retrieves the current offset of the (media) data
 * Returns 1 if successful or -1 on error
 */
int libmodi_handle_get_offset(
     libmodi_handle_t *handle,
     off64_t *offset,
     libcerror_error_t **error )
{
	libmodi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libmodi_handle_get_offset";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libmodi_internal_handle_t *) handle;

	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing file IO handle.",
		 function );

		return( -1 );
	}
	if( offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	*offset = internal_handle->current_offset;

#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}

/* Sets the maximum number of (concurrent) open file handles
 * Returns 1 if successful or -1 on error
 */
int libmodi_handle_set_maximum_number_of_open_handles(
     libmodi_handle_t *handle,
     int maximum_number_of_open_handles,
     libcerror_error_t **error )
{
	libmodi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libmodi_handle_set_maximum_number_of_open_handles";
	int result                                 = 1;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libmodi_internal_handle_t *) handle;

#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	if( internal_handle->band_data_file_io_pool != NULL )
	{
		result = libbfio_pool_set_maximum_number_of_open_handles(
		          internal_handle->band_data_file_io_pool,
		          maximum_number_of_open_handles,
		          error );

		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set maximum number of open handles in band data file IO pool.",
			 function );
		}
	}
	if( result == 1 )
	{
		internal_handle->maximum_number_of_open_handles = maximum_number_of_open_handles;
	}
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Sets the path to the band data files
 * Returns 1 if successful or -1 on error
 */
int libmodi_handle_set_band_data_files_path(
     libmodi_handle_t *handle,
     const char *path,
     size_t path_length,
     libcerror_error_t **error )
{
	libmodi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libmodi_handle_set_band_data_files_path";
	int result                                 = 1;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libmodi_internal_handle_t *) handle;

	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	if( path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path.",
		 function );

		return( -1 );
	}
	if( path_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid path length value exceeds maximum.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	if( internal_handle->io_handle->image_type == LIBMODI_IMAGE_TYPE_SPARSE_BUNDLE )
	{
		if( libmodi_internal_handle_set_bands_directory_path(
		     internal_handle,
		     path,
		     path_length,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set bands directory path.",
			 function );

			result = -1;
		}
	}
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Sets the path to the band data files
 * Returns 1 if successful or -1 on error
 */
int libmodi_handle_set_band_data_files_path_wide(
     libmodi_handle_t *handle,
     const wchar_t *path,
     size_t path_length,
     libcerror_error_t **error )
{
	libmodi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libmodi_handle_set_band_data_files_path_wide";
	int result                                 = 1;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libmodi_internal_handle_t *) handle;

	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	if( path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path.",
		 function );

		return( -1 );
	}
	if( path_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid path length value exceeds maximum.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	if( internal_handle->io_handle->image_type == LIBMODI_IMAGE_TYPE_SPARSE_BUNDLE )
	{
		if( libmodi_internal_handle_set_bands_directory_path_wide(
		     internal_handle,
		     path,
		     path_length,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set bands directory path.",
			 function );

			result = -1;
		}
	}
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Retrieves the media size
 * Returns the 1 if succesful or -1 on error
 */
int libmodi_handle_get_media_size(
     libmodi_handle_t *handle,
     size64_t *media_size,
     libcerror_error_t **error )
{
	libmodi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libmodi_handle_get_media_size";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libmodi_internal_handle_t *) handle;

	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing file IO handle.",
		 function );

		return( -1 );
	}
	if( media_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid media size.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	*media_size = internal_handle->io_handle->media_size;

#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}

