/*
 * Bit-stream testing program
 *
 * Copyright (C) 2012-2022, Joachim Metz <joachim.metz@gmail.com>
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
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "modi_test_libcerror.h"
#include "modi_test_macros.h"
#include "modi_test_memory.h"
#include "modi_test_unused.h"

#include "../libmodi/libmodi_bit_stream.h"

uint8_t modi_test_bit_stream_data[ 16 ] = {
	0x78, 0xda, 0xbd, 0x59, 0x6d, 0x8f, 0xdb, 0xb8, 0x11, 0xfe, 0x7c, 0xfa, 0x15, 0xc4, 0x7e, 0xb9 };

#if defined( __GNUC__ ) && !defined( LIBMODI_DLL_IMPORT )

/* Tests the libmodi_bit_stream_initialize function
 * Returns 1 if successful or 0 if not
 */
int modi_test_bit_stream_initialize(
     void )
{
	libcerror_error_t *error         = NULL;
	libmodi_bit_stream_t *bit_stream = NULL;
	int result                       = 0;

#if defined( HAVE_MODI_TEST_MEMORY )
	int number_of_malloc_fail_tests  = 1;
	int number_of_memset_fail_tests  = 1;
	int test_number                  = 0;
#endif

	/* Test regular cases
	 */
	result = libmodi_bit_stream_initialize(
	          &bit_stream,
	          modi_test_bit_stream_data,
	          16,
	          0,
	          LIBMODI_BIT_STREAM_STORAGE_TYPE_BYTE_BACK_TO_FRONT,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "bit_stream",
	 bit_stream );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libmodi_bit_stream_free(
	          &bit_stream,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "bit_stream",
	 bit_stream );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libmodi_bit_stream_initialize(
	          NULL,
	          modi_test_bit_stream_data,
	          16,
	          0,
	          LIBMODI_BIT_STREAM_STORAGE_TYPE_BYTE_BACK_TO_FRONT,
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

	bit_stream = (libmodi_bit_stream_t *) 0x12345678UL;

	result = libmodi_bit_stream_initialize(
	          &bit_stream,
	          modi_test_bit_stream_data,
	          16,
	          0,
	          LIBMODI_BIT_STREAM_STORAGE_TYPE_BYTE_BACK_TO_FRONT,
	          &error );

	bit_stream = NULL;

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MODI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libmodi_bit_stream_initialize(
	          &bit_stream,
	          NULL,
	          16,
	          0,
	          LIBMODI_BIT_STREAM_STORAGE_TYPE_BYTE_BACK_TO_FRONT,
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

	result = libmodi_bit_stream_initialize(
	          &bit_stream,
	          modi_test_bit_stream_data,
	          (size_t) SSIZE_MAX + 1,
	          0,
	          LIBMODI_BIT_STREAM_STORAGE_TYPE_BYTE_BACK_TO_FRONT,
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

	result = libmodi_bit_stream_initialize(
	          &bit_stream,
	          modi_test_bit_stream_data,
	          16,
	          (size_t) SSIZE_MAX + 1,
	          LIBMODI_BIT_STREAM_STORAGE_TYPE_BYTE_BACK_TO_FRONT,
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

	result = libmodi_bit_stream_initialize(
	          &bit_stream,
	          modi_test_bit_stream_data,
	          16,
	          0,
	          0xff,
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

#if defined( HAVE_MODI_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libmodi_bit_stream_initialize with malloc failing
		 */
		modi_test_malloc_attempts_before_fail = test_number;

		result = libmodi_bit_stream_initialize(
		          &bit_stream,
		          modi_test_bit_stream_data,
		          16,
		          0,
		          LIBMODI_BIT_STREAM_STORAGE_TYPE_BYTE_BACK_TO_FRONT,
		          &error );

		if( modi_test_malloc_attempts_before_fail != -1 )
		{
			modi_test_malloc_attempts_before_fail = -1;

			if( bit_stream != NULL )
			{
				libmodi_bit_stream_free(
				 &bit_stream,
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
			 "bit_stream",
			 bit_stream );

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
		/* Test libmodi_bit_stream_initialize with memset failing
		 */
		modi_test_memset_attempts_before_fail = test_number;

		result = libmodi_bit_stream_initialize(
		          &bit_stream,
		          modi_test_bit_stream_data,
		          16,
		          0,
		          LIBMODI_BIT_STREAM_STORAGE_TYPE_BYTE_BACK_TO_FRONT,
		          &error );

		if( modi_test_memset_attempts_before_fail != -1 )
		{
			modi_test_memset_attempts_before_fail = -1;

			if( bit_stream != NULL )
			{
				libmodi_bit_stream_free(
				 &bit_stream,
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
			 "bit_stream",
			 bit_stream );

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
	if( bit_stream != NULL )
	{
		libmodi_bit_stream_free(
		 &bit_stream,
		 NULL );
	}
	return( 0 );
}

/* Tests the libmodi_bit_stream_free function
 * Returns 1 if successful or 0 if not
 */
int modi_test_bit_stream_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libmodi_bit_stream_free(
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

/* Tests the libmodi_bit_stream_read function
 * Returns 1 if successful or 0 if not
 */
int modi_test_bit_stream_read(
     void )
{
	libmodi_bit_stream_t *bit_stream = NULL;
	libcerror_error_t *error         = NULL;
	int result                       = 0;

	/* Initialize test
	 */
	result = libmodi_bit_stream_initialize(
	          &bit_stream,
	          modi_test_bit_stream_data,
	          16,
	          0,
	          LIBMODI_BIT_STREAM_STORAGE_TYPE_BYTE_BACK_TO_FRONT,
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
	result = libmodi_bit_stream_read(
	          bit_stream,
	          8,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	MODI_TEST_ASSERT_EQUAL_SIZE(
	 "bit_stream->byte_stream_offset",
	 bit_stream->byte_stream_offset,
	 (size_t) 1 );

	MODI_TEST_ASSERT_EQUAL_UINT32(
	 "bit_stream->bit_buffer",
	 bit_stream->bit_buffer,
	 (uint32_t) 0x00000078UL );

	MODI_TEST_ASSERT_EQUAL_UINT8(
	 "bit_stream->bit_buffer_size",
	 bit_stream->bit_buffer_size,
	 (uint8_t) 8 );

	/* Test error cases
	 */
	result = libmodi_bit_stream_read(
	          NULL,
	          8,
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
	result = libmodi_bit_stream_free(
	          &bit_stream,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( bit_stream != NULL )
	{
		libmodi_bit_stream_free(
		 &bit_stream,
		 NULL );
	}
	return( 0 );
}

/* Tests the libmodi_bit_stream_get_value function
 * Returns 1 if successful or 0 if not
 */
int modi_test_bit_stream_get_value(
     void )
{
	libmodi_bit_stream_t *bit_stream = NULL;
	libcerror_error_t *error         = NULL;
	uint32_t value_32bit             = 0;
	int result                       = 0;

	/* Initialize test
	 */
	result = libmodi_bit_stream_initialize(
	          &bit_stream,
	          modi_test_bit_stream_data,
	          16,
	          0,
	          LIBMODI_BIT_STREAM_STORAGE_TYPE_BYTE_BACK_TO_FRONT,
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
	result = libmodi_bit_stream_get_value(
	          bit_stream,
	          0,
	          &value_32bit,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_EQUAL_UINT32(
	 "value_32bit",
	 value_32bit,
	 (uint32_t) 0x00000000UL );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	MODI_TEST_ASSERT_EQUAL_SIZE(
	 "bit_stream->byte_stream_offset",
	 bit_stream->byte_stream_offset,
	 (size_t) 0 );

	MODI_TEST_ASSERT_EQUAL_UINT32(
	 "bit_stream->bit_buffer",
	 bit_stream->bit_buffer,
	 (uint32_t) 0x00000000UL );

	MODI_TEST_ASSERT_EQUAL_UINT8(
	 "bit_stream->bit_buffer_size",
	 bit_stream->bit_buffer_size,
	 (uint8_t) 0 );

	result = libmodi_bit_stream_get_value(
	          bit_stream,
	          4,
	          &value_32bit,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_EQUAL_UINT32(
	 "value_32bit",
	 value_32bit,
	 (uint32_t) 0x00000008UL );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	MODI_TEST_ASSERT_EQUAL_SIZE(
	 "bit_stream->byte_stream_offset",
	 bit_stream->byte_stream_offset,
	 (size_t) 1 );

	MODI_TEST_ASSERT_EQUAL_UINT32(
	 "bit_stream->bit_buffer",
	 bit_stream->bit_buffer,
	 (uint32_t) 0x00000007UL );

	MODI_TEST_ASSERT_EQUAL_UINT8(
	 "bit_stream->bit_buffer_size",
	 bit_stream->bit_buffer_size,
	 (uint8_t) 4 );

	result = libmodi_bit_stream_get_value(
	          bit_stream,
	          12,
	          &value_32bit,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_EQUAL_UINT32(
	 "value_32bit",
	 value_32bit,
	 (uint32_t) 0x00000da7UL );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	MODI_TEST_ASSERT_EQUAL_SIZE(
	 "bit_stream->byte_stream_offset",
	 bit_stream->byte_stream_offset,
	 (size_t) 2 );

	MODI_TEST_ASSERT_EQUAL_UINT32(
	 "bit_stream->bit_buffer",
	 bit_stream->bit_buffer,
	 (uint32_t) 0x00000000UL );

	MODI_TEST_ASSERT_EQUAL_UINT8(
	 "bit_stream->bit_buffer_size",
	 bit_stream->bit_buffer_size,
	 (uint8_t) 0 );

	result = libmodi_bit_stream_get_value(
	          bit_stream,
	          32,
	          &value_32bit,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_EQUAL_UINT32(
	 "value_32bit",
	 value_32bit,
	 (uint32_t) 0x8f6d59bdUL );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	MODI_TEST_ASSERT_EQUAL_SIZE(
	 "bit_stream->byte_stream_offset",
	 bit_stream->byte_stream_offset,
	 (size_t) 6 );

	MODI_TEST_ASSERT_EQUAL_UINT32(
	 "bit_stream->bit_buffer",
	 bit_stream->bit_buffer,
	 (uint32_t) 0x00000000UL );

	MODI_TEST_ASSERT_EQUAL_UINT8(
	 "bit_stream->bit_buffer_size",
	 bit_stream->bit_buffer_size,
	 (uint8_t) 0 );

	/* Test error cases
	 */
	result = libmodi_bit_stream_get_value(
	          NULL,
	          32,
	          &value_32bit,
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

	result = libmodi_bit_stream_get_value(
	          bit_stream,
	          64,
	          &value_32bit,
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

	result = libmodi_bit_stream_get_value(
	          bit_stream,
	          32,
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

	bit_stream->byte_stream_offset = 16;
        bit_stream->bit_buffer_size    = 0;

	result = libmodi_bit_stream_get_value(
	          bit_stream,
	          32,
	          &value_32bit,
	          &error );

	bit_stream->byte_stream_offset = 0;

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
	result = libmodi_bit_stream_free(
	          &bit_stream,
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( bit_stream != NULL )
	{
		libmodi_bit_stream_free(
		 &bit_stream,
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
	 "libmodi_bit_stream_initialize",
	 modi_test_bit_stream_initialize );

	MODI_TEST_RUN(
	 "libmodi_bit_stream_free",
	 modi_test_bit_stream_free );

	MODI_TEST_RUN(
	 "libmodi_bit_stream_read",
	 modi_test_bit_stream_read );

	MODI_TEST_RUN(
	 "libmodi_bit_stream_get_value",
	 modi_test_bit_stream_get_value );

#endif /* defined( __GNUC__ ) && !defined( LIBMODI_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBMODI_DLL_IMPORT )

on_error:
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBMODI_DLL_IMPORT ) */
}
