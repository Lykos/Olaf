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
    searcherfactory.cpp \
    alphabetasearcher.cpp \
    iterativedeepener.cpp \
    simpletimedsearcher.cpp \
    compositestopper.cpp \
    simplemovecreator.cpp \
    timestopper.cpp \
    forcedstopper.cpp \
    nodestopper.cpp \
    evaluatorsearcher.cpp \
    parallelnegamaxer.cpp \
    capturegenerator.cpp

HEADERS += \
    simplemovegenerator.h \
    searchresult.h \
    nomoveorderer.h \
    negamaxer.h \
    moveorderer.h \
    movegenerator.h \
    searcherfactory.h \
    depthsearcher.h \
    alphabetasearcher.h \
    timedsearcher.h \
    iterativedeepener.h \
    simpletimedsearcher.h \
    stopper.h \
    compositestopper.h \
    movecreator.h \
    simplemovecreator.h \
    timestopper.h \
    forcedstopper.h \
    nodestopper.h \
    evaluatorsearcher.h \
    iterativesearcher.h \
    parallelnegamaxer.h \
    capturegenerator.h

header_files.files = $$HEADERS
header_files.path = /usr/local/include/OlafSearching

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/local/lib
    } else {
        target.path = /usr/local/lib
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

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../
