/*
 * Library handle type test program
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
#include <file_stream.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#if defined( TIME_WITH_SYS_TIME )
#include <sys/time.h>
#include <time.h>
#elif defined( HAVE_SYS_TIME_H )
#include <sys/time.h>
#else
#include <time.h>
#endif

#include "modi_test_functions.h"
#include "modi_test_getopt.h"
#include "modi_test_libbfio.h"
#include "modi_test_libcdirectory.h"
#include "modi_test_libcerror.h"
#include "modi_test_libcpath.h"
#include "modi_test_libmodi.h"
#include "modi_test_macros.h"
#include "modi_test_memory.h"
#include "modi_test_unused.h"

#include "../libmodi/libmodi_handle.h"

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make modi_test_handle generate verbose output
#define MODI_TEST_HANDLE_VERBOSE
 */

#define MODI_TEST_HANDLE_READ_BUFFER_SIZE	4096

#if !defined( LIBMODI_HAVE_BFIO )

LIBMODI_EXTERN \
int libmodi_handle_open_file_io_handle(
     libmodi_handle_t *handle,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libmodi_error_t **error );

#endif /* !defined( LIBMODI_HAVE_BFIO ) */

/* Creates and opens a source handle
 * Returns 1 if successful or -1 on error
 */
int modi_test_handle_open_source(
     libmodi_handle_t **handle,
     const system_character_t *source,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function = "modi_test_handle_open_source";
	size_t string_length  = 0;
	int result            = 0;

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
	if( libmodi_handle_initialize(
	     handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize handle.",
		 function );

		goto on_error;
	}
	result = libmodi_handle_open_file_io_handle(
	          *handle,
	          file_io_handle,
	          LIBMODI_OPEN_READ,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open handle.",
		 function );

		goto on_error;
	}
	string_length = system_string_length(
	                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libmodi_handle_set_band_data_files_path_wide(
	          *handle,
	          source,
	          string_length,
	          error );
#else
	result = libmodi_handle_set_band_data_files_path(
	          *handle,
	          source,
	          string_length,
	          error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set band data files path.",
		 function );

		goto on_error;
	}
	if( libmodi_handle_open_band_data_files(
	     *handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open band data files.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *handle != NULL )
	{
		libmodi_handle_free(
		 handle,
		 NULL );
	}
	return( -1 );
}

/* Closes and frees a source handle
 * Returns 1 if successful or -1 on error
 */
int modi_test_handle_close_source(
     libmodi_handle_t **handle,
     libcerror_error_t **error )
{
	static char *function = "modi_test_handle_close_source";
	int result            = 0;

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
	if( libmodi_handle_free(
	     handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free handle.",
		 function );

		result = -1;
	}
	return( result );
}

/* Tests the libmodi_handle_initialize function
 * Returns 1 if successful or 0 if not
 */
int modi_test_handle_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libmodi_handle_t *handle        = NULL;
	int result                      = 0;

