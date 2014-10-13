#-------------------------------------------------
#
# Project created by QtCreator 2012-11-04T14:23:35
#
#-------------------------------------------------

include(../common.pri)

QT       -= core gui

TEMPLATE = lib

DEFINES += OLAFEVALUATION_LIBRARY

SOURCES += \
    materialevaluator.cpp \
    evaluatorfactory.cpp \
    config.cpp

HEADERS += \
    positionevaluator.h \
    materialevaluator.h \
    evaluatorfactory.h \
    config.h

header_files.files = $$HEADERS
header_files.path = /usr/local/include/OlafEvaluation

target.path = /usr/local/lib
INSTALLS += target

CONFIG(release, debug|release): LIBS += -L../OlafRules -lOlafRules
CONFIG(debug, debug|release): LIBS += -L../OlafRules -lOlafRules

LIBS += -lyaml-cpp
