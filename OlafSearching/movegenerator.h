#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H

#include "OlafRules/move.h"
#include "OlafRules/chessboard.h"
#include "OlafRules/piece.h"
#include <vector>

class MoveGenerator
{
public:
  virtual std::vector<Move> generate_moves(const ChessBoard& board) = 0;

};

#endif // MOVEGENERATOR_H
