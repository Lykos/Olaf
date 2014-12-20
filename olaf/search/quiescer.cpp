#include "olaf/search/quiescer.h"

#include <cassert>
#include <algorithm>

#include "olaf/evaluation/positionevaluator.h"
#include "olaf/search/searchcontext.h"
#include "olaf/search/movegenerator.h"

using namespace std;

namespace olaf
{

Quiescer::Quiescer(unique_ptr<PositionEvaluator> evaluator,
                   unique_ptr<MoveGenerator> generator,
                   MoveOrderer orderer,
                   unique_ptr<AlphaBetaSearcher> sub_searcher,
                   const depth_t sub_searcher_depth,
                   const bool ignore_depth):
  AlphaBetaSearcher(move(generator),
                    orderer,
                    move(sub_searcher),
                    sub_searcher_depth,
                    ignore_depth),
  m_evaluator(move(evaluator))
{}

SearchResult Quiescer::alpha_beta(SearchState* const state,
                                  SearchContext* const context)
{
  SearchResult result;
  const PositionEvaluator::score_t stand_pat = m_evaluator->evaluate(state, context);
  result.depth = context->search_depth - state->depth;
  if (stand_pat >= state->beta) {
    result.score = stand_pat;
    result.terminal = context->board.finished();
    return result;
  }
  if (state->alpha < stand_pat) {
    state->alpha = stand_pat;
  }
  result.score = state->alpha;
  vector<Move> moves;
  generate_ordered_moves(*context, *state, &moves);
  if (moves.empty()) {
    return recurse_sub_searcher(*state, context);
  }
  for (const Move move : moves) {
    SearchResult current_result = recurse_move(move, *state, context);
    switch (update_result(move, &current_result, context, state, &result)) {
      case ResultReaction::INVALID:
        return SearchResult::invalid();
      case ResultReaction::RETURN:
        return result;
      case ResultReaction::CONTINUE:
        break;
    }
  }
  return result;

} // namespace olaf
}
