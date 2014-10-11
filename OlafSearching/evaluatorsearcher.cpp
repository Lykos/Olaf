#include "evaluatorsearcher.h"

using namespace std;

EvaluatorSearcher::EvaluatorSearcher(unique_ptr<PositionEvaluator> evaluator):
  m_evaluator(move(evaluator))
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
