#include "olaf/search/quiescer.h"

#include <cassert>
#include <algorithm>

#include "olaf/evaluation/positionevaluator.h"
#include "olaf/search/searchcontext.h"
#include "olaf/search/movegenerator.h"
#include "olaf/rules/movechecker.h"
#include "olaf/rules/undoinfo.h"

using namespace std;

namespace olaf
{

Quiescer::Quiescer(unique_ptr<MoveGenerator> generator,
                   MoveOrderer orderer,
                   unique_ptr<PositionEvaluator> evaluator):
  m_generator(move(generator)),
  m_orderer(orderer),
  m_evaluator(move(evaluator))
{}

static bool is_checked(ChessBoard* const board)
{
  board->next_turn();
  const bool result = MoveChecker::can_kill_king(*board);
  board->previous_turn();
  return result;
}

static const Quiescer::score_t c_safety_margin = 10000;

SearchResult Quiescer::quiesce(const SearchState& state,
                               SearchContext* const context)
{
#ifdef TRACE
  cout << indentation(state) << "entering quiesce " << state << endl;
  stringstream ss;
  ss << context->board;
  string line;
  while (!ss.eof()) {
    getline(ss, line);
    cout << indentation(state) << line << endl;
  }
#endif
  assert(state.depth <= 0 || context->board.finished());
  assert(state.depth >= -32);
  // stand pat
  SearchResult result = m_evaluator->alpha_beta(state, context);
  if (!result.valid) {
    return result;
  }
  assert(result.search_depth == 0);
  assert(result.real_depth == 0);
  assert(result.node_type_valid);
  if (context->board.finished()) {
    return result;
  }
  vector<Move> moves = m_generator->generate_moves(context->board);
  if (moves.empty()) {
#ifdef TRACE
    cout << indentation(state) << "Returning final evaluation because no moves are present." << endl;
#endif
    const SearchResult& result = m_evaluator->alpha_beta(state, context);
    assert(result.search_depth == 0);
    assert(result.real_depth == 0);
    assert(result.node_type_valid);
    return result;
  }
  ++(context->nodes);
  score_t alpha = state.alpha;
  const score_t beta = state.beta;
  SearchResult tt_result;
  tt_result.valid = false;
  const bool tt_success = context->get(state.depth, &tt_result);
  if (tt_success) {
    assert(tt_result.valid);
    assert(tt_result.node_type_valid);
    if (tt_result.search_depth >= state.depth) {
      if (tt_result.node_type == NodeType::PvNode
          || (tt_result.node_type == NodeType::AllNode && tt_result.score <= alpha)
          || (tt_result.node_type == NodeType::CutNode && tt_result.score >= beta)) {
        // Note that during this search, the node type does NOT have to be the same.
        tt_result.node_type = tt_result.score >= beta ? NodeType::CutNode : tt_result.score <= alpha ? NodeType::AllNode : NodeType::PvNode;
        return tt_result;
      }
    }
  }
  m_orderer.order_moves(tt_result, state, context, &moves);
  for (const Move move : moves) {
    assert(alpha < beta);
#ifdef TRACE
    cout << indentation(state) << "checking move " << move << endl;
#endif
    assert(move.is_capture());
    UndoInfo undo_info;
    assert(MoveChecker::pseudo_valid_move(context->board, move));
    move.execute(&(context->board), &undo_info);
    const SearchState sub_state{-beta, -alpha, static_cast<SearchState::depth_t>(state.depth - 1)};
    SearchResult sub_result = quiesce(sub_state, context);
    assert(sub_result.search_depth >= 0);
    assert(sub_result.node_type_valid);
    const score_t sub_score = -sub_result.score;
    move.undo(undo_info, &(context->board));
    if (!sub_result.valid) {
      return sub_result;
    } else if (sub_score > result.score) {
      result.has_best_move = true;
      result.best_move = move;
      result.score = sub_score;
      result.search_depth = 0;
      result.real_depth = sub_result.real_depth + 1;
      result.terminal = sub_result.terminal;
      if (sub_score >= beta) {
        result.node_type = NodeType::CutNode;
#ifdef TRACE
    cout << indentation(state) << move << " caused a cutoff" << endl;
#endif
        break;
      } else if (sub_score > alpha) {
        alpha = sub_score;
        result.node_type = NodeType::PvNode;
      }
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
