#include "perft.h"

#include <vector>
#include <QtTest/QTest>
#include <iostream>

#include "OlafSearching/movegenerator.h"
#include "OlafSearching/movecreator.h"
#include "OlafSearching/searcherfactory.h"
#include "OlafRules/chessboard.h"
#include "OlafRules/move.h"
#include "OlafRules/pieceset.h"
#include "OlafRules/fenparser.h"
#include "testutil.h"

using namespace std;

typedef unsigned long long u64;

struct PerftResult {
  u64 nodes;
  u64 captures;
  u64 ep;
  u64 castles;
  u64 promotions;
  u64 mates;

  PerftResult& operator +=(const PerftResult& right)
  {
    nodes += right.nodes;
    captures += right.captures;
    ep += right.ep;
    castles += right.castles;
    promotions += right.promotions;
    mates += right.mates;
    return *this;
  }
};

static const vector<PerftResult> expected_results_initial{
  PerftResult{1, 0, 0, 0, 0, 0},
  PerftResult{20, 0, 0, 0, 0, 0},
  PerftResult{400, 0, 0, 0, 0, 0},
  PerftResult{8902, 34, 0, 0, 0, 0},
  PerftResult{197281, 1576, 0, 0, 0, 8},
  PerftResult{4865609, 82719, 258, 0, 0, 347},
  PerftResult{119060324, 2812008, 5248, 0, 0, 10828}};

static const vector<PerftResult> expected_results_position2{
  PerftResult{1, 0, 0, 0, 0, 0},
  PerftResult{48, 8, 0, 2, 0, 0},
  PerftResult{2039, 351, 1, 91, 0, 0},
  PerftResult{97862, 17102, 45, 3162, 0, 1},
  PerftResult{4085603, 757163, 1929, 128013, 15172, 43},
  PerftResult{193690690, 35043416, 73365, 4993637, 8392, 30171}};

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

static vector<Move> valid_moves(const ChessBoard& board,
                                MoveGenerator* const generator,
                                MoveCreator* const creator)
{
  vector<Move> moves = generator->generate_moves(board);
  vector<Move> result;
  for (const Move& move : moves) {
    if (valid_move(board, move, creator)) {
      result.push_back(move);
    }
  }
  return result;
}

static PerftResult perft(const int depth,
                         ChessBoard* const board,
                         MoveGenerator* const generator,
                         MoveCreator* const creator)
{
  if (depth == 0) {
    return {1, 0, 0, 0, 0, 0};
  }
  PerftResult result{0, 0, 0, 0, 0, 0};
  vector<Move> moves = valid_moves(*board, generator, creator);
  for (Move& move : moves) {
    move.execute(board);
    if (depth == 1) {
      ++result.nodes;
      if (move.is_capture()) {
        ++result.captures;
        if (board->ep_possible()
            && move.destination() == board->ep_capture_position()) {
          ++result.ep;
        }
      }
      if (abs(move.source().column() - move.destination().column()) == 2
          && board->noturn_board().piece_index(move.destination())
          == PieceSet::instance().king().piece_index()) {
        ++result.castles;
      }
      if (move.is_conversion()) {
        ++result.promotions;
      }
      if (valid_moves(*board, generator, creator).empty()) {
        ++result.mates;
      }
    } else {
      result += perft(depth - 1, board, generator, creator);
    }
    move.undo(board);
  }
  return result;
}

void debug_perft(const int depth,
                 ChessBoard* const board,
                 MoveGenerator* const generator,
                 MoveCreator* const creator)
{
  vector<Move> moves = valid_moves(*board, generator, creator);
  int sum = 0;
  for (Move& move : moves) {
    move.execute(board);
    cout << "setboard " << FenParser::serialize(*board) << endl;
    const PerftResult& result =
        perft(depth - 1, board, generator, creator);
    move.undo(board);
    sum += result.nodes;
    cout << "perft " << depth - 1 << endl;
    cout << result.nodes << endl;
  }
  cout << "sum " << sum << endl;
}

Q_DECLARE_METATYPE(ChessBoard)
Q_DECLARE_METATYPE(vector<PerftResult>)

void Perft::test_perft_data()
{
  QTest::addColumn<int>("depth");
  QTest::addColumn<ChessBoard>("board");
  QTest::addColumn<vector<PerftResult>>("expected_results");

  // QTest::newRow("initial") << 3 << create_initial_board() << expected_results_initial;
  // QTest::newRow("position2")
  //    << 3 << parse_fen("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1")
  //    << expected_results_position2;
  QTest::newRow("debug")
      << 2 << parse_fen("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/1R2K2R b Kkq - 0 1") << vector<PerftResult>();
}

void Perft::test_perft()
{
  QFETCH(int, depth);
  QFETCH(ChessBoard, board);
  QFETCH(vector<PerftResult>, expected_results);

  SearcherFactory factory(nullptr);
  std::unique_ptr<MoveGenerator> generator = factory.move_generator();
  std::unique_ptr<MoveCreator> creator = factory.move_creator();
  debug_perft(depth, &board, generator.get(), creator.get());
  const PerftResult& expected_result = expected_results.at(depth);
  const PerftResult& actual_result = perft(depth, &board, generator.get(), creator.get());
  QCOMPARE(int(expected_result.mates), int(actual_result.mates));
  QCOMPARE(int(expected_result.promotions), int(actual_result.promotions));
  QCOMPARE(int(expected_result.ep), int(actual_result.ep));
  QCOMPARE(int(expected_result.captures), int(actual_result.captures));
  QCOMPARE(int(expected_result.nodes), int(actual_result.nodes));
  QCOMPARE(int(expected_result.castles), int(actual_result.castles));
}
