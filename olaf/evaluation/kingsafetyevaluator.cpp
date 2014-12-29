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
  const ColorBoard& color_board = board.color_board(color);
  const int color_index = static_cast<int>(board.turn_color()) * BitBoard::c_bitboard_size;
  const BitBoard potential_pawn_shield(c_pawn_shield[color_index + king_position.index()]);
  const BitBoard pawn_shield = potential_pawn_shield & color_board.piece_board(PieceSet::c_pawn_index);
  return pawn_shield.number() * c_pawn_shield_score;
}

static const PositionEvaluator::score_t c_open_file_score = 10;

static PositionEvaluator::score_t open_files_score(const ChessBoard& board,
                                                   const Position king_position,
                                                   const Color color)
{
#define has_pawns(col) ((c_columns[col] & pawns) != BitBoard(0))
  const BitBoard pawns = board.color_board(other_color(color)).piece_board(PieceSet::c_pawn_index);
  const Position::index_t column = king_position.column();
  PositionEvaluator::score_t open_files;
  if (column == 0) {
    open_files = has_pawns(column) + has_pawns(column + 1);
  } else if (column == Position::c_column_size - 1) {
    open_files = has_pawns(column - 1) + has_pawns(column);
  } else {
    open_files = has_pawns(column - 1) + has_pawns(column) + has_pawns(column + 1);
  }
#undef has_pawns
  return open_files * c_open_file_score;
}

static PositionEvaluator::score_t king_safety_score(const ChessBoard& board, const Color color)
{
  const Position king_position = board.color_board(color).piece_board(PieceSet::c_king_index).first_position();
  return pawn_shield_score(board, king_position, color) + open_files_score(board, king_position, color);
}

PositionEvaluator::score_t KingSafetyEvaluator::evaluate(
    SearchState* const /* state */, SearchContext* const context)
{
  const ChessBoard& board = context->board;
  const score_t score = king_safety_score(board, board.turn_color()) - king_safety_score(board, board.noturn_color());
  return IncrementalUpdater::weighted_score(score, 0, board.incremental_state().material_score);
}

} // namespace olaf
