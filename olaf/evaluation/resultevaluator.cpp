#include "olaf/evaluation/resultevaluator.h"

#include <memory>

#include "olaf/rules/pieceset.h"
#include "olaf/rules/chessboard.h"

using namespace std;

namespace olaf
{

ResultEvaluator::ResultEvaluator(std::unique_ptr<PositionEvaluator> evaluator):
  m_evaluator(move(evaluator))
{}

PositionEvaluator::score_t ResultEvaluator::evaluate(const ChessBoard& board)
{
  static const score_t c_win_score = 50000;
  static const score_t c_draw_score = 0;
  if (board.won(board.turn_color())) {
    return c_win_score;
  } else if (board.won(board.noturn_color())) {
    return -c_win_score;
  } else if (board.draw()) {
    return c_draw_score;
  }
  return m_evaluator->evaluate(board);
}

} // namespace olaf
