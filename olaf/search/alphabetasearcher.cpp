#include "olaf/search/alphabetasearcher.h"

#include <cassert>
#include <limits>

#include "olaf/search/searchcontext.h"
#include "olaf/search/movegenerator.h"
#include "olaf/rules/movechecker.h"
#include "olaf/search/moveorderer.h"
#include "olaf/search/stopper.h"
#include "olaf/transposition_table/transpositiontable.h"
#include "olaf/rules/undoinfo.h"
#include "olaf/evaluation/positionevaluator.h"

using namespace std;

namespace olaf
{

AlphaBetaSearcher::AlphaBetaSearcher():
  m_sub_searcher(nullptr),
  m_sub_searcher_depth(0),
  m_ignore_depth(true)
{}

AlphaBetaSearcher::AlphaBetaSearcher(std::unique_ptr<MoveGenerator> generator,
                                     const MoveOrderer& orderer,
                                     std::unique_ptr<AlphaBetaSearcher> sub_searcher,
                                     const depth_t sub_searcher_depth,
                                     const bool ignore_depth):
  m_generator(move(generator)),
  m_orderer(orderer),
  m_sub_searcher(move(sub_searcher)),
  m_sub_searcher_depth(sub_searcher_depth),
  m_ignore_depth(ignore_depth)
{}

AlphaBetaSearcher::~AlphaBetaSearcher()
{}

bool AlphaBetaSearcher::generate_ordered_moves(
    const TranspositionTableEntry* const entry,
    const SearchState& state,
    SearchContext* const context,
    vector<Move>* const moves)
{
  *moves = m_generator->generate_moves(context->board);
  if (moves->empty()) {
    return false;
  }
  const bool has_hash_move = m_orderer.order_moves(entry, state, context, moves);
  return has_hash_move;
}

SearchResult AlphaBetaSearcher::search(SearchContext* const context)
{
  assert(context->depth_mode == SearchContext::DepthMode::FIXED_DEPTH);
  // We increment the depth by 1 because it gets immediately decremented again.
  SearchState initial_state{-numeric_limits<score_t>::max(),
                            numeric_limits<score_t>::max(),
                            static_cast<depth_t>(context->search_depth + 1)};
  return recurse_alpha_beta(initial_state, context);
}

SearchResult AlphaBetaSearcher::search_windowed(SearchContext* const context,
                                                const score_t alpha,
                                                const score_t beta)
{
  assert(context->depth_mode == SearchContext::DepthMode::FIXED_DEPTH);
  // We increment the depth by 1 because it gets immediately decremented again.
  SearchState initial_state{-beta,
                            -alpha,
                            static_cast<depth_t>(context->search_depth + 1)};
  return recurse_alpha_beta(initial_state, context);
}

static bool is_checked(ChessBoard* const board)
{
  board->next_turn();
  const bool result = MoveChecker::can_kill_king(*board);
  board->previous_turn();
  return result;
}

static const int c_stop_check_nodes = 10000;

static const SearchResult::score_t c_safety_margin = 10000;

static bool is_terminal(const SearchResult::score_t score)
{
  return abs(score) >= (PositionEvaluator::c_win_score - c_safety_margin);
}

SearchResult AlphaBetaSearcher::recurse_alpha_beta(const SearchState& current_state,
                                                   SearchContext* const context)
{
  ++context->nodes;
  const depth_t recurse_depth = current_state.depth - 1;
  if (context->nodes % c_stop_check_nodes == 0 && context->forced_stopper->should_stop()) {
    return SearchResult::invalid();
  } else if ((!m_ignore_depth && recurse_depth <= m_sub_searcher_depth)
             || (m_sub_searcher != nullptr && context->board.finished())) {
    return m_sub_searcher->recurse_alpha_beta(current_state, context);
  }
  SearchState recurse_state{static_cast<score_t>(-current_state.beta),
                            static_cast<score_t>(-current_state.alpha),
                            recurse_depth};
  score_t endgame_score;
  if (context->probe(&endgame_score)
      && (endgame_score >= recurse_state.beta
          || endgame_score <= recurse_state.alpha)) {
    SearchResult result;
    result.score = endgame_score;
    return result;
  }
  const TranspositionTableEntry* const entry = context->get();
  if (entry != nullptr && (entry->depth >= current_state.depth || entry->terminal)) {
    if (entry->node_type == NodeType::PvNode
        || entry->terminal
        || (entry->node_type == NodeType::AllNode && entry->score <= current_state.alpha)
        || (entry->node_type == NodeType::CutNode && entry->score >= current_state.beta)) {
      SearchResult result;
      result.score = entry->score;
      result.terminal = entry->terminal;
      result.depth = entry->result_depth;
      if (entry->has_best_move) {
        result.main_variation.emplace_back(entry->best_move);
      }
    } else if (entry->depth == current_state.depth) {
      if (entry->node_type == NodeType::AllNode) {
        // We know entry.score > alpha from the above conditional.
        // We also know we found a proof that the score is at most entry.score with the same depth.
        // So we can reduce beta to entry.score + 1, i.e. raise recursive alpha to -entry.score - 1.
        recurse_state.alpha = -entry->score - 1;
      } else if (entry->node_type == NodeType::CutNode) {
        // We know entry.score < beta from the above conditional.
        // We also know we found a proof that the score is at least entry.score with the same depth.
        // So we can raise alpha to entry.score - 1, i.e. reduce recursive beta to -entry.score + 1.
        recurse_state.beta = -entry->score + 1;
      }
    }
  }
  SearchResult result = alpha_beta(entry, &recurse_state, context);
  // Stalemate. Not in check, but all moves lead to an immediate loss of the king.
  if (is_terminal(result.score)
      && result.depth == context->search_depth - recurse_depth + 2
      && !is_checked(&(context->board))) {
    result.score = PositionEvaluator::c_draw_score;
    result.terminal = true;
    result.main_variation.clear();
  }
  {
    TranspositionTableEntry new_entry;
    if (is_terminal(result.score)) {
      new_entry.score = result.score < 0
          ? result.score + context->search_depth - current_state.depth - 1
          : result.score - context->search_depth + current_state.depth + 1;
    } else {
      new_entry.score = result.score;
    }
    new_entry.terminal = result.terminal;
    new_entry.depth = current_state.depth;
    new_entry.result_depth = result.depth;
    if (result.main_variation.empty()) {
      new_entry.has_best_move = false;
    } else {
      new_entry.has_best_move = true;
      new_entry.best_move = result.main_variation.back();
    }
    new_entry.node_type = result.score <= current_state.alpha
        ? NodeType::AllNode
        : (result.score >= current_state.beta ? NodeType::CutNode : NodeType::PvNode);
    context->put(std::move(new_entry));
  }
  return result;
}

AlphaBetaSearcher::ResultReaction AlphaBetaSearcher::update_result(
    const Move move,
    SearchResult* const recursive_result,
    SearchContext* const context,
    SearchState* const state,
    SearchResult* const result) const
{
  if (!recursive_result->valid) {
    return ResultReaction::INVALID;
  }
  ResultReaction reaction;
  const score_t recursive_score = -recursive_result->score;
  if (recursive_score > result->score) {
    result->score = recursive_score;
    result->terminal = recursive_result->terminal;
    result->depth = recursive_result->depth;
    result->main_variation.clear();
    result->main_variation.emplace_back(move);
  }
  if (recursive_score > state->alpha) {
    if (recursive_score >= state->beta) {
      if (!move.is_capture()) {
        const depth_t depth = context->search_depth - state->depth;
        if (static_cast<int>(context->killers.size()) <= depth) {
          context->killers.resize(depth + 1);
        }
        SearchContext::Killers& killers = context->killers[depth];
        if (!(killers[0] == move)) {
          killers[1] = killers[0];
          killers[0] = move;
        }
      }
      reaction = ResultReaction::RETURN;
    } else {
      state->alpha = recursive_score;
      result->main_variation = std::move(recursive_result->main_variation);
      result->main_variation.emplace_back(move);
      reaction = ResultReaction::CONTINUE;
    }
  } else {
    reaction = ResultReaction::CONTINUE;
  }
  return reaction;
}

} // namespace olaf
