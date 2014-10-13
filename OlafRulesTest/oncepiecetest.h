#ifndef ONCEPIECETEST_H
#define ONCEPIECETEST_H

#include <QObject>
#include <QtTest/QTest>

#include "OlafRules/chessboard.h"
#include "OlafRules/piece.h"
#include "OlafTestUtil/autotest.h"

class OncePieceTest : public QObject
{
  Q_OBJECT

private:
  ChessBoard m_board;

  Piece::piece_index_t m_knight_index;

  Piece::piece_index_t m_king_index;

  const Piece* m_knight;

  const Piece* m_king;

private Q_SLOTS:
  void initTestCase();

  void test_can_move_data();

  void test_can_move();

  void test_moves_data();

  void test_moves();

};

DECLARE_TEST(OncePieceTest)

#endif // ONCEPIECETEST_H
