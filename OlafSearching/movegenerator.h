#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H

#include "move.h"
#include "chessboard.h"
#include "piece.h"
#include <vector>

class MoveGenerator
{
public:
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
