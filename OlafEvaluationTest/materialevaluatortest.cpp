#include "materialevaluatortest.h"

#include <QtTest/QTest>

#include "OlafRules/chessboard.h"

typedef MaterialEvaluator::score_t score_t;

Q_DECLARE_METATYPE(ChessBoard)

void MaterialEvaluatorTest::test_evaluate_data()
{
  QTest::addColumn<ChessBoard>("board");
  QTest::addColumn<score_t>("score");

  QTest::newRow("empty") << create_empty_board() << 0;
  QTest::newRow("initial") << create_initial_board() << 0;
}


void MaterialEvaluatorTest::test_evaluate()
{
  QFETCH(ChessBoard, board);
  QFETCH(score_t, score);

  QCOMPARE(m_evaluator.evaluate(board), score);
}
