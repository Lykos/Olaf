#ifndef SEARCHER_H
#define SEARCHER_H

#include "searchcontext.h"
#include "searchresult.h"

namespace olaf
{

class Searcher
{
public:
  virtual SearchResult search(SearchContext* context) = 0;

  virtual ~Searcher();
};

} // namespace olaf

#endif // SEARCHER_H
