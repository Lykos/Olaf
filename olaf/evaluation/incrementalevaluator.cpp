#include "olaf/evaluation/incrementalevaluator.h"

#include "olaf/rules/pieceset.h"
#include "olaf/rules/chessboard.h"
#include "olaf/search/searchcontext.h"

namespace olaf
{

IncrementalEvaluator::score_t IncrementalEvaluator::evaluate(
    const SearchState& /* state */,
    SearchContext* const context)
{
  return context->board.incremental_score();
}

} // namespace olaf
