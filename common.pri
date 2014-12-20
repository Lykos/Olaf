INCLUDEPATH += . ..
DEPENDPATH += . ..

VERSION=0.0.16

DEFINES += \
    VERSION=\\\"$$VERSION\\\" \
    VERSION_NAME=\\\"Principal_variation_search\\\"

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror -pedantic
CONFIG(release, debug|release) QMAKE_CXXFLAGS += -O3 -g
CONFIG(release, debug|release) DEFINES += NDEBUG
