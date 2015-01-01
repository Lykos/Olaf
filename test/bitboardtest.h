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

  void test_one_up();

  void test_one_up_data();

  void test_one_down();

  void test_one_down_data();

  void test_one_left();

  void test_one_left_data();

  void test_one_right();

  void test_one_right_data();

  void test_north_fill();

  void test_north_fill_data();

  void test_south_fill();

  void test_south_fill_data();

};

DECLARE_TEST(BitboardTest)

} // namespace test
} // namespace olaf

#endif // BITBOARDTEST_H
