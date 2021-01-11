/*
 * Library to access the Mac OS disk image formats
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

#if !defined( _LIBMODI_H )
#define _LIBMODI_H

#include <libmodi/codepage.h>
#include <libmodi/definitions.h>
#include <libmodi/error.h>
#include <libmodi/extern.h>
#include <libmodi/features.h>
#include <libmodi/types.h>

#include <stdio.h>

#if defined( LIBMODI_HAVE_BFIO )
#include <libbfio.h>
#endif

#if defined( __cplusplus )
extern "C" {
#endif

/* -------------------------------------------------------------------------
 * Support functions
 * ------------------------------------------------------------------------- */

/* Returns the library version
 */
LIBMODI_EXTERN \
const char *libmodi_get_version(
             void );

/* Returns the access flags for reading
 */
LIBMODI_EXTERN \
int libmodi_get_access_flags_read(
     void );

/* Returns the access flags for reading and writing
 */
LIBMODI_EXTERN \
int libmodi_get_access_flags_read_write(
     void );

/* Returns the access flags for writing
 */
LIBMODI_EXTERN \
int libmodi_get_access_flags_write(
     void );

/* Retrieves the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBMODI_EXTERN \
int libmodi_get_codepage(
     int *codepage,
     libmodi_error_t **error );

/* Sets the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBMODI_EXTERN \
int libmodi_set_codepage(
     int codepage,
     libmodi_error_t **error );

/* Determines if a file contains a Mac OS disk image file signature
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBMODI_EXTERN \
int libmodi_check_file_signature(
     const char *filename,
     libmodi_error_t **error );

#if defined( LIBMODI_HAVE_WIDE_CHARACTER_TYPE )

/* Determines if a file contains a Mac OS disk image file signature
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBMODI_EXTERN \
int libmodi_check_file_signature_wide(
     const wchar_t *filename,
     libmodi_error_t **error );

#endif /* defined( LIBMODI_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBMODI_HAVE_BFIO )

/* Determines if a file contains a Mac OS disk image file signature using a Basic File IO (bfio) handle
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBMODI_EXTERN \
int libmodi_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libmodi_error_t **error );

#endif /* defined( LIBMODI_HAVE_BFIO ) */

/* -------------------------------------------------------------------------
 * Notify functions
 * ------------------------------------------------------------------------- */

/* Sets the verbose notification
 */
LIBMODI_EXTERN \
void libmodi_notify_set_verbose(
      int verbose );

/* Sets the notification stream
 * Returns 1 if successful or -1 on error
 */
LIBMODI_EXTERN \
int libmodi_notify_set_stream(
     FILE *stream,
     libmodi_error_t **error );

/* Opens the notification stream using a filename
 * The stream is opened in append mode
 * Returns 1 if successful or -1 on error
 */
LIBMODI_EXTERN \
int libmodi_notify_stream_open(
     const char *filename,
     libmodi_error_t **error );

/* Closes the notification stream if opened using a filename
 * Returns 0 if successful or -1 on error
 */
LIBMODI_EXTERN \
int libmodi_notify_stream_close(
     libmodi_error_t **error );

/* -------------------------------------------------------------------------
 * Error functions
 * ------------------------------------------------------------------------- */

/* Frees an error
 */
LIBMODI_EXTERN \
void libmodi_error_free(
      libmodi_error_t **error );

/* Prints a descriptive string of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBMODI_EXTERN \
int libmodi_error_fprint(
     libmodi_error_t *error,
     FILE *stream );

/* Prints a descriptive string of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the number of printed characters if successful or -1 on error
 */
LIBMODI_EXTERN \
int libmodi_error_sprint(
     libmodi_error_t *error,
     char *string,
     size_t size );

/* Prints a backtrace of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBMODI_EXTERN \
int libmodi_error_backtrace_fprint(
     libmodi_error_t *error,
     FILE *stream );

/* Prints a backtrace of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the number of printed characters if successful or -1 on error
 */
LIBMODI_EXTERN \
int libmodi_error_backtrace_sprint(
     libmodi_error_t *error,
     char *string,
     size_t size );

/* -------------------------------------------------------------------------
 * Handle functions
 * ------------------------------------------------------------------------- */

/* Creates a handle
 * Make sure the value handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBMODI_EXTERN \
int libmodi_handle_initialize(
     libmodi_handle_t **handle,
     libmodi_error_t **error );

/* Frees a handle
 * Returns 1 if successful or -1 on error
 */
LIBMODI_EXTERN \
int libmodi_handle_free(
     libmodi_handle_t **handle,
     libmodi_error_t **error );

/* Signals a handle to abort its current activity
 * Returns 1 if successful or -1 on error
 */
