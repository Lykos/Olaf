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

SearchResult SimpleTimedSearcher::search(ChessBoard &board, std::shared_ptr<Stopper> &stopper)
{
  shared_ptr<Stopper> timed_stopper (new TimeStopper(search_milliseconds));
  return m_searcher->search_infinite(board, stopper, timed_stopper);
}
