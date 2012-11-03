#include "iterativedeepener.h"

using namespace std;

IterativeDeepener::IterativeDeepener(const boost::shared_ptr<DepthSearcher>& searcher):
  m_searcher (searcher)
{}


SearchResult IterativeDeepener::search_infinite(ChessBoard &board)
{
  unique_lock lock (m_mutex);
  SearchResult result = m_searcher->search_depth(board, min_depth);
  m_move_found = true;
  if (m_time_stop) {
    return result;
  }
  while (!StoppableSearcher::stop_requested()) {
    m_searcher->search_depth(board, ++m_current_depth);
  }
  m_move_found = false;
  StoppableSearcher::stopped();
}

void IterativeDeepener::request_time_stop()
{
  m_time_stop = true;
  if (m_move_found) {
    StoppableSearcher::request_stop();
  }
}
