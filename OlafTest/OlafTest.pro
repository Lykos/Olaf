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
    boardtest.cpp \
    pawntest.cpp \
    oncepiecetest.cpp \
    fenparsertest.cpp \
    main.cpp \
    materialevaluatortest.cpp \
    testutil.cc \
    movegeneratortest.cpp \
    perfttest.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    boardtest.h \
    pawntest.h \
    oncepiecetest.h \
    autotest.h \
    testutil.h \
    fenparsertest.h \
    materialevaluatortest.h \
    movegeneratortest.h \
    perfttest.h

CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Olaf-Release/OlafRules -lOlafRules
CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Olaf-Debug/OlafRules -lOlafRules

CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Olaf-Release/OlafEvaluation -lOlafEvaluation
CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Olaf-Debug/OlafEvaluation -lOlafEvaluation

CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Olaf-Release/OlafSearching -lOlafSearching
CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Olaf-Debug/OlafSearching -lOlafSearching

CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Olaf-Release/OlafProtocols -lOlafProtocols
CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Olaf-Debug/OlafProtocols -lOlafProtocols

LIBS += -L$$PWD/../../../../Downloads/gmock-1.7.0/build/ -lgmock

INCLUDEPATH += $$PWD/../../../../Downloads/gmock-1.7.0/include
DEPENDPATH += $$PWD/../../../../Downloads/gmock-1.7.0/include

INCLUDEPATH += $$PWD/../../../../Downloads/gmock-1.7.0/gtest/include
DEPENDPATH += $$PWD/../../../../Downloads/gmock-1.7.0/gtest/include

PRE_TARGETDEPS += $$PWD/../../../../Downloads/gmock-1.7.0/build/libgmock.a
