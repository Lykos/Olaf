#include "fenparsertest.h"

#include <QtTest/QTest>
#include <iostream>
#include <string>

#include "OlafRules/fenparser.h"
#include "OlafRules/chessboard.h"

using namespace std;

Q_DECLARE_METATYPE(ChessBoard)

void FenParserTest::test_parse_data()
{
  QTest::addColumn<QString>("fen");
  QTest::addColumn<ChessBoard>("board");

  QTest::newRow("initial board")
      << QString("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1")
      << create_initial_board();
  QTest::newRow("empty board")
      << QString("8/8/8/8/8/8/8/8 w - - 0 1")
      << create_empty_board();
}

void FenParserTest::test_parse()
{
  QFETCH(QString, fen);
  QFETCH(ChessBoard, board);
  ChessBoard actual_board;
  QVERIFY(FenParser::parse(fen.toStdString(), &actual_board));
  QCOMPARE(board, actual_board);
}