LIBMODI_EXTERN \
int libmodi_handle_signal_abort(
     libmodi_handle_t *handle,
     libmodi_error_t **error );

/* Opens a handle
 * Returns 1 if successful or -1 on error
 */
LIBMODI_EXTERN \
int libmodi_handle_open(
     libmodi_handle_t *handle,
     const char *filename,
     int access_flags,
     libmodi_error_t **error );

#if defined( LIBMODI_HAVE_WIDE_CHARACTER_TYPE )

/* Opens a handle
 * Returns 1 if successful or -1 on error
 */
LIBMODI_EXTERN \
int libmodi_handle_open_wide(
     libmodi_handle_t *handle,
     const wchar_t *filename,
     int access_flags,
     libmodi_error_t **error );

#endif /* defined( LIBMODI_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBMODI_HAVE_BFIO )

/* Opens a handle using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBMODI_EXTERN \
int libmodi_handle_open_file_io_handle(
     libmodi_handle_t *handle,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libmodi_error_t **error );

#endif /* defined( LIBMODI_HAVE_BFIO ) */

/* Opens the band data files
 * If the band data filenames were not set explicitly this function assumes the band data files
 * are in the sub directory band in the same location as the Info.plist file
 * Returns 1 if successful or -1 on error
 */
LIBMODI_EXTERN \
int libmodi_handle_open_band_data_files(
     libmodi_handle_t *handle,
     libmodi_error_t **error );

#if defined( LIBMODI_HAVE_BFIO )

/* Opens the band data files using a Basic File IO (bfio) pool
 * This function assumes the band data files are in order and
 * non-existing band data files are set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBMODI_EXTERN \
int libmodi_handle_open_band_data_files_file_io_pool(
     libmodi_handle_t *handle,
     libbfio_pool_t *file_io_pool,
     libmodi_error_t **error );

#endif /* defined( LIBMODI_HAVE_BFIO ) */

/* Closes a handle
 * Returns 0 if successful or -1 on error
 */
LIBMODI_EXTERN \
int libmodi_handle_close(
     libmodi_handle_t *handle,
     libmodi_error_t **error );

/* Reads (media) data at the current offset
 * Returns the number of bytes read or -1 on error
 */
LIBMODI_EXTERN \
ssize_t libmodi_handle_read_buffer(
         libmodi_handle_t *handle,
         void *buffer,
         size_t buffer_size,
         libmodi_error_t **error );

/* Reads (media) data at a specific offset
 * Returns the number of bytes read or -1 on error
 */
LIBMODI_EXTERN \
ssize_t libmodi_handle_read_buffer_at_offset(
         libmodi_handle_t *handle,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libmodi_error_t **error );

/* Seeks a certain offset of the (media) data
 * Returns the offset if seek is successful or -1 on error
 */
LIBMODI_EXTERN \
off64_t libmodi_handle_seek_offset(
         libmodi_handle_t *handle,
         off64_t offset,
         int whence,
         libmodi_error_t **error );

/* Retrieves the current offset of the (media) data
 * Returns the offset if successful or -1 on error
 */
LIBMODI_EXTERN \
int libmodi_handle_get_offset(
     libmodi_handle_t *handle,
     off64_t *offset,
     libmodi_error_t **error );

/* Sets the maximum number of (concurrent) open file handles
 * Returns 1 if successful or -1 on error
 */
LIBMODI_EXTERN \
int libmodi_handle_set_maximum_number_of_open_handles(
     libmodi_handle_t *handle,
     int maximum_number_of_open_handles,
     libmodi_error_t **error );

/* Sets the path to the band data files
 * Returns 1 if successful or -1 on error
 */
LIBMODI_EXTERN \
int libmodi_handle_set_band_data_files_path(
     libmodi_handle_t *handle,
     const char *path,
     size_t path_length,
     libmodi_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Sets the path to the band data files
 * Returns 1 if successful or -1 on error
 */
LIBMODI_EXTERN \
int libmodi_handle_set_band_data_files_path_wide(
     libmodi_handle_t *handle,
     const wchar_t *path,
     size_t path_length,
     libmodi_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Retrieves the media size
 * Returns the 1 if succesful or -1 on error
 */
LIBMODI_EXTERN \
int libmodi_handle_get_media_size(
     libmodi_handle_t *handle,
     size64_t *media_size,
     libmodi_error_t **error );

/* Retrieves the image type
 * Returns the 1 if succesful or -1 on error
 */
LIBMODI_EXTERN \
int libmodi_handle_get_image_type(
     libmodi_handle_t *handle,
     int *image_type,
     libmodi_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMODI_H ) */

