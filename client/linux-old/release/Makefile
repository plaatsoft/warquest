#############################################################################
# Makefile for building: WarQuest
# Generated by qmake (2.01a) (Qt 4.8.1) on: Mon Jul 2 21:28:34 2012
# Project:  ../src/WarQuest.pro
# Template: app
# Command: /home/wplaat/QtSDK/Desktop/Qt/4.8.1/gcc/bin/qmake -spec ../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/linux-g++ -o Makefile ../src/WarQuest.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_WEBKIT_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/linux-g++ -I../src -I../../../../QtSDK/Desktop/Qt/4.8.1/gcc/include/QtCore -I../../../../QtSDK/Desktop/Qt/4.8.1/gcc/include/QtNetwork -I../../../../QtSDK/Desktop/Qt/4.8.1/gcc/include/QtGui -I../../../../QtSDK/Desktop/Qt/4.8.1/gcc/include/QtWebKit -I../../../../QtSDK/Desktop/Qt/4.8.1/gcc/include -I. -I. -I../src -I.
LINK          = g++
LFLAGS        = -Wl,-O1 -Wl,-rpath,/home/wplaat/QtSDK/Desktop/Qt/4.8.1/gcc/lib
LIBS          = $(SUBLIBS)  -L/home/wplaat/QtSDK/Desktop/Qt/4.8.1/gcc/lib -lQtWebKit -lQtGui -L/home/wplaat/QtSDK/Desktop/Qt/4.8.1/gcc/lib -L/usr/X11R6/lib -lQtNetwork -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /home/wplaat/QtSDK/Desktop/Qt/4.8.1/gcc/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = ../src/main.cpp \
		../src/mainwindow.cpp \
		../src/proxy.cpp \
		../src/about.cpp moc_mainwindow.cpp \
		moc_proxy.cpp \
		moc_about.cpp \
		qrc_resources.cpp
OBJECTS       = main.o \
		mainwindow.o \
		proxy.o \
		about.o \
		moc_mainwindow.o \
		moc_proxy.o \
		moc_about.o \
		qrc_resources.o
DIST          = ../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/unix.conf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/linux.conf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/gcc-base.conf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/gcc-base-unix.conf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/g++-base.conf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/g++-unix.conf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/qconfig.pri \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/modules/qt_webkit_version.pri \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt_functions.prf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt_config.prf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/exclusive_builds.prf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/default_pre.prf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/release.prf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/default_post.prf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/unix/gdb_dwarf_index.prf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/warn_on.prf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt.prf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/unix/thread.prf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/moc.prf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/resources.prf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/uic.prf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/yacc.prf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/lex.prf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/include_source_dir.prf \
		../src/WarQuest.pro
QMAKE_TARGET  = WarQuest
DESTDIR       = 
TARGET        = WarQuest

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_mainwindow.h ui_proxy.h ui_about.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: ../src/WarQuest.pro  ../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/linux-g++/qmake.conf ../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/unix.conf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/linux.conf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/gcc-base.conf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/gcc-base-unix.conf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/g++-base.conf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/g++-unix.conf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/qconfig.pri \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/modules/qt_webkit_version.pri \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt_functions.prf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt_config.prf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/exclusive_builds.prf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/default_pre.prf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/release.prf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/default_post.prf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/unix/gdb_dwarf_index.prf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/warn_on.prf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt.prf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/unix/thread.prf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/moc.prf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/resources.prf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/uic.prf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/yacc.prf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/lex.prf \
		../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/include_source_dir.prf \
		/home/wplaat/QtSDK/Desktop/Qt/4.8.1/gcc/lib/libQtWebKit.prl \
		/home/wplaat/QtSDK/Desktop/Qt/4.8.1/gcc/lib/libQtGui.prl \
		/home/wplaat/QtSDK/Desktop/Qt/4.8.1/gcc/lib/libQtCore.prl \
		/home/wplaat/QtSDK/Desktop/Qt/4.8.1/gcc/lib/libQtNetwork.prl
	$(QMAKE) -spec ../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/linux-g++ -o Makefile ../src/WarQuest.pro
