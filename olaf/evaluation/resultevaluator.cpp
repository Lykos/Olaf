#include "olaf/evaluation/resultevaluator.h"

#include <memory>

#include "olaf/rules/pieceset.h"
#include "olaf/rules/chessboard.h"
#include "olaf/search/searchcontext.h"

using namespace std;

namespace olaf
{

ResultEvaluator::ResultEvaluator(std::unique_ptr<PositionEvaluator> evaluator):
  m_evaluator(move(evaluator))
{}

PositionEvaluator::score_t ResultEvaluator::evaluate(
    SearchState* const state,
    SearchContext* const context)
{
  if (context->board.won(context->board.turn_color())) {
    return c_win_score - context->search_depth + state->depth;
  } else if (context->board.won(context->board.noturn_color())) {
    return -c_win_score + context->search_depth - state->depth;
  } else if (context->board.draw()) {
    return c_draw_score;
  }
  return m_evaluator->evaluate(state, context);
}

} // namespace olaf
