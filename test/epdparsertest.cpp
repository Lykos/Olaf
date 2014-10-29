#include "epdparsertest.h"

#include <QtTest/QTest>
#include <string>

#include "olaf/search/searcherfactory.h"
#include "olaf/parse/epdparser.h"
#include "olaf/parse/epdposition.h"
#include "olaf/search/nothinkingwriter.h"
#include "olaf/rules/movechecker.h"
#include "testutil.h"

using namespace std;
using namespace testing;

namespace olaf
{
namespace test
{

void EpdParserTest::initTestCase()
{
  m_parser = m_factory_owner.factory.epd_parser();
}

void EpdParserTest::test_parse()
{
  const string epd = "1k1r4/pp1b1R2/3q2pp/4p3/2B5/4Q3/PPP2B2/2K5 b - - bm Qd1+; id \"BK.01\"";
  EpdPosition position;
  QVERIFY(m_parser->parse(epd, &position));
  const Move move = MoveChecker::complete(Position("d6"), Position("d1"), position.board);
  QASSERT_THAT(position.id, Eq(string("BK.01")));
  QASSERT_THAT(position.best_moves, ElementsAre(move));
}

} // namespace test
} // namespace olaf
