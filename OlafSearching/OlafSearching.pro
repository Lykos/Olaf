#-------------------------------------------------
#
# Project created by QtCreator 2012-11-03T12:33:33
#
#-------------------------------------------------

include(../common.pri)

QT       -= core gui

TARGET = OlafSearching
TEMPLATE = lib

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
    capturegenerator.cpp \
    thinkingwriter.cpp \
    timedsearcher.cpp \
    nostopper.cpp \
    stopper.cpp \
    iterativesearcher.cpp

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
    capturegenerator.h \
    thinkingwriter.h \
    nostopper.h

header_files.files = $$HEADERS
header_files.path = /usr/local/include/OlafSearching

target.path = /usr/local/lib
INSTALLS += target

CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Olaf-Desktop-Release/OlafRules -lOlafRules
CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Olaf-Desktop-Debug/OlafRules -lOlafRules

CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Olaf-Desktop-Release/OlafEvaluation -lOlafEvaluation
CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Olaf-Desktop-Debug/OlafEvaluation -lOlafEvaluation
