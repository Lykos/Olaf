#include "negamaxer.h"
#include "move.h"
#include <limits>
#include <future>

using namespace std;

SearchResult NegaMaxer::alpha_beta(SearchState* const state,
                                   SearchContext* const context)
{
  vector<Move> moves = generate_ordered_moves(*context);
  if (moves.empty()) {
    return recurse_sub_searcher(*state, context);
  }
  SearchResult result;
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
