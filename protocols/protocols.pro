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
    event/undoevent.cpp \
    event/settimeevent.cpp \
    event/setnpsevent.cpp \
    event/setdepthevent.cpp \
    event/setboardevent.cpp \
    event/ponderingflipevent.cpp \
    event/pingevent.cpp \
    event/myturnflipevent.cpp \
    event/moveevent.cpp \
    event/forceflipevent.cpp \
    event/engineevent.cpp \
    event/deferredponderingevent.cpp \
    simplethinkingwriter.cpp \
    protocolwriter.cpp \
    protocolreader.cpp \
    engineeventhelper.cpp \
    engine.cpp \
    boardstate.cpp \
    event/setanalyzeevent.cpp \
    event/setlevelevent.cpp

HEADERS +=\
    xboardwriter.h \
    xboardreader.h \
    result.h \
    event/undoevent.h \
    event/settimeevent.h \
    event/setnpsevent.h \
    event/setdepthevent.h \
    event/setboardevent.h \
    event/ponderingflipevent.h \
    event/pingevent.h \
    event/myturnflipevent.h \
    event/moveevent.h \
    event/forceflipevent.h \
    event/engineevent.h \
    event/deferredponderingevent.h \
    simplethinkingwriter.h \
    protocolwriter.h \
    protocolreader.h \
    enginestate.h \
    engineeventhelper.h \
    engine.h \
    boardstate.h \
    event/setanalyzeevent.h \
    event/setlevelevent.h

target.path = /usr/local/lib

INSTALLS += target

CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Olaf-Release/olaf -lolaf
CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Olaf-Debug/olaf -lolaf
