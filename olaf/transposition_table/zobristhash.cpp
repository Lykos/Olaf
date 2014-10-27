#include "olaf/transposition_table/zobristhash.h"

#include "olaf/rules/chessboard.h"
#include "olaf/rules/color.h"
#include "olaf/rules/pieceset.h"
#include "olaf/rules/bitboard.h"
#include "olaf/transposition_table/randomnumbers.h"

namespace olaf
{

static_assert(RandomNumbers::c_no_colors == c_no_colors, "Different number of colors.");

static_assert(RandomNumbers::c_no_pieces == PieceSet::c_no_pieces, "Different number of pieces.");

static_assert(RandomNumbers::c_no_squares == BitBoard::c_bitboard_size, "Different number of squares.");

// static
void ZobristHash::calculate(ChessBoard* const board)
{
  board->m_zobrist_hash = 0;
  for (const Color color : c_colors) {
    for (const PieceBoard& piece_board : board->color_board(color).piece_boards()) {
      if (piece_board.bit_board() == 0) {
        continue;
      }
      const Piece::piece_index_t piece_index =
          piece_board.piece().piece_index();
      for (const Position& position : piece_board.positions()) {
        update(color, piece_index, position, board);
      }
    }
    if (board->color_board(color).can_castle_k()) {
      update_castle_k(color, board);
    }
    if (board->color_board(color).can_castle_q()) {
      update_castle_q(color, board);
    }
  }
  if (board->ep_possible()) {
    update_ep(board->ep_captures().first_position(), board);
  }
  if (board->turn_color() == Color::Black) {
    update_turn_color(board);
  }
}

// static
void ZobristHash::update(Color color,
                         Piece::piece_index_t piece_index,
                         const Position& position,
                         ChessBoard* board)
{
  const int color_index = static_cast<int>(color);
  board->m_zobrist_hash ^= RandomNumbers::c_piece_randomness[color_index * PieceSet::c_no_pieces * BitBoard::c_bitboard_size + piece_index * BitBoard::c_bitboard_size + BitBoard::index(position)];
}

// static
void ZobristHash::update_castle_k(const Color color,
                                  ChessBoard* const board)
{
  const int color_index = static_cast<int>(color);
  board->m_zobrist_hash ^= RandomNumbers::c_castle_k_randomness[color_index];
}

// static
void ZobristHash::update_castle_q(const Color color,
                                  ChessBoard* const board)
{
  const int color_index = static_cast<int>(color);
  board->m_zobrist_hash ^= RandomNumbers::c_castle_q_randomness[color_index];
}

// static
void ZobristHash::update_ep(const Position& position,
                            ChessBoard* const board)
{
  board->m_zobrist_hash ^= RandomNumbers::c_ep_randomness[BitBoard::index(position)];
}

// static
void ZobristHash::update_turn_color(ChessBoard* const board)
{
  board->m_zobrist_hash ^= RandomNumbers::c_turn_color_randomness;
}

} // namespace olaf
