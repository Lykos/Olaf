#ifndef PAWNEVALUATOR_H
#define PAWNEVALUATOR_H

#include "olaf/evaluation/positionevaluator.h"

namespace olaf
{

class PawnEvaluator : public PositionEvaluator
{
public:
  virtual score_t evaluate(const SearchState& state, SearchContext* context) override;
};

} // namespace olaf

#endif // PAWNEVALUATOR_H

