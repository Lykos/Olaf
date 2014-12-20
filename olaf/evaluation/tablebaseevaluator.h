#ifndef TABLEBASEEVALUATOR_H
#define TABLEBASEEVALUATOR_H

#include "olaf/evaluation/positionevaluator.h"

#include <memory>

namespace olaf
{

/**
 * @brief The ResultEvaluator class evaluates the position according to the tablebases if it has a
 *        tablebase for the position. If not, it forwards the position to another evaluator and returns its result.
 */
class TablebaseEvaluator : public PositionEvaluator
{
public:
  explicit TablebaseEvaluator(std::unique_ptr<PositionEvaluator> evaluator);

  score_t evaluate(SearchState* state, SearchContext* context) override;

private:
  std::unique_ptr<PositionEvaluator> m_evaluator;
};

} // namespace olaf

#endif // TABLEBASEEVALUATOR_H

