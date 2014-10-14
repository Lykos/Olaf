#include "fenparsertest.h"

#include <QtTest/QTest>
#include <iostream>
#include <string>

#include "OlafRules/fenparser.h"
#include "OlafRules/chessboard.h"
#include "OlafRules/pieceset.h"
#include "OlafRules/piece.h"

using namespace std;

Q_DECLARE_METATYPE(ChessBoard)

static ChessBoard create_ep_board()
{
  ChessBoard board = create_empty_board();
  Piece::piece_index_t pawn_index = PieceSet::instance().pawn().piece_index();
  Piece::piece_index_t knight_index = PieceSet::instance().knight().piece_index();
  PieceBoard &pawn_board = board.turn_board().piece_board(pawn_index);
  PieceBoard &knight_board = board.turn_board().piece_board(knight_index);
  PieceBoard &opawn_board = board.noturn_board().piece_board(pawn_index);
  PieceBoard &oknight_board = board.noturn_board().piece_board(knight_index);

  pawn_board.set(Position("a2"), true);
  pawn_board.set(Position("a5"), true);
  pawn_board.set(Position("b2"), true);
  pawn_board.set(Position("c2"), true);
  pawn_board.set(Position("d2"), true);
  pawn_board.set(Position("e2"), true);
  pawn_board.set(Position("f3"), true);
  pawn_board.set(Position("g4"), true);
  pawn_board.set(Position("h5"), true);
  pawn_board.set(Position("b7"), true);
  pawn_board.set(Position("c7"), true);
  pawn_board.set(Position("d7"), true);
  opawn_board.set(Position("b3"), true);
  opawn_board.set(Position("g5"), true);
  knight_board.set(Position("d4"), true);
  knight_board.set(Position("e3"), true);
  knight_board.set(Position("h6"), true);
  knight_board.set(Position("d8"), true);
  oknight_board.set(Position("c4"), true);
  oknight_board.set(Position("f5"), true);
  oknight_board.set(Position("b8"), true);
  board.ep_possible(true);
  board.ep_capture_position(Position("g6"));
  board.ep_victim_position(Position("g5"));
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
  QTest::newRow("empty board ignores ply")
      << "8/8/8/8/8/8/8/8 w - - 10 1"
      << true
      << false
      << create_empty_board();
  QTest::newRow("empty board ignores suffix")
      << "8/8/8/8/8/8/8/8 w - - 0 1asdflkjadsflkjadsf"
      << true
      << false
      << create_empty_board();
  ChessBoard board = create_empty_board();
  board.turn_number(100);
  board.turn_color(Color::Black);
  QTest::newRow("empty board blacks turn")
      << "8/8/8/8/8/8/8/8 b - - 0 100"
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
  QCOMPARE(FenParser::parse(fen.toStdString(), &actual_board), parseable);
  if (parseable) {
    QFETCH(ChessBoard, board);
    QCOMPARE(board, actual_board);
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
    QCOMPARE(FenParser::serialize(board), fen.toStdString());
  }
}
