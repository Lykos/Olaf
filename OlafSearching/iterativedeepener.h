#ifndef ITERATIVEDEEPENER_H
#define ITERATIVEDEEPENER_H

#include "infinitesearcher.h"
#include "OlafRules/chessboard.h"
#include <boost/shared_ptr.hpp>
#include "depthsearcher.h"

class IterativeDeepener : public InfiniteSearcher
{
public:
  IterativeDeepener(const boost::shared_ptr<DepthSearcher>& searcher);

  SearchResult search_infinite(ChessBoard &board);

private:
  static const unsigned int min_depth = 2;

  volatile unsigned int m_current_depth;

  volatile bool m_time_stop;

  boost::shared_ptr<DepthSearcher> m_searcher;

};

#endif // ITERATIVEDEEPENER_H
