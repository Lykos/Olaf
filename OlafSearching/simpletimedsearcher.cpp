#include "simpletimedsearcher.h"
#include "timestopper.h"
#include "compositestopper.h"
#include <vector>

using namespace std;
using namespace chrono;

SimpleTimedSearcher::SimpleTimedSearcher(const std::shared_ptr<IterativeSearcher> &searcher):
  m_searcher (searcher)
{}

static const milliseconds search_milliseconds (1000);

SearchResult SimpleTimedSearcher::search(ChessBoard &board, const std::shared_ptr<Stopper> &forced_stopper, const std::shared_ptr<Stopper>& weak_stopper)
{
  shared_ptr<Stopper> timed_stopper (new TimeStopper(search_milliseconds));
  vector< shared_ptr<Stopper> > stoppers {weak_stopper, timed_stopper};
  shared_ptr<Stopper> composite_stopper (new CompositeStopper(stoppers));
  return m_searcher->search_infinite(board, forced_stopper, composite_stopper);
}
