#include "evaluatorsearcher.h"

EvaluatorSearcher::EvaluatorSearcher(const std::shared_ptr<PositionEvaluator> &evaluator):
  m_evaluator (evaluator)
{}

SearchResult EvaluatorSearcher::search_alpha_beta(ChessBoard &board, int depth, int nodes_searched, int alpha, int beta, const std::shared_ptr<Stopper> &stopper)
{
  int value = m_evaluator->evaluate(board);
  return SearchResult(1, value);
}
