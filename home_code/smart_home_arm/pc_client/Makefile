#############################################################################
# Makefile for building: pc_client
# Generated by qmake (2.01a) (Qt 4.8.5) on: Sun May 11 14:58:23 2014
# Project:  pc_client.pro
# Template: app
# Command: /usr/local/Trolltech/QtEmbedded-4.8.5-arm/bin/qmake -o Makefile pc_client.pro
#############################################################################

####### Compiler, tools and options

CC            = arm-linux-gcc
CXX           = arm-linux-g++
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/qws/linux-arm-g++ -I. -I/usr/local/Trolltech/QtEmbedded-4.8.5-arm/include/QtCore -I/usr/local/Trolltech/QtEmbedded-4.8.5-arm/include/QtNetwork -I/usr/local/Trolltech/QtEmbedded-4.8.5-arm/include/QtGui -I/usr/local/Trolltech/QtEmbedded-4.8.5-arm/include -I. -I. -I.
LINK          = arm-linux-g++
LFLAGS        = -Wl,-O1 -Wl,-rpath,/usr/local/Trolltech/QtEmbedded-4.8.5-arm/lib
LIBS          = $(SUBLIBS)  -L/usr/local/Trolltech/QtEmbedded-4.8.5-arm/lib -lQtGui -L/usr/local/Trolltech/QtEmbedded-4.8.5-arm/lib -lQtNetwork -lQtCore -lpthread 
AR            = arm-linux-ar cqs
RANLIB        = 
QMAKE         = /usr/local/Trolltech/QtEmbedded-4.8.5-arm/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = arm-linux-strip
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

SOURCES       = main.cpp \
		mainwindow.cpp \
		utils.cpp moc_mainwindow.cpp \
		qrc_img.cpp
OBJECTS       = main.o \
		mainwindow.o \
		utils.o \
		moc_mainwindow.o \
		qrc_img.o
DIST          = /usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/unix.conf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/linux.conf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/gcc-base.conf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/gcc-base-unix.conf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/g++-base.conf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/g++-unix.conf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/qws.conf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/qconfig.pri \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/qt_functions.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/qt_config.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/exclusive_builds.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/default_pre.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/release.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/default_post.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/shared.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/warn_on.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/qt.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/unix/thread.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/moc.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/resources.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/uic.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/yacc.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/lex.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/include_source_dir.prf \
		pc_client.pro
QMAKE_TARGET  = pc_client
DESTDIR       = 
TARGET        = pc_client

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

$(TARGET): ui_mainwindow.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: pc_client.pro  /usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/qws/linux-arm-g++/qmake.conf /usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/unix.conf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/linux.conf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/gcc-base.conf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/gcc-base-unix.conf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/g++-base.conf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/g++-unix.conf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/qws.conf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/qconfig.pri \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/qt_functions.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/qt_config.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/exclusive_builds.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/default_pre.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/release.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/default_post.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/shared.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/warn_on.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/qt.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/unix/thread.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/moc.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/resources.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/uic.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/yacc.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/lex.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/include_source_dir.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/lib/libQtGui.prl \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/lib/libQtNetwork.prl \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/lib/libQtCore.prl
	$(QMAKE) -o Makefile pc_client.pro
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/unix.conf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/linux.conf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/gcc-base.conf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/gcc-base-unix.conf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/g++-base.conf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/g++-unix.conf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/qws.conf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/qconfig.pri:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/qt_functions.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/qt_config.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/exclusive_builds.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/default_pre.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/release.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/default_post.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/shared.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/warn_on.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/qt.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/unix/thread.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/moc.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/resources.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/uic.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/yacc.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/lex.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/include_source_dir.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/lib/libQtGui.prl:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/lib/libQtNetwork.prl:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile pc_client.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/pc_client1.0.0 || $(MKDIR) .tmp/pc_client1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/pc_client1.0.0/ && $(COPY_FILE) --parents mainwindow.h utils.h .tmp/pc_client1.0.0/ && $(COPY_FILE) --parents img.qrc .tmp/pc_client1.0.0/ && $(COPY_FILE) --parents main.cpp mainwindow.cpp utils.cpp .tmp/pc_client1.0.0/ && $(COPY_FILE) --parents mainwindow.ui .tmp/pc_client1.0.0/ && (cd `dirname .tmp/pc_client1.0.0` && $(TAR) pc_client1.0.0.tar pc_client1.0.0 && $(COMPRESS) pc_client1.0.0.tar) && $(MOVE) `dirname .tmp/pc_client1.0.0`/pc_client1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/pc_client1.0.0


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

compiler_moc_header_make_all: moc_mainwindow.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp
moc_mainwindow.cpp: utils.h \
		mainwindow.h
	/usr/local/Trolltech/QtEmbedded-4.8.5-arm/bin/moc $(DEFINES) $(INCPATH) mainwindow.h -o moc_mainwindow.cpp

compiler_rcc_make_all: qrc_img.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_img.cpp
qrc_img.cpp: img.qrc \
		image/beijin.jpg
	/usr/local/Trolltech/QtEmbedded-4.8.5-arm/bin/rcc -name img img.qrc -o qrc_img.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainwindow.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h
ui_mainwindow.h: mainwindow.ui
	/usr/local/Trolltech/QtEmbedded-4.8.5-arm/bin/uic mainwindow.ui -o ui_mainwindow.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 

####### Compile

main.o: main.cpp mainwindow.h \
		utils.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

mainwindow.o: mainwindow.cpp mainwindow.h \
		utils.h \
		ui_mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

utils.o: utils.cpp utils.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o utils.o utils.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

qrc_img.o: qrc_img.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_img.o qrc_img.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

