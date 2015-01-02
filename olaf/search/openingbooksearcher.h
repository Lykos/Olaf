#ifndef OPENINGBOOKSEARCHER_H
#define OPENINGBOOKSEARCHER_H

#include <memory>

#include "olaf/search/searcher.h"

namespace olaf
{

class OpeningBookSearcher : public Searcher
{
public:
  OpeningBookSearcher(std::unique_ptr<Searcher> searcher);

  SearchResult search(SearchContext* context) override;

private:
  std::unique_ptr<Searcher> m_searcher;
};

} // namespace olaf

#endif // OPENINGBOOKSEARCHER_H

