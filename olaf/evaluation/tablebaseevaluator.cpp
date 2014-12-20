#include "olaf/evaluation/tablebaseevaluator.h"

#include <memory>

using namespace std;

namespace olaf
{

TablebaseEvaluator::TablebaseEvaluator(std::unique_ptr<PositionEvaluator> evaluator):
  m_evaluator(move(evaluator))
{}

TablebaseEvaluator::score_t TablebaseEvaluator::evaluate(
    SearchState* const state,
    SearchContext* const context)
{
  score_t tablebase_score;
  score_t heuristic_score = m_evaluator->evaluate(state, context);
  if (context->probe(&tablebase_score)) {
    return tablebase_score + heuristic_score;
  } else {
    return heuristic_score;
  }
}

} // namespace olaf
