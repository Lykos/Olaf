#include "olaf/rules/movechecker.h"

#include <cassert>
#include <vector>

#include "olaf/rules/pawn.h"
#include "olaf/rules/pieceset.h"
#include "olaf/rules/move.h"
#include "olaf/rules/undoinfo.h"

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
  const Position src(incomplete_move.source());
  return board.friendd(src)
      && board.turn_board().piece(src).can_move(incomplete_move, board);
}

// static
Move MoveChecker::complete(IncompleteMove incomplete_move,
                           const ChessBoard& board)
{
  const Position src(incomplete_move.source());
  const Piece::piece_index_t piece_index = board.turn_board().piece_index(src);
  assert(piece_index != Piece::c_no_piece);
  assert(board.turn_board().piece(src).can_move(incomplete_move, board));
  const Position dst(incomplete_move.destination());
  const Color turn_color = board.turn_color();
  const Position::row_t gnd = ground_line(turn_color);
  if (src.row() == gnd
      && dst.row() == gnd
      && abs(src.column() - dst.column()) == 2
      && piece_index == PieceSet::c_king_index) {
    if (dst.column() == Position::c_kings_knight_column) {
      return Move(src, dst, Move::c_castle_k_flag);
    } else {
      assert(dst.column() == Position::c_queens_bishop_column);
      return Move(src, dst, Move::c_castle_q_flag);
    }
  }
  BitBoard capturable = board.opponents() | board.king_captures();
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
      board.noturn_board().piece_board(PieceSet::c_king_index).bit_board() | board.king_captures();
  if (!king_captures) {
    return false;
  }
  const vector<Position>& king_positions = king_captures.positions();
  if (king_positions.empty()) {
    return false;
  }
  for (const PieceBoard& piece_board : board.turn_board().piece_boards()) {
    const Piece& piece = piece_board.piece();
    for (Position source : piece_board.positions()) {
      for (const Position& king_position : king_positions) {
        static const Pawn& pawn = PieceSet::instance().pawn();
        if (piece.can_move(IncompleteMove(source, king_position), board)) {
          return true;
        } else if (&piece == &pawn
                   && pawn.can_move(IncompleteMove::promotion(source, king_position, PieceSet::c_queen_index), board)) {
          return true;
        }
      }
    }
  }
  return false;
}

} // namespace olaf
