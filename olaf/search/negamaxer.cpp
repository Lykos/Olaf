#include "olaf/search/negamaxer.h"

#include <limits>
#include <cassert>
#include <vector>
#ifdef TRACE
#include <iostream>
#endif

#include "olaf/rules/move.h"
#include "olaf/rules/undoinfo.h"
#include "olaf/rules/movechecker.h"
#include "olaf/search/searchcontext.h"
#include "olaf/search/stopper.h"
#include "olaf/search/quiescer.h"
#include "olaf/search/movegenerator.h"
#include "olaf/search/moveorderer.h"

using namespace std;

namespace olaf
{

NegaMaxer::NegaMaxer(unique_ptr<MoveGenerator> generator,
                     const MoveOrderer& orderer,
                     unique_ptr<Quiescer> quiescer):
  m_generator(std::move(generator)),
  m_orderer(orderer),
  m_quiescer(std::move(quiescer))
{}

SearchResult NegaMaxer::search(SearchContext* const context)
{
  assert(context->depth_mode == SearchContext::DepthMode::FIXED_DEPTH);
  // We use -max because numeric_limits is asymmetric and min
  // would not work.
  const SearchState initial_state{-numeric_limits<score_t>::max(),
                            numeric_limits<score_t>::max(),
                            context->search_depth};
#ifdef TRACE
  cout << indentation(initial_state) << "doing a search for " << initial_state << endl;
#endif
  return alpha_beta(initial_state, context);
}

SearchResult NegaMaxer::search_windowed(SearchContext* const context, const score_t alpha, const score_t beta)
{
  assert(context->depth_mode == SearchContext::DepthMode::FIXED_DEPTH);
  const SearchState initial_state{alpha, beta, context->search_depth}; 
#ifdef TRACE
  cout << indentation(initial_state) << "doing a windowed search for " << initial_state << endl;
#endif
  return alpha_beta(initial_state, context);
}

static bool is_checked(ChessBoard* const board)
{
  board->next_turn();
  const bool result = MoveChecker::can_kill_king(*board);
  board->previous_turn();
  return result;
}

static const NegaMaxer::score_t c_safety_margin = 10000;

const int c_stop_check_nodes = 10000;

SearchResult NegaMaxer::alpha_beta(const SearchState& state,
                                   SearchContext* const context)
{
#ifdef TRACE
  cout << indentation(state) << "entering alpha beta " << state << endl;
  stringstream ss;
  ss << context->board;
  string line;
  while (!ss.eof()) {
    getline(ss, line);
    cout << indentation(state) << line << endl;
  }
#endif
  assert(state.depth >= 0);
  if (context->nodes % c_stop_check_nodes == 0 && context->forced_stopper->should_stop()) {
    return SearchResult::invalid();
  }
  if (state.depth == 0 || context->board.finished()) {
     const SearchResult& result = m_quiescer->quiesce(state, context);
     if (result.valid) {
       assert(result.search_depth >= 0);
       assert(result.real_depth >= 0);
       assert(result.node_type_valid);
     }
     return result;
  }
  vector<Move> moves = m_generator->generate_moves(context->board);
  if (moves.empty()) {
#ifdef TRACE
    cout << indentation(state) << "Returning final evaluation because no moves are present." << endl;
#endif
    const SearchResult& result = m_quiescer->quiesce(state, context);
    if (result.valid) {
      assert(result.terminal);
      assert(result.search_depth >= 0);
      assert(result.real_depth == 0);
      assert(result.node_type_valid);
    }
    return result;
  }
  ++(context->nodes);
  score_t alpha = state.alpha;
  const score_t beta = state.beta;
  SearchResult tt_result;
  tt_result.valid = false;
  if (state.depth >= 3) {
    ++(context->statistics.retrievals_of_tt);
  }
  const bool tt_success = context->get(state.depth, &tt_result);
  if (tt_success) {
    if (state.depth >= 3) {
      ++(context->statistics.hits_of_tt);
    }
    assert(tt_result.valid);
    assert(tt_result.node_type_valid);
    if (tt_result.search_depth >= state.depth) {
      if (state.depth >= 3) {
        ++(context->statistics.useful_hits_of_tt);
      }
      if (tt_result.node_type == NodeType::PvNode
          || (tt_result.node_type == NodeType::AllNode && tt_result.score <= alpha)
          || (tt_result.node_type == NodeType::CutNode && tt_result.score >= beta)) {
        if (state.depth >= 3) {
          ++(context->statistics.useful_hits_of_tt);
        }
        // Note that during this search, the node type does NOT have to be the same.
        tt_result.node_type = tt_result.score >= beta ? NodeType::CutNode : tt_result.score <= alpha ? NodeType::AllNode : NodeType::PvNode;
        return tt_result;
      }
    }
  }
  const bool has_hash_move = m_orderer.order_moves(tt_result, state, context, &moves);
  SearchResult result;
  // We use -max because numeric_limits is asymmetric and min
  // would not work.
  result.has_best_move = false;
  result.score = -numeric_limits<score_t>::max();
  result.search_depth = state.depth;
  result.real_depth = state.depth;
  result.valid = true;
  result.terminal = false;
  result.node_type = NodeType::AllNode;
  result.node_type_valid = true;
  bool hash_move_done = false;
  for (const Move move : moves) {
    assert(alpha < beta);
#ifdef TRACE
    cout << indentation(state) << "checking move " << move << endl;
#endif
    assert(MoveChecker::pseudo_valid_move(context->board, move));
    UndoInfo undo_info;
    move.execute(&(context->board), &undo_info);
    SearchResult sub_result;
    bool result_found = false;
    if (hash_move_done && state.depth >= 3) {
#ifdef TRACE
    cout << indentation(state) << "Doing null window search" << endl;
#endif
      const SearchState null_search_state{-alpha - 1, -alpha, static_cast<SearchState::depth_t>(state.depth - 1)};
      sub_result = alpha_beta(null_search_state, context);
      if (!sub_result.valid || -sub_result.score < alpha || -sub_result.score >= beta) {
        if (-sub_result.score < alpha) {
          ++(context->statistics.very_successful_null_window_searches);
        }
        ++(context->statistics.successful_null_window_searches);
        result_found = true;
#ifdef TRACE
    cout << indentation(state) << "Accepted null window result" << endl;
#endif
      } else {
        ++(context->statistics.unsuccessful_null_window_searches);
#ifdef TRACE
    cout << indentation(state) << "Rejected null window result because it is in the window" << endl;
#endif
      }
    }
    if (!result_found) {
      const SearchState sub_state{-beta, -alpha, static_cast<SearchState::depth_t>(state.depth - 1)};
      sub_result = alpha_beta(sub_state, context);
    }
    move.undo(undo_info, &(context->board));
    if (!sub_result.valid) {
      return sub_result;
    }
    assert(sub_result.search_depth + 1 >= state.depth || sub_result.terminal);
    assert(sub_result.node_type_valid);
    const score_t sub_score = -sub_result.score;
    if (sub_score > result.score) {
      result.has_best_move = true;
      result.best_move = move;
      result.score = sub_score;
      result.real_depth = sub_result.real_depth + 1;
      result.terminal = sub_result.terminal;
      if (sub_score >= beta) {
        result.node_type = NodeType::CutNode;
        // Update killer moves
        if (!move.is_capture()) {
          const depth_t killer_depth = context->search_depth - state.depth;
          if (static_cast<int>(context->killers.size()) <= killer_depth) {
            context->killers.resize(killer_depth + 1);
          }
          SearchContext::Killers& killers = context->killers[killer_depth];
          if (!(killers[0] == move)) {
            killers[1] = killers[0];
            killers[0] = move;
          }
        }
#ifdef TRACE
    cout << indentation(state) << move << " caused a cutoff" << endl;
#endif
        break;
      } else if (sub_score > alpha) {
        alpha = sub_score;
        result.node_type = NodeType::PvNode;
      }
    }
    if (has_hash_move) {
      hash_move_done = true;
    }
  }
  // stalemate
  if (abs(result.score) >= (PositionEvaluator::c_win_score - c_safety_margin)
      && result.real_depth == 2 && !is_checked(&(context->board))) {
    result.score = PositionEvaluator::c_draw_score;
    result.terminal = true;
    result.has_best_move = false;
  }
  if (result.valid) {
    context->put(state.depth, result);
  }
#ifdef TRACE
  cout << indentation(state) << "returning " << result << endl;
#endif
  return result;
}

} // namespace olaf
