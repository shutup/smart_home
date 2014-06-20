#-------------------------------------------------
#
# Project created by QtCreator 2014-03-11T11:04:17
#
#-------------------------------------------------

QT       += core gui network sql

TARGET = first_server
TEMPLATE = app


SOURCES += main.cpp\
    utils.cpp \
    win_qextserialport.cpp \
    qextserialport.cpp \
    qextserialbase.cpp \
    mainwindow.cpp \
    mythread.cpp

HEADERS  += \
    utils.h \
    connection.h \
    win_qextserialport.h \
    qextserialport.h \
    qextserialbase.h \
    mainwindow.h \
    mythread.h

FORMS    += \
    mainwindow.ui



OTHER_FILES += \
    myappicon.rc
RC_FILE += myappicon.rc
