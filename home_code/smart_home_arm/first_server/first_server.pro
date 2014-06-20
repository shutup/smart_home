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
    qextserialport.cpp \
    qextserialbase.cpp \
    mainwindow.cpp \
    posix_qextserialport.cpp \
    mythread.cpp

HEADERS  += \
    utils.h \
    connection.h \
    qextserialport.h \
    qextserialbase.h \
    mainwindow.h \
    posix_qextserialport.h \
    mythread.h

FORMS    += \
    mainwindow.ui
