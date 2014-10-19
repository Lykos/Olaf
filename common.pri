INCLUDEPATH += . ..
DEPENDPATH += . ..

VERSION=0.0.5

DEFINES += "VERSION=\\\"$$VERSION\\\""

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror -pedantic
CONFIG(release, debug|release) QMAKE_CXXFLAGS += -O3

OTHER_FILES += \
    ../start_game.txt
    ../epd_files/*
