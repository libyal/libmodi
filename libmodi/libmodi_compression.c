/*
 * Compression functions
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
#include <memory.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#if defined( HAVE_BZLIB ) || defined( BZ_DLL )
#include <bzlib.h>
#endif

#if defined( HAVE_LIBLZMA ) || defined( LIBLZMA_DLL )
#include <lzma.h>
#endif

#if defined( HAVE_ZLIB ) || defined( ZLIB_DLL )
#include <zlib.h>
#endif

#include "libmodi_adc.h"
#include "libmodi_compression.h"
#include "libmodi_definitions.h"
#include "libmodi_deflate.h"
#include "libmodi_libcerror.h"
#include "libmodi_libcnotify.h"

/* Decompresses data using the compression method
 * Returns 1 on success or -1 on error
 */
int libmodi_decompress_data(
     const uint8_t *compressed_data,
     size_t compressed_data_size,
     int compression_method,
     uint8_t *uncompressed_data,
     size_t *uncompressed_data_size,
     libcerror_error_t **error )
{
	static char *function                     = "libmodi_decompress_data";

#if defined( HAVE_BZLIB ) || defined( BZ_DLL )
	unsigned int bzip2_uncompressed_data_size = 0;
	int bzlib_result                          = 0;
#endif
#if defined( HAVE_LIBLZMA ) || defined( LIBLZMA_DLL )
	lzma_stream lzma_compressed_stream        = LZMA_STREAM_INIT;
	lzma_ret lzma_result                      = 0;
#endif
#if ( defined( HAVE_ZLIB ) && defined( HAVE_ZLIB_UNCOMPRESS ) ) || defined( ZLIB_DLL )
	uLongf zlib_uncompressed_data_size        = 0;
	int zlib_result                           = 0;
#endif

	if( compressed_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid compressed data buffer.",
		 function );

		return( -1 );
	}
	if( uncompressed_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid uncompressed data buffer.",
		 function );

		return( -1 );
	}
	if( uncompressed_data == compressed_data )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid compressed data buffer equals uncompressed data buffer.",
		 function );

		return( -1 );
	}
	if( uncompressed_data_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid uncompressed data size.",
		 function );

		return( -1 );
	}
	if( compression_method == LIBMODI_COMPRESSION_METHOD_ADC )
	{
		if( libmodi_adc_decompress(
		     compressed_data,
		     compressed_data_size,
		     uncompressed_data,
		     uncompressed_data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_COMPRESSION,
			 LIBCERROR_COMPRESSION_ERROR_DECOMPRESS_FAILED,
			 "%s: unable to decompress ADC compressed data.",
			 function );

			goto on_error;
		}
	}
	else if( compression_method == LIBMODI_COMPRESSION_METHOD_BZIP2 )
	{
#if defined( HAVE_BZLIB ) || defined( BZ_DLL )
		if( compressed_data_size > (size_t) UINT_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid compressed data size value exceeds maximum.",
			 function );

			goto on_error;
		}
		if( *uncompressed_data_size > (size_t) UINT_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid uncompressed data size value exceeds maximum.",
			 function );

			goto on_error;
		}
		bzip2_uncompressed_data_size = (unsigned int) *uncompressed_data_size;

		bzlib_result = BZ2_bzBuffToBuffDecompress(
		                (char *) uncompressed_data,
		                &bzip2_uncompressed_data_size,
		                (char *) compressed_data,
		                (unsigned int) compressed_data_size,
		                0,
		                0 );

		if( ( bzlib_result == BZ_DATA_ERROR )
		 || ( bzlib_result == BZ_DATA_ERROR_MAGIC ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to decompress data: data error.",
			 function );

			goto on_error;
		}
		else if( bzlib_result == BZ_OUTBUFF_FULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_COMPRESSION,
			 LIBCERROR_COMPRESSION_ERROR_DECOMPRESS_FAILED,
			 "%s: unable to decompress data: target buffer too small.",
			 function );

			goto on_error;
		}
		else if( bzlib_result == BZ_MEM_ERROR )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to decompress data: insufficient memory.",
			 function );

			goto on_error;
		}
		else if( bzlib_result != BZ_OK )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_COMPRESSION,
			 LIBCERROR_COMPRESSION_ERROR_DECOMPRESS_FAILED,
			 "%s: bzlib returned undefined error: %d.",
			 function,
			 bzlib_result );

			goto on_error;
		}
		*uncompressed_data_size = (size_t) bzip2_uncompressed_data_size;
#else
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: missing support for bzip2 compression.",
		 function );

		goto on_error;
