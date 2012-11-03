#include "alphabetasearcher.h"
#include <limits>

using namespace std;

SearchResult AlphaBetaSearcher::search_depth(ChessBoard &board, int depth)
{
  return search_alpha_beta(board, depth, numeric_limits<int>::min(), numeric_limits<int>::max());
}
