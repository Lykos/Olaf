#ifndef MATERIALEVALUATORTEST_H
#define MATERIALEVALUATORTEST_H

#include <QObject>
#include <QtTest/QTest>

#include "autotest.h"
#include "OlafSearching/materialevaluator.h"

namespace olaf
{
namespace test
{

class MaterialEvaluatorTest : public QObject
{
  Q_OBJECT

  MaterialEvaluator m_evaluator;

private Q_SLOTS:
  void test_evaluate_data();

  void test_evaluate();
};

DECLARE_TEST(MaterialEvaluatorTest)

} // namespace test
} // namespace olaf

#endif // MATERIALEVALUATORTEST_H
