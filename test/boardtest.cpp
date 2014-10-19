#include "boardtest.h"

#include "olaf/rules/chessboard.h"
#include "olaf/rules/pieceset.h"

namespace olaf
{
namespace test
{

BoardTest::BoardTest():
  m_bishop(PieceSet::instance().bishop().piece_index())
{}

void BoardTest::test_friends()
{
  ChessBoard board = create_empty_board();
  board.turn_board().piece_board(m_bishop).set(Position(4, 4), true);
  board.noturn_board().piece_board(m_bishop).set(Position(5, 2), true);
  BitBoard result (0);
  result.set(Position(4, 4), true);
  QCOMPARE(result, board.friends());
}

void BoardTest::test_opponents()
{
  ChessBoard board = create_empty_board();
  board.turn_board().piece_board(m_bishop).set(Position(4, 4), true);
  board.noturn_board().piece_board(m_bishop).set(Position(5, 2), true);
  BitBoard result (0);
  result.set(Position(5, 2), true);
  QCOMPARE(result, board.opponents());
}

void BoardTest::test_occupied()
{
  ChessBoard board = create_empty_board();
  board.turn_board().piece_board(m_bishop).set(Position(4, 4), true);
  board.noturn_board().piece_board(m_bishop).set(Position(5, 2), true);
  BitBoard result (0);
  result.set(Position(4, 4), true);
  result.set(Position(5, 2), true);
  QCOMPARE(result, board.occupied());

} // namespace test
} // namespace olaf
}
