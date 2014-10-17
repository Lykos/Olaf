#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include "OlafRules/move.h"
#include <vector>

struct SearchResult
{
  static const SearchResult& invalid();

  SearchResult();

  int nodes;

  int score;

  std::vector<Move> main_variation;

  bool valid() const;
};

#endif // SEARCHRESULT_H
