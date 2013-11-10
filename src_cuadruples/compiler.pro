#-------------------------------------------------
#
# Project created by QtCreator 2013-10-17T11:42:17
#
#-------------------------------------------------

QT       += core gui
QT       += webkit webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = compiler
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cuadruple.cpp \
    cuaarithmetic.cpp \
    cuaprint.cpp \
    cualogic.cpp \
    cuaend.cpp \
    cuaasign.cpp \
    cuaindex.cpp \
    cuaifnot.cpp \
    cuagoto.cpp

HEADERS  += mainwindow.h \
    cuadruple.h \
    cuaarithmetic.h \
    cuaprint.h \
    cualogic.h \
    cuaend.h \
    cuaasign.h \
    cuaindex.h \
    cuaifnot.h \
    cuagoto.h

FORMS    += mainwindow.ui
