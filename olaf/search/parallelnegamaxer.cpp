#include "olaf/search/parallelnegamaxer.h"

#include <limits>
#include <future>

#include "olaf/rules/move.h"
#include "olaf/search/searchcontext.h"

using namespace std;

namespace olaf
{

static pair<Move, SearchResult> eval_move(ParallelNegaMaxer* const searcher,
                                          const SearchState& state,
                                          const SearchContext& context,
                                          const Move move)
{
  // Note that the stoppers are pointers, so they will still point
  // to the same object in the copy. The rest of the state, however,
  // will be copied. We need this because we cannot use the same board.
  SearchContext context_copy(context);
  return {move, searcher->recurse_move_noundo(move, state, &context_copy)};
}

SearchResult ParallelNegaMaxer::alpha_beta(SearchState* const state,
                                           SearchContext* const context)
{
  vector<Move> moves;
  generate_ordered_moves(*context, *state, &moves);
  if (moves.empty()) {
    return recurse_sub_searcher(*state, context);
  }
  auto it = moves.begin();
  // Do the first one synchronously
  SearchResult result;
  result.score = state->alpha;
  SearchResult first_result = recurse_move(*it, *state, context);
  switch (update_result(*it, &first_result, context, state, &result)) {
    case ResultReaction::INVALID:
      return SearchResult::invalid();
    case ResultReaction::RETURN:
      return result;
    case ResultReaction::CONTINUE:
      break;
  }
  ++it;
  vector<future<pair<Move, SearchResult>>> other_results;
  for (; it < moves.end(); ++it) {
    other_results.push_back(async(launch::async, eval_move, this, *state, *context, *it));
  }
  for (future<pair<Move, SearchResult>>& fut : other_results) {
    fut.wait();
    pair<Move, SearchResult> fut_res = fut.get();
    const Move move = fut_res.first;
    SearchResult& current_result = fut_res.second;
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
}

} // namespace olaf
