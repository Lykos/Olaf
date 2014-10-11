#ifndef NOMOVEORDERER_H
#define NOMOVEORDERER_H

#include "moveorderer.h"

class NoMoveOrderer : public MoveOrderer
{
public:
  void order_moves(const ChessBoard& board, std::vector<Move>* moves) override;

};

#endif // NOMOVEORDERER_H
