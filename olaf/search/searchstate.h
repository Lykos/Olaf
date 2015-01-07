#ifndef SEARCHSTATE_H
#define SEARCHSTATE_H

#ifdef TRACE
#include <ostream>
#include <string>
#endif

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

#ifdef TRACE
std::ostream& operator <<(std::ostream& out, const SearchState& state);

/**
 * @brief Returns the indentation for this search branch for debug output.
 */
std::string indentation(const SearchState& state);
#endif

}  // namespace olaf

#endif // SEARCHSTATE_H
