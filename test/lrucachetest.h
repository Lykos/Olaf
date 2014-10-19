#ifndef PAWNTEST_H
#define PAWNTEST_H

#include "autotest.h"
#include <QtTest/QTest>
#include <QObject>

namespace olaf
{
namespace test
{

class LruCacheTest : public QObject
{
  Q_OBJECT

private Q_SLOTS:
  void test_get_set();

};

DECLARE_TEST(LruCacheTest)

} // namespace test
} // namespace olaf

#endif // PAWNTEST_H
