#-------------------------------------------------
#
# Project created by QtCreator 2012-11-04T14:23:06
#
#-------------------------------------------------

include(../common.pri)

QT       -= core gui

TARGET = OlafProtocols
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
    setboardevent.cpp

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
    setboardevent.h

header_files.files = $$HEADERS
header_files.path = /usr/local/include/OlafProtocols

target.path = /usr/local/lib
INSTALLS += target

CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Olaf-Release/OlafRules -lOlafRules
CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Olaf-Debug/OlafRules -lOlafRules

CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Olaf-Release/OlafEvaluation -lOlafEvaluation
CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Olaf-Debug/OlafEvaluation -lOlafEvaluation

CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Olaf-Release/OlafSearching -lOlafSearching
CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Olaf-Debug/OlafSearching -lOlafSearching
