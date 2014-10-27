INCLUDEPATH += . ..
DEPENDPATH += . ..

VERSION=0.0.11

DEFINES += \
    VERSION=\\\"$$VERSION\\\" \
    VERSION_NAME=\\\"Static_exchange_evaluation\\\"

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror -pedantic
CONFIG(release, debug|release) QMAKE_CXXFLAGS += -O3
# CONFIG(release, debug|release) DEFINES += NDEBUG

OTHER_FILES += \
    ../start_game.txt
    ../epd_files/*
