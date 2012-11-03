#ifndef DEPTHSEARCHER_H
#define DEPTHSEARCHER_H

#include "OlafRules/chessboard.h"
#include "searchresult.h"
#include "stoppablesearcher.h"

class DepthSearcher : public StoppableSearcher {
public:
  virtual SearchResult search_depth(ChessBoard &board, int depth) = 0;

};

#endif // DEPTHSEARCHER_H
