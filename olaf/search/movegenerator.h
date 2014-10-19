#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H

#include "olaf/rules/move.h"
#include "olaf/rules/chessboard.h"
#include "olaf/rules/piece.h"
#include <vector>

namespace olaf
{

/**
 * @brief The MoveGenerator class is responsible for generating moves in a position for
 *        the engine.
 */
class MoveGenerator
{
public:
  virtual ~MoveGenerator();

  /**
   * @brief generate_moves generates all pseudo valid moves for the given position.
   */
  virtual std::vector<Move> generate_moves(const ChessBoard& board) = 0;

  /**
   * @brief generate_moves generates all strictly valid moves for the given position.
   */
  virtual std::vector<Move> generate_valid_moves(const ChessBoard& board) = 0;
};

} // namespace olaf

#endif // MOVEGENERATOR_H