#-------------------------------------------------
#
# Project created by QtCreator 2012-11-05T02:03:02
#
#-------------------------------------------------

include(../common.pri)

QT       += testlib

QT       -= gui

TARGET = tst_olafrulestesttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    tst_olafrules.cpp \
    boardtest.cpp \
    pawntest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    boardtest.h \
    pawntest.h

CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Olaf-Desktop-Release/OlafRules -lOlafRules
CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Olaf-Desktop-Debug/OlafRules -lOlafRules
