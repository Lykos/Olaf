#ifndef BITBOARDTEST_H
#define BITBOARDTEST_H

#include <QObject>

#include "autotest.h"

class BitboardTest : public QObject
{
  Q_OBJECT
private Q_SLOTS:
  void test_number();

  void test_number_data();

  void test_positions();

  void test_positions_data();

  void test_get();

  void test_get_data();

  void test_set();

  void test_set_data();

};

DECLARE_TEST(BitboardTest)

#endif // BITBOARDTEST_H
