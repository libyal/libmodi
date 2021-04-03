/*
 * Handle functions
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

#if !defined( _LIBMODI_HANDLE_H )
#define _LIBMODI_HANDLE_H

#include <common.h>
#include <types.h>

#include "libmodi_bands_data_handle.h"
#include "libmodi_block_chunks_data_handle.h"
#include "libmodi_extern.h"
#include "libmodi_io_handle.h"
#include "libmodi_libbfio.h"
#include "libmodi_libcdirectory.h"
#include "libmodi_libcerror.h"
#include "libmodi_libcthreads.h"
#include "libmodi_libfcache.h"
#include "libmodi_libfdata.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libmodi_internal_handle libmodi_internal_handle_t;

struct libmodi_internal_handle
{
	/* The IO handle
	 */
	libmodi_io_handle_t *io_handle;

	/* The bands directory path
	 */
	system_character_t *bands_directory_path;

	/* The bands directory path size
	 */
	size_t bands_directory_path_size;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* Value to indicate if the file IO handle was created inside the library
	 */
	uint8_t file_io_handle_created_in_library;

	/* Value to indicate if the file IO handle was opened inside the library
	 */
	uint8_t file_io_handle_opened_in_library;

	/* The band data file IO pool
	 */
	libbfio_pool_t *band_data_file_io_pool;

	/* Value to indicate if the file IO pool was created inside the library
	 */
	uint8_t band_data_file_io_pool_created_in_library;

	/* The access flags
	 */
	int access_flags;

	/* The bands data handle
	 */
	libmodi_bands_data_handle_t *bands_data_handle;

	/* The block chunks data handle
	 */
	libmodi_block_chunks_data_handle_t *block_chunks_data_handle;

	/* The data stream
	 */
	libfdata_stream_t *data_stream;

	/* The maximum number of open handles in the pool
	 */
	int maximum_number_of_open_handles;

#if defined( HAVE_LIBMODI_MULTI_THREAD_SUPPORT )
	/* The read/write lock
	 */
	libcthreads_read_write_lock_t *read_write_lock;
#endif
};

LIBMODI_EXTERN \
int libmodi_handle_initialize(
     libmodi_handle_t **handle,
     libcerror_error_t **error );

LIBMODI_EXTERN \
int libmodi_handle_free(
     libmodi_handle_t **handle,
     libcerror_error_t **error );

LIBMODI_EXTERN \
int libmodi_handle_signal_abort(
     libmodi_handle_t *handle,
     libcerror_error_t **error );

int libmodi_internal_handle_set_bands_directory_path(
     libmodi_internal_handle_t *internal_handle,
     const char *path,
     size_t path_length,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

int libmodi_internal_handle_set_bands_directory_path_wide(
     libmodi_internal_handle_t *internal_handle,
     const wchar_t *path,
     size_t path_length,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBMODI_EXTERN \
int libmodi_handle_open(
     libmodi_handle_t *handle,
     const char *filename,
     int access_flags,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

LIBMODI_EXTERN \
int libmodi_handle_open_wide(
     libmodi_handle_t *handle,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBMODI_EXTERN \
int libmodi_handle_open_file_io_handle(
     libmodi_handle_t *handle,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error );

LIBMODI_EXTERN \
int libmodi_handle_open_band_data_files(
     libmodi_handle_t *handle,
     libcerror_error_t **error );

LIBMODI_EXTERN \
int libmodi_handle_open_band_data_files_file_io_pool(
     libmodi_handle_t *handle,
     libbfio_pool_t *file_io_pool,
     libcerror_error_t **error );

int libmodi_internal_handle_open_band_data_files_file_io_pool(
     libmodi_internal_handle_t *internal_handle,
     libbfio_pool_t *file_io_pool,
     libcerror_error_t **error );

int libmodi_internal_handle_open_band_data_file(
     libmodi_internal_handle_t *internal_handle,
     libbfio_pool_t *file_io_pool,
     int band_index,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

int libmodi_internal_handle_open_band_data_file_wide(
     libmodi_internal_handle_t *internal_handle,
     libbfio_pool_t *file_io_pool,
     int band_index,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBMODI_EXTERN \
int libmodi_handle_close(
     libmodi_handle_t *handle,
     libcerror_error_t **error );

int libmodi_internal_handle_open_read(
     libmodi_internal_handle_t *internal_handle,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

int libmodi_internal_handle_open_read_sparse_bundle(
     libmodi_internal_handle_t *internal_handle,
     libbfio_handle_t *file_io_handle,
     size64_t file_size,
     libcerror_error_t **error );

int libmodi_internal_handle_open_read_sparse_image(
     libmodi_internal_handle_t *internal_handle,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

int libmodi_internal_handle_open_read_udif_image(
     libmodi_internal_handle_t *internal_handle,
     libbfio_handle_t *file_io_handle,
     size64_t file_size,
     libcerror_error_t **error );

LIBMODI_EXTERN \
ssize_t libmodi_handle_read_buffer(
         libmodi_handle_t *handle,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error );

LIBMODI_EXTERN \
ssize_t libmodi_handle_read_buffer_at_offset(
         libmodi_handle_t *handle,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libcerror_error_t **error );

LIBMODI_EXTERN \
off64_t libmodi_handle_seek_offset(
         libmodi_handle_t *handle,
         off64_t offset,
         int whence,
         libcerror_error_t **error );

LIBMODI_EXTERN \
int libmodi_handle_get_offset(
     libmodi_handle_t *handle,
     off64_t *offset,
     libcerror_error_t **error );

LIBMODI_EXTERN \
int libmodi_handle_set_maximum_number_of_open_handles(
     libmodi_handle_t *handle,
     int maximum_number_of_open_handles,
     libcerror_error_t **error );

LIBMODI_EXTERN \
int libmodi_handle_set_band_data_files_path(
     libmodi_handle_t *handle,
     const char *path,
     size_t path_length,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

LIBMODI_EXTERN \
int libmodi_handle_set_band_data_files_path_wide(
     libmodi_handle_t *handle,
     const wchar_t *path,
     size_t path_length,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBMODI_EXTERN \
int libmodi_handle_get_media_size(
     libmodi_handle_t *handle,
     size64_t *media_size,
     libcerror_error_t **error );

LIBMODI_EXTERN \
int libmodi_handle_get_image_type(
     libmodi_handle_t *handle,
     int *image_type,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMODI_HANDLE_H ) */

