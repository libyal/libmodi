/*
 * OSS-Fuzz target for libmodi file type
 *
 * Copyright (C) 2012-2026, Joachim Metz <joachim.metz@gmail.com>
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

#include <stddef.h>
#include <stdint.h>

/* Note that some of the OSS-Fuzz engines use C++
 */
extern "C" {

#include "ossfuzz_libbfio.h"
#include "ossfuzz_libmodi.h"

#if !defined( LIBMODI_HAVE_BFIO )

/* Determines if a file contains a Mac OS disk image file signature
 * using a Basic File IO (bfio) handle
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBMODI_EXTERN \
int libmodi_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libmodi_error_t **error );

/* Opens a handle using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBMODI_EXTERN \
int libmodi_handle_open_file_io_handle(
     libmodi_handle_t *handle,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libmodi_error_t **error );

#endif /* !defined( LIBMODI_HAVE_BFIO ) */

int LLVMFuzzerTestOneInput(
     const uint8_t *data,
     size_t size )
{
	uint8_t buffer[ 512 ];

	libbfio_handle_t *file_io_handle = NULL;
	libmodi_handle_t *handle         = NULL;
	ssize_t read_count               = 0;
	off64_t media_offset             = 0;
	size64_t media_size              = 0;
	int image_type                   = 0;
	int read_iterator                = 0;

	if( libbfio_memory_range_initialize(
	     &file_io_handle,
	     NULL ) != 1 )
	{
		return( 0 );
	}
	if( libbfio_memory_range_set(
	     file_io_handle,
	     (uint8_t *) data,
	     size,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libmodi_check_file_signature_file_io_handle(
	     file_io_handle,
	     NULL ) == -1 )
	{
		goto on_error_libbfio;
	}
	if( libmodi_handle_initialize(
	     &handle,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libmodi_handle_open_file_io_handle(
	     handle,
	     file_io_handle,
	     LIBMODI_OPEN_READ,
	     NULL ) != 1 )
	{
		goto on_error_libmodi;
	}
	if( libmodi_handle_set_maximum_number_of_open_handles(
	     handle,
	     8,
	     NULL ) != 1 )
	{
		goto on_error_libmodi;
	}
	if( libmodi_handle_get_image_type(
	     handle,
	     &image_type,
	     NULL ) != 1 )
	{
		goto on_error_libmodi;
	}
	if( libmodi_handle_get_media_size(
	     handle,
	     &media_size,
	     NULL ) != 1 )
	{
		goto on_error_libmodi;
	}
	for( read_iterator = 0;
	     read_iterator < 512;
	     read_iterator++ )
	{
		read_count = libmodi_handle_read_buffer(
		                  handle,
		                  buffer,
		                  497,
		                  NULL );

		if( read_count == -1 )
		{
			goto on_error_libmodi;
		}
		if( read_count == 0 )
		{
			break;
		}
	}
	if( media_size > 0 )
	{
		if( libmodi_handle_seek_offset(
		     handle,
		     (off64_t) ( media_size / 2 ),
		     SEEK_SET,
		     NULL ) == -1 )
		{
			goto on_error_libmodi;
		}
	}
	if( libmodi_handle_seek_offset(
	     handle,
	     512,
	     SEEK_CUR,
	     NULL ) == -1 )
	{
		goto on_error_libmodi;
	}
	if( libmodi_handle_seek_offset(
	     handle,
	     0,
	     SEEK_END,
	     NULL ) == -1 )
	{
		goto on_error_libmodi;
	}
	if( libmodi_handle_get_offset(
	     handle,
	     &media_offset,
	     NULL ) != 1 )
	{
		goto on_error_libmodi;
	}
	read_count = libmodi_handle_read_buffer(
	                  handle,
	                  buffer,
	                  497,
	                  NULL );

	if( read_count == -1 )
	{
		goto on_error_libmodi;
	}
	if( libmodi_handle_seek_offset(
	     handle,
	     0,
	     SEEK_SET,
	     NULL ) == -1 )
	{
		goto on_error_libmodi;
	}
	media_offset = 0;

	for( read_iterator = 0;
	     read_iterator < 512;
	     read_iterator++ )
	{
		if( media_offset >= media_size )
		{
			break;
		}
		if( libmodi_handle_read_buffer_at_offset(
		     handle,
		     buffer,
		     497,
		     media_offset,
		     NULL ) == -1 )
		{
			goto on_error_libmodi;
		}
		media_offset += 497;
	}
	if( libmodi_handle_signal_abort(
	     handle,
	     NULL ) != 1 )
	{
		goto on_error_libmodi;
	}
	libmodi_handle_close(
	 handle,
	 NULL );

on_error_libmodi:
	libmodi_handle_free(
	 &handle,
	 NULL );

on_error_libbfio:
	libbfio_handle_free(
	 &file_io_handle,
	 NULL );

	return( 0 );
}

} /* extern "C" */
