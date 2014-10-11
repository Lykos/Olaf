#ifndef ALPHABETASEARCHER_H
#define ALPHABETASEARCHER_H

#include "depthsearcher.h"
#include "stopper.h"
#include <memory>

/**
 * @brief The AlphaBetaSearcher class is an abstract searcher which provides
 *        the method search_stoppable_alpha_beta which can be called by subclasses.
 *        It stops, if required, otherwise, it calls search_alpha_beta which should
 *        be implemented by its subclasses.
 *        Note that this class does NOT implement any kind of alpha beta algorithm,
 *        it just implements the possibility of stopping and supports forwarding of
 *        alpha and beta.
 */
class AlphaBetaSearcher : public DepthSearcher
{
public:
  SearchResult search_depth(ChessBoard* board,
                            int depth,
                            int nodes_searched,
                            const Stopper& stopper) final;

  SearchResult search_stoppable_alpha_beta(ChessBoard* board,
                                           int depth,
                                           int nodes_searched,
                                           int alpha,
                                           int beta,
                                           const Stopper& stopper);

  virtual SearchResult search_alpha_beta(ChessBoard* board,
                                         int depth,
                                         int nodes_searched,
                                         int alpha,
                                         int beta,
                                         const Stopper& stopper) = 0;

};

#endif // ALPHABETASEARCHER_H
