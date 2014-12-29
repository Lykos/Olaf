INCLUDEPATH += . ..
DEPENDPATH += . ..

VERSION=0.0.17

DEFINES += \
    VERSION=\\\"$$VERSION\\\" \
    VERSION_NAME=\\\"Pawn_shield\\\"

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror -pedantic
CONFIG(release, debug|release) QMAKE_CXXFLAGS += -O3 -g
CONFIG(release, debug|release) DEFINES += NDEBUG
