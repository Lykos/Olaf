#include "olaf/search/moveorderer.h"

#include <array>
#include <cassert>
#include <iostream>

#include "olaf/transposition_table/transpositiontable.h"
#include "olaf/search/searchcontext.h"
#include "olaf/rules/magicmoves.h"
#include "olaf/rules/magicnumbers.h"

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
    if (subset) {
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
  BitBoard occupied = board.occupied();
  BitBoard straight_pieces;
  BitBoard diagonal_pieces;
  for (const Color color : c_colors) {
    const ColorBoard& color_board = board.color_board(color);
    for (Piece::piece_index_t piece_index : xray_pieces) {
      may_xray = may_xray | color_board.piece_board(piece_index).bit_board();
    }
    const int src_index = BitBoard::index(src);
    // Pawns can attack this square from the squares an opposing pawn would attack from here.
    const int color_index = static_cast<int>(other_color(color));
    BitBoard pawn_attackers(MagicNumbers::c_pawn_capture_table[color_index + src_index]);
    attackers = attackers | (pawn_attackers & color_board.piece_board(PieceSet::c_pawn_index));
    // We use the fact that the pieces except for the pawn behave symmetrically.
    straight_pieces = straight_pieces
        | color_board.piece_board(PieceSet::c_rook_index).bit_board()
        | color_board.piece_board(PieceSet::c_queen_index).bit_board();
    diagonal_pieces = diagonal_pieces
        | color_board.piece_board(PieceSet::c_bishop_index).bit_board()
        | color_board.piece_board(PieceSet::c_queen_index).bit_board();
    attackers = attackers | (MagicNumbers::c_knight_table[src_index] & color_board.piece_board(PieceSet::c_knight_index));
    attackers = attackers | (MagicNumbers::c_king_table[src_index] & color_board.piece_board(PieceSet::c_king_index));
  }
  attackers = attackers | (MagicMoves::sliding_magic_moves(MagicNumbers::c_rook_magic, src, occupied) & straight_pieces);
  attackers = attackers | (MagicMoves::sliding_magic_moves(MagicNumbers::c_bishop_magic, src, occupied) & diagonal_pieces);
  array<Searcher::score_t, 32> gain;
  Searcher::depth_t depth = 0;
  gain[depth] = values[board.noturn_board().piece_index(dst)];
  Piece::piece_index_t attacker = board.turn_board().piece_index(move.source());
  BitBoard from = BitBoard(src);
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
    if (from & may_xray) {
      attackers = attackers | (MagicMoves::sliding_magic_moves(MagicNumbers::c_rook_magic, src, occupied) & straight_pieces);
      attackers = attackers | (MagicMoves::sliding_magic_moves(MagicNumbers::c_bishop_magic, src, occupied) & diagonal_pieces);
    }
    from = least_valuable_piece(board, color, attackers);
    if (from) {
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