#if defined( HAVE_MODI_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libmodi_handle_initialize(
	          &handle,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libmodi_handle_free(
	          &handle,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "handle",
	 handle );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libmodi_handle_initialize(
	          NULL,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	handle = (libmodi_handle_t *) 0x12345678UL;

	result = libmodi_handle_initialize(
	          &handle,
	          &error );

	handle = NULL;

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_MODI_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libmodi_handle_initialize with malloc failing
		 */
		modi_test_malloc_attempts_before_fail = test_number;

		result = libmodi_handle_initialize(
		          &handle,
		          &error );

		if( modi_test_malloc_attempts_before_fail != -1 )
		{
			modi_test_malloc_attempts_before_fail = -1;

			if( handle != NULL )
			{
				libmodi_handle_free(
				 &handle,
				 NULL );
			}
		}
		else
		{
			MODI_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			MODI_TEST_ASSERT_IS_NULL(
			 "handle",
			 handle );

			MODI_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libmodi_handle_initialize with memset failing
		 */
		modi_test_memset_attempts_before_fail = test_number;

		result = libmodi_handle_initialize(
		          &handle,
		          &error );

		if( modi_test_memset_attempts_before_fail != -1 )
		{
			modi_test_memset_attempts_before_fail = -1;

			if( handle != NULL )
			{
				libmodi_handle_free(
				 &handle,
				 NULL );
			}
		}
		else
		{
			MODI_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			MODI_TEST_ASSERT_IS_NULL(
			 "handle",
			 handle );

			MODI_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_MODI_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( handle != NULL )
	{
		libmodi_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libmodi_handle_free function
 * Returns 1 if successful or 0 if not
 */
int modi_test_handle_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libmodi_handle_free(
	          NULL,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libmodi_handle_open function
 * Returns 1 if successful or 0 if not
 */
int modi_test_handle_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error = NULL;
	libmodi_handle_t *handle = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = modi_test_get_narrow_source(
	          source,
	          narrow_source,
	          256,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libmodi_handle_initialize(
	          &handle,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libmodi_handle_open(
	          handle,
	          narrow_source,
	          LIBMODI_OPEN_READ,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libmodi_handle_open(
	          NULL,
	          narrow_source,
	          LIBMODI_OPEN_READ,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libmodi_handle_open(
	          handle,
	          NULL,
	          LIBMODI_OPEN_READ,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libmodi_handle_open(
	          handle,
	          narrow_source,
	          -1,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test open when already opened
	 */
	result = libmodi_handle_open(
	          handle,
	          narrow_source,
	          LIBMODI_OPEN_READ,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libmodi_handle_free(
	          &handle,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "handle",
	 handle );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( handle != NULL )
	{
		libmodi_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libmodi_handle_open_wide function
 * Returns 1 if successful or 0 if not
 */
int modi_test_handle_open_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error = NULL;
	libmodi_handle_t *handle = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = modi_test_get_wide_source(
	          source,
	          wide_source,
	          256,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libmodi_handle_initialize(
	          &handle,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libmodi_handle_open_wide(
	          handle,
	          wide_source,
	          LIBMODI_OPEN_READ,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libmodi_handle_open_wide(
	          NULL,
	          wide_source,
	          LIBMODI_OPEN_READ,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libmodi_handle_open_wide(
	          handle,
	          NULL,
	          LIBMODI_OPEN_READ,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libmodi_handle_open_wide(
	          handle,
	          wide_source,
	          -1,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test open when already opened
	 */
	result = libmodi_handle_open_wide(
	          handle,
	          wide_source,
	          LIBMODI_OPEN_READ,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libmodi_handle_free(
	          &handle,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "handle",
	 handle );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( handle != NULL )
	{
		libmodi_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libmodi_handle_open_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int modi_test_handle_open_file_io_handle(
     const system_character_t *source )
{
	libbfio_handle_t *file_io_handle     = NULL;
	libcdirectory_directory_t *directory = NULL;
	libcerror_error_t *error             = NULL;
	libmodi_handle_t *handle             = NULL;
	system_character_t *info_plist_path  = NULL;
	size_t info_plist_path_size          = 0;
	size_t string_length                 = 0;
	int is_directory                     = 0;
	int result                           = 0;

	/* Initialize test
	 */
	result = libbfio_file_initialize(
	          &file_io_handle,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        MODI_TEST_ASSERT_IS_NOT_NULL(
         "file_io_handle",
         file_io_handle );

        MODI_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libcdirectory_directory_initialize(
	          &directory,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        MODI_TEST_ASSERT_IS_NOT_NULL(
         "directory",
         directory );

        MODI_TEST_ASSERT_IS_NULL(
         "error",
         error );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	is_directory = libcdirectory_directory_open_wide(
	                directory,
	                source,
	                NULL );
#else
	is_directory = libcdirectory_directory_open(
	                directory,
	                source,
	                NULL );
#endif

	result = libcdirectory_directory_free(
	          &directory,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
         "directory",
         directory );

        MODI_TEST_ASSERT_IS_NULL(
         "error",
         error );

	string_length = system_string_length(
	                 source );

	if( is_directory == 1 )
	{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libcpath_path_join_wide(
		          &info_plist_path,
		          &info_plist_path_size,
		          source,
		          string_length,
		          L"Info.plist",
		          10,
		          &error );
#else
		result = libcpath_path_join(
		          &info_plist_path,
		          &info_plist_path_size,
		          source,
		          string_length,
		          "Info.plist",
		          10,
		          &error );
#endif

		MODI_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        MODI_TEST_ASSERT_IS_NOT_NULL(
	         "info_plist_path",
	         info_plist_path );

	        MODI_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libbfio_file_set_name_wide(
		          file_io_handle,
		          info_plist_path,
		          info_plist_path_size - 1,
		          &error );
#else
		result = libbfio_file_set_name(
		          file_io_handle,
		          info_plist_path,
		          info_plist_path_size - 1,
		          &error );
#endif
	}
	else
	{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libbfio_file_set_name_wide(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#else
		result = libbfio_file_set_name(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#endif
	}
	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        MODI_TEST_ASSERT_IS_NULL(
         "error",
         error );

	if( info_plist_path != NULL )
	{
		memory_free(
		 info_plist_path );

		info_plist_path = NULL;
	} 
	result = libmodi_handle_initialize(
	          &handle,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libmodi_handle_open_file_io_handle(
	          handle,
	          file_io_handle,
	          LIBMODI_OPEN_READ,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libmodi_handle_open_file_io_handle(
	          NULL,
	          file_io_handle,
	          LIBMODI_OPEN_READ,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libmodi_handle_open_file_io_handle(
	          handle,
	          NULL,
	          LIBMODI_OPEN_READ,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libmodi_handle_open_file_io_handle(
	          handle,
	          file_io_handle,
	          -1,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test open when already opened
	 */
	result = libmodi_handle_open_file_io_handle(
	          handle,
	          file_io_handle,
	          LIBMODI_OPEN_READ,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libmodi_handle_free(
	          &handle,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "handle",
	 handle );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_handle_free(
	          &file_io_handle,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
         "file_io_handle",
         file_io_handle );

        MODI_TEST_ASSERT_IS_NULL(
         "error",
         error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( handle != NULL )
	{
		libmodi_handle_free(
		 &handle,
		 NULL );
	}
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
	return( 0 );
}

/* Tests the libmodi_handle_close function
 * Returns 1 if successful or 0 if not
 */
int modi_test_handle_close(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libmodi_handle_close(
	          NULL,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libmodi_handle_open and libmodi_handle_close functions
 * Returns 1 if successful or 0 if not
 */
int modi_test_handle_open_close(
     const system_character_t *source )
{
	libcerror_error_t *error = NULL;
	libmodi_handle_t *handle = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libmodi_handle_initialize(
	          &handle,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libmodi_handle_open_wide(
	          handle,
	          source,
	          LIBMODI_OPEN_READ,
	          &error );
#else
	result = libmodi_handle_open(
	          handle,
	          source,
	          LIBMODI_OPEN_READ,
	          &error );
#endif

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libmodi_handle_close(
	          handle,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close a second time to validate clean up on close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libmodi_handle_open_wide(
	          handle,
	          source,
	          LIBMODI_OPEN_READ,
	          &error );
#else
	result = libmodi_handle_open(
	          handle,
	          source,
	          LIBMODI_OPEN_READ,
	          &error );
#endif

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libmodi_handle_close(
	          handle,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libmodi_handle_free(
	          &handle,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "handle",
	 handle );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( handle != NULL )
	{
		libmodi_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libmodi_handle_signal_abort function
 * Returns 1 if successful or 0 if not
 */
int modi_test_handle_signal_abort(
     libmodi_handle_t *handle )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libmodi_handle_signal_abort(
	          handle,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libmodi_handle_signal_abort(
	          NULL,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libmodi_handle_read_buffer function
 * Returns 1 if successful or 0 if not
 */
int modi_test_handle_read_buffer(
     libmodi_handle_t *handle )
{
	uint8_t buffer[ MODI_TEST_HANDLE_READ_BUFFER_SIZE ];

	libcerror_error_t *error      = NULL;
	time_t timestamp              = 0;
	size64_t media_size           = 0;
	size64_t remaining_media_size = 0;
	size_t read_size              = 0;
	ssize_t read_count            = 0;
	off64_t media_offset          = 0;
	off64_t offset                = 0;
	int number_of_tests           = 1024;
	int random_number             = 0;
	int result                    = 0;
	int test_number               = 0;

	/* Determine size
	 */
	result = libmodi_handle_get_media_size(
	          handle,
	          &media_size,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Reset offset to 0
	 */
	offset = libmodi_handle_seek_offset(
	          handle,
	          0,
	          SEEK_SET,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	read_size = MODI_TEST_HANDLE_READ_BUFFER_SIZE;

	if( media_size < MODI_TEST_HANDLE_READ_BUFFER_SIZE )
	{
		read_size = (size_t) media_size;
	}
	read_count = libmodi_handle_read_buffer(
	              handle,
	              buffer,
	              MODI_TEST_HANDLE_READ_BUFFER_SIZE,
	              &error );

	MODI_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) read_size );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	if( media_size > 8 )
	{
		/* Set offset to media_size - 8
		 */
		offset = libmodi_handle_seek_offset(
		          handle,
		          -8,
		          SEEK_END,
		          &error );

		MODI_TEST_ASSERT_EQUAL_INT64(
		 "offset",
		 offset,
		 (int64_t) media_size - 8 );

		MODI_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Read buffer on media_size boundary
		 */
		read_count = libmodi_handle_read_buffer(
		              handle,
		              buffer,
		              MODI_TEST_HANDLE_READ_BUFFER_SIZE,
		              &error );

		MODI_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) 8 );

		MODI_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Read buffer beyond media_size boundary
		 */
		read_count = libmodi_handle_read_buffer(
		              handle,
		              buffer,
		              MODI_TEST_HANDLE_READ_BUFFER_SIZE,
		              &error );

		MODI_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) 0 );

		MODI_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Stress test read buffer
	 */
	timestamp = time(
	             NULL );

	srand(
	 (unsigned int) timestamp );

	offset = libmodi_handle_seek_offset(
	          handle,
	          0,
	          SEEK_SET,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	remaining_media_size = media_size;

	for( test_number = 0;
	     test_number < number_of_tests;
	     test_number++ )
	{
		random_number = rand();

		MODI_TEST_ASSERT_GREATER_THAN_INT(
		 "random_number",
		 random_number,
		 -1 );

		read_size = (size_t) random_number % MODI_TEST_HANDLE_READ_BUFFER_SIZE;

#if defined( MODI_TEST_HANDLE_VERBOSE )
		fprintf(
		 stdout,
		 "libmodi_handle_read_buffer: at offset: %" PRIi64 " (0x%08" PRIx64 ") of size: %" PRIzd "\n",
		 media_offset,
		 media_offset,
		 read_size );
#endif
		read_count = libmodi_handle_read_buffer(
		              handle,
		              buffer,
		              read_size,
		              &error );

		if( read_size > remaining_media_size )
		{
			read_size = (size_t) remaining_media_size;
		}
		MODI_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) read_size );

		MODI_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		media_offset += read_count;

		result = libmodi_handle_get_offset(
		          handle,
		          &offset,
		          &error );

		MODI_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		MODI_TEST_ASSERT_EQUAL_INT64(
		 "offset",
		 offset,
		 media_offset );

		MODI_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		remaining_media_size -= read_count;

		if( remaining_media_size == 0 )
		{
			offset = libmodi_handle_seek_offset(
			          handle,
			          0,
			          SEEK_SET,
			          &error );

			MODI_TEST_ASSERT_EQUAL_INT64(
			 "offset",
			 offset,
			 (int64_t) 0 );

			MODI_TEST_ASSERT_IS_NULL(
			 "error",
			 error );

			media_offset = 0;

			remaining_media_size = media_size;
		}
	}
	/* Test error cases
	 */
	read_count = libmodi_handle_read_buffer(
	              NULL,
	              buffer,
	              MODI_TEST_HANDLE_READ_BUFFER_SIZE,
	              &error );

	MODI_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libmodi_handle_read_buffer(
	              handle,
	              NULL,
	              MODI_TEST_HANDLE_READ_BUFFER_SIZE,
	              &error );

	MODI_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libmodi_handle_read_buffer(
	              handle,
	              buffer,
	              (size_t) SSIZE_MAX + 1,
	              &error );

	MODI_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libmodi_handle_read_buffer_at_offset function
 * Returns 1 if successful or 0 if not
 */
int modi_test_handle_read_buffer_at_offset(
     libmodi_handle_t *handle )
{
	uint8_t buffer[ MODI_TEST_HANDLE_READ_BUFFER_SIZE ];

	libcerror_error_t *error      = NULL;
	time_t timestamp              = 0;
	size64_t media_size           = 0;
	size64_t remaining_media_size = 0;
	size_t read_size              = 0;
	ssize_t read_count            = 0;
	off64_t media_offset          = 0;
	off64_t offset                = 0;
	int number_of_tests           = 1024;
	int random_number             = 0;
	int result                    = 0;
	int test_number               = 0;

	/* Determine size
	 */
	result = libmodi_handle_get_media_size(
	          handle,
	          &media_size,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	read_size = MODI_TEST_HANDLE_READ_BUFFER_SIZE;

	if( media_size < MODI_TEST_HANDLE_READ_BUFFER_SIZE )
	{
		read_size = (size_t) media_size;
	}
	read_count = libmodi_handle_read_buffer_at_offset(
	              handle,
	              buffer,
	              MODI_TEST_HANDLE_READ_BUFFER_SIZE,
	              0,
	              &error );

	MODI_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) read_size );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	if( media_size > 8 )
	{
		/* Read buffer on media_size boundary
		 */
		read_count = libmodi_handle_read_buffer_at_offset(
		              handle,
		              buffer,
		              MODI_TEST_HANDLE_READ_BUFFER_SIZE,
		              media_size - 8,
		              &error );

		MODI_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) 8 );

		MODI_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Read buffer beyond media_size boundary
		 */
		read_count = libmodi_handle_read_buffer_at_offset(
		              handle,
		              buffer,
		              MODI_TEST_HANDLE_READ_BUFFER_SIZE,
		              media_size + 8,
		              &error );

		MODI_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) 0 );

		MODI_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Stress test read buffer
	 */
	timestamp = time(
	             NULL );

	srand(
	 (unsigned int) timestamp );

	for( test_number = 0;
	     test_number < number_of_tests;
	     test_number++ )
	{
		random_number = rand();

		MODI_TEST_ASSERT_GREATER_THAN_INT(
		 "random_number",
		 random_number,
		 -1 );

		if( media_size > 0 )
		{
			media_offset = (off64_t) random_number % media_size;
		}
		read_size = (size_t) random_number % MODI_TEST_HANDLE_READ_BUFFER_SIZE;

#if defined( MODI_TEST_HANDLE_VERBOSE )
		fprintf(
		 stdout,
		 "libmodi_handle_read_buffer_at_offset: at offset: %" PRIi64 " (0x%08" PRIx64 ") of size: %" PRIzd "\n",
		 media_offset,
		 media_offset,
		 read_size );
#endif
		read_count = libmodi_handle_read_buffer_at_offset(
		              handle,
		              buffer,
		              read_size,
		              media_offset,
		              &error );

		remaining_media_size = media_size - media_offset;

		if( read_size > remaining_media_size )
		{
			read_size = (size_t) remaining_media_size;
		}
		MODI_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) read_size );

		MODI_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		media_offset += read_count;

		result = libmodi_handle_get_offset(
		          handle,
		          &offset,
		          &error );

		MODI_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		MODI_TEST_ASSERT_EQUAL_INT64(
		 "offset",
		 offset,
		 media_offset );

		MODI_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	read_count = libmodi_handle_read_buffer_at_offset(
	              NULL,
	              buffer,
	              MODI_TEST_HANDLE_READ_BUFFER_SIZE,
	              0,
	              &error );

	MODI_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libmodi_handle_read_buffer_at_offset(
	              handle,
	              NULL,
	              MODI_TEST_HANDLE_READ_BUFFER_SIZE,
	              0,
	              &error );

	MODI_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libmodi_handle_read_buffer_at_offset(
	              handle,
	              buffer,
	              (size_t) SSIZE_MAX + 1,
	              0,
	              &error );

	MODI_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libmodi_handle_read_buffer_at_offset(
	              handle,
	              buffer,
	              MODI_TEST_HANDLE_READ_BUFFER_SIZE,
	              -1,
	              &error );

	MODI_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libmodi_handle_seek_offset function
 * Returns 1 if successful or 0 if not
 */
int modi_test_handle_seek_offset(
     libmodi_handle_t *handle )
{
	libcerror_error_t *error = NULL;
	size64_t size            = 0;
	off64_t offset           = 0;

	/* Test regular cases
	 */
	offset = libmodi_handle_seek_offset(
	          handle,
	          0,
	          SEEK_END,
	          &error );

	MODI_TEST_ASSERT_NOT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	size = (size64_t) offset;

	offset = libmodi_handle_seek_offset(
	          handle,
	          1024,
	          SEEK_SET,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 1024 );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset = libmodi_handle_seek_offset(
	          handle,
	          -512,
	          SEEK_CUR,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 512 );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset = libmodi_handle_seek_offset(
	          handle,
	          (off64_t) ( size + 512 ),
	          SEEK_SET,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) ( size + 512 ) );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Reset offset to 0
	 */
	offset = libmodi_handle_seek_offset(
	          handle,
	          0,
	          SEEK_SET,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	offset = libmodi_handle_seek_offset(
	          NULL,
	          0,
	          SEEK_SET,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	offset = libmodi_handle_seek_offset(
	          handle,
	          -1,
	          SEEK_SET,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	offset = libmodi_handle_seek_offset(
	          handle,
	          -1,
	          SEEK_CUR,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	offset = libmodi_handle_seek_offset(
	          handle,
	          (off64_t) ( -1 * ( size + 1 ) ),
	          SEEK_END,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libmodi_handle_get_offset function
 * Returns 1 if successful or 0 if not
 */
int modi_test_handle_get_offset(
     libmodi_handle_t *handle )
{
	libcerror_error_t *error = NULL;
	off64_t offset           = 0;
	int offset_is_set        = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libmodi_handle_get_offset(
	          handle,
	          &offset,
	          &error );

	MODI_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset_is_set = result;

	/* Test error cases
	 */
	result = libmodi_handle_get_offset(
	          NULL,
	          &offset,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	if( offset_is_set != 0 )
	{
		result = libmodi_handle_get_offset(
		          handle,
		          NULL,
		          &error );

		MODI_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		MODI_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libmodi_handle_get_media_size function
 * Returns 1 if successful or 0 if not
 */
int modi_test_handle_get_media_size(
     libmodi_handle_t *handle )
{
	libcerror_error_t *error = NULL;
	size64_t media_size      = 0;
	int media_size_is_set    = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libmodi_handle_get_media_size(
	          handle,
	          &media_size,
	          &error );

	MODI_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	media_size_is_set = result;

	/* Test error cases
	 */
	result = libmodi_handle_get_media_size(
	          NULL,
	          &media_size,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	if( media_size_is_set != 0 )
	{
		result = libmodi_handle_get_media_size(
		          handle,
		          NULL,
		          &error );

		MODI_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		MODI_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc,
     wchar_t * const argv[] )
#else
int main(
     int argc,
     char * const argv[] )
#endif
{
	libbfio_handle_t *file_io_handle     = NULL;
	libcdirectory_directory_t *directory = NULL;
	libcerror_error_t *error             = NULL;
	libmodi_handle_t *handle             = NULL;
	system_character_t *info_plist_path  = NULL;
	system_character_t *source           = NULL;
	system_integer_t option              = 0;
	size_t info_plist_path_size          = 0;
	size_t string_length                 = 0;
	int is_directory                     = 0;
	int result                           = 0;

	while( ( option = modi_test_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );
		}
	}
	if( optind < argc )
	{
		source = argv[ optind ];
	}
#if defined( HAVE_DEBUG_OUTPUT ) && defined( MODI_TEST_HANDLE_VERBOSE )
	libmodi_notify_set_verbose(
	 1 );
	libmodi_notify_set_stream(
	 stderr,
	 NULL );
#endif

	MODI_TEST_RUN(
	 "libmodi_handle_initialize",
	 modi_test_handle_initialize );

	MODI_TEST_RUN(
	 "libmodi_handle_free",
	 modi_test_handle_free );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
		result = libcdirectory_directory_initialize(
		          &directory,
		          &error );

		MODI_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        MODI_TEST_ASSERT_IS_NOT_NULL(
	         "directory",
	         directory );

	        MODI_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		is_directory = libcdirectory_directory_open_wide(
		                directory,
		                source,
		                NULL );
#else
		is_directory = libcdirectory_directory_open(
		                directory,
		                source,
		                NULL );
#endif

		result = libcdirectory_directory_free(
		          &directory,
		          &error );

		MODI_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		MODI_TEST_ASSERT_IS_NULL(
	         "directory",
	         directory );

	        MODI_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		result = libbfio_file_initialize(
		          &file_io_handle,
		          &error );

		MODI_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        MODI_TEST_ASSERT_IS_NOT_NULL(
	         "file_io_handle",
	         file_io_handle );

	        MODI_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		string_length = system_string_length(
		                 source );

		if( is_directory == 1 )
		{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libcpath_path_join_wide(
			          &info_plist_path,
			          &info_plist_path_size,
			          source,
			          string_length,
			          L"Info.plist",
			          10,
			          &error );
#else
			result = libcpath_path_join(
			          &info_plist_path,
			          &info_plist_path_size,
			          source,
			          string_length,
			          "Info.plist",
			          10,
			          &error );
#endif

			MODI_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 1 );

		        MODI_TEST_ASSERT_IS_NOT_NULL(
		         "info_plist_path",
		         info_plist_path );

		        MODI_TEST_ASSERT_IS_NULL(
		         "error",
		         error );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libbfio_file_set_name_wide(
			          file_io_handle,
			          info_plist_path,
			          info_plist_path_size - 1,
			          &error );
#else
			result = libbfio_file_set_name(
			          file_io_handle,
			          info_plist_path,
			          info_plist_path_size - 1,
			          &error );
#endif
		}
		else
		{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libbfio_file_set_name_wide(
			          file_io_handle,
			          source,
			          string_length,
			          &error );
#else
			result = libbfio_file_set_name(
			          file_io_handle,
			          source,
			          string_length,
			          &error );
#endif
		}
		MODI_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        MODI_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		if( info_plist_path != NULL )
		{
			memory_free(
			 info_plist_path );

			info_plist_path = NULL;
		} 
		MODI_TEST_RUN_WITH_ARGS(
		 "libmodi_handle_open",
		 modi_test_handle_open,
		 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		MODI_TEST_RUN_WITH_ARGS(
		 "libmodi_handle_open_wide",
		 modi_test_handle_open_wide,
		 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

		MODI_TEST_RUN_WITH_ARGS(
		 "libmodi_handle_open_file_io_handle",
		 modi_test_handle_open_file_io_handle,
		 source );

		MODI_TEST_RUN(
		 "libmodi_handle_close",
		 modi_test_handle_close );

		MODI_TEST_RUN_WITH_ARGS(
		 "libmodi_handle_open_close",
		 modi_test_handle_open_close,
		 source );

		/* Initialize handle for tests
		 */
		result = modi_test_handle_open_source(
		          &handle,
		          source,
		          file_io_handle,
		          &error );

		MODI_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		MODI_TEST_ASSERT_IS_NOT_NULL(
		 "handle",
		 handle );

		MODI_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		MODI_TEST_RUN_WITH_ARGS(
		 "libmodi_handle_signal_abort",
		 modi_test_handle_signal_abort,
		 handle );

#if defined( __GNUC__ ) && !defined( LIBMODI_DLL_IMPORT )

		/* TODO: add tests for libmodi_handle_set_bands_directory_path */

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		/* TODO: add tests for libmodi_handle_set_bands_directory_path_wide */

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#endif /* defined( __GNUC__ ) && !defined( LIBMODI_DLL_IMPORT ) */

		/* TODO: add tests for libmodi_handle_open_band_data_files */

		/* TODO: add tests for libmodi_handle_open_band_data_files_file_io_pool */

#if defined( __GNUC__ ) && !defined( LIBMODI_DLL_IMPORT )

		/* TODO: add tests for libmodi_handle_open_band_data_file */

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		/* TODO: add tests for libmodi_handle_open_band_data_file_wide */

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

		/* TODO: add tests for libmodi_handle_open_read */

#endif /* defined( __GNUC__ ) && !defined( LIBMODI_DLL_IMPORT ) */

		MODI_TEST_RUN_WITH_ARGS(
		 "libmodi_handle_read_buffer",
		 modi_test_handle_read_buffer,
		 handle );

		MODI_TEST_RUN_WITH_ARGS(
		 "libmodi_handle_read_buffer_at_offset",
		 modi_test_handle_read_buffer_at_offset,
		 handle );

		/* TODO: add tests for libmodi_handle_write_buffer */

		/* TODO: add tests for libmodi_handle_write_buffer_at_offset */

		MODI_TEST_RUN_WITH_ARGS(
		 "libmodi_handle_seek_offset",
		 modi_test_handle_seek_offset,
		 handle );

		MODI_TEST_RUN_WITH_ARGS(
		 "libmodi_handle_get_offset",
		 modi_test_handle_get_offset,
		 handle );

		/* TODO: add tests for libmodi_handle_set_maximum_number_of_open_handles */

		MODI_TEST_RUN_WITH_ARGS(
		 "libmodi_handle_get_media_size",
		 modi_test_handle_get_media_size,
		 handle );

		/* Clean up
		 */
		result = modi_test_handle_close_source(
		          &handle,
		          &error );

		MODI_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		MODI_TEST_ASSERT_IS_NULL(
		 "handle",
		 handle );

		MODI_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = libbfio_handle_free(
		          &file_io_handle,
		          &error );

		MODI_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		MODI_TEST_ASSERT_IS_NULL(
	         "file_io_handle",
	         file_io_handle );

	        MODI_TEST_ASSERT_IS_NULL(
	         "error",
	         error );
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( handle != NULL )
	{
		libmodi_handle_free(
		 &handle,
		 NULL );
	}
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
	return( EXIT_FAILURE );
}

