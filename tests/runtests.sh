#!/bin/sh
# Script to run tests
#
# Version: 20260714

if [ -f "${PWD}/libmodi/.libs/libmodi.1.dylib" ] && [ -f ./pymodi/.libs/pymodi.so ]
then
    install_name_tool -change /usr/local/lib/libmodi.1.dylib "${PWD}/libmodi/.libs/libmodi.1.dylib" ./pymodi/.libs/pymodi.so
fi

make check-build > /dev/null

# shellcheck disable=SC2068
make check $@
RESULT=$?

if [ ${RESULT} -ne 0 ]
then
    find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

