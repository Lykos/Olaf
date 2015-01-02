#-------------------------------------------------
#
# Project created by QtCreator 2014-10-27T20:23:34
#
#-------------------------------------------------

include(../common.pri)

QT       -= core gui

TARGET = olafgeneration
TEMPLATE = lib

DEFINES += OLAFGENERATION_LIBRARY

SOURCES += \
    generation.cpp

HEADERS += \
    generation.h

LIBS += -lgflags

target.path = /usr/local/lib

INSTALLS += target

CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Olaf-Release/olaf -lolaf
CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Olaf-Debug/olaf -lolaf
