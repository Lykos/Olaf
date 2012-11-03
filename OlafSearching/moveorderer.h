#ifndef MOVEORDERER_H
#define MOVEORDERER_H

#include "chessboard.h"
#include "move.h"
#include <vector>

class MoveOrderer
{
public:
  virtual void order_moves(const ChessBoard &board, std::vector<Move>& moves) = 0;

};

#endif // MOVEORDERER_H
