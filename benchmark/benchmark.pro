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
    main.cpp \
    benchmark.cpp \
    autobenchmark.cpp \
    epdbenchmark.cpp \
    benchmarkresult.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    perftbenchmark.h \
    testutil.h \
    comparemacros.h \
    autobenchmark.h \
    benchmark.h \
    epdbenchmark.h \
    benchmarkresult.h \
    compositebenchmarkresult.h

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

copy_epd_files.commands = $(COPY_DIR) $$PWD/epd_files $$OUT_PWD
first.depends = $(first) copy_epd_files
export(first.depends)
export(copy_epd_files.commands)
QMAKE_EXTRA_TARGETS += first copy_epd_files
