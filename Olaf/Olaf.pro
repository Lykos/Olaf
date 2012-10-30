#-------------------------------------------------
#
# Project created by QtCreator 2012-10-28T11:33:16
#
#-------------------------------------------------

TARGET = Olaf
CONFIG   += console
CONFIG   -= app_bundle
QMAKE_CXXFLAGS += -std=c++11
CONFIG(release, debug|release) QMAKE_CXXFLAGS += -O3

TEMPLATE = app


SOURCES += main.cpp \
    bitboard.cpp \
    positiondelta.cpp \
    colorboard.cpp \
    pieceboard.cpp \
    chessboard.cpp \
    position.cpp \
    move.cpp \
    pawn.cpp \
    linepiece.cpp \
    oncepiece.cpp \
    anticastleaction.cpp \
    captureaction.cpp \
    piecemoveaction.cpp \
    turnflipaction.cpp \
    epenableaction.cpp \
    epdisableaction.cpp \
    pieceset.cpp \
    conversionaction.cpp \
    piece.cpp \
    movegenerator.cpp \
    engine.cpp \
    xboardreader.cpp \
    xboardwriter.cpp \
    searchresult.cpp \
    searcher.cpp

HEADERS += \
    bitboard.h \
    colorboard.h \
    color.h \
    oncepiece.h \
    positiondelta.h \
    bitboard.h \
    pieceboard.h \
    colorboard.h \
    chessboard.h \
    color.h \
    move.h \
    moveaction.h \
    pawn.h \
    piece.h \
    linepiece.h \
    anticastleaction.h \
    captureaction.h \
    epenablaction.h \
    piecemoveaction.h \
    turnflipaction.h \
    epdisableaction.h \
    pieceset.h \
    conversionaction.h \
    movegenerator.h \
    engine.h \
    position.h \
    protocolreader.h \
    protocolwriter.h \
    xboardreader.h \
    xboardwriter.h \
    result.h \
    searchresult.h \
    searcher.h
