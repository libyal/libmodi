/*
 * Library sparse_bundle_xml_plist type test program
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

#include "../libmodi/libmodi_sparse_bundle_xml_plist.h"

uint8_t modi_test_sparse_bundle_xml_plist_data1[ 494 ] = {
	0x3c, 0x3f, 0x78, 0x6d, 0x6c, 0x20, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x3d, 0x22, 0x31,
	0x2e, 0x30, 0x22, 0x20, 0x65, 0x6e, 0x63, 0x6f, 0x64, 0x69, 0x6e, 0x67, 0x3d, 0x22, 0x55, 0x54,
	0x46, 0x2d, 0x38, 0x22, 0x3f, 0x3e, 0x0a, 0x3c, 0x21, 0x44, 0x4f, 0x43, 0x54, 0x59, 0x50, 0x45,
	0x20, 0x70, 0x6c, 0x69, 0x73, 0x74, 0x20, 0x50, 0x55, 0x42, 0x4c, 0x49, 0x43, 0x20, 0x22, 0x2d,
	0x2f, 0x2f, 0x41, 0x70, 0x70, 0x6c, 0x65, 0x2f, 0x2f, 0x44, 0x54, 0x44, 0x20, 0x50, 0x4c, 0x49,
	0x53, 0x54, 0x20, 0x31, 0x2e, 0x30, 0x2f, 0x2f, 0x45, 0x4e, 0x22, 0x20, 0x22, 0x68, 0x74, 0x74,
	0x70, 0x3a, 0x2f, 0x2f, 0x77, 0x77, 0x77, 0x2e, 0x61, 0x70, 0x70, 0x6c, 0x65, 0x2e, 0x63, 0x6f,
	0x6d, 0x2f, 0x44, 0x54, 0x44, 0x73, 0x2f, 0x50, 0x72, 0x6f, 0x70, 0x65, 0x72, 0x74, 0x79, 0x4c,
	0x69, 0x73, 0x74, 0x2d, 0x31, 0x2e, 0x30, 0x2e, 0x64, 0x74, 0x64, 0x22, 0x3e, 0x0a, 0x3c, 0x70,
	0x6c, 0x69, 0x73, 0x74, 0x20, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x3d, 0x22, 0x31, 0x2e,
	0x30, 0x22, 0x3e, 0x0a, 0x3c, 0x64, 0x69, 0x63, 0x74, 0x3e, 0x0a, 0x09, 0x3c, 0x6b, 0x65, 0x79,
	0x3e, 0x43, 0x46, 0x42, 0x75, 0x6e, 0x64, 0x6c, 0x65, 0x49, 0x6e, 0x66, 0x6f, 0x44, 0x69, 0x63,
	0x74, 0x69, 0x6f, 0x6e, 0x61, 0x72, 0x79, 0x56, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x3c, 0x2f,
	0x6b, 0x65, 0x79, 0x3e, 0x0a, 0x09, 0x3c, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x3e, 0x36, 0x2e,
	0x30, 0x3c, 0x2f, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x3e, 0x0a, 0x09, 0x3c, 0x6b, 0x65, 0x79,
	0x3e, 0x62, 0x61, 0x6e, 0x64, 0x2d, 0x73, 0x69, 0x7a, 0x65, 0x3c, 0x2f, 0x6b, 0x65, 0x79, 0x3e,
	0x0a, 0x09, 0x3c, 0x69, 0x6e, 0x74, 0x65, 0x67, 0x65, 0x72, 0x3e, 0x38, 0x33, 0x38, 0x38, 0x36,
	0x30, 0x38, 0x3c, 0x2f, 0x69, 0x6e, 0x74, 0x65, 0x67, 0x65, 0x72, 0x3e, 0x0a, 0x09, 0x3c, 0x6b,
	0x65, 0x79, 0x3e, 0x62, 0x75, 0x6e, 0x64, 0x6c, 0x65, 0x2d, 0x62, 0x61, 0x63, 0x6b, 0x69, 0x6e,
	0x67, 0x73, 0x74, 0x6f, 0x72, 0x65, 0x2d, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x3c, 0x2f,
	0x6b, 0x65, 0x79, 0x3e, 0x0a, 0x09, 0x3c, 0x69, 0x6e, 0x74, 0x65, 0x67, 0x65, 0x72, 0x3e, 0x31,
	0x3c, 0x2f, 0x69, 0x6e, 0x74, 0x65, 0x67, 0x65, 0x72, 0x3e, 0x0a, 0x09, 0x3c, 0x6b, 0x65, 0x79,
	0x3e, 0x64, 0x69, 0x73, 0x6b, 0x69, 0x6d, 0x61, 0x67, 0x65, 0x2d, 0x62, 0x75, 0x6e, 0x64, 0x6c,
	0x65, 0x2d, 0x74, 0x79, 0x70, 0x65, 0x3c, 0x2f, 0x6b, 0x65, 0x79, 0x3e, 0x0a, 0x09, 0x3c, 0x73,
	0x74, 0x72, 0x69, 0x6e, 0x67, 0x3e, 0x63, 0x6f, 0x6d, 0x2e, 0x61, 0x70, 0x70, 0x6c, 0x65, 0x2e,
	0x64, 0x69, 0x73, 0x6b, 0x69, 0x6d, 0x61, 0x67, 0x65, 0x2e, 0x73, 0x70, 0x61, 0x72, 0x73, 0x65,
	0x62, 0x75, 0x6e, 0x64, 0x6c, 0x65, 0x3c, 0x2f, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x3e, 0x0a,
	0x09, 0x3c, 0x6b, 0x65, 0x79, 0x3e, 0x73, 0x69, 0x7a, 0x65, 0x3c, 0x2f, 0x6b, 0x65, 0x79, 0x3e,
	0x0a, 0x09, 0x3c, 0x69, 0x6e, 0x74, 0x65, 0x67, 0x65, 0x72, 0x3e, 0x34, 0x31, 0x39, 0x34, 0x33,
	0x30, 0x34, 0x3c, 0x2f, 0x69, 0x6e, 0x74, 0x65, 0x67, 0x65, 0x72, 0x3e, 0x0a, 0x3c, 0x2f, 0x64,
	0x69, 0x63, 0x74, 0x3e, 0x0a, 0x3c, 0x2f, 0x70, 0x6c, 0x69, 0x73, 0x74, 0x3e, 0x0a };

#if defined( __GNUC__ ) && !defined( LIBMODI_DLL_IMPORT )

/* Tests the libmodi_sparse_bundle_xml_plist_initialize function
 * Returns 1 if successful or 0 if not
 */
