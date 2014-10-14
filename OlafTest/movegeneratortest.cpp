#include "movegeneratortest.h"

#include <memory>
#include <iostream>
#include <QtTest/QTest>

#include "OlafSearching/searcherfactory.h"
#include "OlafSearching/movegenerator.h"
#include "testutil.h"

using namespace std;
using namespace testing;

static bool valid_move(const ChessBoard& board,
                       const Move& move,
                       MoveCreator* const creator)
{
  if (move.is_conversion()) {
    return creator->valid_move(board,
                               move.source(),
                               move.destination(),
                               move.created_piece());
  } else {
    return creator->valid_move(board,
                               move.source(),
                               move.destination());
  }
}

Q_DECLARE_METATYPE(ChessBoard)
Q_DECLARE_METATYPE(vector<Move>)

void MoveGeneratorTest::test_generate_data()
{
  QTest::addColumn<ChessBoard>("board");
  QTest::addColumn<vector<Move>>("moves");
/*
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
  }*/
  {
    QTest::newRow("bug")
         << parse_fen("8/2p5/3p4/KP5r/1R2Pp1k/8/6P1/8 b - - 0 1")
         << vector<Move>();
  }
}

void MoveGeneratorTest::test_generate()
{
  QFETCH(ChessBoard, board);
  QFETCH(vector<Move>, moves);

  SearcherFactory factory(nullptr);
  unique_ptr<MoveGenerator> generator(factory.move_generator());
  unique_ptr<MoveCreator> creator(factory.move_creator());
  const vector<Move>& actual_moves = generator->generate_moves(board);
  vector<Move> valid_moves;
  for (const Move& move : actual_moves) {
    if (valid_move(board, move, creator.get())) {
      cout << move << endl;
      valid_moves.push_back(move);
    }
  }
  vector<Matcher<Move>> move_matchers;
  for (const Move& move : moves) {
    move_matchers.push_back(IsSameMove(move));
  }
  QASSERT_THAT(valid_moves, UnorderedElementsAreArray(move_matchers));
}
