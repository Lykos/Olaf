#include "olaf/search/alphabetasearcher.h"

#include "olaf/search/searchcontext.h"
#include "olaf/transposition_table/transpositiontable.h"
#include "olaf/rules/movecreator.h"

#include <cassert>
#include <limits>

using namespace std;

namespace olaf
{

AlphaBetaSearcher::AlphaBetaSearcher():
  m_sub_searcher(nullptr),
  m_sub_searcher_depth(0),
  m_ignore_depth(true)
{}

AlphaBetaSearcher::AlphaBetaSearcher(std::unique_ptr<MoveGenerator> generator,
                                     std::unique_ptr<AlphaBetaSearcher> sub_searcher,
                                     const int sub_searcher_depth,
                                     const bool ignore_depth):
  m_generator(move(generator)),
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
  MoveOrderer::order_moves(context, &moves);
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
    const TranspositionTableEntry* const entry =
        context->transposition_table->get(context->board.zobrist_hash());
    if (entry != nullptr && entry->depth >= current_state.depth) {
      if (entry->node_type == NodeType::PvNode
          || (entry->node_type == NodeType::AllNode && entry->score < current_state.alpha)
          || (entry->node_type == NodeType::CutNode && entry->score >= current_state.beta)) {
        SearchResult result;
        result.nodes = 1;
        result.score = entry->score;
        if (entry->has_best_move) {
          if (entry->best_move_is_conversion) {
            result.main_variation.emplace_back(MoveCreator::create_move(
                                                 context->board,
                                                 entry->best_move_source,
                                                 entry->best_move_destination));
          } else {
            result.main_variation.emplace_back(MoveCreator::create_move(
                                                 context->board,
                                                 entry->best_move_source,
                                                 entry->best_move_destination,
                                                 entry->best_move_created_piece));
          }
        }
      }
    }
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
    SearchContext* const context,
    SearchState* const state,
    SearchResult* const result) const
{
  if (!recursive_result->valid()) {
    return ResultReaction::INVALID;
  }
  ResultReaction reaction;
  result->nodes += recursive_result->nodes;
  const int recursive_score = -recursive_result->score;
  TranspositionTableEntry entry;
  entry.score = recursive_score;
  entry.depth = state->depth - 1;
  if (recursive_result->main_variation.empty()) {
    entry.has_best_move = false;
  } else {
    entry.has_best_move = true;
    const Move& move = recursive_result->main_variation.back();
    entry.best_move_source = move.source();
    entry.best_move_destination = move.destination();
    entry.best_move_is_conversion = move.is_conversion();
    if (entry.best_move_is_conversion) {
      entry.best_move_created_piece = move.created_piece();
    }
  }
  if (recursive_score > state->alpha) {
    result->score = recursive_score;
    if (recursive_score >= state->beta) {
      result->main_variation.clear();
      entry.node_type = NodeType::CutNode;
      reaction = ResultReaction::RETURN;
    } else {
      state->alpha = recursive_score;
      result->main_variation = std::move(recursive_result->main_variation);
      result->main_variation.emplace_back(move);
      entry.node_type = NodeType::PvNode;
      reaction = ResultReaction::CONTINUE;
    }
  } else {
    entry.node_type = NodeType::AllNode;
    reaction = ResultReaction::CONTINUE;
  }
  context->transposition_table->put(context->board.zobrist_hash(), std::move(entry));
  return reaction;

} // namespace olaf
}
