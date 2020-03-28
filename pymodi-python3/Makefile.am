# Note that we cannot use: AUTOMAKE_OPTIONS = subdir-objects
# subdir-objects will compile the source files to a single version of Python.
# Since subdir-objects is being deprecated we copy the source files instead.
am__installdirs = "$(DESTDIR)$(pyexecdir3)"
pyexecdir = $(pyexecdir3)

if HAVE_PYTHON3
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

am_pymodi_la_rpath = -rpath $(pyexecdir3)

BUILT_SOURCES = \
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

pyexec_LTLIBRARIES = pymodi.la

nodist_pymodi_la_SOURCES = $(BUILT_SOURCES)

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

pymodi_la_CPPFLAGS = $(PYTHON3_CPPFLAGS)
pymodi_la_LDFLAGS  = -module -avoid-version $(PYTHON3_LDFLAGS)

$(BUILT_SOURCES):
	/bin/cp -f $(top_srcdir)/pymodi/$@ $@

endif

MAINTAINERCLEANFILES = \
	Makefile.in

clean-local:
	/bin/rm -f pymodi*.[ch]

distclean: clean
	/bin/rm -f Makefile

