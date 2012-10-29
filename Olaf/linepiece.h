#ifndef LINEPIECE_H
#define LINEPIECE_H

#include "piece.h"
#include <vector>

/**
 * @brief The LinePiece class represents pieces that move along a line like the rook, the queen or the bishop.
 */
class LinePiece : public Piece
{
public:
  LinePiece(const std::vector<PositionDelta>& directions);

  std::vector<Move> moves(Position, Color) const;

private:
  std::vector<PositionDelta> m_directions;

};

#endif // LINEPIECE_H
