#ifndef TABLEBASEEVALUATOR_H
#define TABLEBASEEVALUATOR_H

#include "olaf/evaluation/positionevaluator.h"

#include <memory>

namespace olaf
{

/**
 * @brief The ResultEvaluator class evaluates the position according to the tablebases if it has a
 *        tablebase for the position.
 */
class TablebaseEvaluator : public PositionEvaluator
{
public:
  score_t evaluate(SearchState* state, SearchContext* context) override;
};

} // namespace olaf

#endif // TABLEBASEEVALUATOR_H

