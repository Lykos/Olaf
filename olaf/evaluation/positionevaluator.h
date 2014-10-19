#ifndef POSITIONEVALUATOR_H
#define POSITIONEVALUATOR_H

#include "olaf/rules/chessboard.h"

namespace olaf
{

class PositionEvaluator
{
public:
  typedef int score_t;

  virtual score_t evaluate(const ChessBoard& board) = 0;

  virtual ~PositionEvaluator();

};

} // namespace olaf

#endif // POSITIONEVALUATOR_H
