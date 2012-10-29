#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece
{
public:
  std::vector<Move> moves(Position, Color) const;

};

#endif // PAWN_H
