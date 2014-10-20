#ifndef ZOBRISTHASHTEST_H
#define ZOBRISTHASHTEST_H

#include <QtTest/QTest>
#include <QObject>
#include <memory>

#include "autotest.h"
#include "olaf/search/movegenerator.h"

namespace olaf
{
namespace test
{

class ZobristHashTest : public QObject
{
  Q_OBJECT

private:
  std::unique_ptr<MoveGenerator> m_generator;

private Q_SLOTS:
  void init_test_case();

  void test_calculate();

  void test_calculate_data();
};

DECLARE_TEST(ZobristHashTest)

} // namespace test
} // namespace olaf

#endif // ZOBRISTHASHTEST_H
