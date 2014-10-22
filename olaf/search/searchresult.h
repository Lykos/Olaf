#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include "olaf/rules/move.h"
#include <limits>
#include <vector>

namespace olaf
{

struct SearchResult
{
  static const SearchResult& invalid();

  bool valid = true;

  int nodes = 0;

  // We use -max because numeric_limits is asymmetric and min
  // would not work.
  int score = -std::numeric_limits<int>::max();

  std::vector<Move> main_variation;
};

} // namespace olaf

#endif // SEARCHRESULT_H
