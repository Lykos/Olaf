#ifndef ALPHABETASEARCHER_H
#define ALPHABETASEARCHER_H

#include "depthsearcher.h"
#include "stopper.h"
#include <memory>

class AlphaBetaSearcher : public DepthSearcher
{
public:
  SearchResult search_depth(ChessBoard &board, int depth, int nodes_searched, const std::shared_ptr<Stopper> &stopper);

  SearchResult search_stoppable_alpha_beta(ChessBoard &board, int depth, int nodes_searched, int alpha, int beta, const std::shared_ptr<Stopper> &stopper);

  virtual SearchResult search_alpha_beta(ChessBoard &board, int depth, int nodes_searched, int alpha, int beta, const std::shared_ptr<Stopper> &stopper) = 0;

};

#endif // ALPHABETASEARCHER_H
