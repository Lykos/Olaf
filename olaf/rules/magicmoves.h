#ifndef MAGICMOVES_H
#define MAGICMOVES_H

#include <array>

#include "olaf/rules/bitboard.h"
#include "olaf/rules/magicnumbers.h"
#include "olaf/rules/chessboard.h"
#include "olaf/rules/position.h"

namespace olaf
{

class MagicMoves
{
public:
  static inline BitBoard sliding_magic_moves(const std::array<Magic, BitBoard::c_bitboard_size>& magics,
                                             const Position& source,
                                             const BitBoard occupied)
  {
    const Magic& magic = magics[BitBoard::index(source)];
    const uint64_t board = occupied;
    return magic.ptr[((board & magic.mask) * magic.magic) >> magic.shift];
  }

  static inline BitBoard moves_rook(const Position& source, const ChessBoard& board)
  {
    return sliding_magic_moves(MagicNumbers::c_rook_magic, source, board.occupied()) & BitBoard(~board.friends());
  }

  static inline BitBoard moves_bishop(const Position& source, const ChessBoard& board)
  {
    return sliding_magic_moves(MagicNumbers::c_bishop_magic, source, board.occupied()) & BitBoard(~board.friends());
  }

  static inline BitBoard moves_queen(const Position& source, const ChessBoard& board)
  {
    return (sliding_magic_moves(MagicNumbers::c_rook_magic, source, board.occupied())
            | sliding_magic_moves(MagicNumbers::c_bishop_magic, source, board.occupied())) & BitBoard(~board.friends());
  }

  static inline BitBoard moves_knight(const Position& source, const ChessBoard& board)
  {
    return BitBoard(MagicNumbers::c_knight_table[BitBoard::index(source)]) & BitBoard(~board.friends());
  }

  static inline BitBoard king_unmoved(const ChessBoard& board, const Color color)
  {
    int index = static_cast<int>(color);
    const BitBoard king_positions = board.color_board(color).piece_board(PieceSet::c_king_index).bit_board();
    return king_positions == BitBoard(MagicNumbers::c_king_positions[index]);
  }

  static inline BitBoard can_castle_k(const ChessBoard& board, const Color color)
  {
    int index = static_cast<int>(color);
    const ColorBoard& color_board = board.color_board(color);
    return color_board.can_castle_k()
        && !(board.occupied() & BitBoard(MagicNumbers::c_castle_k_room[index]))
        && (color_board.piece_board(PieceSet::c_rook_index) & BitBoard(MagicNumbers::c_castle_k_rook[index]));
  }

  static inline BitBoard can_castle_q(const ChessBoard& board, const Color color)
  {
    int index = static_cast<int>(color);
    const ColorBoard& color_board = board.color_board(color);
    return color_board.can_castle_q()
        && !(board.occupied() & BitBoard(MagicNumbers::c_castle_q_room[index]))
        && (color_board.piece_board(PieceSet::c_rook_index) & BitBoard(MagicNumbers::c_castle_q_rook[index]));
  }

  static BitBoard moves_king(const Position& source, const ChessBoard& board);

  static BitBoard moves_pawn(const Position& source, const ChessBoard& board);
};

} // namespace

#endif // MAGICMOVES_H
