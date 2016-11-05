AM_CPPFLAGS = \
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
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBCSYSTEM_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBMODI_DLL_IMPORT@

if HAVE_PYTHON_TESTS
TESTS_PYMODI =
endif

TESTS = \
	test_api_functions.sh \
	test_api_types.sh \
	$(TESTS_PYMODI)

check_SCRIPTS = \
	test_api_functions.sh \
	test_api_types.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	modi_test_error \
	modi_test_handle \
	modi_test_notify \
	modi_test_support

modi_test_error_SOURCES = \
	modi_test_error.c \
	modi_test_libcstring.h \
	modi_test_libmodi.h \
	modi_test_macros.h \
	modi_test_unused.h

modi_test_error_LDADD = \
	../libmodi/libmodi.la \
	@LIBCSTRING_LIBADD@

modi_test_handle_SOURCES = \
	modi_test_handle.c \
	modi_test_libcerror.h \
	modi_test_libclocale.h \
	modi_test_libcstring.h \
	modi_test_libcsystem.h \
	modi_test_libmodi.h \
	modi_test_libuna.h \
	modi_test_macros.h \
	modi_test_memory.c modi_test_memory.h \
	modi_test_unused.h

modi_test_handle_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libmodi/libmodi.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

modi_test_notify_SOURCES = \
	modi_test_libcstring.h \
	modi_test_libmodi.h \
	modi_test_macros.h \
	modi_test_notify.c \
	modi_test_unused.h

modi_test_notify_LDADD = \
	../libmodi/libmodi.la \
	@LIBCSTRING_LIBADD@

modi_test_support_SOURCES = \
	modi_test_libcerror.h \
	modi_test_libclocale.h \
	modi_test_libcstring.h \
	modi_test_libcsystem.h \
	modi_test_libmodi.h \
	modi_test_libuna.h \
	modi_test_macros.h \
	modi_test_support.c \
	modi_test_unused.h

modi_test_support_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libmodi/libmodi.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

