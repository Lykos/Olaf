#ifndef PARALLELNEGAMAXER_H
#define PARALLELNEGAMAXER_H

#include "alphabetasearcher.h"
#include "searchresult.h"
#include "movegenerator.h"
#include "moveorderer.h"
#include <memory>

class ParallelNegaMaxer : public AlphaBetaSearcher
{
public:
  ParallelNegaMaxer(std::unique_ptr<MoveGenerator> generator,
                    std::unique_ptr<MoveOrderer> orderer,
                    std::unique_ptr<AlphaBetaSearcher> sub_searcher,
                    int sub_searcher_depth,
                    bool ignore_depth);

  SearchResult alpha_beta(SearchState* state, SearchContext* context);

private:
  std::unique_ptr<MoveGenerator> m_generator;

  std::unique_ptr<MoveOrderer> m_orderer;

};

#endif // PARALLELNEGAMAXER_H
