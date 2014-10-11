#include "iterativedeepener.h"
#include "compositestopper.h"
#include <chrono>

using namespace std;
using namespace chrono;

IterativeDeepener::IterativeDeepener(const shared_ptr<DepthSearcher>& searcher,
                                     ThinkingWriter* const writer):
  m_searcher (searcher),
  m_writer (writer)
{}


SearchResult IterativeDeepener::internal_search(ChessBoard* const board,
                                                const Stopper& forced_stopper,
                                                const Stopper& weak_stopper,
                                                const int max_depth,
                                                const bool infinite)
{
  steady_clock::time_point start = steady_clock::now();
  int nodes_searched = 0;
  SearchResult result = m_searcher->search_depth(board, min_depth, nodes_searched, forced_stopper);
  milliseconds time = duration_cast<milliseconds>(steady_clock::now() - start);
  m_writer->output(*board, result, time, min_depth);
  nodes_searched += result.nodes();
  CompositeStopper composite_stopper{&forced_stopper, &weak_stopper};
  for (int depth = min_depth + 1; depth <= max_depth || infinite; ++depth) {
    SearchResult next_result = m_searcher->search_depth(board, depth, nodes_searched, composite_stopper);
    if (!next_result.valid()) {
      break;
    }
    nodes_searched += result.nodes();
    result = SearchResult(nodes_searched, next_result.value(), next_result.main_variation());
    milliseconds time = duration_cast<milliseconds>(steady_clock::now() - start);
    m_writer->output(*board, result, time, depth);
  }
  return result;
}

SearchResult IterativeDeepener::search_infinite(ChessBoard* const board,
                                                const Stopper& forced_stopper,
                                                const Stopper& weak_stopper)
{
  return internal_search(board, forced_stopper, weak_stopper, 0, true);
}

SearchResult IterativeDeepener::search_bounded(ChessBoard* const board,
                                               const int max_depth,
                                               const Stopper& forced_stopper,
                                               const Stopper& weak_stopper)
{
  return internal_search(board, forced_stopper, weak_stopper, max_depth, false);
}
