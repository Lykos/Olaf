#include "iterativedeepener.h"
#include "compositestopper.h"
#include <chrono>

using namespace std;
using namespace chrono;

IterativeDeepener::IterativeDeepener(const shared_ptr<DepthSearcher>& searcher, const shared_ptr<ThinkingWriter> &writer):
  m_searcher (searcher),
  m_writer (writer)
{}


SearchResult IterativeDeepener::internal_search(ChessBoard &board, const shared_ptr<Stopper> &forced_stopper, const shared_ptr<Stopper> &weak_stopper, int max_depth, bool infinite)
{
  steady_clock::time_point start = steady_clock::now();
  int nodes_searched = 0;
  SearchResult result = m_searcher->search_depth(board, min_depth, nodes_searched, forced_stopper);
  milliseconds time = duration_cast<milliseconds>(steady_clock::now() - start);
  m_writer->output(board, result, time, min_depth);
  nodes_searched += result.nodes();
  vector< shared_ptr<Stopper> > stoppers {forced_stopper, weak_stopper};
  shared_ptr<Stopper> combined_stopper (new CompositeStopper(stoppers));
  for (int depth = min_depth + 1; depth <= max_depth || infinite; ++depth) {
    SearchResult next_result = m_searcher->search_depth(board, depth, nodes_searched, combined_stopper);
    nodes_searched += result.nodes();
    if (combined_stopper->should_stop(nodes_searched)) {
      break;
    }
    result = SearchResult(nodes_searched, result.value(), result.main_variation());
    milliseconds time = duration_cast<milliseconds>(steady_clock::now() - start);
    m_writer->output(board, result, time, depth);
  }
  return result;
}

SearchResult IterativeDeepener::search_infinite(ChessBoard &board, const shared_ptr<Stopper> &forced_stopper, const shared_ptr<Stopper> &weak_stopper)
{
  return internal_search(board, forced_stopper, weak_stopper, 0, true);
}

SearchResult IterativeDeepener::search_bounded(ChessBoard &board, int max_depth, const shared_ptr<Stopper> &forced_stopper, const shared_ptr<Stopper> &weak_stopper)
{
  return internal_search(board, forced_stopper, weak_stopper, max_depth, false);
}
