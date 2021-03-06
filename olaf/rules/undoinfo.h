#ifndef UNDOINFO_H
#define UNDOINFO_H

#include <cstdint>
#include "olaf/rules/bitboard.h"
#include "olaf/rules/piece.h"
#include "olaf/rules/position.h"

namespace olaf
{

/**
 * @brief The UndoInfo stores information that is needed to undo a move.
 */
struct UndoInfo
{
  BitBoard ep_captures;
  BitBoard king_captures;
  Position king_victim_position;
  Position rook_source;
  Position rook_destination;
  Piece::piece_index_t captured_piece;
  std::int_fast8_t reversible_plies;
  bool can_castle_k;
  bool can_castle_q;
};

} // namespace olaf

#endif // UNDOINFO_H
