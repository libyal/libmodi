AM_CPPFLAGS = \
	-DLOCALEDIR=\"$(datadir)/locale\" \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCDIRECTORY_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFCACHE_CPPFLAGS@ \
	@LIBFDATA_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@

lib_LTLIBRARIES = libmodi.la

libmodi_la_SOURCES = \
	libmodi.c \
	libmodi_bands_table.c libmodi_bands_table.h \
	libmodi_codepage.h \
	libmodi_data_band.c libmodi_data_band.h \
	libmodi_debug.c libmodi_debug.h \
	libmodi_definitions.h \
	libmodi_error.c libmodi_error.h \
	libmodi_extern.h \
	libmodi_handle.c libmodi_handle.h \
	libmodi_i18n.c libmodi_i18n.h \
	libmodi_io_handle.c libmodi_io_handle.h \
	libmodi_libbfio.h \
	libmodi_libcdirectory.h \
	libmodi_libcerror.h \
	libmodi_libclocale.h \
	libmodi_libcnotify.h \
	libmodi_libcstring.h \
	libmodi_libcthreads.h \
	libmodi_libfcache.h \
	libmodi_libfdata.h \
	libmodi_libuna.h \
	libmodi_metadata.c libmodi_metadata.h \
	libmodi_notify.c libmodi_notify.h \
	libmodi_support.c libmodi_support.h \
	libmodi_types.h \
	libmodi_unused.h \
	modi_sparse_image_header.h

libmodi_la_LIBADD = \
	@LIBCSTRING_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCTHREADS_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCDIRECTORY_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFCACHE_LIBADD@ \
	@LIBFDATA_LIBADD@ \
	@PTHREAD_LIBADD@

libmodi_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libmodi_definitions.h.in \
	libmodi.rc \
	libmodi.rc.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libmodi_definitions.h
	/bin/rm -f libmodi.rc
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libmodi ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libmodi_la_SOURCES)

