#-------------------------------------------------
#
# Project created by QtCreator 2012-11-05T02:03:02
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_olafrulestesttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11
CONFIG(release, debug|release) QMAKE_CXXFLAGS += -O3


SOURCES += \
    tst_olafrules.cpp \
    boardtest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    boardtest.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../OlafRules-build-Desktop-Release/ -lOlafRules
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OlafRules-build-Desktop-Debug/ -lOlafRules
else:symbian: LIBS += -lOlafRules
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../OlafRules-build-Desktop-Release/ -lOlafRules
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OlafRules-build-Desktop-Debug/ -lOlafRules

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../
