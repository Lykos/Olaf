#include "alphabetasearcher.h"
#include "searchcontext.h"
#include <cassert>
#include <limits>

using namespace std;

AlphaBetaSearcher::AlphaBetaSearcher():
  m_sub_searcher(nullptr),
  m_sub_searcher_depth(0),
  m_ignore_depth(true)
{}

AlphaBetaSearcher::AlphaBetaSearcher(std::unique_ptr<MoveGenerator> generator,
                                     std::unique_ptr<MoveOrderer> orderer,
                                     std::unique_ptr<AlphaBetaSearcher> sub_searcher,
                                     const int sub_searcher_depth,
                                     const bool ignore_depth):
  m_generator(move(generator)),
  m_orderer(move(orderer)),
  m_sub_searcher(move(sub_searcher)),
  m_sub_searcher_depth(sub_searcher_depth),
  m_ignore_depth(ignore_depth)
{}

AlphaBetaSearcher::~AlphaBetaSearcher()
{}

vector<Move> AlphaBetaSearcher::generate_ordered_moves(const SearchContext& context)
{
  vector<Move> moves = m_generator->generate_moves(context.board);
  if (moves.empty()) {
    return moves;
  }
  m_orderer->order_moves(context.board, &moves);
  return moves;
}

SearchResult AlphaBetaSearcher::search(SearchContext* const context)
{
  assert(context->depth_mode == SearchContext::DepthMode::FIXED_DEPTH);
  // We increment the depth by 1 because it gets immediately decremented again.
  SearchState initial_state{-numeric_limits<int>::max(),
                            numeric_limits<int>::max(),
                            context->search_depth + 1};
  return recurse_alpha_beta(initial_state, context);
}

SearchResult AlphaBetaSearcher::recurse_sub_searcher(const SearchState& current_state,
                                                     SearchContext* const context)
{
 return m_sub_searcher->recurse_alpha_beta(current_state, context);
}

SearchResult AlphaBetaSearcher::recurse_alpha_beta(const SearchState& current_state,
                                                   SearchContext* const context)
{
  const int recurse_depth = current_state.depth - 1;
  if (context->forced_stopper->should_stop()) {
    return SearchResult::invalid();
  } else if ((!m_ignore_depth && recurse_depth <= m_sub_searcher_depth)
             || (m_sub_searcher != nullptr && context->board.finished())) {
    return recurse_sub_searcher(current_state, context);
  } else {
    SearchState state{-current_state.beta,
                      -current_state.alpha,
                      recurse_depth};
    return alpha_beta(&state, context);
  }
}

SearchResult AlphaBetaSearcher::recurse_move_noundo(const SearchState& current_state,
                                                    SearchContext* const context,
                                                    Move* const move)
{
  move->execute(&(context->board));
  return recurse_alpha_beta(current_state, context);
}

SearchResult AlphaBetaSearcher::recurse_move(const SearchState& current_state,
                                             SearchContext* const context,
                                             Move* const move)
{
  move->execute(&(context->board));
  const SearchResult& result = recurse_alpha_beta(current_state, context);
  move->undo(&(context->board));
  return result;
}

AlphaBetaSearcher::ResultReaction AlphaBetaSearcher::update_result(
    const Move& move,
    SearchResult* const recursive_result,
    SearchState* const state,
    SearchResult* const result) const
{
  if (!recursive_result->valid()) {
    return ResultReaction::INVALID;
  }
  result->nodes += recursive_result->nodes;
  const int recursive_score = -recursive_result->score;
  if (recursive_score > state->alpha) {
    result->score = recursive_score;
    if (recursive_score >= state->beta) {
      result->main_variation.clear();
      return ResultReaction::RETURN;
    }
    state->alpha = recursive_score;
    result->main_variation = std::move(recursive_result->main_variation);
    result->main_variation.emplace_back(move);
  }
  return ResultReaction::CONTINUE;
}
