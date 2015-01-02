#include "olaf/rules/movechecker.h"

#include <cassert>
#include <vector>

#include "olaf/rules/pieceset.h"
#include "olaf/rules/move.h"
#include "olaf/rules/undoinfo.h"
#include "olaf/rules/magicmoves.h"
#include "olaf/rules/magicnumbers.h"

using namespace std;

namespace olaf
{

// static
bool MoveChecker::valid_move(const ChessBoard& board,
                             const IncompleteMove incomplete_move)
{
  if (!pseudo_valid_move(board, incomplete_move)) {
    return false;
  } else {
    UndoInfo undo_info;
    ChessBoard try_board(board);
    complete(incomplete_move, try_board).execute(&try_board, &undo_info);
    return !can_kill_king(try_board);
  }
}

// static
bool MoveChecker::pseudo_valid_move(const ChessBoard& board,
                                    const IncompleteMove incomplete_move)
{
  // TODO Improve this.
  const Position source(incomplete_move.source());
  const BitBoard destinations(incomplete_move.destination());
  if (board.rook_board(board.turn_color()).get(source)) {
    return destinations & MagicMoves::moves_rook(source, board);
  } else if (board.knight_board(board.turn_color()).get(source)) {
    return destinations & MagicMoves::moves_knight(source, board);
  } else if (board.bishop_board(board.turn_color()).get(source)) {
    return destinations & MagicMoves::moves_bishop(source, board);
  } else if (board.queen_board(board.turn_color()).get(source)) {
    return destinations & MagicMoves::moves_queen(source, board);
  } else if (board.king_board(board.turn_color()).get(source)) {
    return destinations & MagicMoves::moves_king(source, board);
  } else if (board.pawn_board(board.turn_color()).get(source)) {
    return destinations & MagicMoves::moves_pawn(source, board);
  } else {
    return false;
  }
}

// static
Move MoveChecker::complete(IncompleteMove incomplete_move,
                           const ChessBoard& board)
{
  const Position src(incomplete_move.source());
  const Piece::piece_index_t piece_index = board.piece_index(src);
  const Position dst(incomplete_move.destination());
  const int color_index = static_cast<int>(board.turn_color());
  if (BitBoard(src) & BitBoard(MagicNumbers::c_king_positions[color_index])
      && BitBoard(dst) & BitBoard(MagicNumbers::c_castle_squares[color_index])
      && piece_index == PieceSet::c_king_index) {
    if (dst.column() == Position::c_kings_knight_column) {
      return Move(src, dst, Move::c_castle_k_flag);
    } else {
      assert(dst.column() == Position::c_queens_bishop_column);
      return Move(src, dst, Move::c_castle_q_flag);
    }
  }
  const BitBoard capturable = board.opponents();
  const BitBoard dst_board(dst);
  const bool is_capture = capturable & dst_board;
  if (piece_index == PieceSet::c_pawn_index) {
    if (board.ep_captures() & dst_board) {
      return Move(src, dst, Move::c_ep_flag);
    } else if (incomplete_move.is_promotion()) {
      const uint16_t flags = (static_cast<uint16_t>(is_capture) << 14) | incomplete_move.m_state;
      return Move(src, dst, flags);
    } else if (abs(src.row() - dst.row()) == 2) {
      return Move(src, dst, Move::c_double_pawn_push_flag);
    }
  }
  return Move(src, dst, is_capture << 14);
}

// static
bool MoveChecker::can_kill_king(const ChessBoard& board)
{
  const BitBoard king_captures =
      board.king_board(board.noturn_color()) | board.king_captures();
  if (!king_captures) {
    return false;
  }
  for (BitBoard sources = board.rook_board(board.turn_color()); sources;) {
    const Position source = sources.next_position();
    if (king_captures & MagicMoves::moves_rook(source, board)) {
      return true;
    }
  }
  for (BitBoard sources = board.knight_board(board.turn_color()); sources;) {
    const Position source = sources.next_position();
    if (king_captures & MagicMoves::moves_knight(source, board)) {
      return true;
    }
  }
  for (BitBoard sources = board.bishop_board(board.turn_color()); sources;) {
    const Position source = sources.next_position();
    if (king_captures & MagicMoves::moves_bishop(source, board)) {
      return true;
    }
  }
  for (BitBoard sources = board.queen_board(board.turn_color()); sources;) {
    const Position source = sources.next_position();
    if (king_captures & MagicMoves::moves_queen(source, board)) {
      return true;
    }
  }
  for (BitBoard sources = board.king_board(board.turn_color()); sources;) {
    const Position source = sources.next_position();
    if (king_captures & MagicMoves::moves_king(source, board)) {
      return true;
    }
  }
  for (BitBoard sources = board.pawn_board(board.turn_color()); sources;) {
    const Position source = sources.next_position();
    if (king_captures & MagicMoves::moves_pawn(source, board)) {
      return true;
    }
  }
  return false;
}

} // namespace olaf
