#ifndef MOVEORDERER_H
#define MOVEORDERER_H

#include "chessboard.h"
#include "move.h"
#include <vector>

/**
 * @brief The MoveOrderer class is responsible for ordering moves.
 */
class MoveOrderer
{
public:
  virtual ~MoveOrderer();

  virtual void order_moves(const ChessBoard& board, std::vector<Move>* moves) = 0;
};

#endif // MOVEORDERER_H
