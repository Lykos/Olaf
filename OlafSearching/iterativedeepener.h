#ifndef ITERATIVEDEEPENER_H
#define ITERATIVEDEEPENER_H

#include "searcher.h"
#include "OlafRules/chessboard.h"
#include "alphabetasearcher.h"
#include "thinkingwriter.h"
#include <memory>
#include <mutex>

class SearchContext;

class IterativeDeepener : public Searcher
{
public:
  IterativeDeepener(std::unique_ptr<AlphaBetaSearcher> searcher,
                    ThinkingWriter* writer,
                    int min_depth);

  SearchResult search(SearchContext* context) override;

private:
  std::unique_ptr<AlphaBetaSearcher> m_searcher;

  ThinkingWriter* const m_writer;

  const int m_min_depth = 1;
};

#endif // ITERATIVEDEEPENER_H
