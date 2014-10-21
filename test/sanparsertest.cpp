#include "sanparsertest.h"

#include <QtTest/QTest>
#include <vector>
#include <iostream>

#include "testutil.h"
#include "olaf/rules/chessboard.h"
#include "olaf/rules/pieceset.h"
#include "olaf/parse/sanparser.h"
#include "olaf/search/searcherfactory.h"
#include "olaf/search/nothinkingwriter.h"

using namespace std;
using namespace testing;

namespace olaf
{
namespace test
{

void SanParserTest::initTestCase()
{
  NoThinkingWriter no_thinking_writer;
  SearcherFactory factory(&no_thinking_writer);
  m_parser = factory.san_parser();
}

void SanParserTest::test_parse_data()
{
  QTest::addColumn<ChessBoard>("board");
  QTest::addColumn<QString>("san");
  QTest::addColumn<Move>("move");

  QTest::newRow("initial pawnmove") << create_initial_board()
                                    << "e4"
                                    << Move::complete(Position("e2"), Position("e4"), create_initial_board());
  ChessBoard board = parse_fen("3k2n1/7P/n1Q2n2/3pP1QQ/2Q1Q1Q1/7p/8/R3K2R w KQ d6 0 1");
  QTest::newRow("pawn capture")
      << board << "exf6" << Move::complete(
                                 Position("e5"),
                                 Position("f6"),
                                 board);
  QTest::newRow("pawn promotion queen")
      << board << "h8=Q" << Move::complete(
                                 Position("h7"),
                                 Position("h8"),
                                 board);
  QTest::newRow("pawn promotion rook")
      << board << "h8=R" << Move::complete(
                                 Position("h7"),
                                 Position("h8"),
                                 board);
  QTest::newRow("pawn promotion bishop")
      << board << "h8=B" << Move::complete(
                                 Position("h7"),
                                 Position("h8"),
                                 board);
  QTest::newRow("pawn promotion knight")
      << board << "h8=N" << Move::complete(
                                 Position("h7"),
                                 Position("h8"),
                                 board);
  QTest::newRow("pawn promotion queen capture")
      << board << "hxg8=Q+" << Move::complete(
                                    Position("h7"),
                                    Position("g8"),
                                    board);
  QTest::newRow("pawn promotion rook capture")
      << board << "hxg8=R+" << Move::complete(
                                    Position("h7"),
                                    Position("g8"),
                                    board);
  QTest::newRow("pawn promotion bishop capture")
      << board << "hxg8=B" << Move::complete(
                                   Position("h7"),
                                   Position("g8"),
                                   board);
  QTest::newRow("pawn promotion knight capture")
      << board << "hxg8=N" << Move::complete(
                                   Position("h7"),
                                   Position("g8"),
                                   board);
  QTest::newRow("row disambiguation")
      << board << "Q4a4" << Move::complete(
                                 Position("c4"),
                                 Position("a4"),
                                 board);
  QTest::newRow("row disambiguation capture")
      << board << "Qgxh3" << Move::complete(
                                 Position("g4"),
                                 Position("h3"),
                                 board);
  QTest::newRow("column disambiguation")
      << board << "Qcc2" << Move::complete(
                                 Position("c4"),
                                 Position("c2"),
                                 board);
  QTest::newRow("column disambiguation capture")
      << board << "Q4xa6" << Move::complete(
                                  Position("c4"),
                                  Position("a6"),
                                  board);
  QTest::newRow("row and column disambiguation")
      << board << "Qg5h4" << Move::complete(
                                  Position("g5"),
                                  Position("h4"),
                                  board);
  QTest::newRow("row and column disambiguation capture")
      << board << "Qc4xd5" << Move::complete(
                                   Position("c4"),
                                   Position("d5"),
                                   board);
  QTest::newRow("ep")
      << board << "exd6" << Move::complete(
                                 Position("e5"),
                                 Position("d6"),
                                 board);
  QTest::newRow("castle q")
      << board << "O-O-O" << Move::complete(
                                  Position("e1"),
                                  Position("c1"),
                                  board);
  QTest::newRow("castle k")
      << board << "O-O" << Move::complete(
                                Position("e1"),
                                Position("g1"),
                                board);
}

void SanParserTest::test_parse()
{
  QFETCH(ChessBoard, board);
  QFETCH(QString, san);
  QFETCH(Move, move);

  Move actual_move;
  QVERIFY(m_parser->parse(san.toStdString(), board, &actual_move));
  QASSERT_THAT(actual_move, Eq(move));

} // namespace test
} // namespace olaf
}
