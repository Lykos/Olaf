#ifndef SANPARSERTEST_H
#define SANPARSERTEST_H

#include <QObject>
#include <memory>

#include "autotest.h"
#include "olaf/sanparser.h"

namespace olaf
{
namespace test
{

class SanParserTest : public QObject
{
  Q_OBJECT
private:
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
