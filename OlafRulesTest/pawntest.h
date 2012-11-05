#ifndef PAWNTEST_H
#define PAWNTEST_H

#include <QtTest/QTest>
#include <QObject>

class PawnTest : public QObject
{
  Q_OBJECT

private Q_SLOTS:
  void test_can_move_data();

  void test_can_move();

  void test_moves_data();

  void test_moves();

};

#endif // PAWNTEST_H
