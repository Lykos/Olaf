#ifndef SANPARSERTEST_H
#define SANPARSERTEST_H

#include <QObject>
#include <memory>

#include "autotest.h"
#include "olaf/parse/sanparser.h"
#include "testutil.h"

namespace olaf
{
namespace test
{

class SanParserTest : public QObject
{
  Q_OBJECT
private:
  TestFactoryOwner m_factory_owner;

  std::unique_ptr<SanParser> m_parser;

private Q_SLOTS:
  void initTestCase();

  void test_parse_data();

  void test_parse();
};

DECLARE_TEST(SanParserTest)

} // namespace test
} // namespace olaf

#endif // SANPARSERTEST_H