../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/unix.conf:
../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/linux.conf:
../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/gcc-base.conf:
../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/gcc-base-unix.conf:
../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/g++-base.conf:
../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/g++-unix.conf:
../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/qconfig.pri:
../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/modules/qt_webkit_version.pri:
../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt_functions.prf:
../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt_config.prf:
../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/exclusive_builds.prf:
../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/default_pre.prf:
../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/release.prf:
../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/default_post.prf:
../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/unix/gdb_dwarf_index.prf:
../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/warn_on.prf:
../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt.prf:
../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/unix/thread.prf:
../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/moc.prf:
../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/resources.prf:
../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/uic.prf:
../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/yacc.prf:
../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/lex.prf:
../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/include_source_dir.prf:
/home/wplaat/QtSDK/Desktop/Qt/4.8.1/gcc/lib/libQtWebKit.prl:
/home/wplaat/QtSDK/Desktop/Qt/4.8.1/gcc/lib/libQtGui.prl:
/home/wplaat/QtSDK/Desktop/Qt/4.8.1/gcc/lib/libQtCore.prl:
/home/wplaat/QtSDK/Desktop/Qt/4.8.1/gcc/lib/libQtNetwork.prl:
qmake:  FORCE
	@$(QMAKE) -spec ../../../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/linux-g++ -o Makefile ../src/WarQuest.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/WarQuest1.4 || $(MKDIR) .tmp/WarQuest1.4 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/WarQuest1.4/ && $(COPY_FILE) --parents ../src/mainwindow.h ../src/proxy.h ../src/about.h ../src/general.h .tmp/WarQuest1.4/ && $(COPY_FILE) --parents ../src/resources.qrc .tmp/WarQuest1.4/ && $(COPY_FILE) --parents ../src/main.cpp ../src/mainwindow.cpp ../src/proxy.cpp ../src/about.cpp .tmp/WarQuest1.4/ && $(COPY_FILE) --parents ../src/mainwindow.ui ../src/proxy.ui ../src/about.ui .tmp/WarQuest1.4/ && (cd `dirname .tmp/WarQuest1.4` && $(TAR) WarQuest1.4.tar WarQuest1.4 && $(COMPRESS) WarQuest1.4.tar) && $(MOVE) `dirname .tmp/WarQuest1.4`/WarQuest1.4.tar.gz . && $(DEL_FILE) -r .tmp/WarQuest1.4


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_mainwindow.cpp moc_proxy.cpp moc_about.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_proxy.cpp moc_about.cpp
moc_mainwindow.cpp: ../src/proxy.h \
		../src/about.h \
		../src/mainwindow.h
	/home/wplaat/QtSDK/Desktop/Qt/4.8.1/gcc/bin/moc $(DEFINES) $(INCPATH) ../src/mainwindow.h -o moc_mainwindow.cpp

moc_proxy.cpp: ../src/proxy.h
	/home/wplaat/QtSDK/Desktop/Qt/4.8.1/gcc/bin/moc $(DEFINES) $(INCPATH) ../src/proxy.h -o moc_proxy.cpp

moc_about.cpp: ../src/about.h
	/home/wplaat/QtSDK/Desktop/Qt/4.8.1/gcc/bin/moc $(DEFINES) $(INCPATH) ../src/about.h -o moc_about.cpp

compiler_rcc_make_all: qrc_resources.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_resources.cpp
qrc_resources.cpp: ../src/resources.qrc \
		../src/images/star.png \
		../src/images/about.png \
		../src/images/reload.gif \
		../src/images/background2.jpg \
		../src/images/plaatsoft.png \
		../src/images/background1.jpg \
		../src/images/settings.png
	/home/wplaat/QtSDK/Desktop/Qt/4.8.1/gcc/bin/rcc -name resources ../src/resources.qrc -o qrc_resources.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainwindow.h ui_proxy.h ui_about.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h ui_proxy.h ui_about.h
ui_mainwindow.h: ../src/mainwindow.ui
	/home/wplaat/QtSDK/Desktop/Qt/4.8.1/gcc/bin/uic ../src/mainwindow.ui -o ui_mainwindow.h

ui_proxy.h: ../src/proxy.ui
	/home/wplaat/QtSDK/Desktop/Qt/4.8.1/gcc/bin/uic ../src/proxy.ui -o ui_proxy.h

ui_about.h: ../src/about.ui
	/home/wplaat/QtSDK/Desktop/Qt/4.8.1/gcc/bin/uic ../src/about.ui -o ui_about.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 

####### Compile

main.o: ../src/main.cpp ../src/mainwindow.h \
		../src/proxy.h \
		../src/about.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o ../src/main.cpp

mainwindow.o: ../src/mainwindow.cpp ../src/mainwindow.h \
		../src/proxy.h \
		../src/about.h \
		../src/ui_mainwindow.h \
		../src/general.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o ../src/mainwindow.cpp

proxy.o: ../src/proxy.cpp ../src/proxy.h \
		../src/general.h \
		../src/ui_proxy.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o proxy.o ../src/proxy.cpp

about.o: ../src/about.cpp ../src/about.h \
		../src/ui_about.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o about.o ../src/about.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_proxy.o: moc_proxy.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_proxy.o moc_proxy.cpp

moc_about.o: moc_about.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_about.o moc_about.cpp

qrc_resources.o: qrc_resources.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_resources.o qrc_resources.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

