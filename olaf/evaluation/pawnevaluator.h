#ifndef PAWNEVALUATOR_H
#define PAWNEVALUATOR_H

#include "olaf/evaluation/positionevaluator.h"

namespace olaf
{

class PawnEvaluator : public PositionEvaluator
{
public:
  score_t evaluate(const ChessBoard& board);
};

} // namespace olaf

#endif // PAWNEVALUATOR_H

