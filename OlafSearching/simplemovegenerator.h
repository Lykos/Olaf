#ifndef SIMPLEMOVEGENERATOR_H
#define SIMPLEMOVEGENERATOR_H

#include "movegenerator.h"
#include "OlafRules/move.h"
#include "OlafRules/chessboard.h"
#include "OlafRules/piece.h"
#include <vector>

class SimpleMoveGenerator : public MoveGenerator
{
public:
  std::vector<Move> generate_moves(const ChessBoard& board);

};

#endif // SIMPLEMOVEGENERATOR_H
