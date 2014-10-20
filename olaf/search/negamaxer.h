#ifndef NEGAMAXER_H
#define NEGAMAXER_H

#include "olaf/search/alphabetasearcher.h"
#include "olaf/search/searchresult.h"
#include "olaf/search/movegenerator.h"
#include "olaf/search/moveorderer.h"
#include <memory>

namespace olaf
{

/**
 * @brief The NegaMaxer class is a class which implements the Negamax algorithm sequentially.
 *        It calls its sub search/searcher for the leaves.
 */
class NegaMaxer : public AlphaBetaSearcher
{
public:
  using AlphaBetaSearcher::AlphaBetaSearcher;

  SearchResult alpha_beta(SearchState* state,
                          SearchContext* context) final;
};

} // namespace olaf

#endif // NEGAMAXER_H
