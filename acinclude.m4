dnl Function to detect if libmodi dependencies are available
AC_DEFUN([AX_LIBMODI_CHECK_LOCAL],
 [dnl Check for internationalization functions in libmodi/libmodi_i18n.c 
 AC_CHECK_FUNCS([bindtextdomain])
 ])

