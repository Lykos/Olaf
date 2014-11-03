INCLUDEPATH += . ..
DEPENDPATH += . ..

VERSION=0.0.14

DEFINES += \
    VERSION=\\\"$$VERSION\\\" \
    VERSION_NAME=\\\"Better_positions_and_pieces\\\"

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror -pedantic
CONFIG(release, debug|release) QMAKE_CXXFLAGS += -O3
CONFIG(release, debug|release) DEFINES += NDEBUG
