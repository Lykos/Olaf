#-------------------------------------------------
#
# Project created by QtCreator 2012-11-04T14:23:06
#
#-------------------------------------------------

QT       -= core gui

TARGET = OlafProtocols
TEMPLATE = lib
QMAKE_CXXFLAGS += -std=c++11
CONFIG(release, debug|release) QMAKE_CXXFLAGS += -O3

DEFINES += OLAFPROTOCOLS_LIBRARY

SOURCES += \
    xboardwriter.cpp \
    xboardreader.cpp \
    enginestate.cpp \
    engineproducer.cpp \
    moveevent.cpp \
    engineconsumer.cpp \
    forceflipevent.cpp \
    ponderingflipevent.cpp \
    myturnflipevent.cpp \
    deferredponderingevent.cpp \
    pingevent.cpp \
    boardstate.cpp

HEADERS +=\
    xboardwriter.h \
    xboardreader.h \
    result.h \
    protocolwriter.h \
    protocolreader.h \
    enginestate.h \
    engineproducer.h \
    engineevent.h \
    moveevent.h \
    engineconsumer.h \
    forceflipevent.h \
    ponderingflipevent.h \
    myturnflipevent.h \
    deferredponderingevent.h \
    pingevent.h \
    boardstate.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../OlafRules-build-Desktop-Release/ -lOlafRules
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OlafRules-build-Desktop-Debug/ -lOlafRules
else:symbian: LIBS += -lOlafRules
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../OlafRules-build-Desktop-Release/ -lOlafRules
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OlafRules-build-Desktop-Debug/ -lOlafRules

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../OlafEvaluation-build-Desktop-Release/ -lOlafEvaluation
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OlafEvaluation-build-Desktop-Debug/ -lOlafEvaluation
else:symbian: LIBS += -lOlafEvaluation
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../OlafEvaluation-build-Desktop-Release/ -lOlafEvaluation
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OlafEvaluation-build-Desktop-Debug/ -lOlafEvaluation

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../OlafSearching-build-Desktop-Release/ -lOlafSearching
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OlafSearching-build-Desktop-Debug/ -lOlafSearching
else:symbian: LIBS += -lOlafSearching
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../OlafSearching-build-Desktop-Release/ -lOlafSearching
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OlafSearching-build-Desktop-Debug/ -lOlafSearching

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../
