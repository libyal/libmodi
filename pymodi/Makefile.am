if HAVE_PYTHON
AM_CFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBMODI_DLL_IMPORT@

pyexec_LTLIBRARIES = pymodi.la

pymodi_la_SOURCES = \
	pymodi.c pymodi.h \
	pymodi_error.c pymodi_error.h \
	pymodi_file_object_io_handle.c pymodi_file_object_io_handle.h \
	pymodi_file_objects_io_pool.c pymodi_file_objects_io_pool.h \
	pymodi_handle.c pymodi_handle.h \
	pymodi_integer.c pymodi_integer.h \
	pymodi_libbfio.h \
	pymodi_libcerror.h \
	pymodi_libclocale.h \
	pymodi_libmodi.h \
	pymodi_python.h \
	pymodi_unused.h

pymodi_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	../libmodi/libmodi.la \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@

pymodi_la_CPPFLAGS = $(PYTHON_CPPFLAGS)
pymodi_la_LDFLAGS  = -module -avoid-version $(PYTHON_LDFLAGS)

endif

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

