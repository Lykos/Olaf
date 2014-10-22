#ifndef SEARCHER_H
#define SEARCHER_H

#include <cstdint>

#include "olaf/search/searchresult.h"

namespace olaf
{

class SearchContext;

class Searcher
{
public:
  typedef std::int16_t depth_t;

  virtual SearchResult search(SearchContext* context) = 0;

  virtual ~Searcher();
};

} // namespace olaf

#endif // SEARCHER_H
