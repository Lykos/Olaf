#include "olaf/search/openingbooksearcher.h"

using namespace std;

namespace olaf
{

OpeningBookSearcher::OpeningBookSearcher(unique_ptr<Searcher> searcher): m_searcher(std::move(searcher))
{}

SearchResult OpeningBookSearcher::search(SearchContext* context)
{
  return m_searcher->search(context);
}

} // namespace olaf

