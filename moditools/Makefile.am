AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
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
	@LIBCSYSTEM_CPPFLAGS@ \
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
	modioutput.c modioutput.h \
	moditools_libbfio.h \
	moditools_libcdata.h \
	moditools_libcerror.h \
	moditools_libclocale.h \
	moditools_libcnotify.h \
	moditools_libcstring.h \
	moditools_libcsystem.h \
	moditools_libmodi.h \
	moditools_libuna.h

modiinfo_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	../libmodi/libmodi.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@LIBINTL@

modimount_SOURCES = \
	mount_handle.c mount_handle.h \
	modimount.c \
	modioutput.c modioutput.h \
	moditools_libbfio.h \
	moditools_libcdata.h \
	moditools_libcerror.h \
	moditools_libclocale.h \
	moditools_libcnotify.h \
	moditools_libcpath.h \
	moditools_libcstring.h \
	moditools_libcsystem.h \
	moditools_libmodi.h \
	moditools_libuna.h

modimount_LDADD = \
	@LIBFUSE_LIBADD@ \
	@LIBCSYSTEM_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	../libmodi/libmodi.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
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

