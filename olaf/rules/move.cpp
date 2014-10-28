#include "olaf/rules/move.h"

#include <cassert>
#include <iostream>

#include "olaf/rules/chessboard.h"
#include "olaf/rules/pieceset.h"
#include "olaf/rules/undoinfo.h"
#include "olaf/rules/color.h"
#include "olaf/rules/pawn.h"

using namespace std;

namespace olaf
{

bool IncompleteMove::is_pseudo_valid(const ChessBoard& board) const
{
  const Position src(source());
  const Piece::piece_index_t piece_index =
      board.turn_board().piece_index(src);
  if (piece_index == Piece::c_no_piece) {
    return false;
  }
  return board.turn_board().piece(src).can_move(*this, board);
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
      PieceSet::c_king_index;
  if (is_capture()) {
    Position victim_position;
    if (is_ep()) {
      victim_position = dst + forward_direction(noturn_color);
    } else if (BitBoard(dst) & board->king_captures()) {
      victim_position =
          board->color_board(noturn_color).piece_board(c_king_index).bit_board().first_position();
    } else {
      victim_position = dst;
    }
    const Piece::piece_index_t captured_piece =
        board->color_board(noturn_color).piece_index(victim_position);
    undo_info->captured_piece = captured_piece;
    undo_info->victim_position = victim_position;
    board->remove_piece(noturn_color, captured_piece, victim_position);
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
      PieceSet::c_rook_index;
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
  undo_info->reversible_plies = board->reversible_plies();
  if (piece_index == PieceSet::c_pawn_index || is_capture()) {
    board->reset_reversible_plies();
  } else {
    board->increment_reversible_plies();
  }
  board->next_turn();
}

void Move::undo(const UndoInfo& undo_info, ChessBoard* const board) const
{
  board->previous_turn();
  board->reversible_plies(undo_info.reversible_plies);
  const Position src(source());
  const Position dst(destination());
  const Color turn_color = board->turn_color();
  const Color noturn_color = other_color(turn_color);
  const Piece::piece_index_t piece_index = board->turn_board().piece_index(dst);
  if (is_castle()) {
    static const Piece::piece_index_t c_rook_index =
        PieceSet::c_rook_index;
    board->remove_piece(turn_color, c_rook_index, undo_info.rook_destination);
    board->add_piece(turn_color, c_rook_index, undo_info.rook_source);
  }
  board->king_captures(undo_info.king_captures);
  board->can_castle_k(turn_color, undo_info.can_castle_k);
  board->can_castle_q(turn_color, undo_info.can_castle_q);
  board->remove_piece(turn_color, piece_index, dst);
  if (is_promotion()) {
    Piece::piece_index_t c_pawn_index = PieceSet::c_pawn_index;
    board->add_piece(turn_color, c_pawn_index, src);
  } else {
    board->add_piece(turn_color, piece_index, src);
  }
  if (is_capture()) {
    board->add_piece(noturn_color, undo_info.captured_piece, undo_info.victim_position);
  }
  board->ep_captures(undo_info.ep_captures);
  assert(is_pseudo_valid(*board));
}

std::ostream& operator <<(std::ostream& out, IncompleteMove move)
{
  out << "Move(" << move.source() << " " << move.destination();
  if (move.is_king_castle()) {
    out << " castle k";
  }
  if (move.is_queen_castle()) {
    out << " castle q";
  }
  if (move.is_capture()) {
    out << " capture";
  }
  if (move.is_promotion()) {
    out << " promotes to " << move.created_piece();
  }
  return out << ")";
}

std::ostream& operator <<(std::ostream& out, const Move move)
{
  return out << IncompleteMove(move);
}

} // namespace olaf
