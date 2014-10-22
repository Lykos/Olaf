#ifndef POSITIONEVALUATOR_H
#define POSITIONEVALUATOR_H

#include <cstdint>

#include "olaf/rules/chessboard.h"

namespace olaf
{

class ChessBoard;

class PositionEvaluator
{
public:
  typedef std::int_fast16_t score_t;

  static const score_t c_win_score = 50000;
  static const score_t c_draw_score = 0;

  virtual score_t evaluate(const ChessBoard& board) = 0;

  virtual ~PositionEvaluator();

};

} // namespace olaf

#endif // POSITIONEVALUATOR_H
