#ifndef QUIESCER_H
#define QUIESCER_H

#include <memory>

#include "olaf/search/alphabetasearcher.h"
#include "olaf/search/searchresult.h"

namespace olaf
{

class MoveGenerator;
class PositionEvaluator;

class Quiescer : public AlphaBetaSearcher
{
public:
  Quiescer(std::unique_ptr<PositionEvaluator> evaluator,
           std::unique_ptr<MoveGenerator> generator,
           MoveOrderer orderer,
           std::unique_ptr<AlphaBetaSearcher> sub_searcher,
           depth_t sub_searcher_depth,
           bool ignore_depth);

  SearchResult alpha_beta(SearchState* state,
                          SearchContext* context) final;

private:
  std::unique_ptr<PositionEvaluator> m_evaluator;
};

} // namespace olaf

#endif // QUIESCER_H
