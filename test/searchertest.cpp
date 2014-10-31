#include "searchertest.h"

#include "olaf/search/searcherfactory.h"
#include "olaf/search/searchcontext.h"
#include "olaf/search/searchresult.h"
#include "test/testutil.h"

using namespace testing;

namespace olaf
{
namespace test
{

const SearchContext::depth_t c_depth = 3;

void SearcherTest::init_test_case()
{
  m_searcher = m_factory_owner.factory.iterative_searcher();
  m_context.depth_mode = SearchContext::DepthMode::FIXED_DEPTH;
  m_context.search_depth = c_depth;
  m_context.forced_stopper = &m_stopper;
  m_context.weak_stopper = &m_stopper;
}

void SearcherTest::test_mate()
{
  m_context.board = parse_fen("7k/6Q1/5K2/6Bp/7P/6P1/8/8 b - - 0 84");
  const SearchResult& result = m_searcher->search(&m_context);
  QVERIFY(result.valid);
  QASSERT_THAT(result.depth, Ge(2));
  QVERIFY(result.terminal);
  QASSERT_THAT(result.score, Eq(-99998));
}

void SearcherTest::test_mate_in_one()
{
  m_context.board = parse_fen("7k/5Q2/5K2/6Bp/7P/6P1/8/8 w - - 0 84");
  const SearchResult& result = m_searcher->search(&m_context);
  QVERIFY(result.valid);
  QASSERT_THAT(result.depth, Ge(3));
  QVERIFY(result.terminal);
  QASSERT_THAT(result.score, Eq(99997));
  QASSERT_THAT(result.main_variation, SizeIs(Gt(0)));
}

void SearcherTest::test_stalemate_data()
{
  QTest::addColumn<ChessBoard>("board");

  //QTest::newRow("simple") << parse_fen("7k/5Q2/5K2/6Bp/7P/6P1/8/8 b - - 0 84");
  QTest::newRow("regression 1") << parse_fen("8/6pk/8/7P/7P/3bp3/4p3/4K3 b - - 0 116");
}

void SearcherTest::test_stalemate()
{
  QFETCH(ChessBoard, board);
  m_context.board = board;
  const SearchResult& result = m_searcher->search(&m_context);
  QVERIFY(result.valid);
  QASSERT_THAT(result.score, Eq(0));
  QVERIFY(result.terminal);
}

} // namespace test
} // namespace olaf
