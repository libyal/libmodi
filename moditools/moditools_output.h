/*
 * Common output functions for the moditools
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

#if !defined( _MODITOOLS_OUTPUT_H )
#define _MODITOOLS_OUTPUT_H

#include <common.h>
#include <file_stream.h>
#include <types.h>

#include "moditools_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

int moditools_output_initialize(
     int stdio_mode,
     libcerror_error_t **error );

void moditools_output_copyright_fprint(
      FILE *stream );

void moditools_output_version_fprint(
      FILE *stream,
      const char *program );

void moditools_output_version_detailed_fprint(
      FILE *stream,
      const char *program );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _MODITOOLS_OUTPUT_H ) */

