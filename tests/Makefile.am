AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
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
	@LIBFGUID_CPPFLAGS@ \
	@LIBFVALUE_CPPFLAGS@ \
	@LIBFPLIST_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBMODI_DLL_IMPORT@

if HAVE_PYTHON_TESTS
TESTS_PYMODI = \
	test_python_functions.sh
endif

TESTS = \
	test_api_functions.sh \
	test_api_types.sh \
	$(TESTS_PYMODI)

check_SCRIPTS = \
	pymodi_test_support.py \
	test_api_functions.sh \
	test_api_types.sh \
	test_python_functions.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	modi_test_bands_table \
	modi_test_data_block \
	modi_test_error \
	modi_test_handle \
	modi_test_io_handle \
	modi_test_notify \
	modi_test_support

modi_test_bands_table_SOURCES = \
	modi_test_bands_table.c \
	modi_test_libcerror.h \
	modi_test_libmodi.h \
	modi_test_macros.h \
	modi_test_memory.c modi_test_memory.h \
	modi_test_unused.h

modi_test_bands_table_LDADD = \
	../libmodi/libmodi.la \
	@LIBCERROR_LIBADD@

modi_test_data_block_SOURCES = \
	modi_test_data_block.c \
	modi_test_libcerror.h \
	modi_test_libmodi.h \
	modi_test_macros.h \
	modi_test_memory.c modi_test_memory.h \
	modi_test_unused.h

modi_test_data_block_LDADD = \
	../libmodi/libmodi.la \
	@LIBCERROR_LIBADD@

modi_test_error_SOURCES = \
	modi_test_error.c \
	modi_test_libmodi.h \
	modi_test_macros.h \
	modi_test_unused.h

modi_test_error_LDADD = \
	../libmodi/libmodi.la

modi_test_handle_SOURCES = \
	modi_test_getopt.c modi_test_getopt.h \
	modi_test_handle.c \
	modi_test_libcerror.h \
	modi_test_libclocale.h \
	modi_test_libcnotify.h \
	modi_test_libmodi.h \
	modi_test_libuna.h \
	modi_test_macros.h \
	modi_test_memory.c modi_test_memory.h

modi_test_handle_LDADD = \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libmodi/libmodi.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@PTHREAD_LIBADD@

modi_test_io_handle_SOURCES = \
	modi_test_io_handle.c \
	modi_test_libcerror.h \
	modi_test_libmodi.h \
	modi_test_macros.h \
	modi_test_memory.c modi_test_memory.h \
	modi_test_unused.h

modi_test_io_handle_LDADD = \
	../libmodi/libmodi.la \
	@LIBCERROR_LIBADD@

modi_test_notify_SOURCES = \
	modi_test_libmodi.h \
	modi_test_macros.h \
	modi_test_notify.c \
	modi_test_unused.h

modi_test_notify_LDADD = \
	../libmodi/libmodi.la

modi_test_support_SOURCES = \
	modi_test_getopt.c modi_test_getopt.h \
	modi_test_libbfio.h \
	modi_test_libcerror.h \
	modi_test_libclocale.h \
	modi_test_libcnotify.h \
	modi_test_libmodi.h \
	modi_test_libuna.h \
	modi_test_macros.h \
	modi_test_support.c

modi_test_support_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libmodi/libmodi.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

