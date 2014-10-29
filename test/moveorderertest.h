#ifndef MOVEORDERERTEST_H
#define MOVEORDERERTEST_H

#include "test/autotest.h"
#include "test/testutil.h"
#include <string>
#include <QtTest/QTest>
#include <QObject>

namespace olaf
{
namespace test
{

class MoveOrdererTest : public QObject
{
  Q_OBJECT

private Q_SLOTS:
  void test_order_data();

  void test_order();

  void test_see_data();

  void test_see();

};

DECLARE_TEST(MoveOrdererTest)

} // namespace test
} // namespace olaf

#endif // MOVEORDERERTEST_H
