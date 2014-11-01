#ifndef INCREMENTALSTATE_H
#define INCREMENTALSTATE_H

#include <array>
#include "olaf/search/searchresult.h"

namespace olaf
{

struct IncrementalState
{
  typedef SearchResult::score_t score_t;

  constexpr IncrementalState(): incremental_score_white(0) {}

  score_t incremental_score_white;
};

constexpr bool operator ==(const IncrementalState& left, const IncrementalState& right)
{
  return left.incremental_score_white == right.incremental_score_white;
}

} // namespace olaf

#endif // INCREMENTALSTATE_H
