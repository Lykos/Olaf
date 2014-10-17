#include "parallelnegamaxer.h"
#include "OlafRules/move.h"
#include <limits>
#include <future>

using namespace std;

ParallelNegaMaxer::ParallelNegaMaxer(unique_ptr<MoveGenerator> generator,
                                     unique_ptr<MoveOrderer> orderer,
                                     unique_ptr<AlphaBetaSearcher> sub_searcher,
                                     const int sub_searcher_depth,
                                     const bool ignore_depth):
  AlphaBetaSearcher(move(sub_searcher), sub_searcher_depth, ignore_depth),
  m_generator(move(generator)),
  m_orderer(move(orderer))
{}


static pair<Move*, SearchResult> eval_move(ParallelNegaMaxer* const searcher,
                                           const AlphaBetaSearcher::SearchState& state,
                                           const SearchContext& context,
                                           Move* const move)
{
  // Note that the stoppers are pointers, so they will still point
  // to the same object in the copy. The rest of the state, however,
  // will be copied. We need this because we cannot use the same board.
  SearchContext context_copy(context);
  return {move, searcher->recurse_move_noundo(state, &context_copy, move)};
}

SearchResult ParallelNegaMaxer::alpha_beta(SearchState* const state,
                                           SearchContext* const context)
{
  vector<Move> moves = m_generator->generate_moves(context->board);
  if (moves.empty()) {
    return recurse_sub_searcher(*state, context);
  }
  m_orderer->order_moves(context->board, &moves);
  auto it = moves.begin();
  // Do the first one synchronously
  SearchResult result;
  Move* const move = &(*it);
  SearchResult first_result = recurse_move(*state, context, move);
  switch (update_result(*move, &first_result, state, &result)) {
    case ResultReaction::INVALID:
      return SearchResult::invalid();
    case ResultReaction::RETURN:
      return result;
    case ResultReaction::CONTINUE:
      break;
  }
  ++it;
  vector<future<pair<Move*, SearchResult>>> other_results;
  for (; it < moves.end(); ++it) {
    Move* const move = &(*it);
    other_results.push_back(async(launch::async, eval_move, this, *state, *context, move));
  }
  for (future<pair<Move*, SearchResult>>& fut : other_results) {
    fut.wait();
    pair<Move*, SearchResult> fut_res = fut.get();
    Move* const move = fut_res.first;
    SearchResult& current_result = fut_res.second;
    switch (update_result(*move, &current_result, state, &result)) {
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
