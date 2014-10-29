#ifndef PARALLELNEGAMAXER_H
#define PARALLELNEGAMAXER_H

#include <memory>

#include "olaf/search/alphabetasearcher.h"
#include "olaf/search/searchresult.h"

namespace olaf
{

class MoveGenerator;
class MoveOrderer;

class ParallelNegaMaxer : public AlphaBetaSearcher
{
public:
  using AlphaBetaSearcher::AlphaBetaSearcher;

  SearchResult alpha_beta(SearchState* state, SearchContext* context);
};

} // namespace olaf

#endif // PARALLELNEGAMAXER_H
