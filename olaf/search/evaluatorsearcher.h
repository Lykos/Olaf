#ifndef EVALUATORSEARCHER_H
#define EVALUATORSEARCHER_H

#include <memory>

#include "olaf/search/alphabetasearcher.h"
#include "olaf/search/searchresult.h"

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
