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
BitBoard MagicMoves::moves_king(const Position& source, const ChessBoard& board)
{
  BitBoard result = BitBoard(MagicNumbers::c_king_table[BitBoard::index(source)]) & BitBoard(~board.friends());
  const Color color = board.turn_color();
  const ColorBoard& turn_board = board.color_board(color);
  const int index = static_cast<int>(color);
  if (turn_board.piece_board(PieceSet::c_king_index).bit_board() == BitBoard(MagicNumbers::c_king_positions[index])) {
    if (turn_board.can_castle_k()
        && !(board.occupied() & BitBoard(MagicNumbers::c_castle_k_room[index]))
        && (turn_board.piece_board(PieceSet::c_rook_index) & BitBoard(MagicNumbers::c_castle_k_rook[index]))) {
      result = result | BitBoard(MagicNumbers::c_castle_k_square[index]);
    }
    if (turn_board.can_castle_q()
        && !(board.occupied() & BitBoard(MagicNumbers::c_castle_q_room[index]))
        && (turn_board.piece_board(PieceSet::c_rook_index) & BitBoard(MagicNumbers::c_castle_q_rook[index]))) {
      result = result | BitBoard(MagicNumbers::c_castle_q_square[index]);
    }
  }
  return result;
}

// static
BitBoard MagicMoves::moves_pawn(const Position& source, const ChessBoard& board)
{
  const BitBoard free = ~board.occupied();
  const int color_index = static_cast<int>(board.turn_color()) * BitBoard::c_bitboard_size;
  const int position_index = BitBoard::index(source);
  BitBoard result = BitBoard(MagicNumbers::c_pawn_one_step_table[color_index + position_index]) & free;
  if (result) {
    result = result | (BitBoard(MagicNumbers::c_pawn_two_step_table[color_index + position_index]) & free);
  }
  const BitBoard capturable = board.opponents() | board.ep_captures() | board.king_captures();
  result = result | (BitBoard(MagicNumbers::c_pawn_capture_table[color_index + position_index]) & capturable);
  return result;
}

} // namespace
