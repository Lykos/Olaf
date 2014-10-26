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
    const Position pawn_source_middle = forward_direction(color) + src;
    const BitBoard pawn_sources = BitBoard(pawn_source_middle + PositionDelta(0, 1))
        | BitBoard(pawn_source_middle + PositionDelta(0, -1));
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
  do {
    for (const Position& pos : attackers.positions()) {
      cout << pos << endl;
    }
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
      // We want to overjump the original piece.
      src2 = src2 + direction;
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
  } while (from != 0);
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
    for (Move move : *moves) {
      if (move == entry->best_move) {
        swap(move, moves->front());
        break;
      }
    }
  }
  vector<Searcher::score_t> see_values(moves->size() - 1);
  for (unsigned int i = 0; i < moves->size() - 1; ++i) {
    see_values[i] = see(context.board, (*moves)[i + 1]);
  }
}

} // namespace olaf
