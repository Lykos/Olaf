#ifndef PERFTTEST_H
#define PERFTTEST_H

#include <QObject>
#include <QtTest/QTest>
#include <memory>
#include "autotest.h"

class PerftTest : public QObject
{
  Q_OBJECT

private Q_SLOTS:
  void test_perft_data();

  void test_perft();
};

DECLARE_TEST(PerftTest)

#endif // PERFTTEST_H
