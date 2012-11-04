#ifndef ITERATIVEDEEPENER_H
#define ITERATIVEDEEPENER_H

#include "iterativesearcher.h"
#include "OlafRules/chessboard.h"
#include "depthsearcher.h"
#include <memory>
#include <mutex>

class IterativeDeepener : public IterativeSearcher
{
public:
  IterativeDeepener(const std::shared_ptr<DepthSearcher>& searcher);

  SearchResult search_infinite(ChessBoard &board, const std::shared_ptr<Stopper> &forced_stopper, const std::shared_ptr<Stopper> &weak_stopper);

  SearchResult search_bounded(ChessBoard &board, int max_depth, const std::shared_ptr<Stopper> &forced_stopper, const std::shared_ptr<Stopper> &weak_stopper);

private:
  SearchResult internal_search(ChessBoard &board, const std::shared_ptr<Stopper> &forced_stopper, const std::shared_ptr<Stopper> &weak_stopper, int max_depth, bool infinite);

  static const unsigned int min_depth = 2;

  std::shared_ptr<DepthSearcher> m_searcher;

};

#endif // ITERATIVEDEEPENER_H
