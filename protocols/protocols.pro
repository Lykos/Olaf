#-------------------------------------------------
#
# Project created by QtCreator 2012-11-04T14:23:06
#
#-------------------------------------------------

include(../common.pri)

QT       -= core gui

TARGET = olafprotocols
TEMPLATE = lib

DEFINES += OLAFPROTOCOLS_LIBRARY

SOURCES += \
    xboardwriter.cpp \
    xboardreader.cpp \
    enginestate.cpp \
    moveevent.cpp \
    forceflipevent.cpp \
    ponderingflipevent.cpp \
    myturnflipevent.cpp \
    deferredponderingevent.cpp \
    pingevent.cpp \
    boardstate.cpp \
    engineevent.cpp \
    protocolwriter.cpp \
    settimeevent.cpp \
    engine.cpp \
    engineeventhelper.cpp \
    simplethinkingwriter.cpp \
    setboardevent.cpp \
    protocolreader.cpp \
    setnpsevent.cpp \
    setdepthevent.cpp

HEADERS +=\
    xboardwriter.h \
    xboardreader.h \
    result.h \
    protocolwriter.h \
    protocolreader.h \
    enginestate.h \
    engineevent.h \
    moveevent.h \
    forceflipevent.h \
    ponderingflipevent.h \
    myturnflipevent.h \
    deferredponderingevent.h \
    pingevent.h \
    boardstate.h \
    settimeevent.h \
    engineeventhelper.h \
    engine.h \
    simplethinkingwriter.h \
    setboardevent.h \
    setnpsevent.h \
    setdepthevent.h

headers.files = $$HEADERS
headers.path = /usr/local/include/protocols

target.path = /usr/local/lib

INSTALLS += target headers

CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Olaf-Release/olaf -lolaf
CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Olaf-Debug/olaf -lolaf
