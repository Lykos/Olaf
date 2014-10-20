#ifndef INCREMENTALEVALUATORTEST_H
#define INCREMENTALEVALUATORTEST_H

#include <QObject>
#include <QtTest/QTest>

#include "autotest.h"
#include "olaf/evaluation/incrementalevaluator.h"
#include "olaf/search/movegenerator.h"

namespace olaf
{
namespace test
{

class IncrementalEvaluatorTest : public QObject
{
  Q_OBJECT

private:
  IncrementalEvaluator m_evaluator;

  std::unique_ptr<MoveGenerator> m_generator;

private Q_SLOTS:
  void init_test_case();

  void test_evaluate_data();

  void test_evaluate();
};

DECLARE_TEST(IncrementalEvaluatorTest)

} // namespace test
} // namespace olaf

#endif // INCREMENTALEVALUATORTEST_H
