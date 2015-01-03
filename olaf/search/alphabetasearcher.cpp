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
    const SearchContext& context,
    const SearchState& state,
    vector<Move>* const moves)
{
  *moves = m_generator->generate_moves(context.board);
  if (moves->empty()) {
    return false;
  }
  return m_orderer.order_moves(context, state, moves);
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

const int c_stop_check_nodes = 10000;

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
    }
  }
  SearchResult result = alpha_beta(&recurse_state, context);
  const score_t c_safety_margin = 10000;
  // Stalemate. Not in check, but all moves lead to an immediate loss of the king.
  if (abs(result.score) >= (PositionEvaluator::c_win_score - c_safety_margin)
      && result.depth == context->search_depth - recurse_depth + 2 && !is_checked(&(context->board))) {
    result.score = PositionEvaluator::c_draw_score;
    result.terminal = true;
    result.main_variation.clear();
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
  TranspositionTableEntry entry;
  entry.score = recursive_score;
  entry.terminal = recursive_result->terminal;
  entry.depth = state->depth - 1;
  entry.result_depth = recursive_result->depth;
  if (recursive_result->main_variation.empty()) {
    entry.has_best_move = false;
  } else {
    entry.has_best_move = true;
    entry.best_move = recursive_result->main_variation.back();
  }
  if (recursive_score > state->alpha) {
    result->score = recursive_score;
    result->terminal = recursive_result->terminal;
    result->depth = recursive_result->depth;
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
  context->put(std::move(entry));
  return reaction;
}

} // namespace olaf
