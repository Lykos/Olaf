#include "compositeevaluator.h"

using namespace std;

namespace olaf
{

CompositeEvaluator::CompositeEvaluator(vector<unique_ptr<PositionEvaluator>>&& sub_evaluators):
  m_sub_evaluators(std::move(sub_evaluators))
{}

PositionEvaluator::score_t CompositeEvaluator::evaluate(const SearchState& state, SearchContext* context)
{
  score_t score = 0;
  for (auto& evaluator : m_sub_evaluators) {
    score += evaluator->evaluate(state, context);
  }
  return score;
}

} // namespace olaf