#endif /* defined( HAVE_BZLIB ) || defined( BZ_DLL ) */
	}
	else if( compression_method == LIBMODI_COMPRESSION_METHOD_DEFLATE )
	{
#if ( defined( HAVE_ZLIB ) && defined( HAVE_ZLIB_UNCOMPRESS ) ) || defined( ZLIB_DLL )
		if( compressed_data_size > (size_t) ULONG_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid compressed data size value exceeds maximum.",
			 function );

			goto on_error;
		}
		if( *uncompressed_data_size > (size_t) ULONG_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid uncompressed data size value exceeds maximum.",
			 function );

			goto on_error;
		}
		zlib_uncompressed_data_size = (uLongf) *uncompressed_data_size;

		zlib_result = uncompress(
		               (Bytef *) uncompressed_data,
		               &zlib_uncompressed_data_size,
		               (Bytef *) compressed_data,
		               (uLong) compressed_data_size );

		if( zlib_result == Z_DATA_ERROR )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to decompress data: data error.",
			 function );

			goto on_error;
		}
		else if( zlib_result == Z_BUF_ERROR )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_COMPRESSION,
			 LIBCERROR_COMPRESSION_ERROR_DECOMPRESS_FAILED,
			 "%s: unable to decompress data: target buffer too small.",
			 function );

			goto on_error;
		}
		else if( zlib_result == Z_MEM_ERROR )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to read compressed data: insufficient memory.",
			 function );

			goto on_error;
		}
		else if( zlib_result != Z_OK )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_COMPRESSION,
			 LIBCERROR_COMPRESSION_ERROR_DECOMPRESS_FAILED,
			 "%s: zlib returned undefined error: %d.",
			 function,
			 zlib_result );

			goto on_error;
		}
		*uncompressed_data_size = (size_t) zlib_uncompressed_data_size;
#else
		if( libmodi_deflate_decompress_zlib(
		     compressed_data,
		     compressed_data_size,
		     uncompressed_data,
		     uncompressed_data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_COMPRESSION,
			 LIBCERROR_COMPRESSION_ERROR_DECOMPRESS_FAILED,
			 "%s: unable to decompress zlib+DEFLATE compressed data.",
			 function );

			goto on_error;
		}
#endif /* ( defined( HAVE_ZLIB ) && defined( HAVE_ZLIB_UNCOMPRESS ) ) || defined( ZLIB_DLL ) */
	}
	else if( compression_method == LIBMODI_COMPRESSION_METHOD_LZFSE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: missing support for LZFSE compression.",
		 function );

		goto on_error;
	}
	else if( compression_method == LIBMODI_COMPRESSION_METHOD_LZMA )
	{
#if defined( HAVE_LIBLZMA ) || defined( LIBLZMA_DLL )
		lzma_result = lzma_stream_decoder(
		               &lzma_compressed_stream,
		               UINT64_MAX,
		               0 );

		if( lzma_result != LZMA_OK )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create LZMA stream.",
			 function );

			goto on_error;
		}
		lzma_compressed_stream.next_in   = compressed_data;
		lzma_compressed_stream.avail_in  = compressed_data_size;
		lzma_compressed_stream.next_out  = uncompressed_data;
		lzma_compressed_stream.avail_out = *uncompressed_data_size;

		lzma_result = lzma_code(
		               &lzma_compressed_stream,
		               LZMA_RUN );

		if( ( lzma_result == LZMA_DATA_ERROR )
		 || ( lzma_result == LZMA_FORMAT_ERROR ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to decompress data: data error.",
			 function );

			goto on_error;
		}
		else if( lzma_result == LZMA_BUF_ERROR )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_COMPRESSION,
			 LIBCERROR_COMPRESSION_ERROR_DECOMPRESS_FAILED,
			 "%s: unable to decompress data: target buffer too small.",
			 function );

			goto on_error;
		}
		else if( lzma_result == LZMA_MEM_ERROR )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to read compressed data: insufficient memory.",
			 function );

			goto on_error;
		}
		else if( lzma_result != LZMA_STREAM_END )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_COMPRESSION,
			 LIBCERROR_COMPRESSION_ERROR_DECOMPRESS_FAILED,
			 "%s: liblzma returned undefined error: %d.",
			 function,
			 lzma_result );

			goto on_error;
		}
		*uncompressed_data_size = (size_t) lzma_compressed_stream.total_out;

		lzma_end(
		 &lzma_compressed_stream );
#else
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: missing support for LZMA compression.",
		 function );

		goto on_error;
#endif /* defined( HAVE_LIBLZMA ) || defined( LIBLZMA_DLL ) */
	}
	else
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported compression method.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
#if defined( HAVE_LIBLZMA ) || defined( LIBLZMA_DLL )
	lzma_end(
	 &lzma_compressed_stream );
#endif
	return( -1 );
}

