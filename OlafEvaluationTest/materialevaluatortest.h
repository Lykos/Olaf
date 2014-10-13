#ifndef MATERIALEVALUATORTEST_H
#define MATERIALEVALUATORTEST_H

#include <QObject>
#include <QtTest/QTest>

#include "OlafEvaluation/materialevaluator.h"

class MaterialEvaluatorTest : public QObject
{
  Q_OBJECT

  MaterialEvaluator m_evaluator;

private Q_SLOTS:
  void test_evaluate_data();

  void test_evaluate();
};

#endif // MATERIALEVALUATORTEST_H
