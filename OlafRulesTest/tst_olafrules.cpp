#include "boardtest.h"
#include "pawntest.h"
#include <QtTest>

int main(int argc, char **argv)
{
  BoardTest board_test;
  QTest::qExec(&board_test, argc, argv);
  PawnTest pawn_test;
  QTest::qExec(&pawn_test, argc, argv);
  return 0;
}
