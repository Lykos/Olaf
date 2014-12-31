#ifndef EVALUATORTEST_H
#define EVALUATORTEST_H

#include <memory>
#include <QObject>

#include "test/autotest.h"
#include "test/testutil.h"
#include "olaf/evaluation/positionevaluator.h"
#include "olaf/search/searchcontext.h"
#include "olaf/search/searchstate.h"

namespace olaf
{
namespace test
{

class EvaluatorTest : public QObject
{
  Q_OBJECT
private:
  TestFactoryOwner m_factory_owner;

  std::unique_ptr<PositionEvaluator> m_evaluator;

  SearchContext m_context;

  SearchState m_state;

private Q_SLOTS:
  void initTestCase();

  void test_compare_data();

  void test_compare();
};

DECLARE_TEST(EvaluatorTest)

} // namespace test
} // namespace olaf

#endif // EVALUATORTEST_H

