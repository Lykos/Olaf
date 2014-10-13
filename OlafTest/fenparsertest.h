#ifndef FENPARSERTEST_H
#define FENPARSERTEST_H

#include <QObject>
#include <QtTest/QTest>
#include "autotest.h"

class FenParserTest : public QObject
{
  Q_OBJECT
private Q_SLOTS:
  void test_serialize_data();

  void test_serialize();

  void test_parse_data();

  void test_parse();
};

DECLARE_TEST(FenParserTest)

#endif // FENPARSERTEST_H
