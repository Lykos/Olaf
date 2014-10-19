#ifndef PAWNTEST_H
#define PAWNTEST_H

#include "olaf/rules/chessboard.h"
#include "olaf/rules/piece.h"
#include "olaf/rules/pawn.h"
#include "autotest.h"
#include <QtTest/QTest>
#include <QObject>

namespace olaf
{
namespace test
{

class PawnTest : public QObject
{
  Q_OBJECT

private:
  ChessBoard m_board;

  Piece::piece_index_t m_pawn_index;

  Piece::piece_index_t m_knight_index;

  const Pawn* m_pawn;

private Q_SLOTS:
  void initTestCase();

  void test_can_move_data();

  void test_can_move();

  void test_moves_data();

  void test_moves();

};

DECLARE_TEST(PawnTest)

} // namespace test
} // namespace olaf

#endif // PAWNTEST_H
