#include "alphabetasearcher.h"
#include <limits>

using namespace std;

SearchResult AlphaBetaSearcher::search_depth(ChessBoard &board, int depth, int nodes_searched, const std::shared_ptr<Stopper> &stopper)
{
  return search_alpha_beta(board, depth, nodes_searched, numeric_limits<int>::min(), numeric_limits<int>::max(), stopper);
}

SearchResult AlphaBetaSearcher::search_stoppable_alpha_beta(ChessBoard &board, int depth, int nodes_searched, int alpha, int beta, const std::shared_ptr<Stopper> &stopper)
{
  if (stopper->should_stop(nodes_searched)) {
    return SearchResult();
  } else {
    return search_alpha_beta(board, depth, nodes_searched, alpha, beta, stopper);
  }
}
