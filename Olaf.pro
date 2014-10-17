TEMPLATE = subdirs

CONFIG += ordered
SUBDIRS += \
    OlafSearching \
    OlafProtocols \
    OlafTest \
    OlafMain \
    OlafBenchmark

OlafProtocols.depends = \
    OlafSearching

OlafTest.depends = \
    OlafSearching \
    OlafProtocols

OlafMain.depends = \
    OlafProtocols \
    OlafSearching

OlafBenchmark.depends = \
    OlafProtocols \
    OlafSearching
