/*
 * Mount handle
 *
 * Copyright (C) 2012-2016, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <memory.h>
#include <types.h>

#include "moditools_libcdata.h"
#include "moditools_libcerror.h"
#include "moditools_libcnotify.h"
#include "moditools_libcpath.h"
#include "moditools_libmodi.h"
#include "mount_handle.h"

/* Creates a mount handle
 * Make sure the value mount_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int mount_handle_initialize(
     mount_handle_t **mount_handle,
     libcerror_error_t **error )
{
	static char *function = "mount_handle_initialize";

	if( mount_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid mount handle.",
		 function );

		return( -1 );
	}
	if( *mount_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid mount handle value already set.",
		 function );

		return( -1 );
	}
	*mount_handle = memory_allocate_structure(
	                 mount_handle_t );

	if( *mount_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create mount handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *mount_handle,
	     0,
	     sizeof( mount_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear mount handle.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( ( *mount_handle )->inputs_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize inputs array.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *mount_handle != NULL )
	{
		memory_free(
		 *mount_handle );

		*mount_handle = NULL;
	}
	return( -1 );
}

/* Frees a mount handle
 * Returns 1 if successful or -1 on error
 */
int mount_handle_free(
     mount_handle_t **mount_handle,
     libcerror_error_t **error )
{
	static char *function = "mount_handle_free";
	int result            = 1;

	if( mount_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid mount handle.",
		 function );

		return( -1 );
	}
	if( *mount_handle != NULL )
	{
		if( libcdata_array_free(
		     &( ( *mount_handle )->inputs_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libmodi_handle_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free inputs array.",
			 function );

			result = -1;
		}
		memory_free(
		 *mount_handle );

		*mount_handle = NULL;
	}
	return( result );
}

/* Signals the mount handle to abort
 * Returns 1 if successful or -1 on error
 */
int mount_handle_signal_abort(
     mount_handle_t *mount_handle,
     libcerror_error_t **error )
{
	libmodi_handle_t *input_handle = NULL;
	static char *function          = "mount_handle_signal_abort";	
	int input_index                = 0;
	int number_of_inputs           = 0;

	if( mount_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid mount handle.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     mount_handle->inputs_array,
	     &number_of_inputs,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of inputs.",
		 function );

		return( -1 );
	}
	for( input_index = number_of_inputs - 1;
	     input_index > 0;
	     input_index-- )
	{
		if( libcdata_array_get_entry_by_index(
		     mount_handle->inputs_array,
		     input_index,
		     (intptr_t **) &input_handle,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve input: %d.",
			 function,
			 input_index );

			return( -1 );
		}
		if( libmodi_handle_signal_abort(
		     input_handle,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to signal input: %d to abort.",
			 function,
			 input_index );

			return( -1 );
		}
	}
	return( 1 );
}

/* Opens the input of the mount handle
 * Returns 1 if successful, 0 if the keys could not be read or -1 on error
 */
