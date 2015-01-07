#include "olaf/evaluation/tablebaseevaluator.h"

#include <memory>

#include "olaf/search/searchcontext.h"

using namespace std;

namespace olaf
{

TablebaseEvaluator::score_t TablebaseEvaluator::evaluate(
    const SearchState& /* state */,
    SearchContext* const context)
{
  score_t score;
  if (context->probe(&score)) {
    return score;
  } else {
    return 0;
  }
}

} // namespace olaf
