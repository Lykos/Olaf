#ifndef NOMOVEORDERER_H
#define NOMOVEORDERER_H

#include "moveorderer.h"

namespace olaf
{

class NoMoveOrderer : public MoveOrderer
{
public:
  void order_moves(const ChessBoard& board, std::vector<Move>* moves) override;

};

} // namespace olaf

#endif // NOMOVEORDERER_H
