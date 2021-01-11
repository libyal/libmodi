/*
 * Library notification functions test program
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "modi_test_libcerror.h"
#include "modi_test_libmodi.h"
#include "modi_test_macros.h"
#include "modi_test_unused.h"

/* Tests the libmodi_notify_set_verbose function
 * Returns 1 if successful or 0 if not
 */
int modi_test_notify_set_verbose(
     void )
{
	/* Test invocation of function only
	 */
	libmodi_notify_set_verbose(
	 0 );

	return( 1 );
}

/* Tests the libmodi_notify_set_stream function
 * Returns 1 if successful or 0 if not
 */
int modi_test_notify_set_stream(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libmodi_notify_set_stream(
	          NULL,
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
/* TODO test libcnotify_stream_set failure */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libmodi_notify_stream_open function
 * Returns 1 if successful or 0 if not
 */
int modi_test_notify_stream_open(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libmodi_notify_stream_open(
	          "notify_stream.log",
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
	result = libmodi_notify_stream_open(
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
	result = libmodi_notify_stream_close(
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
	return( 0 );
}

/* Tests the libmodi_notify_stream_close function
 * Returns 1 if successful or 0 if not
 */
int modi_test_notify_stream_close(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libmodi_notify_stream_close(
	          &error );

	MODI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	MODI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
/* TODO test libcnotify_stream_close failure */

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

	MODI_TEST_RUN(
	 "libmodi_notify_set_verbose",
	 modi_test_notify_set_verbose )

	MODI_TEST_RUN(
	 "libmodi_notify_set_stream",
	 modi_test_notify_set_stream )

	MODI_TEST_RUN(
	 "libmodi_notify_stream_open",
	 modi_test_notify_stream_open )

	MODI_TEST_RUN(
	 "libmodi_notify_stream_close",
	 modi_test_notify_stream_close )

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

