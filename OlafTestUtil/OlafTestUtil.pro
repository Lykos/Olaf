#-------------------------------------------------
#
# Project created by QtCreator 2014-10-13T12:48:03
#
#-------------------------------------------------

QT       -= gui

TARGET = OlafTestUtil
TEMPLATE = lib

DEFINES += OLAFTESTUTIL_LIBRARY

SOURCES +=

HEADERS += \
    autotest.h \
    testutil.h

header_files.files = $$HEADERS
header_files.path = /usr/local/include/OlafRules

target.path = /usr/local/lib
INSTALLS += target

LIBS += -L$$PWD/../../../../Downloads/gmock-1.7.0/build/ -lgmock

INCLUDEPATH += $$PWD/../../../../Downloads/gmock-1.7.0/include
DEPENDPATH += $$PWD/../../../../Downloads/gmock-1.7.0/include

INCLUDEPATH += $$PWD/../../../../Downloads/gmock-1.7.0/gtest/include
DEPENDPATH += $$PWD/../../../../Downloads/gmock-1.7.0/gtest/include

PRE_TARGETDEPS += $$PWD/../../../../Downloads/gmock-1.7.0/build/libgmock.a
