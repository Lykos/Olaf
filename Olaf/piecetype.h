#ifndef PIECETYPE_H
#define PIECETYPE_H

#include "position.h"
#include "color.h"
#include "move.h"
#include <vector>

/**
 * @brief The PieceType class is an abstract class which represents a particular piece type (e.g. Knight)
 */
class PieceType
{
public:
  PieceType();

  std::vector<Move> moves(Position, Color) const;
};

#endif // PIECETYPE_H
