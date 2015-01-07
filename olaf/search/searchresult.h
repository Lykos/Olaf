#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include <limits>
#include <vector>
#ifdef TRACE
#include <ostream>
#endif

#include "olaf/rules/move.h"
#include "olaf/search/nodetype.h"

namespace olaf
{

struct SearchResult
{
  typedef std::int16_t depth_t;

  typedef std::int32_t score_t;

  static const SearchResult& invalid();

  bool has_best_move = false;

  Move best_move;

  // We use -max because numeric_limits is asymmetric and min
  // would not work.
  score_t score;

  /**
   * @brief depth is the search depth of this search result. Quiescent search is not counted.
   *        Generally this is to be used for deciding how useful a result is.
   */
  depth_t search_depth;

  /**
   * @brief real_depth is the actual depth (including quiescent search) from this result to the
   *        evaluation. Generally, this should only be used in very special cases. You cannot use
   *        it for comparison because even at the same real_depth, the number of quiescent plies
   *        could differ a lot making the result with more quiescent depth less valuable.
   *        It is however used for some interior node detection.
   */
  depth_t real_depth;

  bool valid = false;

  bool terminal;

  NodeType node_type;

  bool node_type_valid;
};

#ifdef TRACE
std::ostream& operator <<(std::ostream& out, const SearchResult& result);
#endif

} // namespace olaf

#endif // SEARCHRESULT_H
