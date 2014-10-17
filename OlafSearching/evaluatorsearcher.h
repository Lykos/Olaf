#ifndef EVALUATORSEARCHER_H
#define EVALUATORSEARCHER_H

#include "alphabetasearcher.h"
#include "OlafEvaluation/positionevaluator.h"
#include <memory>

/**
 * @brief The EvaluatorSearcher class is a searcher wrapper which just evaluates the position.
 */
class EvaluatorSearcher : public AlphaBetaSearcher
{
public:
  EvaluatorSearcher(std::unique_ptr<PositionEvaluator> evaluator);

  SearchResult alpha_beta(SearchState* state, SearchContext* context) final;

private:
  std::unique_ptr<PositionEvaluator> m_evaluator;
};

#endif // EVALUATORSEARCHER_H
