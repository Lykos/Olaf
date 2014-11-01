#ifndef INCREMENTALSTATE_H
#define INCREMENTALSTATE_H

#include <array>
#include "olaf/search/searchresult.h"

namespace olaf
{

struct IncrementalState
{
  typedef SearchResult::score_t score_t;

  constexpr IncrementalState():
    incremental_score_white_middlegame(0),
    incremental_score_white_endgame(0),
    incremental_score_white(0),
    material_score(0)
  {}

  score_t incremental_score_white_middlegame;

  score_t incremental_score_white_endgame;

  score_t incremental_score_white;

  score_t material_score;
};

constexpr bool operator ==(const IncrementalState& left, const IncrementalState& right)
{
  return left.incremental_score_white_middlegame == right.incremental_score_white_middlegame
      && left.incremental_score_white_endgame == right.incremental_score_white_endgame
      && left.incremental_score_white == right.incremental_score_white;
}

} // namespace olaf

#endif // INCREMENTALSTATE_H
