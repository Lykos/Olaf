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
    pawntest.cpp \
    oncepiecetest.cpp \
    fenparsertest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    boardtest.h \
    pawntest.h \
    oncepiecetest.h \
    testutil.h \
    fenparsertest.h

CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Olaf-Desktop-Release/OlafRules -lOlafRules
CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Olaf-Desktop-Debug/OlafRules -lOlafRules

LIBS += -L$$PWD/../../../../Downloads/gmock-1.7.0/build/ -lgmock

INCLUDEPATH += $$PWD/../../../../Downloads/gmock-1.7.0/include
DEPENDPATH += $$PWD/../../../../Downloads/gmock-1.7.0/include

INCLUDEPATH += $$PWD/../../../../Downloads/gmock-1.7.0/gtest/include
DEPENDPATH += $$PWD/../../../../Downloads/gmock-1.7.0/gtest/include

PRE_TARGETDEPS += $$PWD/../../../../Downloads/gmock-1.7.0/build/libgmock.a
