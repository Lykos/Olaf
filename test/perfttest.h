#ifndef PERFTTEST_H
#define PERFTTEST_H

#include <QObject>
#include <QtTest/QTest>
#include <memory>
#include "autotest.h"
#include "testutil.h"

namespace olaf
{
namespace test
{

class PerftTest : public QObject
{
  Q_OBJECT

private:
  TestFactoryOwner m_factory_owner;

private Q_SLOTS:
  void test_perft_data();

  void test_perft();
};

DECLARE_TEST(PerftTest)

} // namespace test
} // namespace olaf

#endif // PERFTTEST_H