int mount_handle_open_input(
     mount_handle_t *mount_handle,
     const libcstring_system_character_t *filename,
     libcerror_error_t **error )
{
	libmodi_handle_t *input_handle = NULL;
	static char *function          = "mount_handle_open_input";
	size_t filename_length         = 0;
	int entry_index                = 0;

	if( mount_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid mount handle.",
		 function );

		return( -1 );
	}
	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	filename_length = libcstring_system_string_length(
	                   filename );

	if( libmodi_handle_initialize(
	     &input_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize input.",
		 function );

		goto on_error;
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	if( libmodi_handle_open_wide(
	     input_handle,
	     filename,
	     LIBMODI_OPEN_READ,
	     error ) != 1 )
#else
	if( libmodi_handle_open(
	     input_handle,
	     filename,
	     LIBMODI_OPEN_READ,
	     error ) != 1 )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open input.",
		 function );

		goto on_error;
	}
	if( libmodi_handle_open_band_data_files(
	     input_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open band data files.",
		 function );

		goto on_error;
	}
	if( libcdata_array_append_entry(
	     mount_handle->inputs_array,
	     &entry_index,
	     (intptr_t *) input_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append input to array.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( input_handle != NULL )
	{
		libmodi_handle_free(
		 &input_handle,
		 NULL );
	}
	libcdata_array_empty(
	 mount_handle->inputs_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libmodi_handle_free,
	 NULL );

	return( -1 );
}

/* Closes the mount handle
 * Returns the 0 if succesful or -1 on error
 */
int mount_handle_close(
     mount_handle_t *mount_handle,
     libcerror_error_t **error )
{
	libmodi_handle_t *input_handle = NULL;
	static char *function          = "mount_handle_close";
	int input_index                = 0;
	int number_of_inputs           = 0;

	if( mount_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid mount handle.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     mount_handle->inputs_array,
	     &number_of_inputs,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of inputs.",
		 function );

		return( -1 );
	}
	for( input_index = number_of_inputs - 1;
	     input_index > 0;
	     input_index-- )
	{
		if( libcdata_array_get_entry_by_index(
		     mount_handle->inputs_array,
		     input_index,
		     (intptr_t **) &input_handle,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve input: %d.",
			 function,
			 input_index );

			return( -1 );
		}
		if( libmodi_handle_close(
		     input_handle,
		     error ) != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close input: %d.",
			 function,
			 input_index );

			return( -1 );
		}
	}
	return( 0 );
}

/* Read a buffer from a specific input
 * Returns the number of bytes read if successful or -1 on error
 */
ssize_t mount_handle_read_buffer(
         mount_handle_t *mount_handle,
         int input_index,
         uint8_t *buffer,
         size_t size,
         libcerror_error_t **error )
{
	libmodi_handle_t *input_handle = NULL;
	static char *function          = "mount_handle_read_buffer";
	ssize_t read_count             = 0;

	if( mount_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid mount handle.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     mount_handle->inputs_array,
	     input_index,
	     (intptr_t **) &input_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve input: %d.",
		 function,
		 input_index );

		return( -1 );
	}
	read_count = libmodi_handle_read_buffer(
	              input_handle,
	              buffer,
	              size,
	              error );

	if( read_count == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read buffer from input: %d.",
		 function,
		 input_index );

		return( -1 );
	}
	return( read_count );
}

/* Seeks a specific offset in a specific input
 * Returns the offset if successful or -1 on error
 */
off64_t mount_handle_seek_offset(
         mount_handle_t *mount_handle,
         int input_index,
         off64_t offset,
         int whence,
         libcerror_error_t **error )
{
	libmodi_handle_t *input_handle = NULL;
	static char *function          = "mount_handle_seek_offset";

	if( mount_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid mount handle.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     mount_handle->inputs_array,
	     input_index,
	     (intptr_t **) &input_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve input: %d.",
		 function,
		 input_index );

		return( -1 );
	}
	offset = libmodi_handle_seek_offset(
	          input_handle,
	          offset,
	          whence,
	          error );

	if( offset == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset in input: %d.",
		 function,
		 input_index );

		return( -1 );
	}
	return( offset );
}

/* Retrieves the media size of a specific input
 * Returns 1 if successful or -1 on error
 */
int mount_handle_get_media_size(
     mount_handle_t *mount_handle,
     int input_index,
     size64_t *size,
     libcerror_error_t **error )
{
	libmodi_handle_t *input_handle = NULL;
	static char *function          = "mount_handle_get_media_size";

	if( mount_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid mount handle.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     mount_handle->inputs_array,
	     input_index,
	     (intptr_t **) &input_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve input: %d.",
		 function,
		 input_index );

		return( -1 );
	}
	if( libmodi_handle_get_media_size(
	     input_handle,
	     size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve media size from input: %d.",
		 function,
		 input_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the number of inputs
 * Returns 1 if successful or -1 on error
 */
int mount_handle_get_number_of_inputs(
     mount_handle_t *mount_handle,
     int *number_of_inputs,
     libcerror_error_t **error )
{
	static char *function = "mount_handle_get_number_of_inputs";

	if( mount_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid mount handle.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     mount_handle->inputs_array,
	     number_of_inputs,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of inputs.",
		 function );

		return( -1 );
	}
	return( 1 );
}

