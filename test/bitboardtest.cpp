
#include "test/bitboardtest.h"
#include <QtTest/QTest>
#include <vector>
#include "test/testutil.h"
#include "olaf/rules/position.h"
#include "olaf/rules/bitboard.h"

using namespace std;
using namespace testing;

namespace olaf
{
namespace test
{

void BitboardTest::test_number_data()
{
  QTest::addColumn<BitBoard>("board");
  QTest::addColumn<int>("number");
  QTest::newRow("empty") << BitBoard(0) << 0;
  QTest::newRow("full") << BitBoard(0xFFFFFFFFFFFFFFFF) << 64;
  QTest::newRow("half") << BitBoard(0x0F0F0F0F0F0F0F0F) << 32;
}

void BitboardTest::test_number()
{
  QFETCH(BitBoard, board);
  QFETCH(int, number);
  QASSERT_THAT(board.number(), Eq(number));
}

void BitboardTest::test_next_position_data()
{
  QTest::addColumn<BitBoard>("board");
  QTest::addColumn<vector<Position>>("positions");
  QTest::newRow("empty") << BitBoard(0) << vector<Position>();
  {
    vector<Position> positions = Position::all_positions();
    QTest::newRow("full") << BitBoard(0xFFFFFFFFFFFFFFFF) << positions;
  }
  {
    vector<Position> positions = {Position("e3"), Position("h8")};
    QTest::newRow("two") << BitBoard(0x8000000000100000) << positions;
  }
}

void BitboardTest::test_next_position()
{
  QFETCH(BitBoard, board);
  QFETCH(vector<Position>, positions);
  vector<Position> extracted_positions;
  for (BitBoard bit_board = board; board; ) {
    extracted_positions.push_back(bit_board.first_position());
    QASSERT_THAT(bit_board.next_position(), Eq(extracted_positions.back()));
  }
  QASSERT_THAT(extracted_positions, UnorderedElementsAreArray(positions));
}

void BitboardTest::test_get_data()
{
  QTest::addColumn<BitBoard>("board");
  QTest::addColumn<Position>("position");
  QTest::addColumn<bool>("result");
  QTest::newRow("empty") << BitBoard(0) << Position("e4") << false;
  QTest::newRow("full") << BitBoard(0xFFFFFFFFFFFFFFFF) << Position("e4") << true;
  QTest::newRow("two false") << BitBoard(0x8000000000100000) << Position("e4") << false;
  QTest::newRow("two true h8") << BitBoard(0x8000000000100000) << Position("h8") << true;
  QTest::newRow("two true c4") << BitBoard(0x8000000000100000) << Position("e3") << true;
}

void BitboardTest::test_get()
{
  QFETCH(BitBoard, board);
  QFETCH(Position, position);
  QFETCH(bool, result);
  QASSERT_THAT(board.get(position), Eq(result));
}

void BitboardTest::test_set_data()
{
  QTest::addColumn<BitBoard>("board");
  QTest::addColumn<Position>("position");
  QTest::addColumn<bool>("value");
  QTest::addColumn<BitBoard>("result");
  QTest::newRow("empty unset") << BitBoard(0) << Position("e4") << false << BitBoard(0);
  QTest::newRow("empty set") << BitBoard(0) << Position("e4") << true << BitBoard(0x0000000010000000);
  QTest::newRow("full unset") << BitBoard(0xFFFFFFFFFFFFFFFF) << Position("e4") << false << BitBoard(0xFFFFFFFFEFFFFFFF);
  QTest::newRow("full set") << BitBoard(0xFFFFFFFFFFFFFFFF) << Position("e4") << true << BitBoard(0xFFFFFFFFFFFFFFFF);
  QTest::newRow("two unset false") << BitBoard(0x8000000000100000) << Position("e4") << false << BitBoard(0x8000000000100000);
  QTest::newRow("two set false") << BitBoard(0x8000000000100000) << Position("e4") << true << BitBoard(0x8000000010100000);
  QTest::newRow("two unset true h8") << BitBoard(0x8000000000100000) << Position("h8") << false << BitBoard(0x0000000000100000);
  QTest::newRow("two set true h8") << BitBoard(0x8000000000100000) << Position("h8") << true << BitBoard(0x8000000000100000);
  QTest::newRow("two unset true c4") << BitBoard(0x8000000000100000) << Position("e3") << false << BitBoard(0x8000000000000000);
  QTest::newRow("two set true c4") << BitBoard(0x8000000000100000) << Position("e3") << true << BitBoard(0x8000000000100000);
}

void BitboardTest::test_set()
{
  QFETCH(BitBoard, board);
  QFETCH(Position, position);
  QFETCH(bool, value);
  QFETCH(BitBoard, result);
  board.set(position, value);
  QASSERT_THAT(board, Eq(result));
}

} // namespace test
} // namespace olaf
