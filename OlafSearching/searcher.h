#ifndef SEARCHER_H
#define SEARCHER_H

#include "searchcontext.h"
#include "searchresult.h"

class Searcher
{
public:
  virtual SearchResult search(SearchContext* context) = 0;
};

#endif // SEARCHER_H