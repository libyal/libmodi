/*
 * OSS-Fuzz target for the libmodi read-buffer (data) path
 *
 * The existing handle_fuzzer only opens and closes the image, so the band /
 * sparse-image table parsing and the per-block decompression (zlib, bzip2,
 * ADC, LZFSE/LZVN) used by the .dmg / UDIF read path are never reached. This
 * target additionally reads the media so those parsers are exercised.
 */

#include <stddef.h>
#include <stdint.h>

/* Note that some of the OSS-Fuzz engines use C++
 */
extern "C" {

#include "ossfuzz_libbfio.h"
#include "ossfuzz_libmodi.h"

#if !defined( LIBMODI_HAVE_BFIO )

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
	libbfio_handle_t *file_io_handle = NULL;
	libmodi_handle_t *handle         = NULL;

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
	/* Read the media to drive the band table / decompression parsing. */
	{
		size64_t media_size = 0;

		if( libmodi_handle_get_media_size(
		     handle,
		     &media_size,
		     NULL ) == 1 )
		{
			uint8_t buffer[ 4096 ];
			off64_t offset = 0;
			int iterations = 0;

			while( ( offset < (off64_t) media_size )
			    && ( iterations < 2048 ) )
			{
				ssize_t read_count = libmodi_handle_read_buffer_at_offset(
				                      handle,
				                      buffer,
				                      sizeof( buffer ),
				                      offset,
				                      NULL );

				if( read_count <= 0 )
				{
					break;
				}
				offset += read_count;
				iterations++;
			}
		}
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
