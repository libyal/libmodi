/*
 * Python object wrapper of libmodi_handle_t
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pymodi_error.h"
#include "pymodi_handle.h"
#include "pymodi_file_object_io_handle.h"
#include "pymodi_file_objects_io_pool.h"
#include "pymodi_integer.h"
#include "pymodi_libbfio.h"
#include "pymodi_libcerror.h"
#include "pymodi_libclocale.h"
#include "pymodi_libmodi.h"
#include "pymodi_python.h"
#include "pymodi_unused.h"

#if !defined( LIBMODI_HAVE_BFIO )

LIBMODI_EXTERN \
int libmodi_handle_open_file_io_handle(
     libmodi_handle_t *handle,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libmodi_error_t **error );

LIBMODI_EXTERN \
int libmodi_handle_open_band_data_files_file_io_pool(
     libmodi_handle_t *handle,
     libbfio_pool_t *file_io_pool,
     libmodi_error_t **error );

#endif /* !defined( LIBMODI_HAVE_BFIO ) */

PyMethodDef pymodi_handle_object_methods[] = {

	{ "signal_abort",
	  (PyCFunction) pymodi_handle_signal_abort,
	  METH_NOARGS,
	  "signal_abort() -> None\n"
	  "\n"
	  "Signals the handle to abort the current activity." },

	/* Functions to access the handle */

	{ "open",
	  (PyCFunction) pymodi_handle_open,
	  METH_VARARGS | METH_KEYWORDS,
	  "open(filename, mode='r') -> None\n"
	  "\n"
	  "Opens a handle." },

	{ "open_file_object",
	  (PyCFunction) pymodi_handle_open_file_object,
	  METH_VARARGS | METH_KEYWORDS,
	  "open_file_object(file_object, mode='r') -> None\n"
	  "\n"
	  "Opens a handle using a file-like object." },

	{ "open_band_data_files",
	  (PyCFunction) pymodi_handle_open_band_data_files,
	  METH_NOARGS,
	  "open_band_data_files() -> None\n"
	  "\n"
	  "Opens the band data files." },

	{ "open_band_data_files_as_file_objects",
	  (PyCFunction) pymodi_handle_open_band_data_files_as_file_objects,
	  METH_VARARGS | METH_KEYWORDS,
	  "open_band_data_files_as_file_objects(file_objects) -> None\n"
	  "\n"
	  "Opens band data files using a list of file-like objects." },

	{ "close",
	  (PyCFunction) pymodi_handle_close,
	  METH_NOARGS,
	  "close() -> None\n"
	  "\n"
	  "Closes a handle." },

	{ "read_buffer",
	  (PyCFunction) pymodi_handle_read_buffer,
	  METH_VARARGS | METH_KEYWORDS,
	  "read_buffer(size) -> String\n"
	  "\n"
	  "Reads a buffer of data." },

	{ "read_buffer_at_offset",
	  (PyCFunction) pymodi_handle_read_buffer_at_offset,
	  METH_VARARGS | METH_KEYWORDS,
	  "read_buffer_at_offset(size, offset) -> String\n"
	  "\n"
	  "Reads a buffer of data at a specific offset." },

	{ "seek_offset",
	  (PyCFunction) pymodi_handle_seek_offset,
	  METH_VARARGS | METH_KEYWORDS,
	  "seek_offset(offset, whence) -> None\n"
	  "\n"
	  "Seeks an offset within the data." },

	{ "get_offset",
	  (PyCFunction) pymodi_handle_get_offset,
	  METH_NOARGS,
	  "get_offset() -> Integer\n"
	  "\n"
	  "Retrieved the current offset within the data." },

	/* Some Pythonesque aliases */

	{ "read",
	  (PyCFunction) pymodi_handle_read_buffer,
	  METH_VARARGS | METH_KEYWORDS,
	  "read(size) -> String\n"
	  "\n"
	  "Reads a buffer of data." },

	{ "seek",
	  (PyCFunction) pymodi_handle_seek_offset,
	  METH_VARARGS | METH_KEYWORDS,
	  "seek(offset, whence) -> None\n"
	  "\n"
	  "Seeks an offset within the data." },

	{ "tell",
	  (PyCFunction) pymodi_handle_get_offset,
	  METH_NOARGS,
	  "tell() -> Integer\n"
	  "\n"
	  "Retrieves the current offset within the data." },

	/* Functions to access the handle values */

	{ "get_media_size",
	  (PyCFunction) pymodi_handle_get_media_size,
	  METH_NOARGS,
	  "get_media_size() -> Integer\n"
	  "\n"
	  "Retrieves the size of the data." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pymodi_handle_object_get_set_definitions[] = {

	{ "media_size",
	  (getter) pymodi_handle_get_media_size,
	  (setter) 0,
	  "The media size.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pymodi_handle_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pymodi.handle",
	/* tp_basicsize */
	sizeof( pymodi_handle_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pymodi_handle_free,
	/* tp_print */
	0,
	/* tp_getattr */
	0,
	/* tp_setattr */
	0,
	/* tp_compare */
	0,
	/* tp_repr */
	0,
	/* tp_as_number */
	0,
	/* tp_as_sequence */
	0,
	/* tp_as_mapping */
	0,
	/* tp_hash */
	0,
	/* tp_call */
	0,
	/* tp_str */
	0,
	/* tp_getattro */
	0,
	/* tp_setattro */
	0,
	/* tp_as_buffer */
	0,
	/* tp_flags */
	Py_TPFLAGS_DEFAULT,
	/* tp_doc */
	"pymodi handle object (wraps libmodi_handle_t)",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	0,
	/* tp_iternext */
	0,
	/* tp_methods */
	pymodi_handle_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pymodi_handle_object_get_set_definitions,
	/* tp_base */
	0,
	/* tp_dict */
	0,
	/* tp_descr_get */
	0,
	/* tp_descr_set */
	0,
	/* tp_dictoffset */
	0,
	/* tp_init */
	(initproc) pymodi_handle_init,
	/* tp_alloc */
	0,
	/* tp_new */
	0,
	/* tp_free */
	0,
	/* tp_is_gc */
	0,
	/* tp_bases */
	NULL,
	/* tp_mro */
	NULL,
	/* tp_cache */
	NULL,
	/* tp_subclasses */
	NULL,
	/* tp_weaklist */
	NULL,
	/* tp_del */
	0
};

/* Initializes a handle object
 * Returns 0 if successful or -1 on error
 */
int pymodi_handle_init(
     pymodi_handle_t *pymodi_handle )
{
	static char *function    = "pymodi_handle_init";
	libcerror_error_t *error = NULL;

	if( pymodi_handle == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	pymodi_handle->handle         = NULL;
	pymodi_handle->file_io_handle = NULL;
	pymodi_handle->file_io_pool   = NULL;

	if( libmodi_handle_initialize(
	     &( pymodi_handle->handle ),
	     &error ) != 1 )
	{
		pymodi_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize handle.",
		 function );

		libcerror_error_free(
		 &error );

		return( -1 );
	}
	return( 0 );
}

/* Frees a handle object
 */
void pymodi_handle_free(
      pymodi_handle_t *pymodi_handle )
{
	libcerror_error_t *error    = NULL;
	struct _typeobject *ob_type = NULL;
	static char *function       = "pymodi_handle_free";
	int result                  = 0;

	if( pymodi_handle == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid handle.",
		 function );

		return;
	}
	if( pymodi_handle->handle == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid handle - missing libmodi handle.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pymodi_handle );

	if( ob_type == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: missing ob_type.",
		 function );

		return;
	}
	if( ob_type->tp_free == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid ob_type - missing tp_free.",
		 function );

		return;
	}
	if( ( pymodi_handle->file_io_handle != NULL )
	 || ( pymodi_handle->file_io_pool != NULL ) )
	{
		if( pymodi_handle_close(
		     pymodi_handle,
		     NULL ) == NULL )
		{
			return;
		}
	}
	if( pymodi_handle->handle != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libmodi_handle_free(
		          &( pymodi_handle->handle ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pymodi_error_raise(
			 error,
			 PyExc_MemoryError,
			 "%s: unable to free libmodi handle.",
			 function );

			libcerror_error_free(
			 &error );
		}
	}
	ob_type->tp_free(
	 (PyObject*) pymodi_handle );
}

/* Signals the handle to abort the current activity
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymodi_handle_signal_abort(
           pymodi_handle_t *pymodi_handle,
           PyObject *arguments PYMODI_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pymodi_handle_signal_abort";
	int result               = 0;

	PYMODI_UNREFERENCED_PARAMETER( arguments )

	if( pymodi_handle == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid handle.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libmodi_handle_signal_abort(
	          pymodi_handle->handle,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymodi_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to signal abort.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Opens a handle
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymodi_handle_open(
           pymodi_handle_t *pymodi_handle,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *string_object      = NULL;
	libcerror_error_t *error     = NULL;
	static char *function        = "pymodi_handle_open";
	static char *keyword_list[]  = { "filename", "mode", NULL };
	const char *filename_narrow  = NULL;
	char *mode                   = NULL;
	int result                   = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	const wchar_t *filename_wide = NULL;
#else
	PyObject *utf8_string_object = NULL;
#endif

	if( pymodi_handle == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid handle.",
		 function );

		return( NULL );
	}
	/* Note that PyArg_ParseTupleAndKeywords with "s" will force Unicode strings to be converted to narrow character string.
	 * On Windows the narrow character strings contains an extended ASCII string with a codepage. Hence we get a conversion
	 * exception. This will also fail if the default encoding is not set correctly. We cannot use "u" here either since that
	 * does not allow us to pass non Unicode string objects and Python (at least 2.7) does not seems to automatically upcast them.
	 */
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|s",
	     keyword_list,
	     &string_object,
	     &mode ) == 0 )
	{
		return( NULL );
	}
	if( ( mode != NULL )
	 && ( mode[ 0 ] != 'r' ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: unsupported mode: %s.",
		 function,
		 mode );

		return( NULL );
	}
	PyErr_Clear();

	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyUnicode_Type );

	if( result == -1 )
	{
		pymodi_error_fetch_and_raise(
	         PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type unicode.",
		 function );

		return( NULL );
	}
	else if( result != 0 )
	{
		PyErr_Clear();

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		filename_wide = (wchar_t *) PyUnicode_AsUnicode(
		                             string_object );
		Py_BEGIN_ALLOW_THREADS

		result = libmodi_handle_open_wide(
		          pymodi_handle->handle,
	                  filename_wide,
		          LIBMODI_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS
#else
		utf8_string_object = PyUnicode_AsUTF8String(
		                      string_object );

		if( utf8_string_object == NULL )
		{
			pymodi_error_fetch_and_raise(
			 PyExc_RuntimeError,
			 "%s: unable to convert unicode string to UTF-8.",
			 function );

			return( NULL );
		}
#if PY_MAJOR_VERSION >= 3
		filename_narrow = PyBytes_AsString(
				   utf8_string_object );
#else
		filename_narrow = PyString_AsString(
				   utf8_string_object );
#endif
		Py_BEGIN_ALLOW_THREADS

		result = libmodi_handle_open(
		          pymodi_handle->handle,
	                  filename_narrow,
		          LIBMODI_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS

		Py_DecRef(
		 utf8_string_object );
#endif
		if( result != 1 )
		{
			pymodi_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to open handle.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
	result = PyObject_IsInstance(
		  string_object,
		  (PyObject *) &PyBytes_Type );
#else
	result = PyObject_IsInstance(
		  string_object,
		  (PyObject *) &PyString_Type );
#endif
	if( result == -1 )
	{
		pymodi_error_fetch_and_raise(
	         PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type string.",
		 function );

		return( NULL );
	}
	else if( result != 0 )
	{
		PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
		filename_narrow = PyBytes_AsString(
				   string_object );
#else
		filename_narrow = PyString_AsString(
				   string_object );
#endif
		Py_BEGIN_ALLOW_THREADS

		result = libmodi_handle_open(
		          pymodi_handle->handle,
	                  filename_narrow,
		          LIBMODI_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pymodi_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to open handle.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	PyErr_Format(
	 PyExc_TypeError,
	 "%s: unsupported string object type.",
	 function );

	return( NULL );
}

/* Opens a handle using a file-like object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymodi_handle_open_file_object(
           pymodi_handle_t *pymodi_handle,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *file_object       = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pymodi_handle_open_file_object";
	static char *keyword_list[] = { "file_object", "mode", NULL };
	char *mode                  = NULL;
	int result                  = 0;

	if( pymodi_handle == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid handle.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|s",
	     keyword_list,
	     &file_object,
	     &mode ) == 0 )
	{
		return( NULL );
	}
	if( ( mode != NULL )
	 && ( mode[ 0 ] != 'r' ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: unsupported mode: %s.",
		 function,
		 mode );

		return( NULL );
	}
	PyErr_Clear();

	result = PyObject_HasAttrString(
	          file_object,
	          "read" );

	if( result != 1 )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: unsupported file object - missing read attribute.",
		 function );

		return( NULL );
	}
	PyErr_Clear();

	result = PyObject_HasAttrString(
	          file_object,
	          "seek" );

	if( result != 1 )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: unsupported file object - missing seek attribute.",
		 function );

		return( NULL );
	}
	if( pymodi_handle->file_io_handle != NULL )
	{
		pymodi_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: invalid handle - file IO handle already set.",
		 function );

		goto on_error;
	}
	if( pymodi_file_object_initialize(
	     &( pymodi_handle->file_io_handle ),
	     file_object,
	     &error ) != 1 )
	{
		pymodi_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize file IO handle.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libmodi_handle_open_file_io_handle(
	          pymodi_handle->handle,
	          pymodi_handle->file_io_handle,
	          LIBMODI_OPEN_READ,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymodi_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to open handle.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );

on_error:
	if( pymodi_handle->file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &( pymodi_handle->file_io_handle ),
		 NULL );
	}
	return( NULL );
}

/* Opens the band data files
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymodi_handle_open_band_data_files(
           pymodi_handle_t *pymodi_handle,
           PyObject *arguments PYMODI_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pymodi_handle_open_band_data_files";
	int result               = 0;

	if( pymodi_handle == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid handle.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libmodi_handle_open_band_data_files(
	          pymodi_handle->handle,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymodi_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to open band data files.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Opens band data files using a list of file-like objects
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymodi_handle_open_band_data_files_as_file_objects(
           pymodi_handle_t *pymodi_handle,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *file_objects      = NULL;
	libcerror_error_t *error    = NULL;
	static char *keyword_list[] = { "file_object", NULL };
	static char *function       = "pymodi_handle_open_band_data_files_as_file_objects";
	int result                  = 0;

	if( pymodi_handle == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O",
	     keyword_list,
	     &file_objects ) == 0 )
	{
		return( NULL );
	}
	if( pymodi_file_objects_pool_initialize(
	     &( pymodi_handle->file_io_pool ),
	     file_objects,
	     LIBBFIO_OPEN_READ,
	     &error ) != 1 )
	{
		pymodi_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize file IO pool.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libmodi_handle_open_band_data_files_file_io_pool(
	          pymodi_handle->handle,
	          pymodi_handle->file_io_pool,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymodi_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to open band data files.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );

on_error:
	if( pymodi_handle->file_io_pool != NULL )
	{
		libbfio_pool_free(
		 &( pymodi_handle->file_io_pool ),
		 NULL );
	}
	return( NULL );
}

/* Closes a handle
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymodi_handle_close(
           pymodi_handle_t *pymodi_handle,
           PyObject *arguments PYMODI_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pymodi_handle_close";
	int result               = 0;

	PYMODI_UNREFERENCED_PARAMETER( arguments )

	if( pymodi_handle == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid handle.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libmodi_handle_close(
	          pymodi_handle->handle,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 0 )
	{
		pymodi_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to close handle.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	if( pymodi_handle->file_io_handle != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libbfio_handle_free(
		          &( pymodi_handle->file_io_handle ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pymodi_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to free libbfio file IO handle.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
	}
	if( pymodi_handle->file_io_pool != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libbfio_pool_free(
		          &( pymodi_handle->file_io_pool ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pymodi_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to free libbfio file IO pool.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Reads data at the current offset into a buffer
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymodi_handle_read_buffer(
           pymodi_handle_t *pymodi_handle,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *integer_object    = NULL;
	PyObject *string_object     = NULL;
	libcerror_error_t *error    = NULL;
	char *buffer                = NULL;
	static char *function       = "pymodi_handle_read_buffer";
	static char *keyword_list[] = { "size", NULL };
	ssize_t read_count          = 0;
	int64_t read_size           = 0;
	int result                  = 0;

	if( pymodi_handle == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid handle.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "|O",
	     keyword_list,
	     &integer_object ) == 0 )
	{
		return( NULL );
	}
	if( integer_object == NULL )
	{
		result = 0;
	}
	else
	{
		result = PyObject_IsInstance(
		          integer_object,
		          (PyObject *) &PyLong_Type );

		if( result == -1 )
		{
			pymodi_error_fetch_and_raise(
			 PyExc_RuntimeError,
			 "%s: unable to determine if integer object is of type long.",
			 function );

			return( NULL );
		}
#if PY_MAJOR_VERSION < 3
		else if( result == 0 )
		{
			PyErr_Clear();

			result = PyObject_IsInstance(
			          integer_object,
			          (PyObject *) &PyInt_Type );

			if( result == -1 )
			{
				pymodi_error_fetch_and_raise(
				 PyExc_RuntimeError,
				 "%s: unable to determine if integer object is of type int.",
				 function );

				return( NULL );
			}
		}
#endif
	}
	if( result != 0 )
	{
		if( pymodi_integer_signed_copy_to_64bit(
		     integer_object,
		     &read_size,
		     &error ) != 1 )
		{
			pymodi_error_raise(
			 error,
			 PyExc_ValueError,
			 "%s: unable to convert integer object into read size.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
	}
	else if( ( integer_object == NULL )
	      || ( integer_object == Py_None ) )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libmodi_handle_get_media_size(
		          pymodi_handle->handle,
		          (size64_t *) &read_size,
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pymodi_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to retrieve media size.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
	}
	else
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: unsupported integer object type.",
		 function );

		return( NULL );
	}
	if( read_size == 0 )
	{
#if PY_MAJOR_VERSION >= 3
		string_object = PyBytes_FromString(
		                 "" );
#else
		string_object = PyString_FromString(
		                 "" );
#endif
		return( string_object );
	}
	if( read_size < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid read size value less than zero.",
		 function );

		return( NULL );
	}
	/* Make sure the data fits into a memory buffer
	 */
	if( ( read_size > (int64_t) INT_MAX )
	 || ( read_size > (int64_t) SSIZE_MAX ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid argument read size value exceeds maximum.",
		 function );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	string_object = PyBytes_FromStringAndSize(
	                 NULL,
	                 (Py_ssize_t) read_size );

	buffer = PyBytes_AsString(
	          string_object );
#else
	/* Note that a size of 0 is not supported
	 */
	string_object = PyString_FromStringAndSize(
	                 NULL,
	                 (Py_ssize_t) read_size );

	buffer = PyString_AsString(
	          string_object );
#endif
	Py_BEGIN_ALLOW_THREADS

	read_count = libmodi_handle_read_buffer(
	              pymodi_handle->handle,
	              (uint8_t *) buffer,
	              (size_t) read_size,
	              &error );

	Py_END_ALLOW_THREADS

	if( read_count == -1 )
	{
		pymodi_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to read data.",
		 function );

		libcerror_error_free(
		 &error );

		Py_DecRef(
		 (PyObject *) string_object );

		return( NULL );
	}
	/* Need to resize the string here in case read_size was not fully read.
	 */
#if PY_MAJOR_VERSION >= 3
	if( _PyBytes_Resize(
	     &string_object,
	     (Py_ssize_t) read_count ) != 0 )
#else
	if( _PyString_Resize(
	     &string_object,
	     (Py_ssize_t) read_count ) != 0 )
#endif
	{
		Py_DecRef(
		 (PyObject *) string_object );

		return( NULL );
	}
	return( string_object );
}

/* Reads data at a specific offset
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymodi_handle_read_buffer_at_offset(
           pymodi_handle_t *pymodi_handle,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *integer_object    = NULL;
	PyObject *string_object     = NULL;
	libcerror_error_t *error    = NULL;
	char *buffer                = NULL;
	static char *function       = "pymodi_handle_read_buffer_at_offset";
	static char *keyword_list[] = { "size", "offset", NULL };
	ssize_t read_count          = 0;
	off64_t read_offset         = 0;
	int64_t read_size           = 0;
	int result                  = 0;

	if( pymodi_handle == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid handle.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "OL",
	     keyword_list,
	     &integer_object,
	     &read_offset ) == 0 )
	{
		return( NULL );
	}
	result = PyObject_IsInstance(
	          integer_object,
	          (PyObject *) &PyLong_Type );

	if( result == -1 )
	{
		pymodi_error_fetch_and_raise(
		 PyExc_RuntimeError,
		 "%s: unable to determine if integer object is of type long.",
		 function );

		return( NULL );
	}
#if PY_MAJOR_VERSION < 3
	else if( result == 0 )
	{
		PyErr_Clear();

		result = PyObject_IsInstance(
		          integer_object,
		          (PyObject *) &PyInt_Type );

		if( result == -1 )
		{
			pymodi_error_fetch_and_raise(
			 PyExc_RuntimeError,
			 "%s: unable to determine if integer object is of type int.",
			 function );

			return( NULL );
		}
	}
#endif
	if( result != 0 )
	{
		if( pymodi_integer_signed_copy_to_64bit(
		     integer_object,
		     &read_size,
		     &error ) != 1 )
		{
			pymodi_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to convert integer object into read size.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
	}
	else
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: unsupported integer object type.",
		 function );

		return( NULL );
	}
	if( read_size == 0 )
	{
#if PY_MAJOR_VERSION >= 3
		string_object = PyBytes_FromString(
		                 "" );
#else
		string_object = PyString_FromString(
		                 "" );
#endif
		return( string_object );
	}
	if( read_size < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid read size value less than zero.",
		 function );

		return( NULL );
	}
	/* Make sure the data fits into a memory buffer
	 */
	if( ( read_size > (int64_t) INT_MAX )
	 || ( read_size > (int64_t) SSIZE_MAX ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid argument read size value exceeds maximum.",
		 function );

		return( NULL );
	}
	if( read_offset < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid read offset value less than zero.",
		 function );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	string_object = PyBytes_FromStringAndSize(
	                 NULL,
	                 (Py_ssize_t) read_size );

	buffer = PyBytes_AsString(
	          string_object );
#else
	/* Note that a size of 0 is not supported
	 */
	string_object = PyString_FromStringAndSize(
	                 NULL,
	                 (Py_ssize_t) read_size );

	buffer = PyString_AsString(
	          string_object );
#endif
	Py_BEGIN_ALLOW_THREADS

	read_count = libmodi_handle_read_buffer_at_offset(
	              pymodi_handle->handle,
	              (uint8_t *) buffer,
	              (size_t) read_size,
	              (off64_t) read_offset,
	              &error );

	Py_END_ALLOW_THREADS

	if( read_count == -1 )
	{
		pymodi_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to read data.",
		 function );

		libcerror_error_free(
		 &error );

		Py_DecRef(
		 (PyObject *) string_object );

		return( NULL );
	}
	/* Need to resize the string here in case read_size was not fully read.
	 */
#if PY_MAJOR_VERSION >= 3
	if( _PyBytes_Resize(
	     &string_object,
	     (Py_ssize_t) read_count ) != 0 )
#else
	if( _PyString_Resize(
	     &string_object,
	     (Py_ssize_t) read_count ) != 0 )
#endif
	{
		Py_DecRef(
		 (PyObject *) string_object );

		return( NULL );
	}
	return( string_object );
}

/* Seeks a certain offset in the data
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymodi_handle_seek_offset(
           pymodi_handle_t *pymodi_handle,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error    = NULL;
	static char *function       = "pymodi_handle_seek_offset";
	static char *keyword_list[] = { "offset", "whence", NULL };
	off64_t offset              = 0;
	int whence                  = 0;

	if( pymodi_handle == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid handle.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "L|i",
	     keyword_list,
	     &offset,
	     &whence ) == 0 )
	{
		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	offset = libmodi_handle_seek_offset(
	          pymodi_handle->handle,
	          offset,
	          whence,
	          &error );

	Py_END_ALLOW_THREADS

 	if( offset == -1 )
	{
		pymodi_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to seek offset.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Retrieves the current offset in the data
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymodi_handle_get_offset(
           pymodi_handle_t *pymodi_handle,
           PyObject *arguments PYMODI_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pymodi_handle_get_offset";
	off64_t current_offset   = 0;
	int result               = 0;

	PYMODI_UNREFERENCED_PARAMETER( arguments )

	if( pymodi_handle == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid handle.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libmodi_handle_get_offset(
	          pymodi_handle->handle,
	          &current_offset,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymodi_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve offset.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pymodi_integer_signed_new_from_64bit(
	                  (int64_t) current_offset );

	return( integer_object );
}

/* Retrieves the media size
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymodi_handle_get_media_size(
           pymodi_handle_t *pymodi_handle,
           PyObject *arguments PYMODI_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pymodi_handle_get_media_size";
	size64_t media_size      = 0;
	int result               = 0;

	PYMODI_UNREFERENCED_PARAMETER( arguments )

	if( pymodi_handle == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid handle.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libmodi_handle_get_media_size(
	          pymodi_handle->handle,
	          &media_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymodi_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: failed to retrieve media size.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pymodi_integer_unsigned_new_from_64bit(
	                  (uint64_t) media_size );

	return( integer_object );
}

