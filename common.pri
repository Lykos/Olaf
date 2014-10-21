INCLUDEPATH += . ..
DEPENDPATH += . ..

VERSION=0.0.10

DEFINES += \
    VERSION=\\\"$$VERSION\\\" \
    VERSION_NAME=\\\"Better_move_representation\\\"

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror -pedantic
CONFIG(release, debug|release) QMAKE_CXXFLAGS += -O3

OTHER_FILES += \
    ../start_game.txt
    ../epd_files/*
