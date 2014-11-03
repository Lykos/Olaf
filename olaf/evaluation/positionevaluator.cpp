#include "olaf/evaluation/positionevaluator.h"

#include "olaf/search/searchcontext.h"

namespace olaf
{

PositionEvaluator::~PositionEvaluator()
{}

SearchResult PositionEvaluator::alpha_beta(
    SearchState* const state,
    SearchContext* const context)
{
  SearchResult result;
  result.depth = context->search_depth - state->depth;
  result.score = evaluate(state, context);
  result.terminal = context->board.finished();
  ++context->nodes;
  return result;
}

} // namespace olaf
