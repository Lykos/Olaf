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
  EvaluatorSearcher(const std::shared_ptr<PositionEvaluator>& evaluator);

  SearchResult search_alpha_beta(ChessBoard* board,
                                 int depth,
                                 int nodes_searched,
                                 int alpha,
                                 int beta,
                                 const Stopper& stopper) final;

private:
  std::shared_ptr<PositionEvaluator> m_evaluator;
};

#endif // EVALUATORSEARCHER_H
