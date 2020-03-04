AC_INIT(

  [Euler],
  [0.1],
  [craig.sanders@gravitas-toolworks.com])

AM_INIT_AUTOMAKE()

LT_INIT()

AC_PROG_CXX()

AC_CONFIG_HEADERS([config.h])

# ACLOCAL_PATH([/home/craig/local/source/c++/e])

AC_CONFIG_MACRO_DIR([m4])

AX_BOOST_BASE(

  1.68,
  [],
  [AC_MSG_ERROR(could not find an installation of the Boost Library whose version number is >= 1.68)])

AX_PATH_GSL(

  2.6,
  [],
  [AC_MSG_ERROR(could not find an installation of the GNU Scientific Library (GSL) whose version number is >= 2.6)])

AC_LANG_CPLUSPLUS

AC_CONFIG_FILES(

  [Makefile \
   src/Makefile])

AC_OUTPUT
