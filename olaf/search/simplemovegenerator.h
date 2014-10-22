#ifndef SIMPLEMOVEGENERATOR_H
#define SIMPLEMOVEGENERATOR_H

#include "olaf/search/movegenerator.h"
#include "olaf/rules/move.h"
#include <vector>

namespace olaf
{

class ChessBoard;

class SimpleMoveGenerator : public MoveGenerator
{
public:
  std::vector<Move> generate_moves(const ChessBoard& board) override;

  std::vector<Move> generate_valid_moves(const ChessBoard& board) override;
};

} // namespace olaf

#endif // SIMPLEMOVEGENERATOR_H
