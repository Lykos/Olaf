#ifndef SEARCHSTATE_H
#define SEARCHSTATE_H

#include "olaf/search/searchresult.h"

namespace olaf
{

/**
 * @brief The SearchState struct represents the current state of the search.
 *        While the SearchContext is used for global things that have to be
 *        carried around, the SearchState contains parameters that are different
 *        for each recursive call.
 */
struct SearchState {
  typedef SearchResult::score_t score_t;
  typedef SearchResult::depth_t depth_t;
  score_t alpha;
  score_t beta;
  depth_t depth;
};

}  // namespace olaf

#endif // SEARCHSTATE_H
