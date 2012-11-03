#ifndef INFINITESEARCHER_H
#define INFINITESEARCHER_H

#include "stoppablesearcher.h"
#include "searchresult.h"
#include "OlafRules/chessboard.h"

/**
 * @brief The InfiniteSearcher class can do incremental searches and hence does not need a search argument
 * for the depth. It can, however, take an argument for an upper bound.
 */
class InfiniteSearcher : public StoppableSearcher
{
public:
  SearchResult search_infinite(ChessBoard &board);

  SearchResult search_bounded(ChessBoard &board, int max_depth);

  /**
   * @brief request_time_stop requests stopping of the search, but allows to think until at least some move is found.
   */
  void request_time_stop();
};

#endif // INFINITESEARCHER_H
