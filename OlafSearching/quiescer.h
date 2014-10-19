#ifndef QUIESCER_H
#define QUIESCER_H

#include <memory>

#include "alphabetasearcher.h"
#include "positionevaluator.h"

class Quiescer : public AlphaBetaSearcher
{
public:
  Quiescer(std::unique_ptr<PositionEvaluator> evaluator,
           std::unique_ptr<MoveGenerator> generator,
           std::unique_ptr<MoveOrderer> orderer,
           std::unique_ptr<AlphaBetaSearcher> sub_searcher,
           int sub_searcher_depth,
           bool ignore_depth);

  SearchResult alpha_beta(SearchState* state,
                          SearchContext* context) final;

private:
  std::unique_ptr<PositionEvaluator> m_evaluator;
};

#endif // QUIESCER_H