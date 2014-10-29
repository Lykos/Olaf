INCLUDEPATH += . ..
DEPENDPATH += . ..

VERSION=0.0.12

DEFINES += \
    VERSION=\\\"$$VERSION\\\" \
    VERSION_NAME=\\\"Magic_moves\\\"

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror -pedantic
CONFIG(release, debug|release) QMAKE_CXXFLAGS += -O3
# CONFIG(release, debug|release) DEFINES += NDEBUG

OTHER_FILES += \
    ../epd_files/*
