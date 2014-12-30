#include "olaf/search/simpletimedsearcher.h"

#include <memory>
#include <vector>

#include "olaf/search/timestopper.h"
#include "olaf/search/compositestopper.h"
#include "olaf/search/searchcontext.h"

using namespace std;
using namespace chrono;

namespace olaf
{

SimpleTimedSearcher::SimpleTimedSearcher(unique_ptr<Searcher> sub_searcher,
                                         const int default_moves_to_play):
  m_sub_searcher(move(sub_searcher)),
  m_default_moves_to_play(default_moves_to_play)
{}

static const milliseconds c_safety_margin(1000);

SearchResult SimpleTimedSearcher::search(SearchContext* const context)
{
  unique_ptr<TimeStopper> time_stopper;
  unique_ptr<CompositeStopper> composite_stopper;
  switch (context->time_mode) {
    case SearchContext::TimeMode::INFINITE:
      break;
    case SearchContext::TimeMode::FIXED:
      time_stopper.reset(new TimeStopper(context->total_time));
      composite_stopper.reset(new CompositeStopper{context->weak_stopper, time_stopper.get()});
      context->weak_stopper = composite_stopper.get();
      break;
    case SearchContext::TimeMode::ADAPTED:
      const int moves_to_play = context->sudden_death ? m_default_moves_to_play : context->moves_to_play;
      // Try to never use up all our time. We need a safety margin.
      const milliseconds total_time = max(context->total_time - c_safety_margin, milliseconds(0));
      const milliseconds time = (total_time + moves_to_play * context->increment) / (moves_to_play + 1);
      time_stopper.reset(new TimeStopper(time));
      composite_stopper.reset(new CompositeStopper{context->weak_stopper, time_stopper.get()});
      context->weak_stopper = composite_stopper.get();
      break;
  }
  return m_sub_searcher->search(context);
}

} // namespace olaf
