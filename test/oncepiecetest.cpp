#include "oncepiecetest.h"

#include <vector>
#include <iostream>

#include "testutil.h"
#include "olaf/rules/pieceset.h"
#include "olaf/rules/move.h"
#include "olaf/rules/position.h"
#include "olaf/rules/movechecker.h"
#include "gmock/gmock-generated-matchers.h"

using namespace std;
using namespace testing;

namespace olaf
{
namespace test
{

void OncePieceTest::initTestCase()
{
  m_king = &(PieceSet::instance().king());
  m_knight = &(PieceSet::instance().knight());
  m_board = parse_fen("K6N/nK6/6N1/8/7N/4k3/6n1/R3K2R w KQ - 0 1");
  m_king_index = m_king->piece_index();
  m_knight_index = m_knight->piece_index();
}

void OncePieceTest::test_can_move_data()
{
  QTest::addColumn<Position>("source");
  QTest::addColumn<Position>("destination");
  QTest::addColumn<bool>("result");
  QTest::addColumn<bool>("is_capture");

  QTest::newRow("king non-existent e4e5")  << Position("e4") << Position("e5") << false << false;

  QTest::newRow("king corner a8a8")  << Position("a8") << Position("a8") << false << false;
  QTest::newRow("king corner a8b8")  << Position("a8") << Position("b8") << true << false;
  QTest::newRow("king corner capture a8a7")  << Position("a8") << Position("a7") << true << true;
  QTest::newRow("king corner friend a8b7")  << Position("a8") << Position("b7") << false << false;
  QTest::newRow("king corner jump straight a8a6")  << Position("a8") << Position("a6") << false << false;
  QTest::newRow("king corner jump diagonal a8c6")  << Position("a8") << Position("c6") << false << false;

  QTest::newRow("king wall e1f1")  << Position("e1") << Position("f1") << true << false;
  QTest::newRow("king wall e1d2")  << Position("e1") << Position("d2") << true << false;
  QTest::newRow("king wall e1e2")  << Position("e1") << Position("e2") << true << false;
  //QTest::newRow("king castle q e1c1")  << Position("e1") << Position("c1") << true << false;
  //QTest::newRow("king castle k e1g1")  << Position("e1") << Position("g1") << true << false;
  QTest::newRow("king wall jump e1e3")  << Position("e1") << Position("e3") << false << false;

  QTest::newRow("king middle friend b7a8")  << Position("b7") << Position("a8") << false << false;
  QTest::newRow("king middle b7c6")  << Position("b7") << Position("c6") << true << false;

  QTest::newRow("knight non-existent e4f6")  << Position("e4") << Position("f6") << false << false;

  QTest::newRow("knight corner h8f7")  << Position("h8") << Position("f7") << true << false;
  QTest::newRow("knight corner friend h8g6")  << Position("h8") << Position("g6") << false << false;

  QTest::newRow("knight middle g6f8")  << Position("g6") << Position("f8") << true << false;
  QTest::newRow("knight middle friend g6h8")  << Position("g6") << Position("h8") << false << false;
  QTest::newRow("knight middle friend g6h4")  << Position("g6") << Position("h4") << false << false;
  QTest::newRow("knight middle g6f4")  << Position("g6") << Position("f4") << true << false;
  QTest::newRow("knight middle jump g6e2")  << Position("g6") << Position("e2") << false << false;

  QTest::newRow("knight wall friend h4g6")  << Position("h4") << Position("g6") << false << false;
  QTest::newRow("knight wall h4f3")  << Position("h4") << Position("f3") << true << false;
  QTest::newRow("knight wall capture h4g2")  << Position("h4") << Position("g2") << true << true;
}

void OncePieceTest::test_can_move()
{
  QFETCH(Position, source);
  QFETCH(Position, destination);
  QFETCH(bool, result);
  QFETCH(bool, is_capture);
  const IncompleteMove incomplete_move = IncompleteMove(source, destination);
  QCOMPARE(MoveChecker::pseudo_valid_move(m_board, incomplete_move), result);
  if (result) {
    const Move move = MoveChecker::complete(incomplete_move, m_board);
    QCOMPARE(move.is_capture(), is_capture);
  }
}
/*
void OncePieceTest::test_moves_data()
{
  QTest::addColumn<ChessBoard>("board");
  QTest::addColumn<const Piece*>("piece");
  QTest::addColumn<Position>("source");
  QTest::addColumn<vector<Move>>("moves");

  {
    vector<Move> moves{
      MoveChecker::complete(Position("a8"), Position("b8"), m_board),
      MoveChecker::complete(Position("a8"), Position("a7"), m_board)
    };
    QTest::newRow("king a8") << m_board  << Position("a8") << moves;
  }
  {
    vector<Move> moves{
      MoveChecker::complete(Position("b7"), Position("b8"), m_board),
      MoveChecker::complete(Position("b7"), Position("c8"), m_board),
      MoveChecker::complete(Position("b7"), Position("a7"), m_board),
      MoveChecker::complete(Position("b7"), Position("c7"), m_board),
      MoveChecker::complete(Position("b7"), Position("a6"), m_board),
      MoveChecker::complete(Position("b7"), Position("b6"), m_board),
      MoveChecker::complete(Position("b7"), Position("c6"), m_board)
    };
    QTest::newRow("king b7") << m_board  << Position("b7") << moves;
  }
  {
    vector<Move> moves{
      MoveChecker::complete(Position("e1"), Position("d1"), m_board),
      MoveChecker::complete(Position("e1"), Position("f1"), m_board),
      MoveChecker::complete(Position("e1"), Position("d2"), m_board),
      MoveChecker::complete(Position("e1"), Position("e2"), m_board),
      MoveChecker::complete(Position("e1"), Position("f2"), m_board),
      MoveChecker::complete(Position("e1"), Position("c1"), m_board),
      MoveChecker::complete(Position("e1"), Position("g1"), m_board)
    };
    ChessBoard board = m_board;
    // Remove extra kings to make castling work.
    board.remove_piece(Color::White, PieceSet::c_king_index, Position("a8"));
    board.remove_piece(Color::White, PieceSet::c_king_index, Position("b7"));
    QTest::newRow("king e1") << board  << Position("e1") << moves;
  }
  {
    vector<Move> moves{
      MoveChecker::complete(Position("h8"), Position("f7"), m_board)
    };
    QTest::newRow("knight h8") << m_board  << Position("h8") << moves;
  }
  {
    vector<Move> moves{
      MoveChecker::complete(Position("g6"), Position("f8"), m_board),
      MoveChecker::complete(Position("g6"), Position("e7"), m_board),
      MoveChecker::complete(Position("g6"), Position("e5"), m_board),
      MoveChecker::complete(Position("g6"), Position("f4"), m_board)
    };
    QTest::newRow("knight g6") << m_board  << Position("g6") << moves;
  }
  {
    vector<Move> moves{
      MoveChecker::complete(Position("h4"), Position("f5"), m_board),
      MoveChecker::complete(Position("h4"), Position("f3"), m_board),
      MoveChecker::complete(Position("h4"), Position("g2"), m_board)
    };
    QTest::newRow("knight h4") << m_board  << Position("h4") << moves;
  }
}

void OncePieceTest::test_moves()
{
  QFETCH(ChessBoard, board);
  QFETCH(const Piece*, piece);
  QFETCH(Position, source);
  QFETCH(vector<Move>, moves);

  const vector<Move>& actual_moves = piece->moves(source, board);
  QASSERT_THAT(actual_moves, UnorderedElementsAreArray(moves));
}
*/
} // namespace test
} // namespace olaf

