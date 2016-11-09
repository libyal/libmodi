/*
 * Python object definition of the libmodi file
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

#if !defined( _PYMODI_FILE_H )
#define _PYMODI_FILE_H

#include <common.h>
#include <types.h>

#include "pymodi_libbfio.h"
#include "pymodi_libmodi.h"
#include "pymodi_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pymodi_file pymodi_file_t;

struct pymodi_file
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libmodi file
	 */
	libmodi_file_t *file;

	/* The libbfio file IO handle
	 */
	libbfio_handle_t *file_io_handle;
};

extern PyMethodDef pymodi_file_object_methods[];
extern PyTypeObject pymodi_file_type_object;

PyObject *pymodi_file_new(
           void );

PyObject *pymodi_file_new_open(
           PyObject *self,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pymodi_file_new_open_file_object(
           PyObject *self,
           PyObject *arguments,
           PyObject *keywords );

int pymodi_file_init(
     pymodi_file_t *pymodi_file );

void pymodi_file_free(
      pymodi_file_t *pymodi_file );

PyObject *pymodi_file_signal_abort(
           pymodi_file_t *pymodi_file,
           PyObject *arguments );

PyObject *pymodi_file_open(
           pymodi_file_t *pymodi_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pymodi_file_open_file_object(
           pymodi_file_t *pymodi_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pymodi_file_set_parent(
           pymodi_file_t *pymodi_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pymodi_file_close(
           pymodi_file_t *pymodi_file,
           PyObject *arguments );

PyObject *pymodi_file_read_buffer(
           pymodi_file_t *pymodi_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pymodi_file_read_buffer_at_offset(
           pymodi_file_t *pymodi_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pymodi_file_seek_offset(
           pymodi_file_t *pymodi_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pymodi_file_get_offset(
           pymodi_file_t *pymodi_file,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYMODI_FILE_H ) */

