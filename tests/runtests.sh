#!/bin/sh
# Script to run tests
#
# Version: 20260602

if test -f ${PWD}/libmodi/.libs/libmodi.1.dylib && test -f ./pymodi/.libs/pymodi.so
then
	install_name_tool -change /usr/local/lib/libmodi.1.dylib ${PWD}/libmodi/.libs/libmodi.1.dylib ./pymodi/.libs/pymodi.so
fi

make check $@
RESULT=$?

if test ${RESULT} -ne 0 && test -f tests/test-suite.log
then
	cat tests/test-suite.log
fi
exit ${RESULT}

