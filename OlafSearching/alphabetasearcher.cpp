#include "alphabetasearcher.h"
#include <limits>

using namespace std;

SearchResult AlphaBetaSearcher::search_depth(ChessBoard* const board,
                                             const int depth,
                                             const int nodes_searched,
                                             const Stopper& stopper)
{
  return search_alpha_beta(board,
                           depth,
                           nodes_searched,
                           numeric_limits<int>::min(),
                           numeric_limits<int>::max(),
                           stopper);
}

SearchResult AlphaBetaSearcher::search_stoppable_alpha_beta(ChessBoard* const board,
                                                            const int depth,
                                                            const int nodes_searched,
                                                            const int alpha,
                                                            const int beta,
                                                            const Stopper& stopper)
{
  if (stopper.should_stop(nodes_searched)) {
    return SearchResult();
  } else {
    return search_alpha_beta(board, depth, nodes_searched, alpha, beta, stopper);
  }
}