int modi_test_sparse_bundle_xml_plist_initialize(
     void )
{
	libcerror_error_t *error                                   = NULL;
	libmodi_sparse_bundle_xml_plist_t *sparse_bundle_xml_plist = NULL;
	int result                                                 = 0;

#if defined( HAVE_MODI_TEST_MEMORY )
	int number_of_malloc_fail_tests                            = 1;
	int number_of_memset_fail_tests                            = 1;
	int test_number                                            = 0;
#endif

	/* Test regular cases
	 */
	result = libmodi_sparse_bundle_xml_plist_initialize(
	          &sparse_bundle_xml_plist,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "sparse_bundle_xml_plist",
	 sparse_bundle_xml_plist );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libmodi_sparse_bundle_xml_plist_free(
	          &sparse_bundle_xml_plist,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "sparse_bundle_xml_plist",
	 sparse_bundle_xml_plist );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libmodi_sparse_bundle_xml_plist_initialize(
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

	sparse_bundle_xml_plist = (libmodi_sparse_bundle_xml_plist_t *) 0x12345678UL;

	result = libmodi_sparse_bundle_xml_plist_initialize(
	          &sparse_bundle_xml_plist,
	          &error );

	sparse_bundle_xml_plist = NULL;

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
		/* Test libmodi_sparse_bundle_xml_plist_initialize with malloc failing
		 */
		modi_test_malloc_attempts_before_fail = test_number;

		result = libmodi_sparse_bundle_xml_plist_initialize(
		          &sparse_bundle_xml_plist,
		          &error );

		if( modi_test_malloc_attempts_before_fail != -1 )
		{
			modi_test_malloc_attempts_before_fail = -1;

			if( sparse_bundle_xml_plist != NULL )
			{
				libmodi_sparse_bundle_xml_plist_free(
				 &sparse_bundle_xml_plist,
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
			 "sparse_bundle_xml_plist",
			 sparse_bundle_xml_plist );

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
		/* Test libmodi_sparse_bundle_xml_plist_initialize with memset failing
		 */
		modi_test_memset_attempts_before_fail = test_number;

		result = libmodi_sparse_bundle_xml_plist_initialize(
		          &sparse_bundle_xml_plist,
		          &error );

		if( modi_test_memset_attempts_before_fail != -1 )
		{
			modi_test_memset_attempts_before_fail = -1;

			if( sparse_bundle_xml_plist != NULL )
			{
				libmodi_sparse_bundle_xml_plist_free(
				 &sparse_bundle_xml_plist,
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
			 "sparse_bundle_xml_plist",
			 sparse_bundle_xml_plist );

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
	if( sparse_bundle_xml_plist != NULL )
	{
		libmodi_sparse_bundle_xml_plist_free(
		 &sparse_bundle_xml_plist,
		 NULL );
	}
	return( 0 );
}

/* Tests the libmodi_sparse_bundle_xml_plist_free function
 * Returns 1 if successful or 0 if not
 */
int modi_test_sparse_bundle_xml_plist_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libmodi_sparse_bundle_xml_plist_free(
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

/* Tests the libmodi_sparse_bundle_xml_plist_read_data function
 * Returns 1 if successful or 0 if not
 */
int modi_test_sparse_bundle_xml_plist_read_data(
     void )
{
	libcerror_error_t *error                                   = NULL;
	libmodi_sparse_bundle_xml_plist_t *sparse_bundle_xml_plist = NULL;
	int result                                                 = 0;

	/* Initialize test
	 */
	result = libmodi_sparse_bundle_xml_plist_initialize(
	          &sparse_bundle_xml_plist,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "sparse_bundle_xml_plist",
	 sparse_bundle_xml_plist );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libmodi_sparse_bundle_xml_plist_read_data(
	          sparse_bundle_xml_plist,
	          modi_test_sparse_bundle_xml_plist_data1,
	          494,
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
	result = libmodi_sparse_bundle_xml_plist_read_data(
	          NULL,
	          modi_test_sparse_bundle_xml_plist_data1,
	          494,
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

	result = libmodi_sparse_bundle_xml_plist_read_data(
	          sparse_bundle_xml_plist,
	          NULL,
	          494,
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

	result = libmodi_sparse_bundle_xml_plist_read_data(
	          sparse_bundle_xml_plist,
	          modi_test_sparse_bundle_xml_plist_data1,
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

	result = libmodi_sparse_bundle_xml_plist_read_data(
	          sparse_bundle_xml_plist,
	          modi_test_sparse_bundle_xml_plist_data1,
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

#if defined( HAVE_MODI_TEST_MEMORY ) && defined( BOGUS )
	/* TODO handle "out of dynamic memory in yy_scan_buffer()" */

	/* Test libmodi_sparse_bundle_xml_plist_read_data with malloc failing in libfplist_property_list_initialize
	 */
	modi_test_malloc_attempts_before_fail = 0;

	result = libmodi_sparse_bundle_xml_plist_read_data(
	          sparse_bundle_xml_plist,
	          modi_test_sparse_bundle_xml_plist_data1,
	          494,
	          &error );

	if( modi_test_malloc_attempts_before_fail != -1 )
	{
		modi_test_malloc_attempts_before_fail = -1;
	}
	else
	{
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
	/* Test libmodi_sparse_bundle_xml_plist_read_data with malloc failing in libfplist_property_list_get_root_property
	 */
	modi_test_malloc_attempts_before_fail = 1;

	result = libmodi_sparse_bundle_xml_plist_read_data(
	          sparse_bundle_xml_plist,
	          modi_test_sparse_bundle_xml_plist_data1,
	          494,
	          &error );

	if( modi_test_malloc_attempts_before_fail != -1 )
	{
		modi_test_malloc_attempts_before_fail = -1;
	}
	else
	{
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
#endif /* defined( HAVE_MODI_TEST_MEMORY ) */

	/* Clean up
	 */
	result = libmodi_sparse_bundle_xml_plist_free(
	          &sparse_bundle_xml_plist,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "sparse_bundle_xml_plist",
	 sparse_bundle_xml_plist );

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
	if( sparse_bundle_xml_plist != NULL )
	{
		libmodi_sparse_bundle_xml_plist_free(
		 &sparse_bundle_xml_plist,
		 NULL );
	}
	return( 0 );
}

/* Tests the libmodi_sparse_bundle_xml_plist_read_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int modi_test_sparse_bundle_xml_plist_read_file_io_handle(
     void )
{
	libbfio_handle_t *file_io_handle                 = NULL;
	libcerror_error_t *error                         = NULL;
	libmodi_sparse_bundle_xml_plist_t *sparse_bundle_xml_plist = NULL;
	int result                                       = 0;

	/* Initialize test
	 */
	result = libmodi_sparse_bundle_xml_plist_initialize(
	          &sparse_bundle_xml_plist,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "sparse_bundle_xml_plist",
	 sparse_bundle_xml_plist );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize file IO handle
	 */
	result = modi_test_open_file_io_handle(
	          &file_io_handle,
	          modi_test_sparse_bundle_xml_plist_data1,
	          494,
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
	result = libmodi_sparse_bundle_xml_plist_read_file_io_handle(
	          sparse_bundle_xml_plist,
	          file_io_handle,
	          0,
	          494,
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
	result = libmodi_sparse_bundle_xml_plist_read_file_io_handle(
	          NULL,
	          file_io_handle,
	          0,
	          494,
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

	result = libmodi_sparse_bundle_xml_plist_read_file_io_handle(
	          sparse_bundle_xml_plist,
	          NULL,
	          0,
	          494,
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

	result = libmodi_sparse_bundle_xml_plist_read_file_io_handle(
	          sparse_bundle_xml_plist,
	          file_io_handle,
	          -1,
	          494,
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

	result = libmodi_sparse_bundle_xml_plist_read_file_io_handle(
	          sparse_bundle_xml_plist,
	          file_io_handle,
	          0,
	          (size64_t) SSIZE_MAX + 1,
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
	          modi_test_sparse_bundle_xml_plist_data1,
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

	result = libmodi_sparse_bundle_xml_plist_read_file_io_handle(
	          sparse_bundle_xml_plist,
	          file_io_handle,
	          0,
	          494,
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
	result = libmodi_sparse_bundle_xml_plist_free(
	          &sparse_bundle_xml_plist,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "sparse_bundle_xml_plist",
	 sparse_bundle_xml_plist );

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
	if( sparse_bundle_xml_plist != NULL )
	{
		libmodi_sparse_bundle_xml_plist_free(
		 &sparse_bundle_xml_plist,
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
	 "libmodi_sparse_bundle_xml_plist_initialize",
	 modi_test_sparse_bundle_xml_plist_initialize );

	MODI_TEST_RUN(
	 "libmodi_sparse_bundle_xml_plist_free",
	 modi_test_sparse_bundle_xml_plist_free );

	MODI_TEST_RUN(
	 "libmodi_sparse_bundle_xml_plist_read_data",
	 modi_test_sparse_bundle_xml_plist_read_data );

	MODI_TEST_RUN(
	 "libmodi_sparse_bundle_xml_plist_read_file_io_handle",
	 modi_test_sparse_bundle_xml_plist_read_file_io_handle );

#endif /* defined( __GNUC__ ) && !defined( LIBMODI_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBMODI_DLL_IMPORT )

on_error:
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBMODI_DLL_IMPORT ) */
}

