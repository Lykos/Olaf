#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H

#include "move.h"
#include "chessboard.h"
#include "piece.h"
#include <vector>

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

#endif // MOVEGENERATOR_H
