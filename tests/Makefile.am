
AUTOMAKE_OPTIONS = -Wno-portability subdir-objects
ACLOCAL_AMFLAGS = -I build-aux/m4

AM_DEFAULT_SOURCE_EXT = .cc
BUILT_SOURCES =
CLEANFILES = $(EXTRA_PROGRAMS)
EXTRA_DIST = $(dist_TESTS)
MAINTAINERCLEANFILES =
TESTS = $(check_PROGRAMS) $(dist_TESTS)
check_PROGRAMS =
dist_TESTS =
dist_noinst_DATA =
# RECHECK_LOGS =

SUBDIRS = .

AM_CPPFLAGS = -I$(top_srcdir)/lib -I$(top_srcdir)/src -I$(top_builddir)/src
AM_CPPFLAGS += $(BOOST_CPPFLAGS)

AM_CPPFLAGS += -DPKGDATADIR="\"$(pkgdatadir)\""
AM_CXXFLAGS = $(WARNING_CXXFLAGS) 

AM_CPPFLAGS += -I$(top_builddir)

EXTRA_DIST += AUTHORS.txt
BUILT_SOURCES += authors.h
CLEANFILES += authors.h
AUTHORS_H_GEN = $(srcdir)/build-aux/bin/authors.h-gen
EXTRA_DIST += AUTHORS.txt $(AUTHORS_H_GEN)
authors.h: AUTHORS.txt $(AUTHORS_H_GEN)
	$(AM_V_GEN)$(AUTHORS_H_GEN) $< >$@.tmp 	
	$(AM_V_at)$(top_srcdir)/build-aux/bin/move-if-change $@.tmp $@
