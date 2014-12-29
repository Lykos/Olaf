#ifndef COMPOSITEEVALUATOR_H
#define COMPOSITEEVALUATOR_H

#include <memory>
#include <vector>

#include "olaf/evaluation/positionevaluator.h"

namespace olaf
{

class CompositeEvaluator : public PositionEvaluator
{
public:
  explicit CompositeEvaluator(std::vector<std::unique_ptr<PositionEvaluator>>&& sub_evaluators);

  score_t evaluate(SearchState* state, SearchContext* context) override;

private:
  std::vector<std::unique_ptr<PositionEvaluator>> m_sub_evaluators;
};

} // namespace olaf

#endif // COMPOSITEEVALUATOR_H

