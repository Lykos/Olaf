#include "kingsafetyevaluator.h"

#include <array>

#include "incrementalupdater.h"

using namespace std;

namespace olaf
{

static const array<bitboard_t, 2 * BitBoard::c_bitboard_size> c_pawn_shield = {
  0x70700, 0x70700, 0xe0e00, 0x1c1c00, 0x383800, 0x707000, 0xe0e000, 0xe0e000,
  0x70700, 0x70700, 0xe0e00, 0x1c1c00, 0x383800, 0x707000, 0xe0e000, 0xe0e000,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0x7070000000000, 0x7070000000000, 0xe0e0000000000, 0x1c1c0000000000,
  0x38380000000000, 0x70700000000000, 0xe0e00000000000, 0xe0e00000000000,
  0x7070000000000, 0x7070000000000, 0xe0e0000000000, 0x1c1c0000000000,
  0x38380000000000, 0x70700000000000, 0xe0e00000000000, 0xe0e00000000000
};

static const PositionEvaluator::score_t c_pawn_shield_score = 10;

static PositionEvaluator::score_t pawn_shield_score(const ChessBoard& board,
                                                    const Position king_position,
                                                    const Color color)
{
  const int color_index = static_cast<int>(color) * BitBoard::c_bitboard_size;
  const BitBoard potential_pawn_shield(c_pawn_shield[color_index + king_position.index()]);
  const BitBoard pawn_shield = potential_pawn_shield & board.pawn_board(color);
  return pawn_shield.number() * c_pawn_shield_score;
}

static const PositionEvaluator::score_t c_own_semi_open_file_score = -12;
static const PositionEvaluator::score_t c_opposing_semi_open_file_score = -8;

static PositionEvaluator::score_t column_score(const ChessBoard& board, const Color color, const Position::index_t column)
{
  const BitBoard opponent_pawns = board.pawn_board(other_color(color));
  const BitBoard friend_pawns = board.pawn_board(other_color(color));
  const BitBoard column_board = c_columns[column];
  return ((column_board & friend_pawns) == BitBoard(0)) * c_own_semi_open_file_score
      + ((column_board & opponent_pawns) == BitBoard(0)) * c_opposing_semi_open_file_score;
}

static PositionEvaluator::score_t open_files_score(const ChessBoard& board,
                                                   const Position king_position,
                                                   const Color color)
{
  const Position::index_t column = king_position.column();
  if (column == 0) {
    return column_score(board, color, column) + column_score(board, color, column + 1);
  } else if (column == Position::c_column_size - 1) {
    return column_score(board, color, column - 1) + column_score(board, color, column);
  } else {
    return column_score(board, color, column - 1) + column_score(board, color, column) + column_score(board, color, column + 1);
  }
}

static PositionEvaluator::score_t king_safety_score(const ChessBoard& board, const Color color)
{
  const Position king_position = board.king_board(color).first_position();
  const PositionEvaluator::score_t score = pawn_shield_score(board, king_position, color) + open_files_score(board, king_position, color);
  return score;
}

PositionEvaluator::score_t KingSafetyEvaluator::evaluate(
    SearchState* const /* state */, SearchContext* const context)
{
  const ChessBoard& board = context->board;
  const score_t score = king_safety_score(board, board.turn_color()) - king_safety_score(board, board.noturn_color());
  return IncrementalUpdater::weighted_score(score, 0, board.incremental_state().material_score);
}

} // namespace olaf
