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
    cuagoto.cpp \
    AAutomata.cpp \
    AgrupationAutomata.cpp \
    Analex.cpp \
    Anasin.cpp \
    ArithmeticAutomata.cpp \
    AsignmentAutomata.cpp \
    CuadrupleGenerator.cpp \
    IdAutomata.cpp \
    Lexema.cpp \
    LexemeTable.cpp \
    NumberAutomata.cpp \
    OutputAutomata.cpp \
    PunctuationAutomata.cpp \
    RelationalAutomata.cpp \
    ReservedAutomata.cpp \
    StringAutomata.cpp

HEADERS  += mainwindow.h \
    cuadruple.h \
    cuaarithmetic.h \
    cuaprint.h \
    cualogic.h \
    cuaend.h \
    cuaasign.h \
    cuaindex.h \
    cuaifnot.h \
    cuagoto.h  \
    AAutomata.hh \
    AgrupationAutomata.hh \
    Analex.hh \
    Anasin.hh \
    ArithmeticAutomata.hh \
    AsignmentAutomata.hh \
    CuadrupleGenerator.hh \
    IdAutomata.hh \
    Lexema.hh \
    LexemeTable.hh \
    NumberAutomata.hh \
    OutputAutomata.hh \
    PunctuationAutomata.hh \
    RelationalAutomata.hh \
    ReservedAutomata.hh \
    StringAutomata.hh

FORMS    += mainwindow.ui
