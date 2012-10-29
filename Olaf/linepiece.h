#ifndef LINEPIECE_H
#define LINEPIECE_H

#include "piece.h"
#include "position.h"
#include "positiondelta.h"
#include "move.h"
#include <vector>

/**
 * @brief The LinePiece class represents pieces that move along a line like the rook, the queen or the bishop.
 */
class LinePiece : public Piece
{
public:
  LinePiece(piece_index_t piece_index, const BitBoard& initial_board, const std::vector<PositionDelta>& directions);

  std::vector<Move> moves(const Position &source,
                          const ChessBoard &board,
                          const BitBoard &opponents,
                          const BitBoard &friends) const;

private:
  std::vector<PositionDelta> m_directions;

};

#endif // LINEPIECE_H
