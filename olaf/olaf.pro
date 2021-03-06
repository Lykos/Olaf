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
    evaluation/evaluatorfactory.cpp \
    search/simplemovegenerator.cpp \
    search/moveorderer.cpp \
    search/negamaxer.cpp \
    search/searcherfactory.cpp \
    search/iterativedeepener.cpp \
    search/simpletimedsearcher.cpp \
    search/compositestopper.cpp \
    search/timestopper.cpp \
    search/forcedstopper.cpp \
    search/capturegenerator.cpp \
    search/thinkingwriter.cpp \
    search/nostopper.cpp \
    search/stopper.cpp \
    search/perft.cpp \
    search/nothinkingwriter.cpp \
    search/searcher.cpp \
    search/searchresult.cpp \
    search/searchcontext.cpp \
    search/quiescer.cpp \
    search/movegenerator.cpp \
    parse/sanparser.cpp \
    parse/epdparser.cpp \
    parse/epdposition.cpp \
    parse/fenparser.cpp \
    rules/position.cpp \
    rules/pieceset.cpp \
    rules/piece.cpp \
    rules/colorboard.cpp \
    rules/chessboard.cpp \
    rules/bitboard.cpp \
    rules/move.cpp \
    transposition_table/zobristhash.cpp \
    transposition_table/transpositiontable.cpp \
    evaluation/incrementalevaluator.cpp \
    evaluation/incrementalupdater.cpp \
    rules/movechecker.cpp \
    evaluation/resultevaluator.cpp \
    transposition_table/randomnumbers.cpp \
    rules/magicnumbers.cpp \
    rules/magicmoves.cpp \
    evaluation/kingsafetyevaluator.cpp \
    status.cpp \
    tablebases/tablebaseprober.cpp \
    tablebases/egbbprober.cpp \
    evaluation/tablebaseevaluator.cpp \
    transposition_table/pawntable.cpp \
    evaluation/pawnevaluator.cpp \
    evaluation/positionevaluator.cpp \
    transposition_table/hashstate.cpp \
    evaluation/compositeevaluator.cpp \
    search/openingbooksearcher.cpp \
    opening_book/openingbook.cpp \
    search/searchstatistics.cpp \
    search/searchstate.cpp \
    search/nodetype.cpp

HEADERS += \
    config.h \
    evaluation/positionevaluator.h \
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
    search/capturegenerator.h \
    search/thinkingwriter.h \
    search/nostopper.h \
    search/perft.h \
    search/searchcontext.h \
    search/nothinkingwriter.h \
    search/searcher.h \
    parse/sanparser.h \
    parse/epdparser.h \
    parse/epdposition.h \
    parse/fenparser.h \
    rules/position.h \
    rules/pieceset.h \
    rules/piece.h \
    rules/colorboard.h \
    rules/color.h \
    rules/chessboard.h \
    rules/bitboard.h \
    rules/move.h \
    transposition_table/zobristhash.h \
    transposition_table/lrucache.h \
    transposition_table/transpositiontable.h \
    evaluation/incrementalevaluator.h \
    evaluation/incrementalupdater.h \
    rules/undoinfo.h \
    rules/movechecker.h \
    evaluation/resultevaluator.h \
    transposition_table/randomnumbers.h \
    rules/magicnumbers.h \
    rules/magicmoves.h \
    search/searchstate.h \
    evaluation/incrementalstate.h \
    evaluation/kingsafetyevaluator.h \
    status.h \
    tablebases/tablebaseprober.h \
    tablebases/egbbprober.h \
    evaluation/tablebaseevaluator.h \
    transposition_table/pawntable.h \
    evaluation/pawnevaluator.h \
    transposition_table/hashstate.h \
    evaluation/compositeevaluator.h \
    search/openingbooksearcher.h \
    opening_book/openingbook.h \
    search/searchstatistics.h \
    search/nodetype.h

target.path = /usr/local/lib

INSTALLS += target

LIBS += -lyaml-cpp -gflags -ldl
