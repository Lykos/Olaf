#ifndef INFINITESEARCHER_H
#define INFINITESEARCHER_H

#include "stopper.h"
#include "searchresult.h"
#include "OlafRules/chessboard.h"
#include "nostopper.h"
#include <memory>

/**
 * @brief The IterativeSearcher class can do incremental searches and hence does not need a search argument
 * for the depth. It can, however, take an argument for an upper bound.
 */
class IterativeSearcher
{
public:
  /**
   * @brief search_infinite
   * @param board
   * @param forced_stopper A stopper that also applies in the first round, before any move has been found.
   * @param weak_stopper A stopper that only applies after a move has been found.
   * @return
   */
  virtual SearchResult search_infinite(ChessBoard* board,
                                       const Stopper& forced_stopper,
                                       const Stopper& weak_stopper = NoStopper()) = 0;

  /**
   * @brief search_bounded
   * @param board
   * @param max_depth The maximum depth.
   * @param forced_stopper A stopper that also applies in the first round, before any move has been found.
   * @param weak_stopper A stopper that only applies after a move has been found.
   * @return
   */
  virtual SearchResult search_bounded(ChessBoard* board,
                                      int max_depth,
                                      const Stopper& forced_stopper,
                                      const Stopper& weak_stopper) = 0;

  virtual ~IterativeSearcher() = 0;

};

#endif // INFINITESEARCHER_H
