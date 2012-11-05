#include "boardtest.h"
#include <QtTest>

int main(int argc, char **argv)
{
  BoardTest board_test;
  QTest::qExec(&board_test, argc, argv);
  return 0;
}
