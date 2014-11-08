#ifndef EPDPARSERTEST_H
#define EPDPARSERTEST_H

#include <QObject>
#include <memory>

#include "test/autotest.h"
#include "test/testutil.h"
#include "olaf/parse/sanparser.h"
#include "olaf/parse/epdparser.h"

namespace olaf
{
namespace test
{

class EpdParserTest : public QObject
{
  Q_OBJECT

private:
  TestFactoryOwner m_factory_owner;

  std::unique_ptr<EpdParser> m_parser;

private Q_SLOTS:
  void initTestCase();

  void test_parse();

};

DECLARE_TEST(EpdParserTest)

} // namespace test
} // namespace olaf

#endif // EPDPARSERTEST_H
