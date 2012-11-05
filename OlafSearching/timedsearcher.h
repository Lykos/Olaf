#ifndef TIMEDSEARCHER_H
#define TIMEDSEARCHER_H

#include "OlafRules/chessboard.h"
#include "stopper.h"
#include "searchresult.h"
#include <memory>

class TimedSearcher
{
public:
  /**
   * @brief search
   * @param board
   * @param forced_stopper A stopper that also applies in the first round, before any move has been found.
   * @param weak_stopper A stopper that only applies after a move has been found.
   * @return
   */
  virtual SearchResult search(ChessBoard &board, const std::shared_ptr<Stopper>& forced_stopper, const std::shared_ptr<Stopper>& weak_stopper) = 0;

};

#endif // TIMEDSEARCHER_H
