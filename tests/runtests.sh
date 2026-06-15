#!/bin/sh
# Script to run tests
#
# Version: 20260609

if test -f ${PWD}/libmodi/.libs/libmodi.1.dylib && test -f ./pymodi/.libs/pymodi.so
then
	install_name_tool -change /usr/local/lib/libmodi.1.dylib ${PWD}/libmodi/.libs/libmodi.1.dylib ./pymodi/.libs/pymodi.so
fi

make check-build > /dev/null

make check $@
RESULT=$?

if test ${RESULT} -ne 0
then
	find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

