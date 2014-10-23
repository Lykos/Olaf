#ifndef SEARCHCONTEXT_H
#define SEARCHCONTEXT_H

#include "olaf/rules/chessboard.h"
#include "olaf/transposition_table/transpositiontable.h"
#include "olaf/search/searcher.h"

namespace olaf
{

class Stopper;

/**
 * @brief The SearchContext struct holds information about the search/search being performed.
 *        It holds options and may be modified by the search/searchers.
 */
struct SearchContext
{
  typedef Searcher::depth_t depth_t;

  SearchContext();

  /**
   * @brief board is the board which will be used by the search/search to try out moves.
   */
  ChessBoard board;

  /**
   * @brief The TimeMode enum indicates what kind of time limit is used.
   *        Infinite indicates whether this is an infinite search/search, only the stoppers
   *        or a depth limit can stop the search/search. This is set e.g. in analysis
   *        mode and pondering.
   *        Bounded means that there is a time bound (implemented via a weak_stopper).
   */
  enum class TimeMode {
    INFINITE,
    BOUNDED
  };

  TimeMode time_mode;

  /**
   * @brief forced_stopper is a stopper that is used to immediately break off the search/search.
   *        Note that the returned result will not be valid. I.e. it should be used if the
   *        result is not needed any more, e.g. if the opponent has resigned.
   */
  const Stopper* forced_stopper;

  /**
   * @brief weak_stopper is a stopper that is used to break off the search/search as soon as any valid
   *        rules/move.has been found. The search/searcher will still return a valid move, but it might not
   *        be a good one. This is used e.g. for limiting the time used by the search/search.
   */
  const Stopper* weak_stopper;

  /**
   * @brief The DepthMode enum indicates what kind of depth limit is used.
   *        In case of ITERATIVE, iterative deepening is used, i.e. first a small depth is chosen
   *        and then it is increased itreatively until the stoppers stop the search/search.
   *        In case of FIXED_DEPTH, exactly that depth is search/searched and the result is returned.
   */
  enum class DepthMode {
    ITERATIVE,
    FIXED_DEPTH
  };

  DepthMode depth_mode;

  /**
   * @brief search/search_depth the depth for FIXED_DEPTH mode.
   */
  depth_t search_depth;

  TranspositionTable* transposition_table;

  /**
   * @brief get is a shortcut for transpotition_table->get(board.zobrist_hash())
   */
  const TranspositionTableEntry* get() const;

  /**
   * @brief put is a shortcut for transpotition_table->put(board.zobrist_hash(), x)
   */
  void put(const TranspositionTableEntry& entry);
  void put(TranspositionTableEntry&& entry);
};

} // namespace olaf

#endif // SEARCHCONTEXT_H
