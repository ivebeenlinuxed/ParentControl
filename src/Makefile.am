## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = parentcontrol

parentcontrol_SOURCES = \
	main.cc \
	HTTPProxy.cc \
	HTTPProxy.h \
	HTTPProxyRequestHandlerFactory.cc \
	HTTPProxyRequestHandlerFactory.h \
	HTTPProxyRequestHandler.cc \
	HTTPProxyRequestHandler.h

parentcontrol_LDFLAGS = 

parentcontrol_LDADD =  \
	-lPocoNet \
	-lPocoUtil \
	-lPocoFoundation


SUBDIRS = \
	Subsystems
