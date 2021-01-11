/*
 * Shows information obtained from a Mac OS disk image
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
#include <memory.h>
#include <system_string.h>
#include <types.h>

#include <stdio.h>

#if defined( HAVE_IO_H ) || defined( WINAPI )
#include <io.h>
#endif

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#if defined( HAVE_UNISTD_H )
#include <unistd.h>
#endif

#include "info_handle.h"
#include "moditools_getopt.h"
#include "moditools_libcerror.h"
#include "moditools_libclocale.h"
#include "moditools_libcnotify.h"
#include "moditools_libmodi.h"
#include "moditools_output.h"
#include "moditools_signal.h"
#include "moditools_unused.h"

info_handle_t *modiinfo_info_handle = NULL;
int modiinfo_abort                  = 0;

/* Prints the executable usage information
 */
void usage_fprint(
      FILE *stream )
{
	if( stream == NULL )
	{
		return;
	}
	fprintf( stream, "Use modiinfo to determine information about a Mac OS disk\n"
	                 "image.\n\n" );

	fprintf( stream, "Usage: modiinfo [ -hvV ] source\n\n" );

	fprintf( stream, "\tsource: the source file or directory\n\n" );

	fprintf( stream, "\t-h:     shows this help\n" );
	fprintf( stream, "\t-v:     verbose output to stderr\n" );
	fprintf( stream, "\t-V:     print version\n" );
}

/* Signal handler for modiinfo
 */
void modiinfo_signal_handler(
      moditools_signal_t signal MODITOOLS_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function   = "modiinfo_signal_handler";

	MODITOOLS_UNREFERENCED_PARAMETER( signal )

	modiinfo_abort = 1;

	if( modiinfo_info_handle != NULL )
	{
		if( info_handle_signal_abort(
		     modiinfo_info_handle,
		     &error ) != 1 )
		{
			libcnotify_printf(
			 "%s: unable to signal info handle to abort.\n",
			 function );

			libcnotify_print_error_backtrace(
			 error );
			libcerror_error_free(
			 &error );
		}
	}
	/* Force stdin to close otherwise any function reading it will remain blocked
	 */
#if defined( WINAPI ) && !defined( __CYGWIN__ )
	if( _close(
	     0 ) != 0 )
#else
	if( close(
	     0 ) != 0 )
#endif
	{
		libcnotify_printf(
		 "%s: unable to close stdin.\n",
		 function );
	}
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libmodi_error_t *error     = NULL;
	system_character_t *source = NULL;
	char *program              = "modiinfo";
	system_integer_t option    = 0;
	int verbose                = 0;

	libcnotify_stream_set(
	 stderr,
	 NULL );
	libcnotify_verbose_set(
	 1 );

	if( libclocale_initialize(
             "moditools",
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize locale values.\n" );

		goto on_error;
	}
        if( moditools_output_initialize(
             _IONBF,
             &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize output settings.\n" );

		goto on_error;
	}
	moditools_output_version_fprint(
	 stdout,
	 program );

	while( ( option = moditools_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "hvV" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM "\n",
				 argv[ optind - 1 ] );

				usage_fprint(
				 stdout );

				return( EXIT_FAILURE );

			case (system_integer_t) 'h':
				usage_fprint(
				 stdout );

				return( EXIT_SUCCESS );

			case (system_integer_t) 'v':
				verbose = 1;

				break;

			case (system_integer_t) 'V':
				moditools_output_copyright_fprint(
				 stdout );

				return( EXIT_SUCCESS );
		}
	}
	if( optind == argc )
	{
		fprintf(
		 stderr,
		 "Missing source file or directory.\n" );

		usage_fprint(
		 stdout );

		return( EXIT_FAILURE );
	}
	source = argv[ optind ];

	libcnotify_verbose_set(
	 verbose );
	libmodi_notify_set_stream(
	 stderr,
	 NULL );
	libmodi_notify_set_verbose(
	 verbose );

	if( info_handle_initialize(
	     &modiinfo_info_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize info handle.\n" );

		goto on_error;
	}
	if( info_handle_open_input(
	     modiinfo_info_handle,
	     source,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to open source file or directory.\n" );

		goto on_error;
	}
	if( info_handle_input_fprint(
	     modiinfo_info_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to print input information.\n" );

		goto on_error;
	}
	if( info_handle_close(
	     modiinfo_info_handle,
	     &error ) != 0 )
	{
		fprintf(
		 stderr,
		 "Unable to close info handle.\n" );

		goto on_error;
	}
	if( info_handle_free(
	     &modiinfo_info_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free info handle.\n" );

		goto on_error;
	}
	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
	if( modiinfo_info_handle != NULL )
	{
		info_handle_free(
		 &modiinfo_info_handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

