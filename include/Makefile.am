include_HEADERS = \
	libmodi.h

pkginclude_HEADERS = \
	libmodi/codepage.h \
	libmodi/definitions.h \
	libmodi/error.h \
	libmodi/extern.h \
	libmodi/features.h \
	libmodi/types.h

EXTRA_DIST = \
	libmodi.h.in \
	libmodi/definitions.h.in \
	libmodi/features.h.in \
	libmodi/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libmodi.h
	-rm -f libmodi/definitions.h
	-rm -f libmodi/features.h
	-rm -f libmodi/types.h
	-rm -f Makefile

