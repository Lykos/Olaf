#ifndef ALPHABETASEARCHER_H
#define ALPHABETASEARCHER_H

#include "depthsearcher.h"

class AlphaBetaSearcher : public DepthSearcher
{
public:
  SearchResult search_depth(ChessBoard &board, int depth);

  virtual SearchResult search_alpha_beta(ChessBoard &board, int depth, int alpha, int beta) = 0;

};

#endif // ALPHABETASEARCHER_H
