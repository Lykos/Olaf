#-------------------------------------------------
#
# Project created by QtCreator 2014-10-11T15:17:28
#
#-------------------------------------------------

include(../common.pri)

QT       += testlib

QT       -= gui

TARGET = tst_olafevaluationtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_olafevaluationtest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Olaf-Desktop-Release/OlafRules -lOlafRules
CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Olaf-Desktop-Debug/OlafRules -lOlafRules

CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Olaf-Desktop-Release/OlafEvaluation -lOlafEvaluation
CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Olaf-Desktop-Debug/OlafEvaluation -lOlafEvaluation
