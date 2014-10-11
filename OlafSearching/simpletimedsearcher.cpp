#include "simpletimedsearcher.h"
#include "timestopper.h"
#include "compositestopper.h"
#include <vector>

using namespace std;
using namespace chrono;

SimpleTimedSearcher::SimpleTimedSearcher(unique_ptr<IterativeSearcher> searcher):
  m_searcher(move(searcher))
{}


SearchResult SimpleTimedSearcher::search_timed(ChessBoard* const board,
                                               const Stopper& forced_stopper,
                                               const Stopper& weak_stopper)
{
  static const milliseconds search_milliseconds(1000);
  TimeStopper time_stopper(search_milliseconds);
  CompositeStopper composite_stopper{&weak_stopper, &time_stopper};
  return m_searcher->search_infinite(board, forced_stopper, composite_stopper);
}

SearchResult SimpleTimedSearcher::search_untimed(ChessBoard* const board,
                                                 const Stopper& forced_stopper)
{
  return m_searcher->search_infinite(board, forced_stopper);
}
