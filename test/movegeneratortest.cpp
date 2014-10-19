#include "movegeneratortest.h"

#include <memory>
#include <iostream>
#include <QtTest/QTest>

#include "olaf/search/searcherfactory.h"
#include "olaf/search/movegenerator.h"
#include "olaf/search/nothinkingwriter.h"
#include "testutil.h"

using namespace std;
using namespace testing;

namespace olaf
{
namespace test
{

static bool valid_move(const ChessBoard& board,
                       const Move& move)
{
  if (move.is_conversion()) {
    return MoveCreator::valid_move(board,
                                   move.source(),
                                   move.destination(),
                                   move.created_piece());
  } else {
    return MoveCreator::valid_move(board,
                                   move.source(),
                                   move.destination());
  }
}

void MoveGeneratorTest::test_generate_data()
{
  QTest::addColumn<ChessBoard>("board");
  QTest::addColumn<vector<Move>>("moves");

  {
    const vector<Move> moves{
      make_move(Position("b1"), Position("a1"), false),
      make_move(Position("b1"), Position("c1"), false),
      make_move(Position("b1"), Position("d1"), false),
      make_move(Position("h1"), Position("g1"), false),
      make_move(Position("h1"), Position("f1"), false),
      make_move(Position("c3"), Position("e2"), true),
      make_move(Position("c3"), Position("d1"), false),
      make_move(Position("c3"), Position("a4"), false),
      make_move(Position("c3"), Position("b5"), false),
      make_move(Position("e5"), Position("c4"), false),
      make_move(Position("e5"), Position("d3"), false),
      make_move(Position("e5"), Position("g4"), false),
      make_move(Position("e5"), Position("c6"), false),
      make_move(Position("e5"), Position("d7"), true),
      make_move(Position("e5"), Position("g6"), true),
      make_move(Position("e5"), Position("f7"), true),
      make_move(Position("d2"), Position("c1"), false),
      make_move(Position("d2"), Position("e3"), false),
      make_move(Position("d2"), Position("f4"), false),
      make_move(Position("d2"), Position("g5"), false),
      make_move(Position("d2"), Position("h6"), false),
      make_move(Position("f3"), Position("e3"), false),
      make_move(Position("f3"), Position("d3"), false),
      make_move(Position("f3"), Position("g3"), false),
      make_move(Position("f3"), Position("h3"), true),
      make_move(Position("f3"), Position("f4"), false),
      make_move(Position("f3"), Position("f5"), false),
      make_move(Position("f3"), Position("f6"), true),
      make_move(Position("f3"), Position("e2"), true),
      make_move(Position("f3"), Position("g4"), false),
      make_move(Position("f3"), Position("h5"), false),
      make_move(Position("e1"), Position("e2"), true),
      make_move(Position("a2"), Position("a3"), false),
      make_move(Position("a2"), Position("a4"), false),
      make_move(Position("b2"), Position("b3"), false),
      make_move(Position("g2"), Position("g3"), false),
      make_move(Position("g2"), Position("g4"), false),
      make_move(Position("g2"), Position("h3"), true),
      make_move(Position("d5"), Position("d6"), false),
      make_move(Position("d5"), Position("e6"), true)};
    QTest::newRow("middle game")
         << parse_fen("r3k2r/p1ppqpb1/1n2pnp1/3PN3/1p2P3/2N2Q1p/PPPBbPPP/1R2K2R w Kkq - 0 2")
         << moves;
  }
}

void MoveGeneratorTest::test_generate()
{
  QFETCH(ChessBoard, board);
  QFETCH(vector<Move>, moves);

  NoThinkingWriter no_thinking_writer;
  SearcherFactory factory(&no_thinking_writer);
  unique_ptr<MoveGenerator> generator(factory.move_generator());
  const vector<Move>& actual_moves = generator->generate_moves(board);
  vector<Move> valid_moves;
  for (const Move& move : actual_moves) {
    if (valid_move(board, move)) {
      valid_moves.push_back(move);
    }
  }
  vector<Matcher<Move>> move_matchers;
  for (const Move& move : moves) {
    move_matchers.push_back(IsSameMove(move));
  }
  QASSERT_THAT(valid_moves, UnorderedElementsAreArray(move_matchers));

} // namespace test
} // namespace olaf
}