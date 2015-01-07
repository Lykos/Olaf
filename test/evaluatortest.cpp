#include "evaluatortest.h"

#include "test/testutil.h"

using namespace std;
using namespace testing;

namespace olaf
{
namespace test
{

void EvaluatorTest::test_compare_data()
{
  QTest::addColumn<ChessBoard>("better_position");
  QTest::addColumn<ChessBoard>("worse_position");

  QTest::newRow("pawn shield before own king")
      << parse_fen("rnbqkbnr/2pppppp/8/8/8/5N1B/2PPPPPP/RNBQ1RK1 w kq - 0 1")
      << parse_fen("rnbqkbnr/2pppppp/8/8/8/5N1B/PPPPPP2/RNBQ1RK1 w kq - 0 1");
  QTest::newRow("semi open files against own king")
      << parse_fen("rnbqkbnr/2pppppp/8/8/8/5N1B/2PPPPPP/RNBQ1RK1 w kq - 0 1")
      << parse_fen("rnbqkbnr/2pppppp/8/8/8/5N1B/PPPPPP2/RNBQ1RK1 w kq - 0 1");
  QTest::newRow("open files are worse than missing pawn shield")
      << parse_fen("rnbqkbnr/2pppppp/8/8/8/5N1B/PPPPPP2/RNBQ1RK1 w kq - 0 1")
      << parse_fen("rnbqkbnr/pppppp2/8/8/8/5N1B/PPPPPP2/RNBQ1RK1 w kq - 0 1");
  QTest::newRow("open files are worse than semi open files against own king")
      << parse_fen("rnbqkbnr/pppppp2/8/8/8/5N1B/2PPPPPP/RNBQ1RK1 w kq - 0 1")
      << parse_fen("rnbqkbnr/pppppp2/8/8/8/5N1B/PPPPPP2/RNBQ1RK1 w kq - 0 1");
}

void EvaluatorTest::test_compare()
{
  QFETCH(ChessBoard, better_position);
  QFETCH(ChessBoard, worse_position);

  m_context.board = better_position;
  PositionEvaluator::score_t better_score = m_evaluator->evaluate(m_state, &m_context);
  m_context.board = worse_position;
  PositionEvaluator::score_t worse_score = m_evaluator->evaluate(m_state, &m_context);
  QASSERT_THAT(better_score, Gt(worse_score));
}

void EvaluatorTest::initTestCase()
{
  m_evaluator = m_factory_owner.factory.evaluator();
  SearchState initial_state{-numeric_limits<PositionEvaluator::score_t>::max(),
                            numeric_limits<PositionEvaluator::score_t>::max(),
                            0};
  m_state = initial_state;
}

} // namespace test
} // namespace olaf

