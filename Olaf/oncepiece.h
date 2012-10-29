#ifndef ONCEPIECE_H
#define ONCEPIECE_H

#include "move.h"
#include "chessboard.h"
#include "piece.h"

/**
 * @brief The OncePiece class represents a piece that can move only once in each
 * direction, e.g. king or knight.
 */
class OncePiece : public Piece
{
public:
  OncePiece(const std::vector<PositionDelta>&);

  std::vector<Move> moves(const ChessBoard&) const;

private:
  std::vector<PositionDelta> m_directions;

};

#endif // ONCEPIECE_H
