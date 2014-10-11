TEMPLATE = subdirs

CONFIG += ordered
SUBDIRS += \
    OlafRules \
    OlafRulesTest \
    OlafEvaluation \
    OlafEvaluationTest \
    OlafSearching \
    OlafProtocols \
    OlafMain

OlafRulesTest.depends = OlafRules

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

OlafMain.depends = \
    OlafEvaluation \
    OlafProtocols \
    OlafRules \
    OlafSearching
