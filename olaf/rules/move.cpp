#include "olaf/rules/move.h"

#include <cassert>
#include <iostream>

#include "olaf/rules/chessboard.h"
#include "olaf/rules/pieceset.h"
#include "olaf/rules/undoinfo.h"
#include "olaf/rules/color.h"
#include "olaf/rules/magicnumbers.h"

using namespace std;

namespace olaf
{

static array<Position::index_t, Position::c_index_size> c_ep_victims = {
   0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,
  24, 25, 26, 27, 28, 29, 30, 31,
   0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,
  32, 33, 34, 35, 36, 37, 38, 39,
   0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0
};

void Move::execute(ChessBoard* const board, UndoInfo* const undo_info) const
{
  const Position src(source());
  const Position dst(destination());
  const Color turn_color = board->turn_color();
  const int color_index = static_cast<int>(turn_color);
  const Color noturn_color = other_color(turn_color);
  const Piece::piece_index_t piece_index = board->piece_index(src);
  undo_info->ep_captures = board->ep_captures();
  if (is_double_pawn_push()) {
    const int color_square_index = color_index * Position::c_index_size + src.index();
    board->ep_captures(MagicNumbers::c_pawn_one_step_table[color_square_index]);
  } else {
    board->disable_ep();
  }
  static const Piece::piece_index_t c_king_index =
      PieceSet::c_king_index;
  if (is_capture()) {
    Position victim_position;
    if (is_ep()) {
      victim_position = Position(c_ep_victims[dst.index()]);
    } else if (BitBoard(dst) & board->king_captures()) {
      victim_position =
          board->color_board(noturn_color).piece_board(c_king_index).first_position();
    } else {
      victim_position = dst;
    }
    const Piece::piece_index_t captured_piece =
        board->piece_index(victim_position);
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
  static const Piece::piece_index_t c_rook_index =
      PieceSet::c_rook_index;
  const BitBoard src_board(src);
  if (is_castle()) {
    board->can_castle_k(board->turn_color(), false);
    board->can_castle_q(board->turn_color(), false);
    Position rook_source;
    Position rook_destination;
    if (is_king_castle()) {
      rook_source = BitBoard(MagicNumbers::c_castle_k_rook_src[color_index]).first_position();
      rook_destination = BitBoard(MagicNumbers::c_castle_k_rook_dst[color_index]).first_position();
    } else {
      rook_source = BitBoard(MagicNumbers::c_castle_q_rook_src[color_index]).first_position();
      rook_destination = BitBoard(MagicNumbers::c_castle_q_rook_dst[color_index]).first_position();
    }
    undo_info->rook_source = rook_source;
    undo_info->rook_destination = rook_destination;
    board->remove_piece(turn_color, c_rook_index, rook_source);
    board->add_piece(turn_color, c_rook_index, rook_destination);
    board->king_captures(src_board | BitBoard(rook_destination));
  } else {
    board->disable_king_captures();
    if (piece_index == c_king_index) {
      board->can_castle_k(turn_color, false);
      board->can_castle_q(turn_color, false);
    } else if (piece_index == c_rook_index) {
      if (src_board & BitBoard(MagicNumbers::c_castle_k_rook_src[color_index])) {
        board->can_castle_k(turn_color, false);
      } else if (src_board & BitBoard(MagicNumbers::c_castle_q_rook_src[color_index])) {
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
  const Piece::piece_index_t piece_index = board->piece_index(dst);
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
