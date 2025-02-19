# Makefile.in generated automatically by automake 1.4-p6 from Makefile.am

# Copyright (C) 1994, 1995-8, 1999, 2001 Free Software Foundation, Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.


SHELL = /bin/bash

srcdir = .
top_srcdir = ..

prefix = /usr/local
exec_prefix = ${prefix}

bindir = ${exec_prefix}/bin
sbindir = ${exec_prefix}/sbin
libexecdir = ${exec_prefix}/libexec
datadir = ${prefix}/share
sysconfdir = ${prefix}/etc
sharedstatedir = ${prefix}/com
localstatedir = ${prefix}/var
libdir = ${exec_prefix}/lib
infodir = ${prefix}/info
mandir = ${prefix}/man
includedir = ${prefix}/include
oldincludedir = /usr/include

DESTDIR =

pkgdatadir = $(datadir)/Mowitz
pkglibdir = $(libdir)/Mowitz
pkgincludedir = $(includedir)/Mowitz

top_builddir = ..

ACLOCAL = /media/dimmus/dev/c/app/Mowitz-0.3.1/missing aclocal-1.4
AUTOCONF = /media/dimmus/dev/c/app/Mowitz-0.3.1/missing autoconf
AUTOMAKE = /media/dimmus/dev/c/app/Mowitz-0.3.1/missing automake-1.4
AUTOHEADER = /media/dimmus/dev/c/app/Mowitz-0.3.1/missing autoheader

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL} $(AM_INSTALL_PROGRAM_FLAGS)
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_SCRIPT = ${INSTALL}
transform = s,x,x,

NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
host_alias = 
host_triplet = x86_64-unknown-linux-gnu
AR = ar
AS = @AS@
AWK = mawk
CC = gcc
CFLAGS_CFG = -DNARROWPROTO=1 
CXX = g++
CXXCPP = g++ -E
DLLTOOL = @DLLTOOL@
ECHO = echo
EGREP = grep -E
EXEEXT = 
F77 = 
GCJ = @GCJ@
GCJFLAGS = @GCJFLAGS@
HAVE_LIB = @HAVE_LIB@
LDFLAGS_CFG = 
LIB = @LIB@
LIBTOOL = $(SHELL) $(top_builddir)/libtool
LN_S = ln -s
LTLIB = @LTLIB@
MAKEINFO = /media/dimmus/dev/c/app/Mowitz-0.3.1/missing makeinfo
OBJDUMP = @OBJDUMP@
OBJEXT = o
PACKAGE = Mowitz
RANLIB = ranlib
RC = @RC@
STRIP = strip
VERSION = 0.3.1

INCLUDES = -I.. -DNeedFunctionPrototypes -DUSE_XPM $(X_CFLAGS)

#LDADD = ../Mowitz/.libs/libMowitz.a $(X_LIBS) $(X_PRE_LIBS) $(X_EXTRA_LIBS)
LDADD = -L../Mowitz/ -lMowitz $(X_LIBS) $(X_PRE_LIBS) $(X_EXTRA_LIBS)

noinst_PROGRAMS = allwidgets listtree listtree2 rulerdemo

allwidgets_SOURCES = allwidgets.c
# html_SOURCES = html.c
listtree_SOURCES = listtree.c
listtree2_SOURCES = listtree2.c TreeFSel.c TreeFSel.h TreeFSelP.h Directory.c Directory.h
rulerdemo_SOURCES = rulerdemo.c
mkinstalldirs = $(SHELL) $(top_srcdir)/mkinstalldirs
CONFIG_CLEAN_FILES = 
noinst_PROGRAMS =  allwidgets$(EXEEXT) listtree$(EXEEXT) \
listtree2$(EXEEXT) rulerdemo$(EXEEXT)
PROGRAMS =  $(noinst_PROGRAMS)


