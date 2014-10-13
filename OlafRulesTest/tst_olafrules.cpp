#include "boardtest.h"
#include "oncepiecetest.h"
#include "pawntest.h"
#include "fenparsertest.h"
#include <QtTest>

int main(int argc, char **argv)
{
  BoardTest board_test;
  QTest::qExec(&board_test, argc, argv);
  OncePieceTest once_piece_test;
  QTest::qExec(&once_piece_test, argc, argv);
  PawnTest pawn_test;
  QTest::qExec(&pawn_test, argc, argv);
  FenParserTest fen_parser_test;
  QTest::qExec(&fen_parser_test, argc, argv);
  return 0;
}
