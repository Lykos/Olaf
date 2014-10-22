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

SearcherTest::SearcherTest():
  m_searcher(move(SearcherFactory(&m_no_thinking_writer).iterative_searcher()))
{}

void SearcherTest::test_mate()
{
  SearchContext context;
  context.board = parse_fen("7k/6Q1/5K2/6Bp/7P/6P1/8/8 b - - 0 84");
  context.depth_mode = SearchContext::DepthMode::FIXED_DEPTH;
  context.search_depth = 2;
  context.forced_stopper = &m_stopper;
  context.weak_stopper = &m_stopper;
  const SearchResult& result = m_searcher->search(&context);
  QVERIFY(result.valid);
  QASSERT_THAT(result.depth, Eq(2));
  QASSERT_THAT(result.score, Le(-40000));
}

void SearcherTest::test_mate_in_one()
{
  SearchContext context;
  context.board = parse_fen("7k/5Q2/5K2/6Bp/7P/6P1/8/8 w - - 0 84");
  context.depth_mode = SearchContext::DepthMode::FIXED_DEPTH;
  context.search_depth = 3;
  context.forced_stopper = &m_stopper;
  context.weak_stopper = &m_stopper;
  const SearchResult& result = m_searcher->search(&context);
  QVERIFY(result.valid);
  QASSERT_THAT(result.depth, Eq(3));
  QASSERT_THAT(result.score, Ge(40000));
  QASSERT_THAT(result.main_variation, SizeIs(Gt(0)));
}

void SearcherTest::test_stalemate()
{
  SearchContext context;
  context.board = parse_fen("7k/5Q2/5K2/6Bp/7P/6P1/8/8 b - - 0 84");
  context.depth_mode = SearchContext::DepthMode::FIXED_DEPTH;
  context.search_depth = 2;
  context.forced_stopper = &m_stopper;
  context.weak_stopper = &m_stopper;
  const SearchResult& result = m_searcher->search(&context);
  QVERIFY(result.valid);
  QASSERT_THAT(result.score, Eq(0));
  QASSERT_THAT(result.main_variation, SizeIs(0));
}

} // namespace test
} // namespace olaf
