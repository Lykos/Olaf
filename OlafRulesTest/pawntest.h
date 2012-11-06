#ifndef PAWNTEST_H
#define PAWNTEST_H

#include "OlafRules/chessboard.h"
#include "OlafRules/piece.h"
#include "OlafRules/pawn.h"
#include <QtTest/QTest>
#include <QObject>
#include <memory>

class PawnTest : public QObject
{
  Q_OBJECT

private:
  ChessBoard m_board;

  Piece::piece_index_t m_pawn_index;

  Piece::piece_index_t m_knight_index;

  std::shared_ptr<const Pawn> m_pawn;

private Q_SLOTS:
  void initTestCase();

  void test_can_move_data();

  void test_can_move();

  void test_moves_data();

  void test_moves();

};

#endif // PAWNTEST_H
