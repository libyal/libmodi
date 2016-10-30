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
	/bin/rm -f libmodi.h
	/bin/rm -f libmodi/definitions.h
	/bin/rm -f libmodi/features.h
	/bin/rm -f libmodi/types.h
	/bin/rm -f Makefile

