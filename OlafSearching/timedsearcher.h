#ifndef TIMEDSEARCHER_H
#define TIMEDSEARCHER_H

#include "OlafRules/chessboard.h"
#include "stopper.h"
#include "searchresult.h"
#include <memory>

class TimedSearcher
{
public:
  virtual SearchResult search(ChessBoard &board, std::shared_ptr<Stopper>& stopper) = 0;

};

#endif // TIMEDSEARCHER_H
