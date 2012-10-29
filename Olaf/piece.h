#ifndef PIECETYPE_H
#define PIECETYPE_H

#include "position.h"
#include "color.h"
#include <vector>

class Move;

typedef std::pair<Position::row_t, Position::column_t> PositionDelta;

/**
 * @brief The Piece class is an abstract class which represents a particular piece type (e.g. Knight)
 */
class Piece
{
public:
  virtual std::vector<Move> moves(Position, Color) const = 0;

  static const std::vector<PositionDelta>& all_directions();

  static const std::vector<PositionDelta>& straight_directions();

  static const std::vector<PositionDelta>& diagonal_directions();

};

#include "move.h"

#endif // PIECETYPE_H