DEFS = -DPACKAGE_NAME=\"\" -DPACKAGE_TARNAME=\"\" -DPACKAGE_VERSION=\"\" -DPACKAGE_STRING=\"\" -DPACKAGE_BUGREPORT=\"\" -DPACKAGE=\"Mowitz\" -DVERSION=\"0.3.1\" -DSTDC_HEADERS=1 -DHAVE_SYS_TYPES_H=1 -DHAVE_SYS_STAT_H=1 -DHAVE_STDLIB_H=1 -DHAVE_STRING_H=1 -DHAVE_MEMORY_H=1 -DHAVE_STRINGS_H=1 -DHAVE_INTTYPES_H=1 -DHAVE_STDINT_H=1 -DHAVE_UNISTD_H=1 -DHAVE_DLFCN_H=1 -DHAVE_DIRENT_H=1 -DTIME_WITH_SYS_TIME=1 -DHAVE_LIBM=1 -DHAVE_FNMATCH=1 -DHAVE_XCREATEIC=1  -I. -I$(srcdir) 
CPPFLAGS = 
LDFLAGS = 
LIBS = -lm 
X_CFLAGS = 
X_LIBS = -lneXtaw -lXpm -lXmu -lXext -lXt -lX11 
X_EXTRA_LIBS = 
X_PRE_LIBS =  -lSM -lICE
allwidgets_OBJECTS =  allwidgets.$(OBJEXT)
allwidgets_LDADD = $(LDADD)
allwidgets_DEPENDENCIES = 
allwidgets_LDFLAGS = 
listtree_OBJECTS =  listtree.$(OBJEXT)
listtree_LDADD = $(LDADD)
listtree_DEPENDENCIES = 
listtree_LDFLAGS = 
listtree2_OBJECTS =  listtree2.$(OBJEXT) TreeFSel.$(OBJEXT) \
Directory.$(OBJEXT)
listtree2_LDADD = $(LDADD)
listtree2_DEPENDENCIES = 
listtree2_LDFLAGS = 
rulerdemo_OBJECTS =  rulerdemo.$(OBJEXT)
rulerdemo_LDADD = $(LDADD)
rulerdemo_DEPENDENCIES = 
rulerdemo_LDFLAGS = 
CFLAGS = -DNARROWPROTO=1 -Wall -g -O2
COMPILE = $(CC) $(DEFS) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
LTCOMPILE = $(LIBTOOL) --mode=compile $(CC) $(DEFS) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
CCLD = $(CC)
LINK = $(LIBTOOL) --mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) $(LDFLAGS) -o $@
DIST_COMMON =  Makefile.am Makefile.in


DISTFILES = $(DIST_COMMON) $(SOURCES) $(HEADERS) $(TEXINFOS) $(EXTRA_DIST)

TAR = tar
GZIP_ENV = --best
SOURCES = $(allwidgets_SOURCES) $(listtree_SOURCES) $(listtree2_SOURCES) $(rulerdemo_SOURCES)
OBJECTS = $(allwidgets_OBJECTS) $(listtree_OBJECTS) $(listtree2_OBJECTS) $(rulerdemo_OBJECTS)

all: all-redirect
.SUFFIXES:
.SUFFIXES: .S .c .lo .o .obj .s
$(srcdir)/Makefile.in: Makefile.am $(top_srcdir)/configure.in $(ACLOCAL_M4) 
	cd $(top_srcdir) && $(AUTOMAKE) --gnu --include-deps examples/Makefile

Makefile: $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) \
	  && CONFIG_FILES=$(subdir)/$@ CONFIG_HEADERS= $(SHELL) ./config.status


mostlyclean-noinstPROGRAMS:

clean-noinstPROGRAMS:
	-test -z "$(noinst_PROGRAMS)" || rm -f $(noinst_PROGRAMS)

distclean-noinstPROGRAMS:

maintainer-clean-noinstPROGRAMS:

.c.o:
	$(COMPILE) -c $<

# FIXME: We should only use cygpath when building on Windows,
# and only if it is available.
.c.obj:
	$(COMPILE) -c `cygpath -w $<`

.s.o:
	$(COMPILE) -c $<

.S.o:
	$(COMPILE) -c $<

mostlyclean-compile:
	-rm -f *.o core *.core
	-rm -f *.$(OBJEXT)

clean-compile:

distclean-compile:
	-rm -f *.tab.c

maintainer-clean-compile:

.c.lo:
	$(LIBTOOL) --mode=compile $(COMPILE) -c $<

.s.lo:
	$(LIBTOOL) --mode=compile $(COMPILE) -c $<

.S.lo:
	$(LIBTOOL) --mode=compile $(COMPILE) -c $<

mostlyclean-libtool:
	-rm -f *.lo

clean-libtool:
	-rm -rf .libs _libs

distclean-libtool:

maintainer-clean-libtool:

allwidgets$(EXEEXT): $(allwidgets_OBJECTS) $(allwidgets_DEPENDENCIES)
	@rm -f allwidgets$(EXEEXT)
	$(LINK) $(allwidgets_LDFLAGS) $(allwidgets_OBJECTS) $(allwidgets_LDADD) $(LIBS)

listtree$(EXEEXT): $(listtree_OBJECTS) $(listtree_DEPENDENCIES)
	@rm -f listtree$(EXEEXT)
	$(LINK) $(listtree_LDFLAGS) $(listtree_OBJECTS) $(listtree_LDADD) $(LIBS)

listtree2$(EXEEXT): $(listtree2_OBJECTS) $(listtree2_DEPENDENCIES)
	@rm -f listtree2$(EXEEXT)
	$(LINK) $(listtree2_LDFLAGS) $(listtree2_OBJECTS) $(listtree2_LDADD) $(LIBS)

