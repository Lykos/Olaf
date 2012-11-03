#ifndef TIMEDSEARCHER_H
#define TIMEDSEARCHER_H

#include "OlafRules/chessboard.h"
#include "stoppablesearcher.h"

class TimedSearcher : public StoppableSearcher
{
public:
  virtual SearchResult search(ChessBoard &board) = 0;

};

#endif // TIMEDSEARCHER_H
