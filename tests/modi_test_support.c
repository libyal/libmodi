/*
 * Library support functions test program
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

#if !defined( LIBMODI_HAVE_BFIO )

LIBMODI_EXTERN \
int libmodi_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

#endif /* !defined( LIBMODI_HAVE_BFIO ) */

/* Tests the libmodi_get_version function
 * Returns 1 if successful or 0 if not
 */
int modi_test_get_version(
     void )
{
	const char *version_string = NULL;
	int result                 = 0;

	version_string = libmodi_get_version();

	result = narrow_string_compare(
	          version_string,
	          LIBMODI_VERSION_STRING,
	          9 );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	return( 1 );

on_error:
	return( 0 );
}

/* Tests the libmodi_get_access_flags_read function
 * Returns 1 if successful or 0 if not
 */
int modi_test_get_access_flags_read(
     void )
{
	int access_flags = 0;

	access_flags = libmodi_get_access_flags_read();

	MODI_TEST_ASSERT_EQUAL_INT(
	 "access_flags",
	 access_flags,
	 LIBMODI_ACCESS_FLAG_READ );

	return( 1 );

on_error:
	return( 0 );
}

/* Tests the libmodi_get_codepage function
 * Returns 1 if successful or 0 if not
 */
int modi_test_get_codepage(
     void )
{
	libcerror_error_t *error = NULL;
	int codepage             = 0;
	int result               = 0;

	result = libmodi_get_codepage(
	          &codepage,
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
	result = libmodi_get_codepage(
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

/* Tests the libmodi_set_codepage function
 * Returns 1 if successful or 0 if not
 */
int modi_test_set_codepage(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	result = libmodi_set_codepage(
	          0,
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
	result = libmodi_set_codepage(
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libmodi_check_file_signature function
 * Returns 1 if successful or 0 if not
 */
int modi_test_check_file_signature(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	if( source != NULL )
	{
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

		/* Test check file signature
		 */
		result = libmodi_check_file_signature(
		          narrow_source,
		          &error );

		/* Note that libmodi_check_file_signature will return 0 for a "raw" modi file
		 */
		MODI_TEST_ASSERT_NOT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		MODI_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libmodi_check_file_signature(
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

	result = libmodi_check_file_signature(
	          "",
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

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libmodi_check_file_signature_wide function
 * Returns 1 if successful or 0 if not
 */
int modi_test_check_file_signature_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	if( source != NULL )
	{
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

		/* Test check file signature
		 */
		result = libmodi_check_file_signature_wide(
		          wide_source,
		          &error );

		MODI_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		MODI_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libmodi_check_file_signature_wide(
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

	result = libmodi_check_file_signature_wide(
	          L"",
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

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libmodi_check_file_signature_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int modi_test_check_file_signature_file_io_handle(
     const system_character_t *source )
{
	uint8_t empty_block[ 8192 ];

	libbfio_handle_t *file_io_handle     = NULL;
	libcdirectory_directory_t *directory = NULL;
	libcerror_error_t *error             = NULL;
	system_character_t *info_plist_path  = NULL;
	void *memset_result                  = NULL;
	size_t info_plist_path_size          = 0;
	size_t source_length                 = 0;
	int is_directory                     = 0;
	int result                           = 0;

	/* Initialize test
	 */
	memset_result = memory_set(
	                 empty_block,
	                 0,
	                 sizeof( uint8_t ) * 8192 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "memset_result",
	 memset_result );

	if( source != NULL )
	{
		/* Initialize test
		 */
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

		source_length = system_string_length(
		                 source );

		if( is_directory == 1 )
		{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libcpath_path_join_wide(
			          &info_plist_path,
			          &info_plist_path_size,
			          source,
			          source_length,
			          L"Info.plist",
			          10,
			          &error );
#else
			result = libcpath_path_join(
			          &info_plist_path,
			          &info_plist_path_size,
			          source,
			          source_length,
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
			          source_length,
			          &error );
#else
			result = libbfio_file_set_name(
			          file_io_handle,
			          source,
			          source_length,
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
		result = libbfio_handle_open(
		          file_io_handle,
		          LIBBFIO_OPEN_READ,
		          &error );

		MODI_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		MODI_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Test check file signature
		 */
		result = libmodi_check_file_signature_file_io_handle(
		          file_io_handle,
		          &error );

		/* Note that libmodi_check_file_signature_file_io_handle will return 0 for a "raw" modi file
		 */
		MODI_TEST_ASSERT_NOT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		MODI_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libmodi_check_file_signature_file_io_handle(
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

	/* Clean up
	 */
	if( source != NULL )
	{
		result = libbfio_handle_close(
		          file_io_handle,
		          &error );

		MODI_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

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
	/* Test check file signature with data too small
	 */
	result = modi_test_open_file_io_handle(
	          &file_io_handle,
	          empty_block,
	          sizeof( uint8_t ) * 1,
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

	result = libmodi_check_file_signature_file_io_handle(
	          file_io_handle,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = modi_test_close_file_io_handle(
	          &file_io_handle,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test check file signature with empty block
	 */
	result = modi_test_open_file_io_handle(
	          &file_io_handle,
	          empty_block,
	          sizeof( uint8_t ) * 8192,
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

	result = libmodi_check_file_signature_file_io_handle(
	          file_io_handle,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = modi_test_close_file_io_handle(
	          &file_io_handle,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

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
	system_character_t *source = NULL;
	system_integer_t option    = 0;

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
	MODI_TEST_RUN(
	 "libmodi_get_version",
	 modi_test_get_version );

	MODI_TEST_RUN(
	 "libmodi_get_access_flags_read",
	 modi_test_get_access_flags_read );

	MODI_TEST_RUN(
	 "libmodi_get_codepage",
	 modi_test_get_codepage );

	MODI_TEST_RUN(
	 "libmodi_set_codepage",
	 modi_test_set_codepage );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	MODI_TEST_RUN_WITH_ARGS(
	 "libmodi_check_file_signature",
	 modi_test_check_file_signature,
	 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

	MODI_TEST_RUN_WITH_ARGS(
	 "libmodi_check_file_signature_wide",
	 modi_test_check_file_signature_wide,
	 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

	MODI_TEST_RUN_WITH_ARGS(
	 "libmodi_check_file_signature_file_io_handle",
	 modi_test_check_file_signature_file_io_handle,
	 source );

#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