rulerdemo$(EXEEXT): $(rulerdemo_OBJECTS) $(rulerdemo_DEPENDENCIES)
	@rm -f rulerdemo$(EXEEXT)
	$(LINK) $(rulerdemo_LDFLAGS) $(rulerdemo_OBJECTS) $(rulerdemo_LDADD) $(LIBS)

tags: TAGS

ID: $(HEADERS) $(SOURCES) $(LISP)
	list='$(SOURCES) $(HEADERS)'; \
	unique=`for i in $$list; do echo $$i; done | \
	  awk '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	here=`pwd` && cd $(srcdir) \
	  && mkid -f$$here/ID $$unique $(LISP)

TAGS:  $(HEADERS) $(SOURCES)  $(TAGS_DEPENDENCIES) $(LISP)
	tags=; \
	here=`pwd`; \
	list='$(SOURCES) $(HEADERS)'; \
	unique=`for i in $$list; do echo $$i; done | \
	  awk '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	test -z "$(ETAGS_ARGS)$$unique$(LISP)$$tags" \
	  || (cd $(srcdir) && etags -o $$here/TAGS $(ETAGS_ARGS) $$tags  $$unique $(LISP))

mostlyclean-tags:

clean-tags:

distclean-tags:
	-rm -f TAGS ID

maintainer-clean-tags:

distdir = $(top_builddir)/$(PACKAGE)-$(VERSION)/$(subdir)

subdir = examples

distdir: $(DISTFILES)
	@for file in $(DISTFILES); do \
	  d=$(srcdir); \
	  if test -d $$d/$$file; then \
	    cp -pr $$d/$$file $(distdir)/$$file; \
	  else \
	    test -f $(distdir)/$$file \
	    || ln $$d/$$file $(distdir)/$$file 2> /dev/null \
	    || cp -p $$d/$$file $(distdir)/$$file || :; \
	  fi; \
	done
allwidgets.o: allwidgets.c ../Mowitz/Mowitz.h ../Mowitz/MwUtils.h \
	../Mowitz/MwFormat.h ../Mowitz/MwXutils.h ../Mowitz/MwXFormat.h \
	../Mowitz/MwAnimator.h ../Mowitz/MwAnimatorTypes.h \
	../Mowitz/MwApplicationShell.h ../Mowitz/MwBase.h \
	../Mowitz/MwNws.h ../Mowitz/MwBaseComp.h \
	../Mowitz/MwBaseConst.h ../Mowitz/MwBaseME.h \
	../Mowitz/MwButton.h ../Mowitz/MwSButton.h ../Mowitz/MwBase.h \
	../Mowitz/MwCanvas.h ../Mowitz/MwCheck.h ../Mowitz/MwCheckME.h \
	../Mowitz/MwLabelME.h ../Mowitz/MwBaseME.h ../Mowitz/MwCombo.h \
	../Mowitz/MwCombo.h ../Mowitz/MwDialog.h ../Mowitz/MwDND.h \
	../Mowitz/MwDNDTypes.h ../Mowitz/MwFilesel.h \
	../Mowitz/MwFrame.h ../Mowitz/MwHandle.h ../Mowitz/MwFrame.h \
	../Mowitz/MwImage.h ../Mowitz/MwLabelME.h ../Mowitz/MwLineME.h \
	../Mowitz/MwListTree.h ../Mowitz/MwMBButton.h \
	../Mowitz/MwMenu.h ../Mowitz/MwMenuBar.h ../Mowitz/MwRow.h \
	../Mowitz/MwBaseConst.h ../Mowitz/MwMenuButton.h \
	../Mowitz/MwButton.h ../Mowitz/MwNotebook.h \
	../Mowitz/MwPopText.h ../Mowitz/MwRichtext.h ../Mowitz/MwRow.h \
	../Mowitz/MwRudegrid.h ../Mowitz/MwRuler.h \
	../Mowitz/MwSButton.h ../Mowitz/MwSlider.h \
	../Mowitz/MwSpinner.h ../Mowitz/MwSubME.h ../Mowitz/MwTabbing.h \
	../Mowitz/MwTable.h ../Mowitz/MwTabs.h ../Mowitz/MwTabstop.h \
	../Mowitz/MwTextField.h ../Mowitz/MwTooltip.h \
	../Mowitz/MwTraverse.h ../Mowitz/MwVSlider.h ../Mowitz/MwXCC.h
