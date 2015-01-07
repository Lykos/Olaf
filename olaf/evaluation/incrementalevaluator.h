#ifndef INCREMENTALEVALUATOR_H
#define INCREMENTALEVALUATOR_H

#include <vector>

#include "olaf/evaluation/positionevaluator.h"

namespace olaf
{

class ChessBoard;

class IncrementalEvaluator : public PositionEvaluator
{
public:
  score_t evaluate(const SearchState& state, SearchContext* context) override;
};

} // namespace olaf

#endif // INCREMENTALEVALUATOR_H
