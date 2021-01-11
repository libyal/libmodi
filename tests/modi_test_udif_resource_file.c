/*
 * Library udif_resource_file type test program
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
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "modi_test_functions.h"
#include "modi_test_libbfio.h"
#include "modi_test_libcerror.h"
#include "modi_test_libmodi.h"
#include "modi_test_macros.h"
#include "modi_test_memory.h"
#include "modi_test_unused.h"

#include "../libmodi/libmodi_udif_resource_file.h"

uint8_t modi_test_udif_resource_file_data1[ 512 ] = {
	0x6b, 0x6f, 0x6c, 0x79, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x01,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x2c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x2c,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x20, 0x33, 0x50, 0xab, 0xf9, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

#if defined( __GNUC__ ) && !defined( LIBMODI_DLL_IMPORT )

/* Tests the libmodi_udif_resource_file_initialize function
 * Returns 1 if successful or 0 if not
 */
int modi_test_udif_resource_file_initialize(
     void )
{
	libcerror_error_t *error                    = NULL;
	libmodi_udif_resource_file_t *resource_file = NULL;
	int result                                  = 0;

#if defined( HAVE_MODI_TEST_MEMORY )
	int number_of_malloc_fail_tests             = 1;
	int number_of_memset_fail_tests             = 1;
	int test_number                             = 0;
#endif

	/* Test regular cases
	 */
	result = libmodi_udif_resource_file_initialize(
	          &resource_file,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "resource_file",
	 resource_file );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libmodi_udif_resource_file_free(
	          &resource_file,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "resource_file",
	 resource_file );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libmodi_udif_resource_file_initialize(
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

	resource_file = (libmodi_udif_resource_file_t *) 0x12345678UL;

	result = libmodi_udif_resource_file_initialize(
	          &resource_file,
	          &error );

	resource_file = NULL;

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
		/* Test libmodi_udif_resource_file_initialize with malloc failing
		 */
		modi_test_malloc_attempts_before_fail = test_number;

		result = libmodi_udif_resource_file_initialize(
		          &resource_file,
		          &error );

		if( modi_test_malloc_attempts_before_fail != -1 )
		{
			modi_test_malloc_attempts_before_fail = -1;

			if( resource_file != NULL )
			{
				libmodi_udif_resource_file_free(
				 &resource_file,
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
			 "resource_file",
			 resource_file );

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
		/* Test libmodi_udif_resource_file_initialize with memset failing
		 */
		modi_test_memset_attempts_before_fail = test_number;

		result = libmodi_udif_resource_file_initialize(
		          &resource_file,
		          &error );

		if( modi_test_memset_attempts_before_fail != -1 )
		{
			modi_test_memset_attempts_before_fail = -1;

			if( resource_file != NULL )
			{
				libmodi_udif_resource_file_free(
				 &resource_file,
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
			 "resource_file",
			 resource_file );

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
	if( resource_file != NULL )
	{
		libmodi_udif_resource_file_free(
		 &resource_file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libmodi_udif_resource_file_free function
 * Returns 1 if successful or 0 if not
 */
int modi_test_udif_resource_file_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libmodi_udif_resource_file_free(
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

/* Tests the libmodi_udif_resource_file_read_data function
 * Returns 1 if successful or 0 if not
 */
int modi_test_udif_resource_file_read_data(
     void )
{
	libcerror_error_t *error                    = NULL;
	libmodi_udif_resource_file_t *resource_file = NULL;
	int result                                  = 0;

	/* Initialize test
	 */
	result = libmodi_udif_resource_file_initialize(
	          &resource_file,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "resource_file",
	 resource_file );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libmodi_udif_resource_file_read_data(
	          resource_file,
	          modi_test_udif_resource_file_data1,
	          512,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular case where signature is invalid
	 */
	byte_stream_copy_from_uint32_big_endian(
	 modi_test_udif_resource_file_data1,
	 0xffffffffUL );

	result = libmodi_udif_resource_file_read_data(
	          resource_file,
	          modi_test_udif_resource_file_data1,
	          512,
	          &error );

	byte_stream_copy_from_uint32_big_endian(
	 modi_test_udif_resource_file_data1,
	 0x6b6f6c79UL );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libmodi_udif_resource_file_read_data(
	          NULL,
	          modi_test_udif_resource_file_data1,
	          512,
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

	result = libmodi_udif_resource_file_read_data(
	          resource_file,
	          NULL,
	          512,
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

	result = libmodi_udif_resource_file_read_data(
	          resource_file,
	          modi_test_udif_resource_file_data1,
	          (size_t) SSIZE_MAX + 1,
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

	result = libmodi_udif_resource_file_read_data(
	          resource_file,
	          modi_test_udif_resource_file_data1,
	          0,
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
	result = libmodi_udif_resource_file_free(
	          &resource_file,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "resource_file",
	 resource_file );

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
	if( resource_file != NULL )
	{
		libmodi_udif_resource_file_free(
		 &resource_file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libmodi_udif_resource_file_read_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int modi_test_udif_resource_file_read_file_io_handle(
     void )
{
	libbfio_handle_t *file_io_handle            = NULL;
	libcerror_error_t *error                    = NULL;
	libmodi_udif_resource_file_t *resource_file = NULL;
	int result                                  = 0;

	/* Initialize test
	 */
	result = libmodi_udif_resource_file_initialize(
	          &resource_file,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "resource_file",
	 resource_file );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize file IO handle
	 */
	result = modi_test_open_file_io_handle(
	          &file_io_handle,
	          modi_test_udif_resource_file_data1,
	          512,
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

	/* Test regular cases
	 */
	result = libmodi_udif_resource_file_read_file_io_handle(
	          resource_file,
	          file_io_handle,
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
	result = libmodi_udif_resource_file_read_file_io_handle(
	          NULL,
	          file_io_handle,
	          0,
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

	result = libmodi_udif_resource_file_read_file_io_handle(
	          resource_file,
	          NULL,
	          0,
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

	result = libmodi_udif_resource_file_read_file_io_handle(
	          resource_file,
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

	/* Clean up file IO handle
	 */
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

	/* Test data too small
	 */
	result = modi_test_open_file_io_handle(
	          &file_io_handle,
	          modi_test_udif_resource_file_data1,
	          8,
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

	result = libmodi_udif_resource_file_read_file_io_handle(
	          resource_file,
	          file_io_handle,
	          0,
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

	/* Clean up
	 */
	result = libmodi_udif_resource_file_free(
	          &resource_file,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "resource_file",
	 resource_file );

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
	if( resource_file != NULL )
	{
		libmodi_udif_resource_file_free(
		 &resource_file,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBMODI_DLL_IMPORT ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc MODI_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] MODI_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc MODI_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] MODI_TEST_ATTRIBUTE_UNUSED )
#endif
{
	MODI_TEST_UNREFERENCED_PARAMETER( argc )
	MODI_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBMODI_DLL_IMPORT )

	MODI_TEST_RUN(
	 "libmodi_udif_resource_file_initialize",
	 modi_test_udif_resource_file_initialize );

	MODI_TEST_RUN(
	 "libmodi_udif_resource_file_free",
	 modi_test_udif_resource_file_free );

	MODI_TEST_RUN(
	 "libmodi_udif_resource_file_read_data",
	 modi_test_udif_resource_file_read_data );

	MODI_TEST_RUN(
	 "libmodi_udif_resource_file_read_file_io_handle",
	 modi_test_udif_resource_file_read_file_io_handle );

#endif /* defined( __GNUC__ ) && !defined( LIBMODI_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBMODI_DLL_IMPORT )

on_error:
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBMODI_DLL_IMPORT ) */
}

