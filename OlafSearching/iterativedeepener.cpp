#include "iterativedeepener.h"

IterativeDeepener::IterativeDeepener(const boost::shared_ptr<DepthSearcher>& searcher):
  m_searcher (searcher)
{}


SearchResult IterativeDeepener::search_infinite(ChessBoard &board)
{
  m_current_depth = 0;
  SearchResult result = m_searcher->search_depth(board, min_depth);
  m_current_depth = min_depth;
  if (m_time_stop) {
    return result;
  }
  while (!StoppableSearcher::stop_requested()) {
    m_searcher->search_depth(board, ++m_current_depth);
  }
}

void IterativeDeepener::request_time_stop()
{
  m_time_stop = true;
  if (m_current_depth >= min_depth) {
    StoppableSearcher::request_stop();
  }
}
