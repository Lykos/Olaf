#ifndef SEARCHCONTEXT_H
#define SEARCHCONTEXT_H

#include "chessboard.h"
#include "stopper.h"
#include "searchresult.h"

namespace olaf
{

/**
 * @brief The SearchContext struct holds information about the search being performed.
 *        It holds options and may be modified by the searchers.
 */
struct SearchContext
{
  SearchContext();

  /**
   * @brief board is the board which will be used by the search to try out moves.
   */
  ChessBoard board;

  /**
   * @brief The TimeMode enum indicates what kind of time limit is used.
   *        Infinite indicates whether this is an infinite search, only the stoppers
   *        or a depth limit can stop the search. This is set e.g. in analysis
   *        mode and pondering.
   *        Bounded means that there is a time bound (implemented via a weak_stopper).
   */
  enum class TimeMode {
    INFINITE,
    BOUNDED
  };

  TimeMode time_mode;

  /**
   * @brief forced_stopper is a stopper that is used to immediately break off the search.
   *        Note that the returned result will not be valid. I.e. it should be used if the
   *        result is not needed any more, e.g. if the opponent has resigned.
   */
  const Stopper* forced_stopper;

  /**
   * @brief weak_stopper is a stopper that is used to break off the search as soon as any valid
   *        move has been found. The searcher will still return a valid move, but it might not
   *        be a good one. This is used e.g. for limiting the time used by the search.
   */
  const Stopper* weak_stopper;

  /**
   * @brief The DepthMode enum indicates what kind of depth limit is used.
   *        In case of ITERATIVE, iterative deepening is used, i.e. first a small depth is chosen
   *        and then it is increased itreatively until the stoppers stop the search.
   *        In case of FIXED_DEPTH, exactly that depth is searched and the result is returned.
   */
  enum class DepthMode {
    ITERATIVE,
    FIXED_DEPTH
  };

  DepthMode depth_mode;

  /**
   * @brief search_depth the depth for FIXED_DEPTH mode.
   */
  int search_depth;
};

} // namespace olaf

#endif // SEARCHCONTEXT_H
