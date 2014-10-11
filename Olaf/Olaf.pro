#-------------------------------------------------
#
# Project created by QtCreator 2012-10-28T11:33:16
#
#-------------------------------------------------

QT       -= core gui
TARGET = Olaf
CONFIG   += console
CONFIG   -= app_bundle
QMAKE_CXXFLAGS += -std=c++11 -Wl,--no-as-needed
CONFIG(release, debug|release) QMAKE_CXXFLAGS += -O3

TEMPLATE = app

SOURCES += main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../OlafRules-build-Desktop-Release/ -lOlafRules
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OlafRules-build-Desktop-Debug/ -lOlafRules
else:symbian: LIBS += -lOlafRules
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../OlafRules-build-Desktop-Release/ -lOlafRules
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OlafRules-build-Desktop-Debug/ -lOlafRules

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../OlafEvaluation-build-Desktop-Release/ -lOlafEvaluation
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OlafEvaluation-build-Desktop-Debug/ -lOlafEvaluation
else:symbian: LIBS += -lOlafRules
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../OlafEvaluation-build-Desktop-Release/ -lOlafEvaluation
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OlafEvaluation-build-Desktop-Debug/ -lOlafEvaluation

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../OlafSearching-build-Desktop-Release/ -lOlafSearching
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OlafSearching-build-Desktop-Debug/ -lOlafSearching
else:symbian: LIBS += -lOlafRules
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../OlafSearching-build-Desktop-Release/ -lOlafSearching
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OlafSearching-build-Desktop-Debug/ -lOlafSearching

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../OlafProtocols-build-Desktop-Release/ -lOlafProtocols
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OlafProtocols-build-Desktop-Debug/ -lOlafProtocols
else:symbian: LIBS += -lOlafRules
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../OlafProtocols-build-Desktop-Release/ -lOlafProtocols
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OlafProtocols-build-Desktop-Debug/ -lOlafProtocols

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../
