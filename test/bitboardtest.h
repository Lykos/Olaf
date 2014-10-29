#ifndef BITBOARDTEST_H
#define BITBOARDTEST_H

#include <QObject>
#include "autotest.h"

namespace olaf
{
namespace test
{

class BitboardTest : public QObject
{
  Q_OBJECT

private Q_SLOTS:
  void test_number();

  void test_number_data();

  void test_next_position();

  void test_next_position_data();

  void test_get();

  void test_get_data();

  void test_set();

  void test_set_data();

};

DECLARE_TEST(BitboardTest)

} // namespace test
} // namespace olaf

#endif // BITBOARDTEST_H
