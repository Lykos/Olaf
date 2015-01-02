#include "olaf/search/openingbooksearcher.h"

#include <cstdint>

#include "olaf/opening_book/openingbook.h"
#include "olaf/search/searchcontext.h"

using namespace std;

namespace olaf
{

OpeningBookSearcher::OpeningBookSearcher(unique_ptr<Searcher> searcher):
  m_searcher(std::move(searcher)),
  m_opening_book(OpeningBook::load())
{}

SearchResult OpeningBookSearcher::search(SearchContext* context)
{
  vector<OpeningBookEntry> entries;
  if (m_opening_book->get(context->board, &entries)) {
    int32_t total_weight = 0;
    for (const OpeningBookEntry& entry : entries) {
      total_weight += entry.weight;
    }
    if (total_weight > 0) {
      std::uniform_int_distribution<int32_t> distribution(0, total_weight);
      int32_t number = distribution(m_random);
      for (const OpeningBookEntry& entry : entries) {
        if (number < entry.weight) {
          SearchResult result;
          result.main_variation.push_back(entry.move);
          result.score = 0;
          return result;
        }
        number -= entry.weight;
      }
    }
  }
  return m_searcher->search(context);
}

} // namespace olaf

