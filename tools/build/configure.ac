# Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved

AC_INIT([visum],[DEV-VERSION],[mokon@mokon.net],[visum], [http://mokon.net])

AC_ARG_ENABLE([debug],
  [  --enable-debug    Turn on feature DEBUG.],
  [case "${enableval}" in
    yes) $debug=true ;;
    no)  $debug=false ;;
    *) AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
  esac],[$debug=true])
AM_CONDITIONAL([DEBUG], [test x$debug = xtrue])
if test x$debug = xtrue ; then
  AC_MSG_NOTICE([Defining $debug])
  AC_DEFINE([DEBUG], [1], [Include the DEBUG. ])
fi

AC_DEFUN([M_CHECK_LIB],
[
  AC_CHECK_LIB([$1],[main],
    [$2_LDADD="$$2_LDADD -l$1"          
      AC_DEFINE([HAVE_LIB$1], [1], [Define if you have lib$1])],
    [AC_MSG_WARN([$1 library not found $2_LDADD ${2}_LDADD])],
    [$3])
])

AC_DEFUN([M_PROG_DEP],[
  M_CHECK_LIB([$1],m4_defn([prog]),[$2])])
AC_DEFUN([M_PROG_DEPS],
[
  define([prog],[$1])
  m4_map([M_PROG_DEP],[$2])
  AC_SUBST([$1_LDADD])
])

if test x$debug = xfalse ; then
AC_DEFINE([GOOGLE_STRIP_LOG], [1], [Strip Logging Messages from Release.])
fi

AM_INIT_AUTOMAKE([-Wall foreign])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AM_PROG_AR
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_USE_SYSTEM_EXTENSIONS
AC_PROG_LIBTOOL

AC_CONFIG_FILES([
  Makefile
])

AC_LANG([C++])
: ${CXXFLAGS=""}
AC_PROG_CXX ([clang++])

AC_REVISION([$Revision: 0.0 $])
AC_COPYRIGHT([Copyright (C) David 'Mokon' Bond 2013-2016])
AC_DEFINE([PACKAGE_COPYRIGHT],
          ["Copyright (C) David 'Mokon' Bond 2013-2016, All Rights Reserved"],
          [Copyright string for the package])

M_PROG_DEPS([visum_server],[
             [[boost_system],[]],
             [[boost_thread],[]],
             [[boost_program_options],[]],
             [[boost_filesystem],[]],
             [[boost_date_time],[]],
             [[glog],[]],
             [[fcgi],[]],
             [["fcgi++"],[]],
             [[jsoncpp],[]],
             [[pthread],[]],
             [[pugixml],[]],
             ])

M_PROG_DEPS([visum_script],[
             [[boost_system],[]],
             [[boost_thread],[]],
             [[boost_program_options],[]],
             [[boost_filesystem],[]],
             [[boost_date_time],[]],
             [[glog],[]],
             [[fcgi],[]],
             [["fcgi++"],[]],
             [[jsoncpp],[]],
             [[pthread],[]],
             [[pugixml],[]],
             ])

M_PROG_DEPS([visum_test],[
             [[boost_system],[]],
             [[boost_thread],[]],
             [[boost_program_options],[]],
             [[boost_filesystem],[]],
             [[boost_date_time],[]],
             [[glog],[]],
             [[gtest],[]],
             [[fcgi],[]],
             [["fcgi++"],[]],
             [[jsoncpp],[]],
             [[pthread],[]],
             [[pugixml],[]],
             ])

AC_OUTPUT
