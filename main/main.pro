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

CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Olaf-Release/olaf -lolaf
CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Olaf-Debug/olaf -lolaf

CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Olaf-Release/protocols -lolafprotocols
CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Olaf-Debug/protocols -lolafprotocols

OTHER_FILES += \
    config.yml \
    ../resources/move_table.bin

config.path = /usr/local/share/olaf
config.files = $$OTHER_FILES

LIBS += -lgflags

target.path = /usr/local/bin

INSTALLS += target config