Directory.o: Directory.c Directory.h
listtree.o: listtree.c ../Mowitz/MwListTree.h
listtree2.o: listtree2.c TreeFSel.h ../Mowitz/MwListTree.h
rulerdemo.o: rulerdemo.c ../Mowitz/Mowitz.h ../Mowitz/MwUtils.h \
	../Mowitz/MwFormat.h ../Mowitz/MwXutils.h ../Mowitz/MwXFormat.h \
	../Mowitz/MwAnimator.h ../Mowitz/MwAnimatorTypes.h \
	../Mowitz/MwApplicationShell.h ../Mowitz/MwBase.h \
	../Mowitz/MwNws.h ../Mowitz/MwBaseComp.h \
	../Mowitz/MwBaseConst.h ../Mowitz/MwBaseME.h \
	../Mowitz/MwButton.h ../Mowitz/MwSButton.h ../Mowitz/MwBase.h \
	../Mowitz/MwCanvas.h ../Mowitz/MwCheck.h ../Mowitz/MwCheckME.h \
	../Mowitz/MwLabelME.h ../Mowitz/MwBaseME.h ../Mowitz/MwCombo.h \
	../Mowitz/MwCombo.h ../Mowitz/MwDialog.h ../Mowitz/MwDND.h \
	../Mowitz/MwDNDTypes.h ../Mowitz/MwFilesel.h \
	../Mowitz/MwFrame.h ../Mowitz/MwHandle.h ../Mowitz/MwFrame.h \
	../Mowitz/MwImage.h ../Mowitz/MwLabelME.h ../Mowitz/MwLineME.h \
	../Mowitz/MwListTree.h ../Mowitz/MwMBButton.h \
	../Mowitz/MwMenu.h ../Mowitz/MwMenuBar.h ../Mowitz/MwRow.h \
	../Mowitz/MwBaseConst.h ../Mowitz/MwMenuButton.h \
	../Mowitz/MwButton.h ../Mowitz/MwNotebook.h \
	../Mowitz/MwPopText.h ../Mowitz/MwRichtext.h ../Mowitz/MwRow.h \
	../Mowitz/MwRudegrid.h ../Mowitz/MwRuler.h \
	../Mowitz/MwSButton.h ../Mowitz/MwSlider.h \
	../Mowitz/MwSpinner.h ../Mowitz/MwSubME.h ../Mowitz/MwTabbing.h \
	../Mowitz/MwTable.h ../Mowitz/MwTabs.h ../Mowitz/MwTabstop.h \
	../Mowitz/MwTextField.h ../Mowitz/MwTooltip.h \
	../Mowitz/MwTraverse.h ../Mowitz/MwVSlider.h ../Mowitz/MwXCC.h
TreeFSel.o: TreeFSel.c Directory.h ../Mowitz/MwListTree.h TreeFSelP.h \
	TreeFSel.h

info-am:
info: info-am
dvi-am:
dvi: dvi-am
check-am: all-am
check: check-am
installcheck-am:
installcheck: installcheck-am
install-exec-am:
install-exec: install-exec-am

install-data-am:
install-data: install-data-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am
install: install-am
uninstall-am:
uninstall: uninstall-am
all-am: Makefile $(PROGRAMS)
all-redirect: all-am
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) AM_INSTALL_PROGRAM_FLAGS=-s install
installdirs:


mostlyclean-generic:

clean-generic:

distclean-generic:
	-rm -f Makefile $(CONFIG_CLEAN_FILES)
	-rm -f config.cache config.log stamp-h stamp-h[0-9]*

maintainer-clean-generic:
mostlyclean-am:  mostlyclean-noinstPROGRAMS mostlyclean-compile \
		mostlyclean-libtool mostlyclean-tags \
		mostlyclean-generic

mostlyclean: mostlyclean-am

clean-am:  clean-noinstPROGRAMS clean-compile clean-libtool clean-tags \
		clean-generic mostlyclean-am

clean: clean-am

distclean-am:  distclean-noinstPROGRAMS distclean-compile \
		distclean-libtool distclean-tags distclean-generic \
		clean-am
	-rm -f libtool

distclean: distclean-am

maintainer-clean-am:  maintainer-clean-noinstPROGRAMS \
		maintainer-clean-compile maintainer-clean-libtool \
		maintainer-clean-tags maintainer-clean-generic \
		distclean-am
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."

maintainer-clean: maintainer-clean-am

.PHONY: mostlyclean-noinstPROGRAMS distclean-noinstPROGRAMS \
clean-noinstPROGRAMS maintainer-clean-noinstPROGRAMS \
mostlyclean-compile distclean-compile clean-compile \
maintainer-clean-compile mostlyclean-libtool distclean-libtool \
clean-libtool maintainer-clean-libtool tags mostlyclean-tags \
distclean-tags clean-tags maintainer-clean-tags distdir info-am info \
dvi-am dvi check check-am installcheck-am installcheck install-exec-am \
install-exec install-data-am install-data install-am install \
uninstall-am uninstall all-redirect all-am all installdirs \
mostlyclean-generic distclean-generic clean-generic \
maintainer-clean-generic clean mostlyclean distclean maintainer-clean


# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
