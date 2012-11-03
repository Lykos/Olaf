#-------------------------------------------------
#
# Project created by QtCreator 2012-11-03T12:33:33
#
#-------------------------------------------------

QT       -= core gui

TARGET = OlafSearching
TEMPLATE = lib
QMAKE_CXXFLAGS += -std=c++11
CONFIG(release, debug|release) QMAKE_CXXFLAGS += -O3

DEFINES += OLAFSEARCHING_LIBRARY

SOURCES += \
    simplemovegenerator.cpp \
    searchresult.cpp \
    nomoveorderer.cpp \
    negamaxer.cpp \
    materialevaluator.cpp \
    searcherfactory.cpp \
    infinitesearcher.cpp \
    stoppablesearcher.cpp \
    alphabetasearcher.cpp \
    timedsearcher.cpp \
    iterativedeepener.cpp

HEADERS += \
    simplemovegenerator.h \
    searchresult.h \
    nomoveorderer.h \
    negamaxer.h \
    moveorderer.h \
    movegenerator.h \
    materialevaluator.h \
    searcherfactory.h \
    depthsearcher.h \
    infinitesearcher.h \
    stoppablesearcher.h \
    alphabetasearcher.h \
    timedsearcher.h \
    iterativedeepener.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../OlafRules-build-desktop-Release/ -lOlafRules
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OlafRules-build-desktop-Debug/ -lOlafRules
else:symbian: LIBS += -lOlafRules
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../OlafRules-build-desktop-Release/ -lOlafRules
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OlafRules-build-desktop-Debug/ -lOlafRules

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../
