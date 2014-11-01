#include "olaf/evaluation/incrementalupdater.h"

#include <cassert>
#include <vector>
#include <iostream>

#include "olaf/rules/pieceset.h"
#include "olaf/rules/bitboard.h"
#include "olaf/rules/chessboard.h"
#include "olaf/evaluation/incrementalstate.h"

using namespace std;

namespace olaf
{

static array<IncrementalUpdater::score_t, PieceSet::c_no_pieces> generate_piece_values()
{
  array<IncrementalUpdater::score_t, PieceSet::c_no_pieces> piece_values;
  piece_values[PieceSet::c_rook_index] = 500;
  piece_values[PieceSet::c_knight_index] = 320;
  piece_values[PieceSet::c_bishop_index] = 330;
  piece_values[PieceSet::c_queen_index] = 900;
  piece_values[PieceSet::c_king_index] = 25000;
  piece_values[PieceSet::c_pawn_index] = 100;
  return piece_values;
}

static array<IncrementalUpdater::score_t, PieceSet::c_no_pieces> generate_material_scores()
{
  array<IncrementalUpdater::score_t, PieceSet::c_no_pieces> piece_values = generate_piece_values();
  piece_values[PieceSet::c_king_index] = 0;
  return piece_values;
}

static const array<IncrementalUpdater::score_t, BitBoard::c_bitboard_size> c_piece_square_values_rook = {
  0,  0,  0,  5,  5,  0,  0,  0,
  -5,  0,  0,  0,  0,  0,  0, -5,
  -5,  0,  0,  0,  0,  0,  0, -5,
  -5,  0,  0,  0,  0,  0,  0, -5,
  -5,  0,  0,  0,  0,  0,  0, -5,
  -5,  0,  0,  0,  0,  0,  0, -5,
  5, 10, 10, 10, 10, 10, 10,  5,
  0,  0,  0,  0,  0,  0,  0,  0
};

static const array<IncrementalUpdater::score_t, BitBoard::c_bitboard_size> c_piece_square_values_knight = {
  -50,-40,-30,-30,-30,-30,-40,-50,
  -40,-20,  0,  5,  5,  0,-20,-40,
  -30,  5, 10, 15, 15, 10,  5,-30,
  -30,  0, 15, 20, 20, 15,  0,-30,
  -30,  5, 15, 20, 20, 15,  5,-30,
  -30,  0, 10, 15, 15, 10,  0,-30,
  -40,-20,  0,  0,  0,  0,-20,-40,
  -50,-40,-30,-30,-30,-30,-40,-50,
};

static const array<IncrementalUpdater::score_t, BitBoard::c_bitboard_size> c_piece_square_values_bishop = {
  -20,-10,-10,-10,-10,-10,-10,-20,
  -10,  5,  0,  0,  0,  0,  5,-10,
  -10, 10, 10, 10, 10, 10, 10,-10,
  -10,  0, 10, 10, 10, 10,  0,-10,
  -10,  5,  5, 10, 10,  5,  5,-10,
  -10,  0,  5, 10, 10,  5,  0,-10,
  -10,  0,  0,  0,  0,  0,  0,-10,
  -20,-10,-10,-10,-10,-10,-10,-20,
};

static const array<IncrementalUpdater::score_t, BitBoard::c_bitboard_size> c_piece_square_values_queen = {
  -20,-10,-10, -5, -5,-10,-10,-20,
  -10,  0,  5,  0,  0,  0,  0,-10,
  -10,  5,  5,  5,  5,  5,  0,-10,
   0,   0,  5,  5,  5,  5,  0, -5,
  -5,   0,  5,  5,  5,  5,  0, -5,
  -10,  0,  5,  5,  5,  5,  0,-10,
  -10,  0,  0,  0,  0,  0,  0,-10,
  -20,-10,-10, -5, -5,-10,-10,-20
};

static const array<IncrementalUpdater::score_t, BitBoard::c_bitboard_size> c_piece_square_values_king_middlegame = {
  20, 30, 10,  0,  0, 10, 30, 20,
  20, 20,  0,  0,  0,  0, 20, 20,
  -10,-20,-20,-20,-20,-20,-20,-10,
  -20,-30,-30,-40,-40,-30,-30,-20,
  -30,-40,-40,-50,-50,-40,-40,-30,
  -30,-40,-40,-50,-50,-40,-40,-30,
  -30,-40,-40,-50,-50,-40,-40,-30,
  -30,-40,-40,-50,-50,-40,-40,-30
};

static const array<IncrementalUpdater::score_t, BitBoard::c_bitboard_size> c_piece_square_values_king_endgame = {
  -50,-30,-30,-30,-30,-30,-30,-50
  -30,-30,  0,  0,  0,  0,-30,-30,
  -30,-10, 20, 30, 30, 20,-10,-30,
  -30,-10, 30, 40, 40, 30,-10,-30,
  -30,-10, 30, 40, 40, 30,-10,-30,
  -30,-10, 20, 30, 30, 20,-10,-30,
  -30,-20,-10,  0,  0,-10,-20,-30,
  -50,-40,-30,-20,-20,-30,-40,-50,
};

static const array<IncrementalUpdater::score_t, BitBoard::c_bitboard_size> c_piece_square_values_pawn = {
  0,  0,  0,  0,  0,  0,  0,  0,
  5, 10, 10,-20,-20, 10, 10,  5,
  5, -5,-10,  0,  0,-10, -5,  5,
  0,  0,  0, 20, 20,  0,  0,  0,
  5,  5, 10, 25, 25, 10,  5,  5,
  10, 10, 20, 30, 30, 20, 10, 10,
  50, 50, 50, 50, 50, 50, 50, 50,
  0,  0,  0,  0,  0,  0,  0,  0
};

static array<array<IncrementalUpdater::score_t, BitBoard::c_bitboard_size>, 2 * PieceSet::c_no_pieces> generate_piece_square_values()
{
  array<array<IncrementalUpdater::score_t, BitBoard::c_bitboard_size>, 2 * PieceSet::c_no_pieces> piece_square_values;
  piece_square_values[PieceSet::c_rook_index] = c_piece_square_values_rook;
  piece_square_values[PieceSet::c_knight_index] = c_piece_square_values_knight;
  piece_square_values[PieceSet::c_bishop_index] = c_piece_square_values_bishop;
  piece_square_values[PieceSet::c_queen_index] = c_piece_square_values_queen;
  piece_square_values[PieceSet::c_king_index] = c_piece_square_values_king_middlegame;
  piece_square_values[PieceSet::c_pawn_index] = c_piece_square_values_pawn;
  piece_square_values[PieceSet::c_no_pieces + PieceSet::c_rook_index] = c_piece_square_values_rook;
  piece_square_values[PieceSet::c_no_pieces + PieceSet::c_knight_index] = c_piece_square_values_knight;
  piece_square_values[PieceSet::c_no_pieces + PieceSet::c_bishop_index] = c_piece_square_values_bishop;
  piece_square_values[PieceSet::c_no_pieces + PieceSet::c_queen_index] = c_piece_square_values_queen;
  piece_square_values[PieceSet::c_no_pieces + PieceSet::c_king_index] = c_piece_square_values_king_endgame;
  piece_square_values[PieceSet::c_no_pieces + PieceSet::c_pawn_index] = c_piece_square_values_pawn;
  return piece_square_values;
}

// static
array<IncrementalUpdater::score_t, PieceSet::c_no_pieces> IncrementalUpdater::piece_values() {
  static const array<IncrementalUpdater::score_t, PieceSet::c_no_pieces> piece_values = generate_piece_values();
  return piece_values;
}

static IncrementalUpdater::score_t piece_value(const Color color,
                                               const int endgame,
                                               const Piece::piece_index_t piece_index,
                                               const Position position)
{
  static const array<array<IncrementalUpdater::score_t, BitBoard::c_bitboard_size>, 2 * PieceSet::c_no_pieces> piece_square_values =
      generate_piece_square_values();
  IncrementalUpdater::score_t result = IncrementalUpdater::piece_values()[piece_index];
  const int index = endgame * PieceSet::c_no_pieces + piece_index;
  // TODO Do this logic by lookup.
  if (color == Color::White) {
    const Position::index_t position_index = position.index();
    result += piece_square_values[index][position_index];
    return result;
  } else {
    Position pos(Position::c_row_size - 1 - position.row(), position.column());
    const Position::index_t position_index = pos.index();
    result += piece_square_values[index][position_index];
    return -result;
  }
}

void IncrementalUpdater::calculate(const ChessBoard& board, IncrementalState* const state)
{
  state->incremental_score_white_middlegame = 0;
  state->incremental_score_white_endgame = 0;
  state->incremental_score_white = 0;
  state->material_score = 0;
  for (const Color color : c_colors) {
    const ColorBoard& color_board = board.color_board(color);
    for (Piece::piece_index_t piece_index = 0; piece_index < PieceSet::c_no_pieces; ++piece_index) {
      BitBoard piece_board = color_board.piece_board(piece_index);
      while (piece_board) {
        add_piece(color, piece_index, piece_board.next_position(), state);
      }
    }
  }
}

static const array<IncrementalUpdater::score_t, PieceSet::c_no_pieces> material_scores()
{
  static const array<IncrementalUpdater::score_t, PieceSet::c_no_pieces> scores = generate_material_scores();
  return scores;
}

static double generate_material_factor()
{
  IncrementalUpdater::score_t sum = 0;
  for (Piece::piece_index_t piece_index = 0; piece_index < PieceSet::c_no_pieces; ++piece_index) {
    const int no_pieces = 2 * PieceSet::instance().piece(piece_index).initial_board(Color::White).number();
    const IncrementalUpdater::score_t score = material_scores()[piece_index];
    sum += no_pieces * score;
  }
  return 1.0 / sum;
}

static void update_total_score(IncrementalState* const state)
{
  static const double c_material_factor = generate_material_factor();
  const double middlegame_weight = min(state->material_score * c_material_factor, 1.0);
  assert(middlegame_weight >= 0 && middlegame_weight <= 1);
  state->incremental_score_white =
      state->incremental_score_white_endgame * (1 - middlegame_weight)
      + state->incremental_score_white_middlegame * middlegame_weight;
}

void IncrementalUpdater::remove_piece(const Color color,
                                      const Piece::piece_index_t index,
                                      const Position position,
                                      IncrementalState* const state)
{
  const score_t middlegame_value = -piece_value(color, 0, index, position);
  const score_t endgame_value = -piece_value(color, 1, index, position);
  state->incremental_score_white_middlegame += middlegame_value;
  state->incremental_score_white_endgame += endgame_value;
  state->material_score -= material_scores()[index];
  update_total_score(state);
}

void IncrementalUpdater::add_piece(const Color color,
                                   const Piece::piece_index_t index,
                                   const Position position,
                                   IncrementalState* const state)
{
  const score_t middlegame_value = piece_value(color, 0, index, position);
  const score_t endgame_value = piece_value(color, 1, index, position);
  state->incremental_score_white_middlegame += middlegame_value;
  state->incremental_score_white_endgame += endgame_value;
  state->material_score += material_scores()[index];
  update_total_score(state);
}

} // namespace olaf
