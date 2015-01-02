#ifndef OPENINGBOOKSEARCHER_H
#define OPENINGBOOKSEARCHER_H

#include <memory>
#include <random>

#include "olaf/search/searcher.h"

namespace olaf
{

class OpeningBook;

class OpeningBookSearcher : public Searcher
{
public:
  OpeningBookSearcher(std::unique_ptr<Searcher> searcher);

  SearchResult search(SearchContext* context) override;

private:
  std::unique_ptr<Searcher> m_searcher;

  std::unique_ptr<OpeningBook> m_opening_book;

  std::default_random_engine m_random;
};

} // namespace olaf

#endif // OPENINGBOOKSEARCHER_H

