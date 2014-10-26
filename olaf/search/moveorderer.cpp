#include "olaf/search/moveorderer.h"

#include <array>
#include <cassert>
#include <iostream>

#include "olaf/transposition_table/transpositiontable.h"
#include "olaf/search/searchcontext.h"

using namespace std;

namespace olaf
{

BitBoard least_valuable_piece(const ChessBoard& board, const Color color, const BitBoard attackers)
{
  static const array<Piece::piece_index_t, PieceSet::c_no_pieces> piece_values = {
    PieceSet::c_pawn_index,
    PieceSet::c_knight_index,
    PieceSet::c_bishop_index,
    PieceSet::c_rook_index,
    PieceSet::c_queen_index,
    PieceSet::c_king_index};
  const ColorBoard& color_board = board.color_board(color);
  for (const Piece::piece_index_t piece_index : piece_values) {
    const BitBoard subset = color_board.piece_board(piece_index).bit_board() & attackers;
    if (subset != 0) {
      return subset & -subset;
    }
  }
  return BitBoard();
}

// static
Searcher::score_t MoveOrderer::see(const ChessBoard& board,
                                   const Move move)
{
  if (!move.is_capture()) {
    return 0;
  }
  static const array<int, PieceSet::c_no_pieces> values =
      IncrementalUpdater::piece_values();
  BitBoard may_xray = 0;
  static const array<Piece::piece_index_t, 4> xray_pieces = {
    PieceSet::c_pawn_index,
    PieceSet::c_bishop_index,
    PieceSet::c_rook_index,
    PieceSet::c_queen_index};
  const Position src = move.source();
  const Position dst = move.destination();
  BitBoard attackers = 0;
  for (const Color color : c_colors) {
    const ColorBoard& color_board = board.color_board(color);
    BitBoard pawn_sources;
    const PositionDelta backward = forward_direction(other_color(color));
    if (src.in_bounds(backward)) {
      const Position pawn_source_middle = backward + dst;
      static const PositionDelta c_left(0, -1);
      static const PositionDelta c_right(0, 1);
      if (pawn_source_middle.in_bounds(c_left)) {
        pawn_sources = pawn_sources | BitBoard(pawn_source_middle + c_left);
      }
      if (pawn_source_middle.in_bounds(c_right)) {
        pawn_sources = pawn_sources | BitBoard(pawn_source_middle + c_right);
      }
    }
    for (Piece::piece_index_t piece_index : xray_pieces) {
      may_xray = may_xray | color_board.piece_board(piece_index).bit_board();
    }
    for (const PieceBoard& piece_board : color_board.piece_boards()) {
      const Piece& piece = piece_board.piece();
      if (piece.piece_index() == PieceSet::c_pawn_index) {
        attackers = attackers | (pawn_sources & piece_board.bit_board());
      } else {
        for (Position source : piece_board.positions()) {
          if (piece.could_move(IncompleteMove(source, dst), board)) {
            attackers = attackers | BitBoard(source);
          }
        }
      }
    }
  }
  array<Searcher::score_t, 32> gain;
  Searcher::depth_t depth = 0;
  gain[depth] = values[board.noturn_board().piece_index(dst)];
  Piece::piece_index_t attacker = board.turn_board().piece_index(move.source());
  BitBoard from = BitBoard(src);
  BitBoard friends = board.friends();
  BitBoard opponents = board.opponents();
  BitBoard occupied = board.occupied();
  Color color = board.turn_color();
  while (true) {
    ++depth;
    gain[depth] = values[attacker] - gain[depth - 1];
    if (max(-gain[depth - 1], gain[depth]) < 0) {
      break;
    }
    attackers = attackers ^ from;
    occupied = occupied ^ from;
    color = other_color(color);
    if ((from & may_xray) != 0) {
      Position src2 = from.first_position();
      const PositionDelta direction = (src2 - dst).unit();
      while (src2.in_bounds(direction)) {
        src2 = src2 + direction;
        BitBoard src3(src2);
        if ((occupied & src3) == 0) {
          continue;
        }
        if ((friends & src3) != 0){
          if (board.turn_board().piece(src2).can_xray(direction)) {
            attackers = attackers | src3;
          }
        } else {
          assert((opponents & src3) != 0);
          if (board.noturn_board().piece(src2).can_xray(direction)) {
            attackers = attackers | src3;
          }
        }
        break;
      }
    }
    from = least_valuable_piece(board, color, attackers);
    if (from != 0) {
      attacker = board.color_board(color).piece_index(from.first_position());
      assert(attacker != Piece::c_no_piece);
    } else {
      break;
    }
  }
  while (--depth) {
    gain[depth - 1] = -max(-gain[depth - 1], gain[depth]);
  }
  return gain[0];
}

// static
void MoveOrderer::order_moves(const SearchContext& context,
                              vector<Move>* moves)
{
  const TranspositionTableEntry* const entry = context.get();
  if (entry != nullptr && entry->has_best_move) {
    for (Move& move : *moves) {
      if (move == entry->best_move) {
        swap(move, moves->front());
        break;
      }
    }
  }
  unsigned int start = entry == nullptr ? 0 : 1;
  vector<Searcher::score_t> move_values(moves->size());
  for (unsigned int i = start; i < moves->size(); ++i) {
    move_values[i] = see(context.board, (*moves)[i]);
  }
  for (unsigned int i = start; i < moves->size() - 1; ++i) {
    int max = numeric_limits<Searcher::score_t>::min();
    unsigned int max_index = i;
    for (unsigned int j = i; j < moves->size(); ++j) {
      if (move_values[j] > max) {
        max = move_values[j];
        max_index = j;
      }
    }
    if (i != max_index) {
      swap(move_values[i], move_values[max_index]);
      swap((*moves)[i], (*moves)[max_index]);
    }
  }
}

} // namespace olaf
