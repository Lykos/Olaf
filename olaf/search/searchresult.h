#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include <limits>
#include <vector>

#include "olaf/rules/move.h"

namespace olaf
{

struct SearchResult
{
  typedef std::int16_t depth_t;

  typedef std::int32_t score_t;

  static const SearchResult& invalid();

  bool valid = true;

  int nodes = 0;

  // We use -max because numeric_limits is asymmetric and min
  // would not work.
  score_t score = -std::numeric_limits<score_t>::max();

  depth_t depth = 0;

  std::vector<Move> main_variation;
};

} // namespace olaf

#endif // SEARCHRESULT_H
