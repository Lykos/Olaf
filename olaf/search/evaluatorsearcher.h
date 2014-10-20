#ifndef EVALUATORSEARCHER_H
#define EVALUATORSEARCHER_H

#include "olaf/search/alphabetasearcher.h"
#include "olaf/evaluation/positionevaluator.h"
#include <memory>

namespace olaf
{

/**
 * @brief The EvaluatorSearcher class is a search/searcher wrapper which just evaluates the position.
 */
class EvaluatorSearcher : public AlphaBetaSearcher
{
public:
  EvaluatorSearcher(std::unique_ptr<PositionEvaluator> evaluator);

  SearchResult alpha_beta(SearchState* state, SearchContext* context) final;

private:
  std::unique_ptr<PositionEvaluator> m_evaluator;
};

} // namespace olaf

#endif // EVALUATORSEARCHER_H
