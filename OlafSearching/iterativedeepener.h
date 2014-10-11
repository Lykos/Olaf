#ifndef ITERATIVEDEEPENER_H
#define ITERATIVEDEEPENER_H

#include "iterativesearcher.h"
#include "OlafRules/chessboard.h"
#include "depthsearcher.h"
#include "thinkingwriter.h"
#include <memory>
#include <mutex>

class IterativeDeepener : public IterativeSearcher
{
public:
  IterativeDeepener(std::unique_ptr<DepthSearcher> searcher, ThinkingWriter* writer);

  SearchResult search_infinite(ChessBoard* board,
                               const Stopper& forced_stopper,
                               const Stopper& weak_stopper) override;

  SearchResult search_bounded(ChessBoard* board,
                              int max_depth,
                              const Stopper& forced_stopper,
                              const Stopper& weak_stopper) override;

private:
  SearchResult internal_search(ChessBoard* board,
                               const Stopper& forced_stopper,
                               const Stopper& weak_stopper,
                               int max_depth,
                               bool infinite);

  static const unsigned int min_depth = 1;

  std::shared_ptr<DepthSearcher> m_searcher;

  ThinkingWriter* const m_writer;

};

#endif // ITERATIVEDEEPENER_H
