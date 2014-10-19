#ifndef PARALLELNEGAMAXER_H
#define PARALLELNEGAMAXER_H

#include <memory>

#include "olaf/search/alphabetasearcher.h"
#include "olaf/search/searchresult.h"
#include "olaf/search/movegenerator.h"
#include "olaf/search/moveorderer.h"

namespace olaf
{

class ParallelNegaMaxer : public AlphaBetaSearcher
{
public:
  using AlphaBetaSearcher::AlphaBetaSearcher;

  SearchResult alpha_beta(SearchState* state, SearchContext* context);

private:
  std::unique_ptr<MoveGenerator> m_generator;

  std::unique_ptr<MoveOrderer> m_orderer;

};

} // namespace olaf

#endif // PARALLELNEGAMAXER_H
