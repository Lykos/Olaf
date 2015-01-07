#ifndef KINGSAFETYEVALUATOR_H
#define KINGSAFETYEVALUATOR_H

#include "olaf/evaluation/positionevaluator.h"

namespace olaf
{

class KingSafetyEvaluator : public PositionEvaluator
{
public:
  score_t evaluate(const SearchState& state, SearchContext* context) override;
};

} // namespace olaf

#endif // KINGSAFETYEVALUATOR_H
