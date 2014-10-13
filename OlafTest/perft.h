#ifndef PERFT_H
#define PERFT_H

#include <QObject>
#include <QtTest/QTest>
#include "autotest.h"

class Perft : public QObject
{
  Q_OBJECT

private Q_SLOTS:
  void test_perft_data();

  void test_perft();
};

DECLARE_TEST(Perft)

#endif // PERFT_H
