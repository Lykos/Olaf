#-------------------------------------------------
#
# Project created by QtCreator 2012-11-03T12:33:33
#
#-------------------------------------------------

include(../common.pri)

QT       -= core gui

TARGET = olaf
TEMPLATE = lib

QMAKE_CXXFLAGS += -march=native -mtune=native
DEFINES += OLAFSEARCHING_LIBRARY

SOURCES += \
    config.cpp \
    evaluation/materialevaluator.cpp \
    evaluation/evaluatorfactory.cpp \
    evaluation/positionevaluator.cpp \
    search/simplemovegenerator.cpp \
    search/moveorderer.cpp \
    search/negamaxer.cpp \
    search/searcherfactory.cpp \
    search/iterativedeepener.cpp \
    search/simpletimedsearcher.cpp \
    search/compositestopper.cpp \
    search/timestopper.cpp \
    search/forcedstopper.cpp \
    search/evaluatorsearcher.cpp \
    search/parallelnegamaxer.cpp \
    search/capturegenerator.cpp \
    search/thinkingwriter.cpp \
    search/nostopper.cpp \
    search/nomoveorderer.cpp \
    search/stopper.cpp \
    search/perft.cpp \
    search/nothinkingwriter.cpp \
    search/searcher.cpp \
    search/searchresult.cpp \
    search/searchcontext.cpp \
    search/quiescer.cpp \
    search/movegenerator.cpp \
    search/alphabetasearcher.cpp \
    search/simplemovecreator.cpp \
    parse/sanparser.cpp \
    parse/epdparser.cpp \
    parse/epdposition.cpp \
    parse/fenparser.cpp \
    rules/oncepiece.cpp \
    rules/epenableaction.cpp \
    rules/epdisableaction.cpp \
    rules/conversionaction.cpp \
    rules/turnflipaction.cpp \
    rules/positiondelta.cpp \
    rules/position.cpp \
    rules/pieceset.cpp \
    rules/piecemoveaction.cpp \
    rules/pieceboard.cpp \
    rules/piece.cpp \
    rules/pawn.cpp \
    rules/linepiece.cpp \
    rules/colorboard.cpp \
    rules/chessboard.cpp \
    rules/captureaction.cpp \
    rules/bitboard.cpp \
    rules/anticastleaction.cpp \
    rules/movebuilder.cpp \
    rules/move.cpp \
    rules/setkingcapturepositionsaction.cpp \
    rules/movecreator.cpp \
    rules/moveaction.cpp \
    transposition_table/zobristhash.cpp

HEADERS += \
    config.h \
    evaluation/positionevaluator.h \
    evaluation/materialevaluator.h \
    evaluation/evaluatorfactory.h \
    evaluation/positionevaluator.h \
    search/simplemovegenerator.h \
    search/quiescer.h \
    search/searchresult.h \
    search/moveorderer.h \
    search/negamaxer.h \
    search/movegenerator.h \
    search/searcherfactory.h \
    search/iterativedeepener.h \
    search/simpletimedsearcher.h \
    search/stopper.h \
    search/compositestopper.h \
    search/timestopper.h \
    search/forcedstopper.h \
    search/evaluatorsearcher.h \
    search/parallelnegamaxer.h \
    search/capturegenerator.h \
    search/thinkingwriter.h \
    search/nostopper.h \
    search/nomoveorderer.h \
    search/perft.h \
    search/searchcontext.h \
    search/nothinkingwriter.h \
    search/searcher.h \
    search/alphabetasearcher.h \
    search/simplemovecreator.h \
    parse/sanparser.h \
    parse/epdparser.h \
    parse/epdposition.h \
    parse/fenparser.h \
    rules/movecreator.h \
    rules/moveaction.h \
    rules/oncepiece.h \
    rules/epdisableaction.h \
    rules/conversionaction.h \
    rules/positiondelta.h \
    rules/position.h \
    rules/pieceset.h \
    rules/piecemoveaction.h \
    rules/pieceboard.h \
    rules/piece.h \
    rules/pawn.h \
    rules/linepiece.h \
    rules/turnflipaction.h \
    rules/colorboard.h \
    rules/color.h \
    rules/chessboard.h \
    rules/captureaction.h \
    rules/bitboard.h \
    rules/anticastleaction.h \
    rules/epenableaction.h \
    rules/movebuilder.h \
    rules/move.h \
    rules/setkingcapturepositionsaction.h \
    transposition_table/zobristhash.h

headers.files = $$HEADERS
headers.path = /usr/local/include/OlafSearching

target.path = /usr/local/lib

INSTALLS += target headers

LIBS += -lyaml-cpp
