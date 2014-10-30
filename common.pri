INCLUDEPATH += . ..
DEPENDPATH += . ..

VERSION=0.0.13

DEFINES += \
    VERSION=\\\"$$VERSION\\\" \
    VERSION_NAME=\\\"Killers\\\"

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror -pedantic
CONFIG(release, debug|release) QMAKE_CXXFLAGS += -O3
CONFIG(release, debug|release) DEFINES += NDEBUG
