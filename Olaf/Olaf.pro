#-------------------------------------------------
#
# Project created by QtCreator 2012-10-28T11:33:16
#
#-------------------------------------------------

QT       -= core gui
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
    simplemovegenerator.cpp \
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
    xboardreader.cpp \
    xboardwriter.cpp \
    searchresult.cpp \
    enginefactory.cpp \
    searcher.cpp \
    materialevaluator.cpp \
    negamaxer.cpp \
    nomoveorderer.cpp \
    engineproducer.cpp \
    enginestate.cpp

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
    simplemovegenerator.h \
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
    position.h \
    protocolreader.h \
    protocolwriter.h \
    xboardreader.h \
    xboardwriter.h \
    result.h \
    searchresult.h \
    searcher.h \
    moveorderer.h \
    enginefactory.h \
    positionevaluator.h \
    materialevaluator.h \
    negamaxer.h \
    nomoveorderer.h \
    engineproducer.h \
    enginestate.h \
    engineevent.h


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../OlafRules-build-desktop-Release/ -lOlafRules
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OlafRules-build-desktop-Debug/ -lOlafRules
else:symbian: LIBS += -lOlafRules
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../OlafRules-build-desktop-Release/ -lOlafRules
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OlafRules-build-desktop-Debug/ -lOlafRules

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../OlafSearching-build-desktop-Release/ -lOlafSearching
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OlafSearching-build-desktop-Debug/ -lOlafSearching
else:symbian: LIBS += -lOlafRules
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../OlafSearching-build-desktop-Release/ -lOlafSearching
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OlafSearching-build-desktop-Debug/ -lOlafSearching

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../
