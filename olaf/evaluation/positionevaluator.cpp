#include "olaf/evaluation/positionevaluator.h"

#ifdef TRACE
#include <iostream>
#endif

#include "olaf/search/searchstate.h"
#include "olaf/search/searchcontext.h"

using namespace std;

namespace olaf
{

PositionEvaluator::~PositionEvaluator()
{}

SearchResult PositionEvaluator::alpha_beta(
    const SearchState& state,
    SearchContext* const context)
{
#ifdef TRACE
  cout << indentation(state) << "Entering evaluation" << endl;
#endif
  ++(context->nodes);
  SearchResult result;
  result.has_best_move = false;
  result.score = evaluate(state, context);
  result.search_depth = 0;
  result.real_depth = 0;
  result.valid = true;
  result.terminal = context->board.finished();
  result.node_type = result.score <= state.alpha
                     ? NodeType::AllNode
                     : (result.score >= state.beta ? NodeType::CutNode : NodeType::PvNode);
  result.node_type_valid = true;
#ifdef TRACE
  cout << indentation(state) << "Got evaluation: " << result << endl;
#endif
  return result;
}

} // namespace olaf
