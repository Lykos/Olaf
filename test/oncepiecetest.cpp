#include "oncepiecetest.h"

#include <vector>
#include <iostream>

#include "testutil.h"
#include "olaf/pieceset.h"
#include "olaf/move.h"
#include "olaf/oncepiece.h"
#include "olaf/position.h"
#include "olaf/fenparser.h"
#include "gmock/gmock-generated-matchers.h"

using namespace std;
using namespace testing;

Q_DECLARE_METATYPE(const olaf::Piece*)
Q_DECLARE_METATYPE(olaf::Position)
Q_DECLARE_METATYPE(vector<olaf::Move>)

namespace olaf
{
namespace test
{

void OncePieceTest::initTestCase()
{
  m_king = &(PieceSet::instance().king());
  m_knight = &(PieceSet::instance().knight());
  m_board = parse_fen("K6N/nK6/6N1/8/7N/8/6n1/R3K2R w KQ - 0 1");
  m_king_index = m_king->piece_index();
  m_knight_index = m_knight->piece_index();
}

void OncePieceTest::test_can_move_data()
{
  QTest::addColumn<const Piece*>("piece");
  QTest::addColumn<Position>("source");
  QTest::addColumn<Position>("destination");
  QTest::addColumn<bool>("result");
  QTest::addColumn<bool>("is_capture");

  QTest::newRow("king non-existent e4e5") << m_king << Position("e4") << Position("e5") << false << false;

  QTest::newRow("king corner a8a8") << m_king << Position("a8") << Position("a8") << false << false;
  QTest::newRow("king corner a8b8") << m_king << Position("a8") << Position("b8") << true << false;
  QTest::newRow("king corner capture a8a7") << m_king << Position("a8") << Position("a7") << true << true;
  QTest::newRow("king corner friend a8b7") << m_king << Position("a8") << Position("b7") << false << false;
  QTest::newRow("king corner jump straight a8a6") << m_king << Position("a8") << Position("a6") << false << false;
  QTest::newRow("king corner jump diagonal a8c6") << m_king << Position("a8") << Position("c6") << false << false;

  QTest::newRow("king wall e1f1") << m_king << Position("e1") << Position("f1") << true << false;
  QTest::newRow("king wall e1d2") << m_king << Position("e1") << Position("d2") << true << false;
  QTest::newRow("king wall e1e2") << m_king << Position("e1") << Position("e2") << true << false;
  QTest::newRow("king castle q e1c1") << m_king << Position("e1") << Position("c1") << true << false;
  QTest::newRow("king castle k e1g1") << m_king << Position("e1") << Position("g1") << true << false;
  QTest::newRow("king wall jump e1e3") << m_king << Position("e1") << Position("e3") << false << false;

  QTest::newRow("king middle friend b7a8") << m_king << Position("b7") << Position("a8") << false << false;
  QTest::newRow("king middle b7c6") << m_king << Position("b7") << Position("c6") << true << false;

  QTest::newRow("knight non-existent e4f6") << m_knight << Position("e4") << Position("f6") << false << false;

  QTest::newRow("knight corner h8f7") << m_knight << Position("h8") << Position("f7") << true << false;
  QTest::newRow("knight corner friend h8g6") << m_knight << Position("h8") << Position("g6") << false << false;

  QTest::newRow("knight middle g6f8") << m_knight << Position("g6") << Position("f8") << true << false;
  QTest::newRow("knight middle friend g6h8") << m_knight << Position("g6") << Position("h8") << false << false;
  QTest::newRow("knight middle friend g6h4") << m_knight << Position("g6") << Position("h4") << false << false;
  QTest::newRow("knight middle g6f4") << m_knight << Position("g6") << Position("f4") << true << false;
  QTest::newRow("knight middle jump g6e2") << m_knight << Position("g6") << Position("e2") << false << false;

  QTest::newRow("knight wall friend h4g6") << m_knight << Position("h4") << Position("g6") << false << false;
  QTest::newRow("knight wall h4f3") << m_knight << Position("h4") << Position("f3") << true << false;
  QTest::newRow("knight wall capture h4g2") << m_knight << Position("h4") << Position("g2") << true << true;
}

void OncePieceTest::test_can_move()
{
  QFETCH(const Piece*, piece);
  QFETCH(Position, source);
  QFETCH(Position, destination);
  QFETCH(bool, result);
  QFETCH(bool, is_capture);

  QCOMPARE(piece->can_move(source, destination, m_board), result);
  if (result) {
    const Move& move = piece->move(source, destination, m_board);
    QCOMPARE(move.is_capture(), is_capture);
  }
}

void OncePieceTest::test_moves_data()
{
  QTest::addColumn<const Piece*>("piece");
  QTest::addColumn<Position>("source");
  QTest::addColumn<vector<Move>>("moves");

  {
    vector<Move> moves{
      make_move(Position("a8"), Position("b8"), false),
      make_move(Position("a8"), Position("a7"), true)};
    QTest::newRow("king a8") << m_king << Position("a8") << moves;
  }
  {
    vector<Move> moves{
      make_move(Position("b7"), Position("b8"), false),
      make_move(Position("b7"), Position("c8"), false),
      make_move(Position("b7"), Position("a7"), true),
      make_move(Position("b7"), Position("c7"), false),
      make_move(Position("b7"), Position("a6"), false),
      make_move(Position("b7"), Position("b6"), false),
      make_move(Position("b7"), Position("c6"), false)};
    QTest::newRow("king b7") << m_king << Position("b7") << moves;
  }
  {
    vector<Move> moves{
      make_move(Position("e1"), Position("d1"), false),
      make_move(Position("e1"), Position("f1"), false),
      make_move(Position("e1"), Position("d2"), false),
      make_move(Position("e1"), Position("e2"), false),
      make_move(Position("e1"), Position("f2"), false),
      make_move(Position("e1"), Position("c1"), false),
      make_move(Position("e1"), Position("g1"), false)};
    QTest::newRow("king e1") << m_king << Position("e1") << moves;
  }
  {
    vector<Move> moves{
      make_move(Position("h8"), Position("f7"), false)};
    QTest::newRow("knight h8") << m_knight << Position("h8") << moves;
  }
  {
    vector<Move> moves{
      make_move(Position("g6"), Position("f8"), false),
      make_move(Position("g6"), Position("e7"), false),
      make_move(Position("g6"), Position("e5"), false),
      make_move(Position("g6"), Position("f4"), false)};
    QTest::newRow("knight g6") << m_knight << Position("g6") << moves;
  }
  {
    vector<Move> moves{
      make_move(Position("h4"), Position("f5"), false),
      make_move(Position("h4"), Position("f3"), false),
      make_move(Position("h4"), Position("g2"), true)};
    QTest::newRow("knight h4") << m_knight << Position("h4") << moves;
  }
}

void OncePieceTest::test_moves()
{
  QFETCH(const Piece*, piece);
  QFETCH(Position, source);
  QFETCH(vector<Move>, moves);

  const vector<Move>& actual_moves = piece->moves(source, m_board);
  vector<Matcher<Move>> move_matchers;
  for (const Move& move : moves) {
    move_matchers.push_back(IsSameMove(move));
  }
  QASSERT_THAT(actual_moves, UnorderedElementsAreArray(move_matchers));

} // namespace test
} // namespace olaf
}
