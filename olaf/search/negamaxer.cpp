#include "olaf/search/negamaxer.h"

#include <limits>
#include <cassert>
#include <vector>

#include "olaf/rules/move.h"
#include "olaf/rules/undoinfo.h"
#include "olaf/search/searchcontext.h"

using namespace std;

namespace olaf
{

SearchResult NegaMaxer::alpha_beta(SearchState* const state,
                                   SearchContext* const context)
{
  vector<Move> moves;
  const bool has_hash_move = generate_ordered_moves(*context, *state, &moves);
  if (moves.empty()) {
    return recurse_sub_searcher(*state, context);
  }
  SearchResult result;
  result.score = state->alpha;
  result.depth = context->search_depth - state->depth;
  bool hash_move_done = false;
  for (Move& move : moves) {
    SearchResult current_result;
    if (hash_move_done) {
      UndoInfo undo_info;
      move.execute(&(context->board), &undo_info);
      SearchState null_window_state = *state;
      null_window_state.beta = null_window_state.alpha + 1;
      const SearchResult& null_window_result =
          recurse_alpha_beta(null_window_state, context);
      if (null_window_result.score > null_window_state.alpha) {
        current_result = recurse_alpha_beta(*state, context);
      } else {
        current_result = null_window_result;
      }
      move.undo(undo_info, &(context->board));
    } else {
      current_result = recurse_move(move, *state, context);
    }
    switch (update_result(move, &current_result, context, state, &result)) {
      case ResultReaction::INVALID:
        return SearchResult::invalid();
      case ResultReaction::RETURN:
        return result;
      case ResultReaction::CONTINUE:
        break;
    }
    if (has_hash_move) {
      hash_move_done = true;
    }
  }
  return result;
}

} // namespace olaf
