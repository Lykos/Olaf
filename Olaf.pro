TEMPLATE = subdirs

CONFIG += ordered
SUBDIRS += \
    OlafRules \
    OlafEvaluation \
    OlafSearching \
    OlafProtocols \
    OlafTest \
    OlafMain

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

OlafRulesTest.depends = \
    OlafRules \
    OlafEvaluation \
    OlafSearching \
    OlafProtocols

OlafMain.depends = \
    OlafEvaluation \
    OlafProtocols \
    OlafRules \
    OlafSearching
