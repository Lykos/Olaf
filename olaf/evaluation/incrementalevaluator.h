#ifndef INCREMENTALEVALUATOR_H
#define INCREMENTALEVALUATOR_H

#include "olaf/evaluation/positionevaluator.h"
#include <vector>

namespace olaf
{

class ChessBoard;

class IncrementalEvaluator : public PositionEvaluator
{
public:
  score_t evaluate(const ChessBoard& board) override;
};

} // namespace olaf

#endif // INCREMENTALEVALUATOR_H
