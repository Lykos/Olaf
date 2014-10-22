#include "olaf/search/evaluatorsearcher.h"

#include <cassert>

#include "olaf/search/searchcontext.h"

using namespace std;

namespace olaf
{

EvaluatorSearcher::EvaluatorSearcher(unique_ptr<PositionEvaluator> evaluator):
  m_evaluator(move(evaluator))
{}

SearchResult EvaluatorSearcher::alpha_beta(SearchState* const /* state */,
                                           SearchContext* const context)
{
  SearchResult result;
  result.nodes = 1;
  result.score = m_evaluator->evaluate(context->board);
  return result;

} // namespace olaf
}
