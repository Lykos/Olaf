#ifndef ONCEPIECE_H
#define ONCEPIECE_H

#include "move.h"
#include "bitboard.h"
#include "piece.h"
#include "color.h"

/**
 * @brief The OncePiece class represents a piece that can move only once in each
 * direction, e.g. king or knight.
 */
class OncePiece : public Piece
{
public:
  OncePiece(piece_index_t piece_index, const BitBoard& initial_board, const std::vector<PositionDelta>&);

  std::vector<Move> moves(const Position &source, const ChessBoard &board, const BitBoard &opponents, const BitBoard &friends) const;

private:
  std::vector<PositionDelta> m_directions;

};

#endif // ONCEPIECE_H
