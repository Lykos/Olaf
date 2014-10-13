#ifndef BOARDTEST_H
#define BOARDTEST_H

#include "OlafRules/piece.h"
#include "autotest.h"
#include <QtTest/QtTest>
#include <QObject>

class BoardTest : public QObject
{
  Q_OBJECT

public:
  BoardTest();

private:
  Piece::piece_index_t m_bishop;

private Q_SLOTS:
  void test_occupied();

  void test_opponents();

  void test_friends();
  
};

DECLARE_TEST(BoardTest)

#endif // BOARDTEST_H
