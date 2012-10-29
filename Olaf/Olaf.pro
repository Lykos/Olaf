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
    xboardprotocol.cpp \
    bitboard.cpp \
    colorboard.cpp \
    pieceboard.cpp \
    chessboard.cpp \
    position.cpp \
    pawndoublemove.cpp \
    anticastlemove.cpp \
    castlemove.cpp \
    initialboardcreator.cpp \
    move.cpp \
    simplemoveaction.cpp \
    color.cpp \
    pawn.cpp \
    bishop.cpp \
    piece.cpp \
    linepiece.cpp

HEADERS += \
    xboardprotocol.h \
    bitboard.h \
    colorboard.h \
    color.h \
    bitboard.h \
    pieceboard.h \
    colorboard.h \
    chessboard.h \
    color.h \
    position.h \
    pawndoublemove.h \
    anticastlemove.h \
    castlemove.h \
    initialboardcreator.h \
    move.h \
    simplemoveaction.h \
    moveaction.h \
    pawn.h \
    piece.h \
    linepiece.h
