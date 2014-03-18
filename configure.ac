#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([kbdencode], [1.0], [matthew@komputerwiz.net])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
if test -z $CXXFLAGS; then
    CXXFLAGS='-O2'
fi
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_11

# Checks for libraries.
AX_BOOST_PROGRAM_OPTIONS

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
