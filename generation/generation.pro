#-------------------------------------------------
#
# Project created by QtCreator 2014-10-27T20:23:34
#
#-------------------------------------------------

include(../common.pri)

QT       -= core gui

TARGET = generation
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += GENERATION_LIBRARY

SOURCES += \
    main.cpp \
    generation.cpp

HEADERS += \
    generation.h

CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Olaf-Release/olaf -lolaf
CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Olaf-Debug/olaf -lolaf
