#include "perft.h"

#include <memory>
#include <iostream>

#include "movecreator.h"
#include "movegenerator.h"
#include "OlafRules/move.h"
#include "OlafRules/pieceset.h"
#include "OlafRules/fenparser.h"

using namespace std;

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
    PerftResult{53392, 0, 0, 0, 0, 0}};

  static const vector<PerftExample> examples{
    PerftExample{"initial", fen_initial, expected_results_initial},
    PerftExample{"position2", fen_position2, expected_results_position2},
    PerftExample{"position3", fen_position3, expected_results_position3},
    PerftExample{"position4", fen_position4, expected_results_position4},
    PerftExample{"position5", fen_position5, expected_results_position5}};
  return examples;
}

Perft::Perft(unique_ptr<MoveCreator> creator,
             unique_ptr<MoveGenerator> generator):
  m_creator(move(creator)),
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
  vector<Move> moves = valid_moves(try_board);
  int sum = 0;
  for (Move& move : moves) {
    move.execute(&try_board);
    cout << "setboard " << FenParser::serialize(try_board) << endl;
    const PerftResult& result = internal_perft(depth - 1, &try_board);
    move.undo(&try_board);
    sum += result.nodes;
    cout << "perft " << depth - 1 << endl;
    cout << "name " << result.nodes << endl;
  }
  cout << "sum " << sum << endl;
}

Perft::PerftResult Perft::internal_perft(const int depth,
                                         ChessBoard* const board)
{
  if (depth == 0) {
    return {1, 0, 0, 0, 0, 0};
  }
  PerftResult result{0, 0, 0, 0, 0, 0};
  vector<Move> moves = valid_moves(*board);
  for (Move& move : moves) {
    move.execute(board);
    if (depth > 1) {
      result += internal_perft(depth - 1, board);
    }
    move.undo(board);
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
          && board->turn_board().piece_index(move.source())
          == PieceSet::instance().king().piece_index()) {
        ++result.castles;
      }
      if (move.is_conversion()) {
        ++result.promotions;
      }
      if (valid_moves(*board).empty()) {
        ++result.mates;
      }
    }
  }
  return result;
}

bool Perft::valid_move(const ChessBoard& board,
                       const Move& move)
{
  if (move.is_conversion()) {
    return m_creator->valid_move(board,
                                 move.source(),
                                 move.destination(),
                                 move.created_piece());
  } else {
    return m_creator->valid_move(board,
                                 move.source(),
                                 move.destination());
  }
}

vector<Move> Perft::valid_moves(const ChessBoard& board)
{
  vector<Move> moves = m_generator->generate_moves(board);
  vector<Move> result;
  for (const Move& move : moves) {
    if (valid_move(board, move)) {
      result.push_back(move);
    }
  }
  return result;
}
