#ifndef NEGAMAXER_H
#define NEGAMAXER_H

#include "alphabetasearcher.h"
#include "searchresult.h"
#include "movegenerator.h"
#include "moveorderer.h"
#include <memory>

/**
 * @brief The NegaMaxer class is a class which implements the Negamax algorithm sequentially.
 *        It calls its sub searcher for the leaves.
 */
class NegaMaxer : public AlphaBetaSearcher
{
public:
  using AlphaBetaSearcher::AlphaBetaSearcher;

  SearchResult alpha_beta(SearchState* state,
                          SearchContext* context) final;
};

#endif // NEGAMAXER_H
