AM_CPPFLAGS = \
	-DLOCALEDIR=\"$(datadir)/locale\" \
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
	@BZIP2_CPPFLAGS@ \
	@LZMA_CPPFLAGS@ \
	@ZLIB_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBMODI_DLL_EXPORT@

lib_LTLIBRARIES = libmodi.la

libmodi_la_SOURCES = \
	libmodi.c \
	libmodi_adc.c libmodi_adc.h \
	libmodi_bands_data_handle.c libmodi_bands_data_handle.h \
	libmodi_block_chunks_data_handle.c libmodi_block_chunks_data_handle.h \
	libmodi_codepage.h \
	libmodi_compression.c libmodi_compression.h \
	libmodi_data_block.c libmodi_data_block.h \
	libmodi_deflate.c libmodi_deflate.h \
	libmodi_debug.c libmodi_debug.h \
	libmodi_definitions.h \
	libmodi_error.c libmodi_error.h \
	libmodi_extern.h \
	libmodi_handle.c libmodi_handle.h \
	libmodi_i18n.c libmodi_i18n.h \
	libmodi_io_handle.c libmodi_io_handle.h \
	libmodi_libbfio.h \
	libmodi_libcdata.h \
	libmodi_libcdirectory.h \
	libmodi_libcerror.h \
	libmodi_libcfile.h \
	libmodi_libclocale.h \
	libmodi_libcnotify.h \
	libmodi_libcpath.h \
	libmodi_libcthreads.h \
	libmodi_libfcache.h \
	libmodi_libfdata.h \
	libmodi_libfplist.h \
	libmodi_libfvalue.h \
	libmodi_libuna.h \
	libmodi_notify.c libmodi_notify.h \
	libmodi_sparse_bundle_xml_plist.c libmodi_sparse_bundle_xml_plist.h \
	libmodi_sparse_image_header.c libmodi_sparse_image_header.h \
	libmodi_support.c libmodi_support.h \
	libmodi_system_string.c libmodi_system_string.h \
	libmodi_types.h \
	libmodi_udif_block_table.c libmodi_udif_block_table.h \
	libmodi_udif_block_table_entry.c libmodi_udif_block_table_entry.h \
	libmodi_udif_resource_file.c libmodi_udif_resource_file.h \
	libmodi_udif_xml_plist.c libmodi_udif_xml_plist.h \
	libmodi_unused.h \
	modi_sparse_image_header.h \
	modi_udif_block_table.h \
	modi_udif_resource_file.h

libmodi_la_LIBADD = \
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
	@LIBFGUID_LIBADD@ \
	@LIBFVALUE_LIBADD@ \
	@LIBFPLIST_LIBADD@ \
	@LIBHMAC_LIBADD@ \
	@LIBCAES_LIBADD@ \
	@LIBCRYPTO_LIBADD@ \
	@BZIP2_LIBADD@ \
	@LZMA_LIBADD@ \
	@ZLIB_LIBADD@ \
	@LIBDL_LIBADD@ \
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

