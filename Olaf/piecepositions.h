#ifndef PIECEPOSITIONS_H
#define PIECEPOSITIONS_H

#include "piecetype.h"
#include "position.h"
#include <vector>

/**
 * @brief The PiecePositions class represents a list of positions of pieces of the same type.
 */
class PiecePositions
{
public:
  PiecePositions(const PieceType& piece_type, const std::vector<Position>& positions);
};

#endif // PIECEPOSITIONS_H
