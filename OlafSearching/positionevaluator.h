#ifndef POSITIONEVALUATOR_H
#define POSITIONEVALUATOR_H

#include "chessboard.h"

class PositionEvaluator
{
public:
  typedef int score_t;

  virtual score_t evaluate(const ChessBoard& board) = 0;

  virtual ~PositionEvaluator();

};

#endif // POSITIONEVALUATOR_H
