#include "negamaxer.h"

#include <limits>
#include <vector>

#include "move.h"

using namespace std;

namespace olaf
{

SearchResult NegaMaxer::alpha_beta(SearchState* const state,
                                   SearchContext* const context)
{
  vector<Move> moves = generate_ordered_moves(*context);
  if (moves.empty()) {
    return recurse_sub_searcher(*state, context);
  }
  SearchResult result;
  result.score = state->alpha;
  for (Move& move : moves) {
    SearchResult current_result = recurse_move(*state, context, &move);
    switch (update_result(move, &current_result, state, &result)) {
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
