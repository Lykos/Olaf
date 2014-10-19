#include "olaf/search/quiescer.h"

using namespace std;

namespace olaf
{

Quiescer::Quiescer(unique_ptr<PositionEvaluator> evaluator,
                   unique_ptr<MoveGenerator> generator,
                   unique_ptr<AlphaBetaSearcher> sub_searcher,
                   const int sub_searcher_depth,
                   const bool ignore_depth):
  AlphaBetaSearcher(move(generator),
                    move(sub_searcher),
                    sub_searcher_depth,
                    ignore_depth),
  m_evaluator(move(evaluator))
{}

SearchResult Quiescer::alpha_beta(SearchState* const state,
                                  SearchContext* const context)
{
  SearchResult result;
  const int stand_pat = m_evaluator->evaluate(context->board);
  result.nodes = 1;
  if (stand_pat >= state->beta) {
    result.score = stand_pat;
    return result;
  }
  if (state->alpha < stand_pat) {
    state->alpha = stand_pat;
  }
  result.score = state->alpha;
  vector<Move> moves = generate_ordered_moves(*context);
  if (moves.empty()) {
    return recurse_sub_searcher(*state, context);
  }
  for (Move& move : moves) {
    SearchResult current_result = recurse_move(*state, context, &move);
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
