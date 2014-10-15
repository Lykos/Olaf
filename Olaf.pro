TEMPLATE = subdirs

CONFIG += ordered
SUBDIRS += \
    OlafRules \
    OlafEvaluation \
    OlafSearching \
    OlafProtocols \
    OlafTest \
    OlafMain \
    OlafBenchmark

OlafEvaluation.depends = OlafRules

OlafEvaluationTest.depends = \
    OlafRules \
    OlafEvaluation

OlafSearching.depends = \
    OlafEvaluation \
    OlafRules

OlafProtocols.depends = \
    OlafEvaluation \
    OlafRules \
    OlafSearching

OlafTest.depends = \
    OlafRules \
    OlafEvaluation \
    OlafSearching \
    OlafProtocols

OlafMain.depends = \
    OlafEvaluation \
    OlafProtocols \
    OlafRules \
    OlafSearching

OlafBenchmark.depends = \
    OlafEvaluation \
    OlafProtocols \
    OlafRules \
    OlafSearching
