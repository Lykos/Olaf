#include "movegeneratortest.h"

#include <memory>
#include <iostream>
#include <QtTest/QTest>

#include "olaf/search/searcherfactory.h"
#include "olaf/search/movegenerator.h"
#include "olaf/search/nothinkingwriter.h"
#include "olaf/rules/movechecker.h"
#include "testutil.h"

using namespace std;
using namespace testing;

namespace olaf
{
namespace test
{

void MoveGeneratorTest::test_generate_data()
{
  QTest::addColumn<ChessBoard>("board");
  QTest::addColumn<vector<Move>>("moves");

  {
    ChessBoard board = parse_fen("r3k2r/p1ppqpb1/1n2pnp1/3PN3/1p2P3/2N2Q1p/PPPBbPPP/1R2K2R w Kkq - 0 2");
    const vector<Move> moves{
      MoveChecker::complete(Position("b1"), Position("a1"), board),
      MoveChecker::complete(Position("b1"), Position("c1"), board),
      MoveChecker::complete(Position("b1"), Position("d1"), board),
      MoveChecker::complete(Position("h1"), Position("g1"), board),
      MoveChecker::complete(Position("h1"), Position("f1"), board),
      MoveChecker::complete(Position("c3"), Position("e2"), board),
      MoveChecker::complete(Position("c3"), Position("d1"), board),
      MoveChecker::complete(Position("c3"), Position("a4"), board),
      MoveChecker::complete(Position("c3"), Position("b5"), board),
      MoveChecker::complete(Position("e5"), Position("c4"), board),
      MoveChecker::complete(Position("e5"), Position("d3"), board),
      MoveChecker::complete(Position("e5"), Position("g4"), board),
      MoveChecker::complete(Position("e5"), Position("c6"), board),
      MoveChecker::complete(Position("e5"), Position("d7"), board),
      MoveChecker::complete(Position("e5"), Position("g6"), board),
      MoveChecker::complete(Position("e5"), Position("f7"), board),
      MoveChecker::complete(Position("d2"), Position("c1"), board),
      MoveChecker::complete(Position("d2"), Position("e3"), board),
      MoveChecker::complete(Position("d2"), Position("f4"), board),
      MoveChecker::complete(Position("d2"), Position("g5"), board),
      MoveChecker::complete(Position("d2"), Position("h6"), board),
      MoveChecker::complete(Position("f3"), Position("e3"), board),
      MoveChecker::complete(Position("f3"), Position("d3"), board),
      MoveChecker::complete(Position("f3"), Position("g3"), board),
      MoveChecker::complete(Position("f3"), Position("h3"), board),
      MoveChecker::complete(Position("f3"), Position("f4"), board),
      MoveChecker::complete(Position("f3"), Position("f5"), board),
      MoveChecker::complete(Position("f3"), Position("f6"), board),
      MoveChecker::complete(Position("f3"), Position("e2"), board),
      MoveChecker::complete(Position("f3"), Position("g4"), board),
      MoveChecker::complete(Position("f3"), Position("h5"), board),
      MoveChecker::complete(Position("e1"), Position("e2"), board),
      MoveChecker::complete(Position("a2"), Position("a3"), board),
      MoveChecker::complete(Position("a2"), Position("a4"), board),
      MoveChecker::complete(Position("b2"), Position("b3"), board),
      MoveChecker::complete(Position("g2"), Position("g3"), board),
      MoveChecker::complete(Position("g2"), Position("g4"), board),
      MoveChecker::complete(Position("g2"), Position("h3"), board),
      MoveChecker::complete(Position("d5"), Position("d6"), board),
      MoveChecker::complete(Position("d5"), Position("e6"), board)};
    QTest::newRow("middle game")
         << board
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
  for (const Move move : actual_moves) {
    if (MoveChecker::valid_move(board, move)) {
      valid_moves.push_back(move);
    }
  }
  QASSERT_THAT(valid_moves, UnorderedElementsAreArray(moves));

} // namespace test
} // namespace olaf
}
