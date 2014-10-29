#ifndef PAWNTEST_H
#define PAWNTEST_H

#include "olaf/rules/chessboard.h"
#include "olaf/rules/piece.h"
#include "autotest.h"
#include <string>
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

  Move make_move(const std::string& source, const std::string& destination);

private Q_SLOTS:
  void initTestCase();

  void test_can_move_data();

  void test_can_move();

  //void test_moves_data();

  //void test_moves();

};

DECLARE_TEST(PawnTest)

} // namespace test
} // namespace olaf

#endif // PAWNTEST_H
