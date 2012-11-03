#ifndef POSITIONEVALUATOR_H
#define POSITIONEVALUATOR_H

#include "chessboard.h"

class PositionEvaluator
{
public:
  virtual int evaluate(const ChessBoard &board) = 0;

  virtual ~PositionEvaluator() {}

};

#endif // POSITIONEVALUATOR_H
