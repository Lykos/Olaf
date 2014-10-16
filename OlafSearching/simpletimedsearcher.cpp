#include "simpletimedsearcher.h"
#include "timestopper.h"
#include "compositestopper.h"
#include <vector>

using namespace std;
using namespace chrono;

SimpleTimedSearcher::SimpleTimedSearcher(unique_ptr<IterativeSearcher> searcher,
                                         const milliseconds& search_millis):
  m_searcher(move(searcher)),
  m_search_millis(search_millis)
{}


SearchResult SimpleTimedSearcher::search_timed(ChessBoard* const board,
                                               const Stopper& forced_stopper,
                                               const Stopper& weak_stopper)
{
  TimeStopper time_stopper(m_search_millis);
  CompositeStopper composite_stopper{&weak_stopper, &time_stopper};
  return m_searcher->search_infinite(board, forced_stopper, composite_stopper);
}

SearchResult SimpleTimedSearcher::search_untimed(ChessBoard* const board,
                                                 const Stopper& forced_stopper)
{
  return m_searcher->search_infinite(board, forced_stopper);
}
