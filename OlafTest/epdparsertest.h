#ifndef EPDPARSERTEST_H
#define EPDPARSERTEST_H

#include <QObject>
#include <memory>

#include "autotest.h"
#include "OlafSearching/epdparser.h"

class EpdParserTest : public QObject
{
  Q_OBJECT

private:
  std::unique_ptr<EpdParser> m_parser;

private Q_SLOTS:
  void initTestCase();

  void test_parse();

};

DECLARE_TEST(EpdParserTest)

#endif // EPDPARSERTEST_H
