#-------------------------------------------------
#
# Project created by QtCreator 2012-11-03T12:33:33
#
#-------------------------------------------------

include(../common.pri)

QT       -= core gui

TARGET = OlafSearching
TEMPLATE = lib

QMAKE_CXXFLAGS += -march=native -mtune=native
DEFINES += OLAFSEARCHING_LIBRARY

SOURCES += \
    materialevaluator.cpp \
    evaluatorfactory.cpp \
    config.cpp \
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
    alphabetasearcher.cpp \
    linepiece.cpp \
    epenableaction.cpp \
    epdisableaction.cpp \
    conversionaction.cpp \
    turnflipaction.cpp \
    positiondelta.cpp \
    position.cpp \
    pieceset.cpp \
    piecemoveaction.cpp \
    pieceboard.cpp \
    piece.cpp \
    pawn.cpp \
    oncepiece.cpp \
    colorboard.cpp \
    chessboard.cpp \
    captureaction.cpp \
    bitboard.cpp \
    anticastleaction.cpp \
    movebuilder.cpp \
    move.cpp \
    fenparser.cpp \
    setkingcapturepositionsaction.cpp \
    quiescer.cpp

HEADERS += \
    positionevaluator.h \
    materialevaluator.h \
    evaluatorfactory.h \
    config.h \
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
    alphabetasearcher.h \
    moveaction.h \
    linepiece.h \
    epdisableaction.h \
    conversionaction.h \
    positionevaluator.h \
    positiondelta.h \
    position.h \
    pieceset.h \
    piecemoveaction.h \
    pieceboard.h \
    piece.h \
    pawn.h \
    oncepiece.h \
    turnflipaction.h \
    colorboard.h \
    color.h \
    chessboard.h \
    captureaction.h \
    bitboard.h \
    anticastleaction.h \
    epenableaction.h \
    movebuilder.h \
    move.h \
    fenparser.h \
    setkingcapturepositionsaction.h \
    quiescer.h

headers.files = $$HEADERS
headers.path = /usr/local/include/OlafSearching

target.path = /usr/local/lib

INSTALLS += target headers

LIBS += -lyaml-cpp
