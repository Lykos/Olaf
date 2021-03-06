#-------------------------------------------------
#
# Project created by QtCreator 2012-11-05T02:03:02
#
#-------------------------------------------------

include(../common.pri)

QT       += testlib

QT       -= gui

TARGET = olaf_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    pawntest.cpp \
    oncepiecetest.cpp \
    fenparsertest.cpp \
    main.cpp \
    movegeneratortest.cpp \
    perfttest.cpp \
    testutil.cpp \
    sanparsertest.cpp \
    epdparsertest.cpp \
    autotest.cpp \
    zobristhashtest.cpp \
    lrucachetest.cpp \
    bitboardtest.cpp \
    incrementalevaluatortest.cpp \
    chessboardtest.cpp \
    searchertest.cpp \
    moveorderertest.cpp \
    egbbprobertest.cpp \
    evaluatortest.cpp \
    openingbooktest.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    pawntest.h \
    oncepiecetest.h \
    autotest.h \
    testutil.h \
    fenparsertest.h \
    movegeneratortest.h \
    perfttest.h \
    sanparsertest.h \
    epdparsertest.h \
    zobristhashtest.h \
    lrucachetest.h \
    bitboardtest.h \
    incrementalevaluatortest.h \
    chessboardtest.h \
    searchertest.h \
    moveorderertest.h \
    egbbprobertest.h \
    evaluatortest.h \
    openingbooktest.h

CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Olaf-Release/olaf -lolaf
CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Olaf-Debug/olaf -lolaf

CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Olaf-Release/protocols -lolafprotocols
CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Olaf-Debug/protocols -lolafprotocols

LIBS += -L$$PWD/../../../../Downloads/gmock-1.7.0/build/ -lgmock

LIBS += -lgflags

INCLUDEPATH += $$PWD/../../../../Downloads/gmock-1.7.0/include
DEPENDPATH += $$PWD/../../../../Downloads/gmock-1.7.0/include

INCLUDEPATH += $$PWD/../../../../Downloads/gmock-1.7.0/gtest/include
DEPENDPATH += $$PWD/../../../../Downloads/gmock-1.7.0/gtest/include

PRE_TARGETDEPS += $$PWD/../../../../Downloads/gmock-1.7.0/build/libgmock.a
