#-------------------------------------------------
#
# Project created by QtCreator 2012-11-04T14:23:35
#
#-------------------------------------------------

QT       -= core gui

TARGET = OlafEvaluation
TEMPLATE = lib
QMAKE_CXXFLAGS += -std=c++11
CONFIG(release, debug|release) QMAKE_CXXFLAGS += -O3

DEFINES += OLAFEVALUATION_LIBRARY

SOURCES += \
    materialevaluator.cpp \
    evaluatorfactory.cpp

HEADERS += \
    positionevaluator.h \
    materialevaluator.h \
    evaluatorfactory.h

header_files.files = $$HEADERS
header_files.path = /usr/local/include/OlafEvaluation

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/local/lib
    } else {
        target.path = /usr/local/lib
    }
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../OlafRules-build-Desktop-Release/ -lOlafRules
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OlafRules-build-Desktop-Debug/ -lOlafRules
else:symbian: LIBS += -lOlafRules
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../OlafRules-build-Desktop-Release/ -lOlafRules
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OlafRules-build-Desktop-Debug/ -lOlafRules

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../
