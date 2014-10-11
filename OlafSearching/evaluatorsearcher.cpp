#include "evaluatorsearcher.h"

EvaluatorSearcher::EvaluatorSearcher(const std::shared_ptr<PositionEvaluator>& evaluator):
  m_evaluator (evaluator)
{}

SearchResult EvaluatorSearcher::search_alpha_beta(ChessBoard* const board,
                                                  const int /* depth */,
                                                  const int /* nodes_searched */,
                                                  const int /* alpha */,
                                                  const int /* beta */,
                                                  const Stopper& /* stopper */)
{
  const int value = m_evaluator->evaluate(*board);
  return SearchResult(1, value);
}
