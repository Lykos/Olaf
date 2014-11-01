#include "olaf/search/perft.h"

#include <cassert>
#include <memory>
#include <iostream>

#include "olaf/rules/movechecker.h"
#include "olaf/search/movegenerator.h"
#include "olaf/rules/move.h"
#include "olaf/rules/undoinfo.h"
#include "olaf/rules/pieceset.h"
#include "olaf/parse/fenparser.h"
#include "olaf/rules/move.h"

using namespace std;

namespace olaf
{

Perft::PerftResult& Perft::PerftResult::operator +=(const PerftResult& right)
{
  nodes += right.nodes;
  captures += right.captures;
  ep += right.ep;
  castles += right.castles;
  promotions += right.promotions;
  mates += right.mates;
  return *this;
}

// static
const vector<Perft::PerftExample>& Perft::examples()
{
  static const string fen_initial = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  static const vector<PerftResult> expected_results_initial{
    PerftResult{1, 0, 0, 0, 0, 0},
    PerftResult{20, 0, 0, 0, 0, 0},
    PerftResult{400, 0, 0, 0, 0, 0},
    PerftResult{8902, 34, 0, 0, 0, 0},
    PerftResult{197281, 1576, 0, 0, 0, 8},
    PerftResult{4865609, 82719, 258, 0, 0, 347},
    PerftResult{119060324, 2812008, 5248, 0, 0, 10828}};

  static const string fen_position2 = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -";
  static const vector<PerftResult> expected_results_position2{
    PerftResult{1, 0, 0, 0, 0, 0},
    PerftResult{48, 8, 0, 2, 0, 0},
    PerftResult{2039, 351, 1, 91, 0, 0},
    PerftResult{97862, 17102, 45, 3162, 0, 1},
    PerftResult{4085603, 757163, 1929, 128013, 15172, 43},
    PerftResult{193690690, 35043416, 73365, 4993637, 8392, 30171}};

  static const string fen_position3 = "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -";
  static const vector<PerftResult> expected_results_position3{
    PerftResult{1, 0, 0, 0, 0, 0},
    PerftResult{14, 1, 0, 0, 0, 0},
    PerftResult{191, 14, 0, 0, 0, 0},
    PerftResult{2812, 209, 2, 0, 0, 0},
    PerftResult{43238, 3348, 123, 0, 0, 17},
    PerftResult{674624, 52051, 1165, 0, 0, 0},
    PerftResult{11030083, 940350, 33325, 0, 7552, 2733},
    PerftResult{178633661, 14519036, 294874, 0, 140024, 87}};

  static const string fen_position4 = "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1";
  static const vector<PerftResult> expected_results_position4{
    PerftResult{1, 0, 0, 0, 0, 0},
    PerftResult{6, 0, 0, 0, 0, 0},
    PerftResult{264, 87, 0, 6, 48, 0},
    PerftResult{9467, 1021, 4, 0, 120, 22},
    PerftResult{422333, 131393, 0, 7795, 60032, 5},
    PerftResult{15833292, 2046173, 6512, 0, 329464, 50562},
    PerftResult{706045033, 210369132, 212, 10882006, 81102984, 81076}};

  static const string fen_position5 = "rnbqkb1r/pp1p1ppp/2p5/4P3/2B5/8/PPP1NnPP/RNBQK2R w KQkq - 0 6";
  static const vector<PerftResult> expected_results_position5{
    PerftResult{1, 0, 0, 0, 0, 0},
    PerftResult{42, 3, 0, 1, 0, 0},
    PerftResult{1352, 95, 0, 0, 0, 0},
    PerftResult{53392, 4381, 75, 969, 0, 24}};

  static const vector<PerftExample> examples{
    PerftExample{"initial", fen_initial, expected_results_initial},
    PerftExample{"position2", fen_position2, expected_results_position2},
    PerftExample{"position3", fen_position3, expected_results_position3},
    PerftExample{"position4", fen_position4, expected_results_position4},
    PerftExample{"position5", fen_position5, expected_results_position5}};
  return examples;
}

Perft::Perft(unique_ptr<MoveGenerator> generator):
  m_generator(move(generator))
{}

Perft::PerftResult Perft::perft(const int depth, const ChessBoard& board)
{
  ChessBoard try_board(board);
  return internal_perft(depth, &try_board);
}

void Perft::debug_perft(const int depth,
                        const ChessBoard& board)
{
  ChessBoard try_board(board);
  vector<Move> moves = m_generator->generate_valid_moves(try_board);
  int sum = 0;
  for (Move& move : moves) {
    UndoInfo undo_info;
    move.execute(&try_board, &undo_info);
    cout << "setboard " << FenParser::serialize(try_board) << endl;
    const PerftResult& result = internal_perft(depth - 1, &try_board);
    move.undo(undo_info, &try_board);
    assert(try_board == board);
    sum += result.nodes;
    cout << "perft " << depth - 1 << endl;
    cout << "name " << result.nodes << endl;
  }
  cout << "sum " << sum << endl;
}

Perft::PerftResult Perft::internal_perft(const int depth,
                                         ChessBoard* const board)
{
  if (depth <= 0) {
    return {1, 0, 0, 0, 0, 0};
  }
  PerftResult result{0, 0, 0, 0, 0, 0};
  vector<Move> moves = m_generator->generate_valid_moves(*board);
  for (Move& move : moves) {
    UndoInfo undo_info;
    move.execute(board, &undo_info);
    if (depth > 1) {
      result += internal_perft(depth - 1, board);
    } else if (m_generator->generate_valid_moves(*board).empty()) {
      ++result.mates;
    }
    move.undo(undo_info, board);
    if (depth == 1) {
      ++result.nodes;
      if (move.is_capture()) {
        ++result.captures;

        if (move.is_ep()) {
          ++result.ep;
        }
      }
      if (move.is_castle()) {
        ++result.castles;
      }
      if (move.is_promotion()) {
        ++result.promotions;
      }
    }
  }
  return result;
}

bool operator ==(const Perft::PerftResult& left, const Perft::PerftResult& right)
{
  if (&left == &right) {
    return true;
  }
  return left.nodes == right.nodes
      && left.captures == right.captures
      && left.ep == right.ep
      && left.castles == right.castles
      && left.promotions == right.promotions
      && left.mates == right.mates;
}

std::ostream& operator <<(std::ostream& out, const Perft::PerftResult& perft_result)
{
  return out << "PerftResult(nodes = " << perft_result.nodes
             << ", captures = " << perft_result.captures
             << ", ep = " << perft_result.ep
             << ", castles = " << perft_result.castles
             << ", promotions = " << perft_result.promotions
             << ", mates = " << perft_result.mates << ")";

} // namespace olaf
}
