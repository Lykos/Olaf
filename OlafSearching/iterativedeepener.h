#ifndef ITERATIVEDEEPENER_H
#define ITERATIVEDEEPENER_H

#include "infinitesearcher.h"
#include "OlafRules/chessboard.h"
#include "depthsearcher.h"
#include <boost/shared_ptr.hpp>
#include <mutex>

class IterativeDeepener : public InfiniteSearcher
{
public:
  IterativeDeepener(const boost::shared_ptr<DepthSearcher>& searcher);

  SearchResult search_infinite(ChessBoard &board);

private:
  std::mutex m_mutex;

  static const unsigned int min_depth = 2;

  // TODO volatile is not good enough here
  volatile bool m_move_found = false;

  volatile bool m_time_stop = false;

  boost::shared_ptr<DepthSearcher> m_searcher;

};

#endif // ITERATIVEDEEPENER_H
