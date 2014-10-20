#include "incrementalevaluatortest.h"

#include <QtTest/QTest>
#include <set>

#include "olaf/rules/chessboard.h"
#include "olaf/search/nothinkingwriter.h"
#include "olaf/search/searcherfactory.h"
#include "testutil.h"

using namespace testing;
using namespace std;

namespace olaf
{
namespace test
{

void IncrementalEvaluatorTest::init_test_case()
{
  NoThinkingWriter no_thinking_writer;
  SearcherFactory factory(&no_thinking_writer);
  m_generator = factory.move_generator();
}

void IncrementalEvaluatorTest::test_evaluate_data()
{
  QTest::addColumn<ChessBoard>("board");
  QTest::addColumn<int>("score");

  QTest::newRow("empty") << create_empty_board() << 0;
  QTest::newRow("initial") << create_initial_board() << 0;
  QTest::newRow("middlegame") << parse_fen("1k1r4/pp1b1R2/3q2pp/4p3/2B5/4Q3/PPP2B2/2K5 b - - 0 1") << -115;
}


void IncrementalEvaluatorTest::test_evaluate()
{
  QFETCH(ChessBoard, board);
  QFETCH(int, score);

  const int actual_score = board.incremental_score();
  IncrementalUpdater::calculate(&board);
  QASSERT_THAT(actual_score, Eq(score));
  QASSERT_THAT(m_evaluator.evaluate(board), Eq(score));
  for (Move& move : m_generator->generate_valid_moves(board)) {
    move.execute(&board);
    const int move_score = board.incremental_score();
    IncrementalUpdater::calculate(&board);
    QASSERT_THAT(board.incremental_score(), Eq(move_score));
    move.undo(&board);
    const int undo_score = board.incremental_score();
    IncrementalUpdater::calculate(&board);
    QASSERT_THAT(board.incremental_score(), Eq(undo_score));
    QASSERT_THAT(undo_score, Eq(score));
  }
}

} // namespace test
} // namespace olaf