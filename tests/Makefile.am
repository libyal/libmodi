AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
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
	@LIBFMOS_CPPFLAGS@ \
	@LIBFPLIST_CPPFLAGS@ \
	@LIBCRYPTO_CPPFLAGS@ \
	@LIBHMAC_CPPFLAGS@ \
	@LIBCAES_CPPFLAGS@ \
	@ZLIB_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBMODI_DLL_IMPORT@

BUILT_SOURCES = package.m4

check_AUTOTESTS = \
	test_library \
	test_manpages \
	test_tools

if HAVE_PYTHON_TESTS
check_AUTOTESTS += test_python_module
endif

check_SCRIPTS = \
	pymodi_test_handle.py \
	pymodi_test_support.py

check_PROGRAMS = \
	modi_test_bands_data_handle \
	modi_test_bit_stream \
	modi_test_bzip \
	modi_test_data_block \
	modi_test_deflate \
	modi_test_error \
	modi_test_handle \
	modi_test_huffman_tree \
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

modi_test_bit_stream_SOURCES = \
	modi_test_bit_stream.c \
	modi_test_libcerror.h \
	modi_test_libmodi.h \
	modi_test_macros.h \
	modi_test_memory.c modi_test_memory.h \
	modi_test_unused.h

modi_test_bit_stream_LDADD = \
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

modi_test_bzip_SOURCES = \
	modi_test_bzip.c \
	modi_test_libcerror.h \
	modi_test_libcnotify.h \
	modi_test_libmodi.h \
	modi_test_macros.h \
	modi_test_unused.h

modi_test_bzip_LDADD = \
	@LIBCNOTIFY_LIBADD@ \
	../libmodi/libmodi.la \
	@LIBCERROR_LIBADD@

modi_test_deflate_SOURCES = \
	modi_test_deflate.c \
	modi_test_libcerror.h \
	modi_test_libcnotify.h \
	modi_test_libmodi.h \
	modi_test_macros.h \
	modi_test_memory.c modi_test_memory.h \
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

modi_test_huffman_tree_SOURCES = \
	modi_test_huffman_tree.c \
	modi_test_libcerror.h \
	modi_test_libmodi.h \
	modi_test_macros.h \
	modi_test_memory.c modi_test_memory.h \
	modi_test_unused.h

modi_test_huffman_tree_LDADD = \
	../libmodi/libmodi.la \
	@LIBCERROR_LIBADD@

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
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

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

AUTOM4TE = autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest

SUFFIXES = .at

.at:
	$(AM_V_GEN)rm -f $@ $@.tmp; \
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $< && \
	mv $@.tmp $@

atconfig: $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status tests/$@

check-build: $(check_PROGRAMS)

check-local: $(check_AUTOTESTS)
	@fail=0; \
	for test_suite in $(check_AUTOTESTS); do \
		$(AM_TESTS_ENVIRONMENT) $(SHELL) "./$$test_suite" $(TESTSUITEFLAGS) || fail=1; \
		echo ""; \
	done; \
	exit $$fail

clean-local:
	for test_suite in $(check_AUTOTESTS); do \
		test ! -f "$$test_suite" || $(SHELL) "./$$test_suite" --clean; \
	done

package.m4: $(top_srcdir)/configure.ac
	$(AM_V_GEN):; \
	{ \
	  echo 'm4_define([AT_PACKAGE_NAME], [$(PACKAGE_NAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_TARNAME], [$(PACKAGE_TARNAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_VERSION], [$(PACKAGE_VERSION)])' ; \
	  echo 'm4_define([AT_PACKAGE_STRING], [$(PACKAGE_STRING)])' ; \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT], [$(PACKAGE_BUGREPORT)])' ; \
	} > $@

test_inputs_libmodi.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) libmodi

test_inputs_pymodi.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) pymodi

test_inputs_modiinfo.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) modiinfo

test_library: \
	package.m4 \
	test_inputs_libmodi.at \
	test_library.at \
	test_macros.at

test_manpages: \
	package.m4 \
	test_manpages.at

test_python_module: \
	package.m4 \
	test_inputs_pymodi.at \
	test_python_module.at

test_tools: \
	package.m4 \
	test_inputs_modiinfo.at \
	test_macros.at \
	test_tools.at

EXTRA_DIST = \
	$(check_AUTOTESTS:=.at) \
	$(check_SCRIPTS) \
	generate_test_inputs.sh \
	package.m4 \
	test_macros.at

CLEANFILES = \
	$(check_AUTOTESTS) \
	*.exe \
	*.tmp \
	notify_stream.log \
	test_inputs_*.at

DISTCLEANFILES = \
	*.log \
	atconfig \
	Makefile \
	Makefile.in

