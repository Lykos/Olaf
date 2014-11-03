#include "fenparsertest.h"

#include <QtTest/QTest>
#include <iostream>
#include <string>

#include "olaf/parse/fenparser.h"
#include "olaf/rules/chessboard.h"
#include "olaf/rules/pieceset.h"
#include "olaf/rules/piece.h"
#include "testutil.h"

using namespace std;
using namespace testing;

namespace olaf
{
namespace test
{

static ChessBoard create_ep_board()
{
  ChessBoard board = create_empty_board();
  Piece::piece_index_t pawn_index = PieceSet::c_pawn_index;
  Piece::piece_index_t knight_index = PieceSet::c_knight_index;

  board.add_piece(Color::White, pawn_index, Position("a2"));
  board.add_piece(Color::White, pawn_index, Position("a5"));
  board.add_piece(Color::White, pawn_index, Position("b2"));
  board.add_piece(Color::White, pawn_index, Position("c2"));
  board.add_piece(Color::White, pawn_index, Position("d2"));
  board.add_piece(Color::White, pawn_index, Position("e2"));
  board.add_piece(Color::White, pawn_index, Position("f3"));
  board.add_piece(Color::White, pawn_index, Position("g4"));
  board.add_piece(Color::White, pawn_index, Position("h5"));
  board.add_piece(Color::White, pawn_index, Position("b7"));
  board.add_piece(Color::White, pawn_index, Position("c7"));
  board.add_piece(Color::White, pawn_index, Position("d7"));
  board.add_piece(Color::Black, pawn_index, Position("b3"));
  board.add_piece(Color::Black, pawn_index, Position("g5"));
  board.add_piece(Color::White, knight_index, Position("d4"));
  board.add_piece(Color::White, knight_index, Position("e3"));
  board.add_piece(Color::White, knight_index, Position("h6"));
  board.add_piece(Color::White, knight_index, Position("d8"));
  board.add_piece(Color::Black, knight_index, Position("c4"));
  board.add_piece(Color::Black, knight_index, Position("f5"));
  board.add_piece(Color::Black, knight_index, Position("b8"));
  board.ep_captures(BitBoard(Position("g6")));
  return board;
}

void FenParserTest::test_parse_data()
{
  QTest::addColumn<QString>("fen");
  QTest::addColumn<bool>("parseable");
  QTest::addColumn<bool>("serializable");
  QTest::addColumn<ChessBoard>("board");

  QTest::newRow("initial board")
      << "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
      << true
      << true
      << create_initial_board();
  QTest::newRow("empty board")
      << "8/8/8/8/8/8/8/8 w - - 0 1"
      << true
      << true
      << create_empty_board();
  QTest::newRow("empty board no moves")
      << "8/8/8/8/8/8/8/8 w - -"
      << true
      << false
      << create_empty_board();
  QTest::newRow("empty board ignores suffix")
      << "8/8/8/8/8/8/8/8 w - - 0 1asdflkjadsflkjadsf"
      << true
      << false
      << create_empty_board();
  ChessBoard board = create_empty_board();
  board.reversible_plies(30);
  board.turn_number(100);
  board.turn_color(Color::Black);
  QTest::newRow("empty board blacks turn")
      << "8/8/8/8/8/8/8/8 b - - 30 100"
      << true
      << true
      << board;
  QTest::newRow("row with ep")
      << "1n1N4/1PPP4/7N/P4npP/2nN2P1/1p2NP2/PPPPP3/8 w - g6 0 1"
      << true
      << true
      << create_ep_board();
  QTest::newRow("wrong number of rows")
      << "8/8/8/8/8/8/8/8/8 w - - 0 1"
      << false
      << false;
  QTest::newRow("wrong number of columns with pieces")
      << "8/8/8/8/8/8/8/8p w - - 0 1"
      << false
      << false;
  QTest::newRow("wrong number of columns big number")
      << "8/8/8/8/8/8/8/9 w - - 0 1"
      << false
      << false;
  QTest::newRow("wrong color")
      << "8/8/8/8/8/8/8/8 W - - 0 1"
      << false
      << false;
  QTest::newRow("wrong ep column")
      << "8/8/8/8/8/8/8/8 W y5 - 0 1"
      << false
      << false;
  QTest::newRow("wrong ep row")
      << "8/8/8/8/8/8/8/8 W c5 - 0 1"
      << false
      << false;
  QTest::newRow("wrong castling")
      << "8/8/8/8/8/8/8/8 W - C 0 1"
      << false
      << false;
  QTest::newRow("wrong ply number")
      << "8/8/8/8/8/8/8/8 W - - a 1"
      << false
      << false;
  QTest::newRow("wrong move number")
      << "8/8/8/8/8/8/8/8 W - - 0 a"
      << false
      << false;
}

void FenParserTest::test_parse()
{
  QFETCH(QString, fen);
  QFETCH(bool, parseable);
  ChessBoard actual_board;
  QASSERT_THAT(FenParser::parse(fen.toStdString(), &actual_board).ok(), Eq(parseable));
  if (parseable) {
    QFETCH(ChessBoard, board);
    QASSERT_THAT(actual_board, Eq(board));
  }
}

void FenParserTest::test_serialize_data()
{
  test_parse_data();
}

void FenParserTest::test_serialize()
{
  QFETCH(bool, serializable);
  if (serializable) {
    QFETCH(QString, fen);
    QFETCH(ChessBoard, board);
    QASSERT_THAT(fen.toStdString(), Eq(FenParser::serialize(board)));
  }

} // namespace test
} // namespace olaf
}
