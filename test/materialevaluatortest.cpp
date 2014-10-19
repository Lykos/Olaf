#include "materialevaluatortest.h"

#include <QtTest/QTest>

#include "olaf/rules/chessboard.h"
#include "testutil.h"

Q_DECLARE_METATYPE(olaf::ChessBoard)

namespace olaf
{
namespace test
{

typedef MaterialEvaluator::score_t score_t;

void MaterialEvaluatorTest::test_evaluate_data()
{
  QTest::addColumn<ChessBoard>("board");
  QTest::addColumn<score_t>("score");

  QTest::newRow("empty") << create_empty_board() << 0;
  QTest::newRow("initial") << create_initial_board() << 0;
  QTest::newRow("middlegame") << parse_fen("1k1r4/pp1b1R2/3q2pp/4p3/2B5/4Q3/PPP2B2/2K5 b - - 0 1") << -100;
}


void MaterialEvaluatorTest::test_evaluate()
{
  QFETCH(ChessBoard, board);
  QFETCH(score_t, score);

  QCOMPARE(m_evaluator.evaluate(board), score);

} // namespace test
} // namespace olaf
}
