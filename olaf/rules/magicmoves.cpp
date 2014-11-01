#include "olaf/rules/magicmoves.h"

#include <array>

#include "olaf/rules/bitboard.h"
#include "olaf/rules/chessboard.h"
#include "olaf/rules/position.h"
#include "olaf/rules/magicnumbers.h"

using namespace std;

namespace olaf
{

static_assert(MagicNumbers::c_no_colors == c_no_colors, "Different number of colors");
static_assert(MagicNumbers::c_no_squares == BitBoard::c_bitboard_size, "Different number of squares");


// static
BitBoard MagicMoves::moves_king(const Position source, const ChessBoard& board)
{
  BitBoard result = BitBoard(MagicNumbers::c_king_table[source.index()]) & BitBoard(~board.friends());
  const Color color = board.turn_color();
  const int index = static_cast<int>(color);
  if (king_unmoved(board, color)) {
    if (can_castle_k(board, color)) {
      result = result | BitBoard(MagicNumbers::c_castle_k_square[index]);
    }
    if (can_castle_q(board, color)) {
      result = result | BitBoard(MagicNumbers::c_castle_q_square[index]);
    }
  }
  return result;
}

// static
BitBoard MagicMoves::moves_pawn(const Position source, const ChessBoard& board)
{
  const BitBoard free = ~board.occupied();
  const int color_index = static_cast<int>(board.turn_color()) * BitBoard::c_bitboard_size;
  const int position_index = source.index();
  BitBoard result = BitBoard(MagicNumbers::c_pawn_one_step_table[color_index + position_index]) & free;
  if (result) {
    result = result | (BitBoard(MagicNumbers::c_pawn_two_step_table[color_index + position_index]) & free);
  }
  const BitBoard capturable = board.opponents() | board.ep_captures() | board.king_captures();
  result = result | (BitBoard(MagicNumbers::c_pawn_capture_table[color_index + position_index]) & capturable);
  return result;
}

} // namespace
