#ifndef CHESSBOARDTEST_H
#define CHESSBOARDTEST_H

#include "olaf/rules/piece.h"
#include "autotest.h"
#include <QtTest/QtTest>
#include <QObject>

namespace olaf
{
namespace test
{

class ChessBoardTest : public QObject
{
  Q_OBJECT

private Q_SLOTS:
  void test_occupied();

  void test_opponents();

  void test_friends();

  void test_finished_data();

  void test_finished();
  
};

DECLARE_TEST(ChessBoardTest)

} // namespace test
} // namespace olaf

#endif // CHESSBOARDTEST_H
