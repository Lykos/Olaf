#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H

#include "move.h"
#include "chessboard.h"
#include <vector>

class MoveGenerator
{
public:
  std::vector<Move> generate_moves(const ChessBoard& board);

};

#endif // MOVEGENERATOR_H
