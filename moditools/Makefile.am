AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFCACHE_CPPFLAGS@ \
	@LIBFDATA_CPPFLAGS@ \
	@LIBFUSE_CPPFLAGS@ \
	@LIBMODI_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	modiinfo \
	modimount

modiinfo_SOURCES = \
	byte_size_string.c byte_size_string.h \
	info_handle.c info_handle.h \
	modiinfo.c \
	moditools_getopt.c moditools_getopt.h \
	moditools_i18n.h \
	moditools_libbfio.h \
	moditools_libcdata.h \
	moditools_libcerror.h \
	moditools_libclocale.h \
	moditools_libcnotify.h \
	moditools_libmodi.h \
	moditools_libuna.h \
	moditools_output.c moditools_output.h \
	moditools_signal.c moditools_signal.h \
	moditools_unused.h

modiinfo_LDADD = \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libmodi/libmodi.la \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

modimount_SOURCES = \
	modimount.c \
	moditools_getopt.c moditools_getopt.h \
	moditools_i18n.h \
	moditools_libbfio.h \
	moditools_libcdata.h \
	moditools_libcerror.h \
	moditools_libclocale.h \
	moditools_libcnotify.h \
	moditools_libcpath.h \
	moditools_libmodi.h \
	moditools_libuna.h \
	moditools_output.c moditools_output.h \
	moditools_signal.c moditools_signal.h \
	moditools_unused.h \
	mount_dokan.c mount_dokan.h \
	mount_file_entry.c mount_file_entry.h \
	mount_file_system.c mount_file_system.h \
	mount_fuse.c mount_fuse.h \
	mount_handle.c mount_handle.h

modimount_LDADD = \
	@LIBFUSE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libmodi/libmodi.la \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on modiinfo ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(modiinfo_SOURCES)
	@echo "Running splint on modimount ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(modimount_SOURCES)

