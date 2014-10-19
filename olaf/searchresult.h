#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include "move.h"
#include <vector>

namespace olaf
{

struct SearchResult
{
  static const SearchResult& invalid();

  SearchResult();

  int nodes;

  int score;

  std::vector<Move> main_variation;

  bool valid() const;
};

} // namespace olaf

#endif // SEARCHRESULT_H
