#include "olaf/search/moveorderer.h"

#include <array>
#include <cassert>
#include <iostream>

#include "olaf/transposition_table/transpositiontable.h"
#include "olaf/search/searchcontext.h"
#include "olaf/rules/magicmoves.h"
#include "olaf/rules/magicnumbers.h"
#include "olaf/config.h"
#include "olaf/evaluation/incrementalupdater.h"

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
    const BitBoard subset = color_board.piece_board(piece_index) & attackers;
    if (subset) {
      return subset & -subset;
    }
  }
  return BitBoard();
}

// static
void MoveOrderer::init_see_state(const ChessBoard& board, SeeState* const see_state)
{
  see_state->may_xray = 0;
  static const array<Piece::piece_index_t, 4> xray_pieces = {
    PieceSet::c_pawn_index,
    PieceSet::c_bishop_index,
    PieceSet::c_rook_index,
    PieceSet::c_queen_index};
  for (const Color color : c_colors) {
    const ColorBoard& color_board = board.color_board(color);
    for (Piece::piece_index_t piece_index : xray_pieces) {
      see_state->may_xray = see_state->may_xray | color_board.piece_board(piece_index);
    }
    see_state->straight_pieces = see_state->straight_pieces
        | board.rook_board(color)
        | board.queen_board(color);
    see_state->diagonal_pieces = see_state->diagonal_pieces
        | board.bishop_board(color)
        | board.queen_board(color);
  }
}

static inline BitBoard consider_xrays(const BitBoard occupied, const Position src, const MoveOrderer::SeeState& see_state)
{
  return ((MagicMoves::rook_magic_moves(src, occupied) & see_state.straight_pieces)
          | (MagicMoves::bishop_magic_moves(src, occupied) & see_state.diagonal_pieces))
          & occupied;
}

static const Searcher::score_t c_killer_value = -1;

static const Searcher::score_t c_quiet_value = -SearchContext::c_no_killers + c_killer_value;

static const Searcher::score_t c_other_promotion_value = -10000;

// static
Searcher::score_t MoveOrderer::see(const ChessBoard& board,
                                   const Move move,
                                   const SeeState& see_state)
{
  if (!move.is_capture()) {
    return 0;
  }
  static const array<int, PieceSet::c_no_pieces> values =
      IncrementalUpdater::piece_values();
  const Position src = move.source();
  const Position dst = move.destination();
  BitBoard attackers = 0;
  BitBoard occupied = board.occupied();
  for (const Color color : c_colors) {
    const int dst_index = dst.index();
    // Pawns can attack this square from the squares an opposing pawn would attack from here.
    const int color_index = static_cast<int>(other_color(color)) * BitBoard::c_bitboard_size;
    BitBoard pawn_attackers(MagicNumbers::c_pawn_capture_table[color_index + dst_index]);
    attackers = attackers | (pawn_attackers & board.pawn_board(color));
    // We use the fact that the knights and kings move symmetrically.
    attackers = attackers | (BitBoard(MagicNumbers::c_knight_table[dst_index]) & board.knight_board(color));
    attackers = attackers | (BitBoard(MagicNumbers::c_king_table[dst_index]) & board.king_board(color));
  }
  attackers = attackers | consider_xrays(occupied, dst, see_state);
  array<Searcher::score_t, 32> gain;
  Searcher::depth_t depth = 0;
  gain[depth] = values[board.piece_index(dst)];
  Piece::piece_index_t attacker = board.piece_index(move.source());
  BitBoard from = BitBoard(src);
  Color color = board.turn_color();
  while (true) {
    ++depth;
    assert(depth < 32);
    gain[depth] = values[attacker] - gain[depth - 1];
    if (max(-gain[depth - 1], gain[depth]) < 0) {
      break;
    }
    attackers = attackers ^ from;
    occupied = occupied ^ from;
    color = other_color(color);
    if (from & see_state.may_xray) {
      attackers = attackers | consider_xrays(occupied, dst, see_state);
    }
    from = least_valuable_piece(board, color, attackers);
    if (from) {
      attacker = board.piece_index(from.first_position());
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

MoveOrderer::MoveOrderer()
{}

MoveOrderer::MoveOrderer(const Config::MoveOrdering& config):
  m_use_hash_move(config.use_hash_move),
  m_use_promotions(config.use_promotions),
  m_use_see(config.use_see),
  m_use_killers(config.use_killers)
{}

bool MoveOrderer::order_moves(const SearchResult& entry,
                              const SearchState& state,
                              SearchContext* const context,
                              vector<Move>* moves)
{
  if (state.depth >= 3) {
    ++(context->statistics.sorts);
  }
  bool hash_move_found = false;
  unsigned int start = 0;
  if (m_use_hash_move && entry.valid && entry.has_best_move) {
    ++start;
    for (Move& move : *moves) {
      if (move == entry.best_move) {
        if (state.depth >= 3) {
          ++(context->statistics.hash_moves);
        }
        swap(move, moves->front());
        hash_move_found = true;
        break;
      }
    }
  }
  vector<Searcher::score_t> move_values(moves->size());
  SeeState see_state;
  if (m_use_see) {
    init_see_state(context->board, &see_state);
  }
  for (unsigned int i = start; i < moves->size(); ++i) {
    move_values[i] = c_quiet_value;
    const Move move = (*moves)[i];
    const int depth = context->search_depth - state.depth;
    if (m_use_see && move.is_capture()) {
      move_values[i] = see(context->board, move, see_state);
    } else if (m_use_promotions && move.is_promotion()) {
      if (move.created_piece() == PieceSet::c_queen_index) {
        move_values[i] =
            IncrementalUpdater::piece_values()[PieceSet::c_queen_index]
            - IncrementalUpdater::piece_values()[PieceSet::c_pawn_index];
      } else {
        move_values[i] = c_other_promotion_value;
      }
    } else if (m_use_killers && static_cast<int>(context->killers.size()) > depth) {
      const SearchContext::Killers& killers = context->killers[depth];
      for (unsigned int j = 0; j < killers.size(); ++j) {
        if (move == killers[j]) {
          move_values[i] = c_killer_value + j;
        }
      }
    }
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
  return hash_move_found;
}

} // namespace olaf
