#include "olaf/search/simpletimedsearcher.h"
#include "olaf/search/timestopper.h"
#include "olaf/search/compositestopper.h"
#include <memory>
#include <vector>

using namespace std;
using namespace chrono;

namespace olaf
{

SimpleTimedSearcher::SimpleTimedSearcher(unique_ptr<Searcher> sub_searcher,
                                         const milliseconds& search_millis):
  m_sub_searcher(move(sub_searcher)),
  m_search_millis(search_millis)
{}


SearchResult SimpleTimedSearcher::search(SearchContext* const context)
{
  unique_ptr<TimeStopper> time_stopper;
  unique_ptr<CompositeStopper> composite_stopper;
  switch (context->time_mode) {
    case SearchContext::TimeMode::BOUNDED:
      time_stopper.reset(new TimeStopper(m_search_millis));
      composite_stopper.reset(new CompositeStopper{context->weak_stopper, time_stopper.get()});
      context->weak_stopper = composite_stopper.get();
      break;
    case SearchContext::TimeMode::INFINITE:
      break;
  }
  return m_sub_searcher->search(context);

} // namespace olaf
}
