AUTOMAKE_OPTIONS = subdir-objects

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
	@LIBCRYPTO_CPPFLAGS@ \
	@LIBHMAC_CPPFLAGS@ \
	@LIBCAES_CPPFLAGS@ \
	@ZLIB_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBMODI_DLL_IMPORT@

if HAVE_PYTHON_TESTS
TESTS_PYMODI = \
	test_python_module.sh
endif

TESTS = \
	test_library.sh \
	test_tools.sh \
	test_modiinfo.sh \
	$(TESTS_PYMODI)

check_SCRIPTS = \
	pymodi_test_handle.py \
	pymodi_test_support.py \
	test_library.sh \
	test_manpage.sh \
	test_modiinfo.sh \
	test_python_module.sh \
	test_runner.sh \
	test_tools.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	modi_test_bands_data_handle \
	modi_test_data_block \
	modi_test_deflate \
	modi_test_error \
	modi_test_handle \
	modi_test_io_handle \
	modi_test_notify \
	modi_test_sparse_bundle_xml_plist \
	modi_test_sparse_image_header \
	modi_test_support \
	modi_test_system_string \
	modi_test_tools_info_handle \
	modi_test_tools_output \
	modi_test_tools_signal \
	modi_test_udif_block_table \
	modi_test_udif_block_table_entry \
	modi_test_udif_resource_file \
	modi_test_udif_xml_plist

modi_test_bands_data_handle_SOURCES = \
	modi_test_bands_data_handle.c \
	modi_test_libcerror.h \
	modi_test_libmodi.h \
	modi_test_macros.h \
	modi_test_memory.c modi_test_memory.h \
	modi_test_unused.h

modi_test_bands_data_handle_LDADD = \
	../libmodi/libmodi.la \
	@LIBCERROR_LIBADD@

modi_test_data_block_SOURCES = \
	modi_test_data_block.c \
	modi_test_functions.c modi_test_functions.h \
	modi_test_libbfio.h \
	modi_test_libcerror.h \
	modi_test_libmodi.h \
	modi_test_macros.h \
	modi_test_memory.c modi_test_memory.h \
	modi_test_unused.h

modi_test_data_block_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libmodi/libmodi.la \
	@LIBCERROR_LIBADD@

modi_test_deflate_SOURCES = \
	modi_test_deflate.c \
	modi_test_libcerror.h \
	modi_test_libcnotify.h \
	modi_test_libmodi.h \
	modi_test_macros.h \
	modi_test_unused.h

modi_test_deflate_LDADD = \
	@LIBCNOTIFY_LIBADD@ \
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
	modi_test_functions.c modi_test_functions.h \
	modi_test_getopt.c modi_test_getopt.h \
	modi_test_handle.c \
	modi_test_libbfio.h \
	modi_test_libcdirectory.h \
	modi_test_libcerror.h \
	modi_test_libclocale.h \
	modi_test_libcnotify.h \
	modi_test_libcpath.h \
	modi_test_libmodi.h \
	modi_test_libuna.h \
	modi_test_macros.h \
	modi_test_memory.c modi_test_memory.h \
	modi_test_unused.h

modi_test_handle_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCDIRECTORY_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
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
	modi_test_libcerror.h \
	modi_test_libmodi.h \
	modi_test_macros.h \
	modi_test_notify.c \
	modi_test_unused.h

modi_test_notify_LDADD = \
	../libmodi/libmodi.la \
	@LIBCERROR_LIBADD@

modi_test_sparse_bundle_xml_plist_SOURCES = \
	modi_test_functions.c modi_test_functions.h \
	modi_test_libbfio.h \
	modi_test_libcerror.h \
	modi_test_libmodi.h \
	modi_test_macros.h \
	modi_test_memory.c modi_test_memory.h \
	modi_test_sparse_bundle_xml_plist.c \
	modi_test_unused.h

modi_test_sparse_bundle_xml_plist_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libmodi/libmodi.la \
	@LIBCERROR_LIBADD@

modi_test_sparse_image_header_SOURCES = \
	modi_test_functions.c modi_test_functions.h \
	modi_test_libbfio.h \
	modi_test_libcerror.h \
	modi_test_libmodi.h \
	modi_test_macros.h \
	modi_test_memory.c modi_test_memory.h \
	modi_test_sparse_image_header.c \
	modi_test_unused.h

