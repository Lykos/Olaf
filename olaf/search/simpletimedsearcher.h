#ifndef SIMPLETIMEDSEARCHER_H
#define SIMPLETIMEDSEARCHER_H

#include <memory>
#include <chrono>

#include "olaf/search/searcher.h"
#include "olaf/search/searchresult.h"

namespace olaf
{

class SearchContext;

/**
 * @brief The SimpleTimedSearcher class adds time bounds to the SearchContext unless
 *        it is an infinite search.
 */
class SimpleTimedSearcher : public Searcher
{
public:
  explicit SimpleTimedSearcher(std::unique_ptr<Searcher> sub_searcher,
                               const std::chrono::milliseconds& search_millis);

  SearchResult search(SearchContext* context) override;

private:
  std::unique_ptr<Searcher> m_sub_searcher;

  const std::chrono::milliseconds m_search_millis;

};

} // namespace olaf

#endif // SIMPLETIMEDSEARCHER_H
