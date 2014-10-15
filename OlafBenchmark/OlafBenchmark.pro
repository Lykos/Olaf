#-------------------------------------------------
#
# Project created by QtCreator 2014-10-14T19:28:55
#
#-------------------------------------------------

include(../common.pri)

QT       += testlib

QT       -= gui

TARGET = olaf_benchmark
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    perftbenchmark.cpp \
    testutil.cpp \
    performanceresult.cpp \
    main.cpp \
    benchmark.cpp \
    autobenchmark.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    perftbenchmark.h \
    performanceresult.h \
    testutil.h \
    comparemacros.h \
    compositeperformanceresult.h \
    autobenchmark.h \
    benchmark.h

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
