#-------------------------------------------------
#
# Project created by QtCreator 2012-10-28T11:33:16
#
#-------------------------------------------------

include(../common.pri)

QT       -= core gui
TARGET = olaf
QMAKE_CXXFLAGS += -pthread -lpthread
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Olaf-Release/OlafRules -lOlafRules
CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Olaf-Debug/OlafRules -lOlafRules

CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Olaf-Release/OlafEvaluation -lOlafEvaluation
CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Olaf-Debug/OlafEvaluation -lOlafEvaluation

CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Olaf-Release/OlafSearching -lOlafSearching
CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Olaf-Debug/OlafSearching -lOlafSearching

CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Olaf-Release/OlafProtocols -lOlafProtocols
CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Olaf-Debug/OlafProtocols -lOlafProtocols

EXTRA_BINFILES += $$PWD/../start_game.txt
for (FILE, EXTRA_BINFILES){
    QMAKE_POST_LINK += $$quote(cp $${FILE} $$OUT_PWD$$escape_expand(\n\t))
}

LIBS += -lgflags

target.path = /usr/local/bin
INSTALLS += target
