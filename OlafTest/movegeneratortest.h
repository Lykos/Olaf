#ifndef MOVEGENERATORTEST_H
#define MOVEGENERATORTEST_H

#include <QObject>
#include <QtTest/QTest>

#include "autotest.h"

class MoveGeneratorTest : public QObject
{
  Q_OBJECT
private Q_SLOTS:
  void test_generate();

  void test_generate_data();
};

DECLARE_TEST(MoveGeneratorTest)

#endif // MOVEGENERATORTEST_H
