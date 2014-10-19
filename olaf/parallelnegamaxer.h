#ifndef PARALLELNEGAMAXER_H
#define PARALLELNEGAMAXER_H

#include "alphabetasearcher.h"
#include "searchresult.h"
#include "movegenerator.h"
#include "moveorderer.h"
#include <memory>

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
