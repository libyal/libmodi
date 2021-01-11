/*
 * Library udif_block_table type test program
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

#include "modi_test_libcerror.h"
#include "modi_test_libmodi.h"
#include "modi_test_macros.h"
#include "modi_test_memory.h"
#include "modi_test_unused.h"

#include "../libmodi/libmodi_udif_block_table.h"
#include "../libmodi/libmodi_udif_block_table_entry.h"

uint8_t modi_test_udif_block_table_data1[ 284 ] = {
	0x6d, 0x69, 0x73, 0x68, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x20, 0x41, 0xf2, 0xfa, 0x33, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x80, 0x00, 0x00, 0x05,
	0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x0d, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

#if defined( __GNUC__ ) && !defined( LIBMODI_DLL_IMPORT )

/* Tests the libmodi_udif_block_table_initialize function
 * Returns 1 if successful or 0 if not
 */
int modi_test_udif_block_table_initialize(
     void )
{
	libcerror_error_t *error                = NULL;
	libmodi_udif_block_table_t *block_table = NULL;
	int result                              = 0;

#if defined( HAVE_MODI_TEST_MEMORY )
	int number_of_malloc_fail_tests         = 1;
	int number_of_memset_fail_tests         = 1;
	int test_number                         = 0;
#endif

	/* Test regular cases
	 */
	result = libmodi_udif_block_table_initialize(
	          &block_table,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "block_table",
	 block_table );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libmodi_udif_block_table_free(
	          &block_table,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "block_table",
	 block_table );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libmodi_udif_block_table_initialize(
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

	block_table = (libmodi_udif_block_table_t *) 0x12345678UL;

	result = libmodi_udif_block_table_initialize(
	          &block_table,
	          &error );

	block_table = NULL;

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
		/* Test libmodi_udif_block_table_initialize with malloc failing
		 */
		modi_test_malloc_attempts_before_fail = test_number;

		result = libmodi_udif_block_table_initialize(
		          &block_table,
		          &error );

		if( modi_test_malloc_attempts_before_fail != -1 )
		{
			modi_test_malloc_attempts_before_fail = -1;

			if( block_table != NULL )
			{
				libmodi_udif_block_table_free(
				 &block_table,
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
			 "block_table",
			 block_table );

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
		/* Test libmodi_udif_block_table_initialize with memset failing
		 */
		modi_test_memset_attempts_before_fail = test_number;

		result = libmodi_udif_block_table_initialize(
		          &block_table,
		          &error );

		if( modi_test_memset_attempts_before_fail != -1 )
		{
			modi_test_memset_attempts_before_fail = -1;

			if( block_table != NULL )
			{
				libmodi_udif_block_table_free(
				 &block_table,
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
			 "block_table",
			 block_table );

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
	if( block_table != NULL )
	{
		libmodi_udif_block_table_free(
		 &block_table,
		 NULL );
	}
	return( 0 );
}

/* Tests the libmodi_udif_block_table_free function
 * Returns 1 if successful or 0 if not
 */
int modi_test_udif_block_table_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libmodi_udif_block_table_free(
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

/* Tests the libmodi_udif_block_table_read_data function
 * Returns 1 if successful or 0 if not
 */
int modi_test_udif_block_table_read_data(
     void )
{
	libcerror_error_t *error                = NULL;
	libmodi_udif_block_table_t *block_table = NULL;
	int result                              = 0;

	/* Initialize test
	 */
	result = libmodi_udif_block_table_initialize(
	          &block_table,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "block_table",
	 block_table );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libmodi_udif_block_table_read_data(
	          block_table,
	          modi_test_udif_block_table_data1,
	          284,
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
	result = libmodi_udif_block_table_read_data(
	          NULL,
	          modi_test_udif_block_table_data1,
	          284,
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

	result = libmodi_udif_block_table_read_data(
	          block_table,
	          NULL,
	          284,
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

	result = libmodi_udif_block_table_read_data(
	          block_table,
	          modi_test_udif_block_table_data1,
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

	result = libmodi_udif_block_table_read_data(
	          block_table,
	          modi_test_udif_block_table_data1,
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

	/* Test error case where signature is invalid
	 */
	byte_stream_copy_from_uint32_big_endian(
	 modi_test_udif_block_table_data1,
	 0xffffffffUL );

	result = libmodi_udif_block_table_read_data(
	          block_table,
	          modi_test_udif_block_table_data1,
	          284,
	          &error );

	byte_stream_copy_from_uint32_big_endian(
	 modi_test_udif_block_table_data1,
	 0x6d697368UL );

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
	result = libmodi_udif_block_table_free(
	          &block_table,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "block_table",
	 block_table );

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
	if( block_table != NULL )
	{
		libmodi_udif_block_table_free(
		 &block_table,
		 NULL );
	}
	return( 0 );
}

/* Tests the libmodi_udif_block_table_get_number_of_entries function
 * Returns 1 if successful or 0 if not
 */
int modi_test_block_table_get_number_of_entries(
     libmodi_udif_block_table_t *block_table )
{
	libcerror_error_t *error = NULL;
	int number_of_entries    = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libmodi_udif_block_table_get_number_of_entries(
	          block_table,
	          &number_of_entries,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "number_of_entries",
	 number_of_entries,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libmodi_udif_block_table_get_number_of_entries(
	          NULL,
	          &number_of_entries,
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

	result = libmodi_udif_block_table_get_number_of_entries(
	          block_table,
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
	return( 0 );
}

/* Tests the libmodi_udif_block_table_get_entry_by_index function
 * Returns 1 if successful or 0 if not
 */
int modi_test_block_table_get_entry_by_index(
     libmodi_udif_block_table_t *block_table )
{
	libcerror_error_t *error                            = NULL;
	libmodi_udif_block_table_entry_t *block_table_entry = NULL;
	int result                                          = 0;

	/* Test regular cases
	 */
	result = libmodi_udif_block_table_get_entry_by_index(
	          block_table,
	          0,
	          &block_table_entry,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "block_table_entry",
	 block_table_entry );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libmodi_udif_block_table_get_entry_by_index(
	          NULL,
	          0,
	          &block_table_entry,
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

	result = libmodi_udif_block_table_get_entry_by_index(
	          block_table,
	          -1,
	          &block_table_entry,
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

	result = libmodi_udif_block_table_get_entry_by_index(
	          block_table,
	          0,
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
#if defined( __GNUC__ ) && !defined( LIBMODI_DLL_IMPORT )

	libcerror_error_t *error                = NULL;
	libmodi_udif_block_table_t *block_table = NULL;
	int result                              = 0;

#endif /* defined( __GNUC__ ) && !defined( LIBMODI_DLL_IMPORT ) */

	MODI_TEST_UNREFERENCED_PARAMETER( argc )
	MODI_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBMODI_DLL_IMPORT )

	MODI_TEST_RUN(
	 "libmodi_udif_block_table_initialize",
	 modi_test_udif_block_table_initialize );

	MODI_TEST_RUN(
	 "libmodi_udif_block_table_free",
	 modi_test_udif_block_table_free );

	MODI_TEST_RUN(
	 "libmodi_udif_block_table_read_data",
	 modi_test_udif_block_table_read_data );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	/* Initialize test
	 */
	result = libmodi_udif_block_table_initialize(
	          &block_table,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "block_table",
	 block_table );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libmodi_udif_block_table_read_data(
	          block_table,
	          modi_test_udif_block_table_data1,
	          284,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Run tests
	 */
	MODI_TEST_RUN_WITH_ARGS(
	 "libmodi_udif_block_table_get_number_of_entries",
	 modi_test_block_table_get_number_of_entries,
	 block_table );

	MODI_TEST_RUN_WITH_ARGS(
	 "libmodi_udif_block_table_get_entry_by_index",
	 modi_test_block_table_get_entry_by_index,
	 block_table );

	/* Clean up
	 */
	result = libmodi_udif_block_table_free(
	          &block_table,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "block_table",
	 block_table );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

#endif /* defined( __GNUC__ ) && !defined( LIBMODI_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBMODI_DLL_IMPORT )
on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( block_table != NULL )
	{
		libmodi_udif_block_table_free(
		 &block_table,
		 NULL );
	}
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBMODI_DLL_IMPORT ) */
}

