#ifndef ITERATIVEDEEPENER_H
#define ITERATIVEDEEPENER_H

#include "olaf/search/searcher.h"
#include "olaf/rules/chessboard.h"
#include "olaf/search/alphabetasearcher.h"
#include "olaf/search/thinkingwriter.h"
#include <memory>
#include <mutex>

namespace olaf
{

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

} // namespace olaf

#endif // ITERATIVEDEEPENER_H
