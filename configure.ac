AC_PREREQ(2.61)
AC_INIT([bcc], [0.0.1], [leonhad@gmail.com])
AM_INIT_AUTOMAKE()
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CANONICAL_HOST
case $host_os in
 darwin* )
	HOST_LIBRARY="osx"
	;;
 linux* )
	HOST_LIBRARY="linux-$host_cpu"
	;;
 windows* )
	HOST_LIBRARY="windows-$host_cpu"
	;;
 *)
	AC_MSG_ERROR([Your platform is not currently  supported])
	;;
esac
AC_SUBST([HOST_LIBRARY])

# Checks for programs.
DEBUG_CFLAGS="-O2 -DNDEBUG"
dnl This mechanism allows one to enable debug compilations...
AC_ARG_ENABLE(debug,
[  --enable-debug     enable debugging and disable optimization],
[  if test "$enable_debug" = "yes"; then
      DEBUG_CFLAGS="-Wall -g3 -DDEBUG"
   fi
]
)
AM_CONDITIONAL(ENABLE_DEBUG, test "$enable_debug" = "yes")
CXXFLAGS="$DEBUG_CFLAGS $CXXFLAGS"

AC_LANG([C++])
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL
AM_PROG_AS
AC_PROG_LN_S

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 bcc/Makefile
                 libbasic/Makefile
                 libbasic/ARM/Makefile
                 libbasic/x86-64/Makefile
])
AC_OUTPUT
