#ifndef SIMPLETIMEDSEARCHER_H
#define SIMPLETIMEDSEARCHER_H

#include "searcher.h"
#include "OlafRules/chessboard.h"
#include "stopper.h"
#include "searchresult.h"
#include "timestopper.h"
#include <memory>
#include <chrono>

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

#endif // SIMPLETIMEDSEARCHER_H