modi_test_sparse_image_header_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libmodi/libmodi.la \
	@LIBCERROR_LIBADD@

modi_test_support_SOURCES = \
	modi_test_functions.c modi_test_functions.h \
	modi_test_getopt.c modi_test_getopt.h \
	modi_test_libbfio.h \
	modi_test_libcdirectory.h \
	modi_test_libcerror.h \
	modi_test_libclocale.h \
	modi_test_libcnotify.h \
	modi_test_libcpath.h \
	modi_test_libmodi.h \
	modi_test_libuna.h \
	modi_test_macros.h \
	modi_test_memory.c modi_test_memory.h \
	modi_test_support.c \
	modi_test_unused.h

modi_test_support_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCDIRECTORY_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libmodi/libmodi.la \
	@LIBCERROR_LIBADD@

modi_test_system_string_SOURCES = \
	modi_test_libcerror.h \
	modi_test_libmodi.h \
	modi_test_macros.h \
	modi_test_system_string.c \
	modi_test_unused.h

modi_test_system_string_LDADD = \
	../libmodi/libmodi.la \
	@LIBCERROR_LIBADD@

modi_test_tools_info_handle_SOURCES = \
	../moditools/byte_size_string.c ../moditools/byte_size_string.h \
	../moditools/info_handle.c ../moditools/info_handle.h \
	modi_test_libcerror.h \
	modi_test_macros.h \
	modi_test_memory.c modi_test_memory.h \
	modi_test_tools_info_handle.c \
	modi_test_unused.h

modi_test_tools_info_handle_LDADD = \
	@LIBCLOCALE_LIBADD@ \
	../libmodi/libmodi.la \
	@LIBCERROR_LIBADD@

modi_test_tools_output_SOURCES = \
	../moditools/moditools_output.c ../moditools/moditools_output.h \
	modi_test_libcerror.h \
	modi_test_macros.h \
	modi_test_tools_output.c \
	modi_test_unused.h

modi_test_tools_output_LDADD = \
	../libmodi/libmodi.la \
	@LIBCERROR_LIBADD@

modi_test_tools_signal_SOURCES = \
	../moditools/moditools_signal.c ../moditools/moditools_signal.h \
	modi_test_libcerror.h \
	modi_test_macros.h \
	modi_test_tools_signal.c \
	modi_test_unused.h

modi_test_tools_signal_LDADD = \
	../libmodi/libmodi.la \
	@LIBCERROR_LIBADD@

modi_test_udif_block_table_SOURCES = \
	modi_test_libcerror.h \
	modi_test_libmodi.h \
	modi_test_macros.h \
	modi_test_memory.c modi_test_memory.h \
	modi_test_unused.h \
	modi_test_udif_block_table.c

modi_test_udif_block_table_LDADD = \
	../libmodi/libmodi.la \
	@LIBCERROR_LIBADD@

modi_test_udif_block_table_entry_SOURCES = \
	modi_test_libcerror.h \
	modi_test_libmodi.h \
	modi_test_macros.h \
	modi_test_memory.c modi_test_memory.h \
	modi_test_unused.h \
	modi_test_udif_block_table_entry.c

modi_test_udif_block_table_entry_LDADD = \
	../libmodi/libmodi.la \
	@LIBCERROR_LIBADD@

modi_test_udif_resource_file_SOURCES = \
	modi_test_functions.c modi_test_functions.h \
	modi_test_libbfio.h \
	modi_test_libcerror.h \
	modi_test_libmodi.h \
	modi_test_macros.h \
	modi_test_memory.c modi_test_memory.h \
	modi_test_unused.h \
	modi_test_udif_resource_file.c

modi_test_udif_resource_file_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libmodi/libmodi.la \
	@LIBCERROR_LIBADD@

modi_test_udif_xml_plist_SOURCES = \
	modi_test_functions.c modi_test_functions.h \
	modi_test_libbfio.h \
	modi_test_libcerror.h \
	modi_test_libmodi.h \
	modi_test_macros.h \
	modi_test_memory.c modi_test_memory.h \
	modi_test_unused.h \
	modi_test_udif_xml_plist.c

modi_test_udif_xml_plist_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libmodi/libmodi.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

