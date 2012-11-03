#ifndef INFINITESEARCHER_H
#define INFINITESEARCHER_H

#include "stoppablesearcher.h"
#include "searchresult.h"
#include "OlafRules/chessboard.h"

class InfiniteSearcher : public StoppableSearcher
{
public:
  SearchResult search_infinite(ChessBoard &board);

  /**
   * @brief request_time_stop requests stopping of the search, but allows to think until at least some move is found.
   */
  void request_time_stop();
};

#endif // INFINITESEARCHER_H
