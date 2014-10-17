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
    nomoveorderer.cpp \
    negamaxer.cpp \
    searcherfactory.cpp \
    iterativedeepener.cpp \
    simpletimedsearcher.cpp \
    compositestopper.cpp \
    simplemovecreator.cpp \
    timestopper.cpp \
    forcedstopper.cpp \
    evaluatorsearcher.cpp \
    parallelnegamaxer.cpp \
    capturegenerator.cpp \
    thinkingwriter.cpp \
    nostopper.cpp \
    stopper.cpp \
    perft.cpp \
    sanparser.cpp \
    epdparser.cpp \
    epdposition.cpp \
    nothinkingwriter.cpp \
    searcher.cpp \
    searchresult.cpp \
    searchcontext.cpp \
    alphabetasearcher.cpp

HEADERS += \
    simplemovegenerator.h \
    searchresult.h \
    nomoveorderer.h \
    negamaxer.h \
    moveorderer.h \
    movegenerator.h \
    searcherfactory.h \
    iterativedeepener.h \
    simpletimedsearcher.h \
    stopper.h \
    compositestopper.h \
    movecreator.h \
    simplemovecreator.h \
    timestopper.h \
    forcedstopper.h \
    evaluatorsearcher.h \
    parallelnegamaxer.h \
    capturegenerator.h \
    thinkingwriter.h \
    nostopper.h \
    perft.h \
    searchcontext.h \
    sanparser.h \
    epdparser.h \
    epdposition.h \
    nothinkingwriter.h \
    searcher.h \
    alphabetasearcher.h

headers.files = $$HEADERS
headers.path = /usr/local/include/OlafSearching

target.path = /usr/local/lib

INSTALLS += target headers

CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Olaf-Release/OlafRules -lOlafRules
CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Olaf-Debug/OlafRules -lOlafRules

CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Olaf-Release/OlafEvaluation -lOlafEvaluation
CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Olaf-Debug/OlafEvaluation -lOlafEvaluation
