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

vector<Move> AlphaBetaSearcher::generate_ordered_moves(const SearchContext& context, const SearchState& state)
{
  vector<Move> moves = m_generator->generate_moves(context.board);
  if (moves.empty()) {
    return moves;
  }
  m_orderer.order_moves(context, state, &moves);
  return moves;
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

SearchResult AlphaBetaSearcher::recurse_sub_searcher(const SearchState& current_state,
                                                     SearchContext* const context)
{
 return m_sub_searcher->recurse_alpha_beta(current_state, context);
}

static bool is_checked(ChessBoard* const board)
{
  board->next_turn();
  const bool result = MoveChecker::can_kill_king(*board);
  board->previous_turn();
  return result;
}

SearchResult AlphaBetaSearcher::recurse_alpha_beta(const SearchState& current_state,
                                                   SearchContext* const context)
{
  const depth_t recurse_depth = current_state.depth - 1;
  if (context->forced_stopper->should_stop()) {
    return SearchResult::invalid();
  } else if ((!m_ignore_depth && recurse_depth <= m_sub_searcher_depth)
             || (m_sub_searcher != nullptr && context->board.finished())) {
    return recurse_sub_searcher(current_state, context);
  } else {
    const TranspositionTableEntry* const entry = context->get();
    if (entry != nullptr && (entry->depth >= current_state.depth || entry->terminal)) {
      if (entry->node_type == NodeType::PvNode
          || entry->terminal
          || (entry->node_type == NodeType::AllNode && entry->score < current_state.alpha)
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
    SearchState state{static_cast<score_t>(-current_state.beta),
                      static_cast<score_t>(-current_state.alpha),
                      recurse_depth};
    SearchResult result = alpha_beta(&state, context);
    const score_t c_safety_margin = 10000;
    // Stalemate. Not in check, but all moves lead to an immediate loss of the king.
    if (abs(result.score) >= (PositionEvaluator::c_win_score - c_safety_margin)
        && result.depth == context->search_depth - state.depth + 2 && !is_checked(&(context->board))) {
      result.score = PositionEvaluator::c_draw_score;
      result.terminal = true;
      result.main_variation.clear();
    }
    return result;
  }
}

SearchResult AlphaBetaSearcher::recurse_move_noundo(const Move move,
                                                    const SearchState& current_state,
                                                    SearchContext* const context)
{
  UndoInfo undo_info;
  move.execute(&(context->board), &undo_info);
  return recurse_alpha_beta(current_state, context);
}

SearchResult AlphaBetaSearcher::recurse_move(const Move move,
                                             const SearchState& current_state,
                                             SearchContext* const context)
{
  UndoInfo undo_info;
  move.execute(&(context->board), &undo_info);
  const SearchResult& result = recurse_alpha_beta(current_state, context);
  move.undo(undo_info, &(context->board));
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
  result->nodes += recursive_result->nodes;
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
        for (unsigned int i = 1; i < killers.size(); ++i) {
          killers[i] = killers[i - 1];
        }
        killers[0] = move;
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
