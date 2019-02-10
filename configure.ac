
m4_pattern_forbid([^(AM|AX|LT|TC)_])

m4_define([TC_CLANG_PREREQ],    [4.0])
m4_define([TC_GCC_PREREQ],      [8.1])
m4_define([TC_HAVM_PREREQ],     [0.27])
m4_define([TC_NOLIMIPS_PREREQ], [0.10])

AC_PREREQ([2.64])

AC_INIT([Tiger Compiler], [1.0], [tc])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([build-aux/m4])
AM_INIT_AUTOMAKE([dist-bzip2 no-dist-gzip foreign
                  color-tests parallel-tests
                  nostdinc silent-rules -Wall -Werror])

AC_LANG([C++])
AC_PROG_CXX

TC_CXX_WARNINGS([[-Wall],
                [-W],
                [-Wcast-align],
                [-Wcast-qual],
                [-Wformat],
                [-Wmissing-prototypes],
                [-Wstrict-prototypes],
                [-Wwrite-strings],
                [-Wbad-function-cast],
                [-Wmissing-declarations],
                [-Wnested-externs],
                [-Wunused-parameter],
                [-Wunused-function],
                [-Woverloaded-virtual],
                ])
TC_CXX_WARNINGS([[[-wd111,193,279,383,444,522,654,810,981,1418]]])
TC_CXX_FLAGS([[-Wno-strict-aliasing]], [NO_STRICT_ALIASING_CXXFLAGS])

TC_PROG([flex], [>= 2.5.35], [FLEX], [Flex scanner generator])
AX_CONFIG_SCRIPTS([build-aux/bin/flex++])
FLEX_VERSION TC_PROG([bison], [>= 3.0], [BISON], [Bison parser generator])
AX_CONFIG_SCRIPTS([build-aux/bin/bison++])

AM_CONDITIONAL([IA32_GNU_LINUX],
               [echo "$host" | grep -q '^\(i.86\|x86_64\).*linux'])
AM_CONDITIONAL([IA32_FREEBSD],
               [echo "$host" | grep -q '^\(i.86\|amd64\).*freebsd'])
AM_CONDITIONAL([SUPPORTED_IA32],
               [echo "$host" | grep -q '^\(i.86\|x86_64\).*linux\|^\(i.86\|amd64\).*freebsd'])

BOOST_REQUIRE([1.61])
BOOST_CONVERSION
BOOST_GRAPH
BOOST_PROGRAM_OPTIONS
BOOST_STRING_ALGO
BOOST_SYSTEM

AM_CONDITIONAL([DARWIN], [echo "$host_os" | grep -q '^darwin'])
TC_WITH_TCSH([with_tcsh=yes], [with_tcsh=no])
AM_CONDITIONAL([ENABLE_TCSH], [test x$with_tcsh = xyes])
#AC_CONFIG_FILES([tcsh/Makefile])
#AC_CONFIG_FILES([doc/Doxyfile])
#AX_CONFIG_SCRIPTS([tcsh/run])

AC_CONFIG_FILES([tests/Makefile])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])

AC_OUTPUT
