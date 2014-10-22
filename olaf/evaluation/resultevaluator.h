#ifndef RESULTEVALUATOR_H
#define RESULTEVALUATOR_H

#include "olaf/evaluation/positionevaluator.h"
#include <memory>

namespace olaf
{

class ChessBoard;

/**
 * @brief The ResultEvaluator class evaluates the position according to the result if it is a terminal position.
 *        If not, it forwards the position to another evaluator and returns its result.
 */
class ResultEvaluator : public PositionEvaluator
{
public:
  ResultEvaluator(std::unique_ptr<PositionEvaluator> evaluator);

  score_t evaluate(const ChessBoard& board) override;

private:
  std::unique_ptr<PositionEvaluator> m_evaluator;
};

} // namespace olaf

#endif // RESULTEVALUATOR_H
