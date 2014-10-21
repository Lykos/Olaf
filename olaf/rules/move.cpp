#include "olaf/rules/move.h"

#include <cassert>

#include "olaf/rules/chessboard.h"
#include "olaf/rules/pieceset.h"
#include "olaf/rules/undoinfo.h"
#include "olaf/rules/color.h"

using namespace std;

namespace olaf
{

bool Move::is_pseudo_valid(const ChessBoard& board) const
{
  const Position src(source());
  const Piece::piece_index_t piece_index =
      board.turn_board().piece_index(src);
  if (piece_index == Piece::c_no_piece) {
    return false;
  }
  return board.turn_board().piece(src).can_move(*this, board);
}

// static
Move Move::complete(IncompleteMove incomplete_move,
                    const ChessBoard& board)
{
  const Position src(incomplete_move.source());
  const Piece::piece_index_t piece_index = board.turn_board().piece_index(src);
  assert(piece_index != Piece::c_no_piece);
  assert(board.turn_board().piece(src).can_move(incomplete_move, board));
  const Position dst(incomplete_move.destination());
  const Color turn_color = board.turn_color();
  const Position::row_t gnd = ground_line(turn_color);
  static const Piece::piece_index_t c_king_index =
      PieceSet::instance().king().piece_index();
  if (src.row() == gnd
      && dst.row() == gnd
      && abs(src.column() - dst.column()) == 2
      && piece_index == c_king_index) {
    if (dst.column() == Position::c_kings_knight_column) {
      return Move(src, dst, c_castle_k_flag);
    } else {
      assert(dst.column() == Position::c_queens_bishop_column);
      return Move(src, dst, c_castle_q_flag);
    }
  }
  static const Piece::piece_index_t c_pawn_index =
      PieceSet::instance().pawn().piece_index();
  BitBoard capturable = board.opponents() | board.king_captures();
  const BitBoard dst_board(dst);
  const bool is_capture = (capturable & dst_board) != 0;
  if (piece_index == c_pawn_index) {
    if ((board.ep_captures() & dst_board) != 0) {
      Move(src, dst, c_ep_flag);
    } else if (incomplete_move.is_promotion()) {
      incomplete_move.m_state |= is_capture << 14;
      return incomplete_move;
    } else if (abs(src.row() - dst.row()) == 2) {
      return Move(src, dst, c_double_pawn_push_flag);
    }
  }
  return Move(src, dst, is_capture << 14);
}

void Move::execute(ChessBoard* const board, UndoInfo* const undo_info) const
{
  assert(is_pseudo_valid(*board));
  const Position src(source());
  const Position dst(destination());
  const Color turn_color = board->turn_color();
  const Color noturn_color = other_color(turn_color);
  const Piece::piece_index_t piece_index = board->turn_board().piece_index(src);
  undo_info->ep_captures = board->ep_captures();
  if (is_double_pawn_push()) {
    board->ep_captures(BitBoard(Position((src.row() + dst.row()) / 2, src.column())));
  } else {
    board->disable_ep();
  }
    static const Piece::piece_index_t c_king_index =
        PieceSet::instance().king().piece_index();  if (is_capture()) {
    Position victim_position;
    if (is_ep()) {
      victim_position = dst + forward_direction(noturn_color);
    } else if ((BitBoard(dst) & board->king_captures()) != 0) {
      victim_position =
          board->color_board(noturn_color).piece_board(c_king_index).bit_board().first_position();
    } else {
      victim_position = dst;
    }
    const Piece::piece_index_t captured_piece =
        board->color_board(noturn_color).piece_index(victim_position);
    undo_info->captured_piece = captured_piece;
    undo_info->victim_position = victim_position;
    board->remove_piece(noturn_color, captured_piece, dst);
  }
  board->remove_piece(turn_color, piece_index, src);
  if (is_promotion()) {
    board->add_piece(turn_color, created_piece(), dst);
  } else {
    board->add_piece(turn_color, piece_index, dst);
  }
  undo_info->can_castle_k = board->turn_board().can_castle_k();
  undo_info->can_castle_q = board->turn_board().can_castle_q();
  undo_info->king_captures = board->king_captures();
  const Position::row_t gnd = ground_line(board->turn_color());
  static const Piece::piece_index_t c_rook_index =
      PieceSet::instance().rook().piece_index();
  if (is_castle()) {
    board->can_castle_k(board->turn_color(), false);
    board->can_castle_q(board->turn_color(), false);
    Position::column_t rook_source_column;
    Position::column_t rook_destination_column;
    if (is_king_castle()) {
      rook_source_column = Position::c_kings_rook_column;
      rook_destination_column = Position::c_kings_bishop_column;
    } else {
      rook_source_column = Position::c_queens_rook_column;
      rook_destination_column = Position::c_queen_column;
    }
    const Position rook_source(gnd, rook_source_column);
    const Position rook_destination(gnd, rook_destination_column);
    undo_info->rook_source = rook_source;
    undo_info->rook_destination = rook_destination;
    board->remove_piece(turn_color, c_rook_index, rook_source);
    board->add_piece(turn_color, c_rook_index, rook_destination);
    board->king_captures(BitBoard(src) | BitBoard(rook_destination));
  } else {
    board->disable_king_captures();
    if (piece_index == c_king_index) {
      board->can_castle_k(turn_color, false);
      board->can_castle_q(turn_color, false);
    } else if (piece_index == c_rook_index && src.row() == gnd) {
      if (src.column() == Position::c_kings_rook_column) {
        board->can_castle_k(turn_color, false);
      } else if (src.column() == Position::c_queens_rook_column) {
        board->can_castle_q(turn_color, false);
      }
    }
  }
  board->next_turn();
}

void Move::undo(const UndoInfo& undo_info, ChessBoard* const board) const
{
  board->previous_turn();
  const Position src(source());
  const Position dst(destination());
  const Color turn_color = board->turn_color();
  const Color noturn_color = other_color(turn_color);
  const Piece::piece_index_t piece_index = board->turn_board().piece_index(src);
  if (is_castle()) {
    static const Piece::piece_index_t c_rook_index =
        PieceSet::instance().rook().piece_index();
    board->remove_piece(turn_color, c_rook_index, undo_info.rook_destination);
    board->add_piece(turn_color, c_rook_index, undo_info.rook_source);
  }
  board->king_captures(undo_info.king_captures);
  board->can_castle_k(turn_color, undo_info.can_castle_k);
  board->can_castle_q(turn_color, undo_info.can_castle_q);
  if (is_promotion()) {
    board->remove_piece(turn_color, created_piece(), dst);
  } else {
    board->remove_piece(turn_color, piece_index, dst);
  }
  board->add_piece(turn_color, piece_index, src);
  if (is_capture()) {
    board->add_piece(noturn_color, undo_info.captured_piece, undo_info.victim_position);
  }
  board->ep_captures(undo_info.ep_captures);
  assert(is_pseudo_valid(*board));
}

std::ostream& operator <<(std::ostream& out, Move move)
{
  out << "Move(" << move.source() << " " << move.destination();
  if (move.is_capture()) {
    out << " capture";
  }
  if (move.is_promotion()) {
    out << " promotes to " << move.created_piece();
  }
  return out << ")";

} // namespace olaf
}
