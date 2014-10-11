#ifndef DEPTHSEARCHER_H
#define DEPTHSEARCHER_H

#include "OlafRules/chessboard.h"
#include "searchresult.h"
#include "stopper.h"
#include <memory>

class DepthSearcher {
public:
  virtual SearchResult search_depth(ChessBoard* board,
                                    int depth,
                                    int nodes_searched,
                                    const Stopper& stopper) = 0;

  virtual ~DepthSearcher() {}

};

#endif // DEPTHSEARCHER_H
