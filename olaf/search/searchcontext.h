#ifndef SEARCHCONTEXT_H
#define SEARCHCONTEXT_H

#include "olaf/rules/chessboard.h"
#include "olaf/transposition_table/transpositiontable.h"
#include "olaf/transposition_table/pawntable.h"
#include "olaf/search/searcher.h"
#include "olaf/search/searchstatistics.h"
#include "olaf/tablebases/tablebaseprober.h"
#include "olaf/rules/move.h"

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
  typedef Searcher::score_t score_t;

  SearchContext();

  /**
   * @brief board is the board which will be used by the search/search to try out moves.
   */
  ChessBoard board;

  /**
   * @brief The TimeMode enum indicates what kind of time limit is used.
   *        INFINITE indicates whether this is an infinite search/search, only the stoppers
   *        or a depth limit can stop the search/search. This is set e.g. in analysis
   *        mode and pondering.
   *        FIXED means that the field time is used as a time bound.
   *        ADAPTED means that the engine decides how much time to use based on moves_to_play,
   *                total_time and increment.
   */
  enum class TimeMode {
    INFINITE,
    FIXED,
    ADAPTED
  };

  TimeMode time_mode;

  /**
   * @brief total_time is the total time left for us.
   */
  std::chrono::milliseconds total_time;

  std::chrono::milliseconds increment;

  /**
   * @brief sudden_death if this is true, then the total_time has to suffice for the whole game. Otherwise,
   *        moves_to_play says how may moves have to be played before new time is added.
   */
  bool sudden_death;

  int moves_to_play;

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
   *        MAX_DEPTH is similar to ITERATIVE, but there is a maximum depth.
   */
  enum class DepthMode {
    ITERATIVE,
    FIXED_DEPTH,
    MAX_DEPTH
  };

  DepthMode depth_mode;

  /**
   * @brief search_depth the depth for FIXED_DEPTH mode.
   *        In ITERATIVE mode, this is set and iteratively increased by the searcher.
   */
  depth_t search_depth;

  /**
   * @brief max_depth the depth for MAX_DEPTH mode.
   */
  depth_t max_depth;

  TablebaseProber* prober;

  bool probe(score_t* score);

  TranspositionTable* transposition_table;

  /**
   * @brief get returns the entry for the current position from the transposition table.
   *        If there is no transposition table or if the entry doesn't exist, returns nullptr.
   * @param current_depth The current remaining depth of the search (can be negative in quiescent search)
   *                      This is stored in SearchState and will be used to calculate the distance to root.
   */
  bool get(depth_t current_depth, SearchResult* result) const;

  /**
   * @brief put puts the entry in the transposition table for the current postion, if it exists.
   * @param current_depth The current remaining depth of the search (can be negative in quiescent search)
   *                      This is stored in SearchState and will be used to calculate the distance to root.
   */
  void put(depth_t current_depth, const SearchResult& entry);
  void put(depth_t current_depth, SearchResult&& entry);

  std::vector<Move> reconstruct_pv();

  /**
   * @brief c_no_killers if this is changed, the replacement logic has to be changed as well.
   */
  static const int c_no_killers = 2;

  typedef std::array<Move, c_no_killers> Killers;

  std::vector<Killers> killers;

  /**
   * @brief nodes is the number of searched nodes.
   */
  int nodes = 0;

  PawnTable* pawn_table;

  /**
   * @brief get returns the entry for the current position from the transposition table.
   *        If there is no pawn table or if the entry doesn't exist, returns nullptr.
   */
  const PawnTableEntry* get_pawns() const;

  /**
   * @brief put puts the entry in the pawn table for the current postion, if it exists.
   */
  void put_pawns(const PawnTableEntry& entry);
  void put_pawns(PawnTableEntry&& entry);

  /**
   * @brief time_start represents the time at which the search started;
   */
  std::chrono::steady_clock::time_point time_start;

  /**
   * @brief elapsed returns the time elapsed since the start of the search.
   */
  std::chrono::milliseconds elapsed() const;

  /**
   * @brief allocated_time is only valid if the time mode is ADAPTED. Then it stores the allocated time for this move.
   */
  std::chrono::milliseconds allocated_time;

  SearchStatistics statistics;
};

} // namespace olaf

#endif // SEARCHCONTEXT_H
