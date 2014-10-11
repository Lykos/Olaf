INCLUDEPATH += . ..
DEPENDPATH += . ..

WARNINGS += -Wall -Wextra -Werror -pedantic
QMAKE_CXXFLAGS += -std=c++11
CONFIG(release, debug|release) QMAKE_CXXFLAGS += -O3

OTHER_FILES += \
    ../start_game.txt
