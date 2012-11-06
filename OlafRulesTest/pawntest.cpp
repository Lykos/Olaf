#include "pawntest.h"
#include "OlafRules/position.h"
#include "OlafRules/pawn.h"
#include "OlafRules/colorboard.h"
#include "OlafRules/pieceboard.h"
#include "OlafRules/pieceset.h"
#include "OlafRules/move.h"
#include <memory>
#include <iostream>

using namespace std;
Q_DECLARE_METATYPE(ChessBoard)
Q_DECLARE_METATYPE(Position)

void PawnTest::initTestCase()
{
  m_pawn = PieceSet::instance().pawn();
  m_board = create_empty_board();
  m_pawn_index = PieceSet::instance().pawn()->piece_index();
  m_knight_index = PieceSet::instance().knight()->piece_index();
  PieceBoard &pawn_board = m_board.turn_board().piece_board(m_pawn_index);
  PieceBoard &knight_board = m_board.turn_board().piece_board(m_knight_index);
  PieceBoard &opawn_board = m_board.noturn_board().piece_board(m_pawn_index);
  PieceBoard &oknight_board = m_board.noturn_board().piece_board(m_knight_index);

  pawn_board.set(Position(1, 0), true); // a2
  pawn_board.set(Position(4, 0), true); // a5
  pawn_board.set(Position(1, 1), true); // b2
  pawn_board.set(Position(1, 2), true); // c2
  pawn_board.set(Position(1, 3), true); // d2
  pawn_board.set(Position(1, 4), true); // e2
  pawn_board.set(Position(2, 5), true); // f3
  pawn_board.set(Position(3, 6), true); // g4
  pawn_board.set(Position(4, 7), true); // h5
  pawn_board.set(Position(6, 1), true); // b7
  pawn_board.set(Position(6, 2), true); // c7
  pawn_board.set(Position(6, 3), true); // d7
  opawn_board.set(Position(2, 1), true); // b3
  opawn_board.set(Position(4, 6), true); // g5
  knight_board.set(Position(3, 3), true); // d4
  knight_board.set(Position(2, 4), true); // e3
  knight_board.set(Position(5, 7), true); // h6
  knight_board.set(Position(7, 3), true); // d8
  oknight_board.set(Position(3, 2), true); // c4
  oknight_board.set(Position(4, 5), true); // f5
  oknight_board.set(Position(7, 1), true); // b8
  m_board.ep_possible(true);
  m_board.ep_capture_position(Position(5, 6)); // g6
  m_board.ep_victim_position(Position(4, 6)); // g5
}

void PawnTest::test_can_move_data()
{
  QTest::addColumn<Position>("source");
  QTest::addColumn<Position>("destination");
  QTest::addColumn<bool>("result");
  QTest::addColumn<bool>("is_capture");
  QTest::addColumn<bool>("is_conversion");

  QTest::newRow("start backwards a2a1") << Position(1, 0) << Position(0, 0) << false << false << false;
  QTest::newRow("nostart backwards f3f2") << Position(2, 5) << Position(1, 5) << false << false << false;
  QTest::newRow("start sidewards e2f2") << Position(1, 4) << Position(1, 4) << false << false << false;
  QTest::newRow("nostart sidewards h5g5") << Position(4, 7) << Position(4, 6) << false << false << false;
  QTest::newRow("start single move not blocked a2a3") << Position(1, 0) << Position(2, 0) << true << false << false;
  QTest::newRow("start single move own blocked e2e3") << Position(1, 4) << Position(2, 4) << false << false << false;
  QTest::newRow("start single move opponent blocked b2b3") << Position(1, 1) << Position(2, 1) << false << false << false;
  QTest::newRow("nostart single move not blocked f3f4") << Position(2, 5) << Position(3, 5) << true << false << false;
  QTest::newRow("nostart single move own blocked h5h6") << Position(4, 7) << Position(5, 7) << false << false << false;
  QTest::newRow("nostart single move opponent noblocked g4g5") << Position(3, 6) << Position(4, 6) << false << false << false;
  QTest::newRow("start double move not blocked a2a4") << Position(1, 0) << Position(3, 0) << true << false << false;
  QTest::newRow("start double move own direct blocked e2e4") << Position(1, 4) << Position(3, 4) << false << false << false;
  QTest::newRow("start double move own blocked d2d4") << Position(1, 3) << Position(3, 3) << false << false << false;
  QTest::newRow("start double move opponent direct blocked b2b4") << Position(1, 1) << Position(3, 1) << false << false << false;
  QTest::newRow("start double move opponent blocked c2c4") << Position(1, 2) << Position(3, 2) << false << false << false;
  QTest::newRow("nostart double move a5a7") << Position(4, 0) << Position(6, 0) << false << false << false;
  QTest::newRow("start opponent capture a2b3") << Position(1, 0) << Position(2, 1) << true << true << false;
  QTest::newRow("start own capture d2e3") << Position(1, 3) << Position(2, 4) << false << false << false;
  QTest::newRow("start empty capture b2a3") << Position(1, 1) << Position(2, 0) << false << false << false;
  QTest::newRow("nostart opponent capture g4f5") << Position(3, 6) << Position(4, 5) << true << true << false;
  QTest::newRow("nostart ep capture h5g6") << Position(4, 7) << Position(5, 6) << false << false << false;
  QTest::newRow("nostart own capture g4h5") << Position(3, 6) << Position(4, 7) << false << false << false;
  QTest::newRow("nostart empty capture f3e4") << Position(2, 5) << Position(3, 4) << false << false << false;
  QTest::newRow("conversion single move not blocked c7c8") << Position(6, 2) << Position(7, 2) << false << false << true;
  QTest::newRow("conversion single move own blocked d7d8") << Position(6, 3) << Position(7, 3) << false << false << false;
  QTest::newRow("conversion single move opponent blocked b7b8") << Position(6, 1) << Position(7, 1) << false << false << false;
  QTest::newRow("conversion empty capture b7c8") << Position(6, 1) << Position(7, 2) << false << false << false;
  QTest::newRow("conversion own capture c7d8") << Position(6, 2) << Position(7, 3) << false << false << false;
  QTest::newRow("conversion opponent capture c7b8") << Position(6, 2) << Position(7, 1) << false << true << true;
}

void PawnTest::test_can_move()
{
  QFETCH(Position, source);
  QFETCH(Position, destination);
  QFETCH(bool, result);
  QFETCH(bool, is_capture);
  QFETCH(bool, is_conversion);

  QCOMPARE(m_pawn->can_move(source, destination, m_board), result);
  if (result) {
    Move move = m_pawn->move(source, destination, m_board);
    QCOMPARE(move.is_capture(), is_capture);
  }
  if (is_conversion) {
    QVERIFY2(m_pawn->can_move(source, destination, m_board, m_knight_index), "Move does not work as a conversion.");
    Move move = m_pawn->move(source, destination, m_board, m_knight_index);
    QCOMPARE(move.is_capture(), is_capture);
    QVERIFY2(move.is_conversion(), "Conversion is not a conversion.");
    QCOMPARE(move.created_piece(), m_knight_index);
  } else {
    QVERIFY2(!m_pawn->can_move(source, destination, m_board, m_knight_index), "Move works as a conversion.");
  }
}

void PawnTest::test_moves_data()
{

}

void PawnTest::test_moves()
{

}
