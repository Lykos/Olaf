#-------------------------------------------------
#
# Project created by QtCreator 2012-11-03T12:31:44
#
#-------------------------------------------------

include(../common.pri)

QT       -= core gui

TARGET = OlafRules
TEMPLATE = lib
QMAKE_CXXFLAGS += -march=native -mtune=native

DEFINES += OLAFRULES_LIBRARY

SOURCES += \
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
    setkingcapturepositionsaction.cpp

HEADERS += \
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
    setkingcapturepositionsaction.h

headers.files = $$HEADERS
headers.path = /usr/local/include/OlafRules

target.path = /usr/local/lib

INSTALLS += target
